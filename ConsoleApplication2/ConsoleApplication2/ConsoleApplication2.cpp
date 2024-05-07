﻿#include <iostream>
#include <string>
#include <algorithm>
#include "mpi.h"
#include "opencv2/opencv.hpp"

using namespace cv;

Mat resizeImage(const Mat& inputImage, int newWidth, int newHeight) {
    Mat resizedImage(newHeight, newWidth, CV_8UC3);

    float scaleX = (float)inputImage.cols / newWidth;
    float scaleY = (float)inputImage.rows / newHeight;

    for (int y = 0; y < newHeight; y++) {
        for (int x = 0; x < newWidth; x++) {
            int originX = scaleX * x;
            int originY = scaleY * y;

            Vec3b& pixel = resizedImage.at<Vec3b>(y, x);
            pixel = inputImage.at<Vec3b>(originY, originX);
        }
    }

    return resizedImage;
}

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    int size;
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // the input image
    Mat image;
    // the total size of the image matrix (rows * columns * channels):
    size_t imageTotalSize;
    // partial size (how many bytes will be sent to each process):
    size_t imagePartialSize;
    // how many channels are there in the image?
    int channels;
    // partial buffer, to contain the image.
   // 'uchar' means 'unsigned char', i.e. an 8-bit value, because each pixel in an image is a byte (0..255)
    uchar* partialBuffer;
    // also create the output image, where we will save the results:
    Mat outImage;

    if (rank == 0) {
        image = imread("img.jpg", IMREAD_UNCHANGED);
        if (image.empty()) {
            std::cerr << "Image is empty, terminating!" << std::endl;
            MPI_Finalize();
            return -1;
        }
        // get the number of channels in the image
        channels = image.channels();
        // get the total size of the image matrix (rows * columns * channels)
        imageTotalSize = image.step[0] * image.rows;

        // check if we can evenly divide the image bytes by the number of processes
      // the image.total() method returns the number of elements, i.e. (rows * cols)
        if (image.total() % size) {
            std::cerr << "Cannot evenly divide the image between the processes. Choose a different number of processes!" << std::endl;
            MPI_Finalize();
            return -2;
        }
        // get partial size (how many bytes are sent to each process):
        imagePartialSize = imageTotalSize / size;
    }
    // send the "partial size" from #0 to other processes:
    MPI_Bcast(&imagePartialSize, 1, MPI_UNSIGNED_LONG_LONG, 0, MPI_COMM_WORLD);
    // send the number of channels in the image from #0 to other processes:
    MPI_Bcast(&channels, 1, MPI_INT, 0, MPI_COMM_WORLD);
    // synchronize the processes here, to make sure that the sizes are initialized:
    MPI_Barrier(MPI_COMM_WORLD);

    // allocate the partial buffer:
    partialBuffer = new uchar[imagePartialSize];
    // synchronize the processe here, to make sure each process has allocated the buffer:
    MPI_Barrier(MPI_COMM_WORLD);

    // scatter the image between the processes:
    MPI_Scatter(image.data, imagePartialSize, MPI_UNSIGNED_CHAR, partialBuffer, imagePartialSize, MPI_UNSIGNED_CHAR, 0, MPI_COMM_WORLD);
    // synchronize the image processing:
    MPI_Barrier(MPI_COMM_WORLD);

    double startTime = MPI_Wtime(); // Measure start time

    // Perform grayscale conversion on the partial image
    for (size_t i = 0; i < imagePartialSize; i += channels) {
        uchar* B = &partialBuffer[i];
        uchar* G = &partialBuffer[i + 1];
        uchar* R = &partialBuffer[i + 2];
        uchar grayscale = (*B + *G + *R) / 3;
        *B = grayscale;
        *G = grayscale;
        *R = grayscale;
    }

    MPI_Barrier(MPI_COMM_WORLD);

    double endTime = MPI_Wtime(); // Measure end time

    double executionTime = endTime - startTime; // Calculate execution time

    std::cout << "Process " << rank << " executed in " << executionTime << " seconds." << std::endl;

    if (rank == 0) {
        outImage = Mat(image.size(), image.type());
    }
    // and now we finally send the partial buffers back to the ROOT, gathering the complete image:
    MPI_Gather(partialBuffer, imagePartialSize, MPI_UNSIGNED_CHAR, outImage.data, imagePartialSize, MPI_UNSIGNED_CHAR, 0, MPI_COMM_WORLD);

    // Save and display image, onle in the ROOT process
    if (rank == 0) {
        int newWidth = 500;
        int newHeight = 200;
        Mat resizedImage = resizeImage(outImage, newWidth, newHeight);
        std::string inputImagePath = "img.jpg";
        size_t lastSlashIndex = inputImagePath.find_last_of("/");
        std::string folderPath = inputImagePath.substr(0, lastSlashIndex + 1);
        std::string fileName = inputImagePath.substr(lastSlashIndex + 1);
        std::string outputImagePath = folderPath + "new_" + fileName;
        imwrite(outputImagePath, resizedImage);
    }

    delete[] partialBuffer;
    MPI_Finalize();

    return 0;
}