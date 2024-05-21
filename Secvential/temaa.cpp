#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

// Funcție pentru conversia la alb-negru
Mat convertToGrayscale(const Mat& inputImage) {
    Mat grayscaleImage = Mat::zeros(inputImage.size(), CV_8UC1); // Imagine alb-negru, 8-bit per pixel
    for (int y = 0; y < inputImage.rows; y++) {
        for (int x = 0; x < inputImage.cols; x++) {
            Vec3b pixel = inputImage.at<Vec3b>(y, x);
            uchar grayscale = (pixel[0] + pixel[1] + pixel[2]) / 3;
            grayscaleImage.at<uchar>(y, x) = grayscale;
        }
    }
    return grayscaleImage;
}

// Funcție pentru redimensionarea imaginii pixel cu pixel
Mat resizeImage(const Mat& inputImage, int newWidth, int newHeight) {
    Mat resizedImage(newHeight, newWidth, CV_8UC3); // Imagine redimensionată

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

int main() {
    // Încarcă imaginea
    Mat image = imread("img.jpg");

    // Verifică dacă imaginea a fost încărcată corect
    if (image.empty()) {
        cout << "Nu s-a putut încărca imaginea!\n";
        return -1;
    }

    // Redimensionează imaginea la dimensiunile dorite
    int newWidth = 300; // Lățimea nouă
    int newHeight = 200; // Înălțimea nouă
    Mat resizedImage = resizeImage(image, newWidth, newHeight);

    // Convertire în alb-negru (grayscale)
    Mat grayscaleImage = convertToGrayscale(resizedImage);

    // Salvează imaginea rezultată
    imwrite("output.jpg", grayscaleImage);

    cout << "Imaginea a fost redimensionată și convertită în alb-negru cu succes!\n";

    return 0;
}
