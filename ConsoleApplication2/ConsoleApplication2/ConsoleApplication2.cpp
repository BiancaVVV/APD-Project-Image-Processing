    #include <opencv2/opencv.hpp>
    #include <iostream>

    using namespace cv;
    using namespace std;



    // Function for resizing images
    void resizeImage(Mat& image, int width, int height) {
    resize(image, image, Size(width, height));
    }

    // Function for transforming images
    void applyTransformation(Mat& image) {
    cvtColor(image, image, COLOR_BGR2GRAY);
    }

    int main(int argc, char** argv) {
   
    // Load my image in a Mat object
    Mat image = imread("img.jpg");

    //Veify if the image was successfully loaded
    if (image.empty()) {
        cout << "Could not open or find the image" << endl;
        return -1;
    }

    // Apply operations on the entire image
    resizeImage(image, image.cols / 2, image.rows / 2);
    applyTransformation(image);

    // Save processed image
    imwrite("processed_img.jpg", image);
    cout << "Image was processed successfully." << endl;

    return 0;
}
