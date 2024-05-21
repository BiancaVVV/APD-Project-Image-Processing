#include <opencv2/opencv.hpp>
#include <iostream>
#include <thread>
#include <vector>
#include <chrono> // Pentru măsurarea timpului

using namespace cv;
using namespace std;

// Funcție pentru conversia la alb-negru
void convertToGrayscale(const Mat& inputImage, Mat& grayscaleImage, int startRow, int endRow) {
    for (int y = startRow; y < endRow; y++) {
        for (int x = 0; x < inputImage.cols; x++) {
            Vec3b pixel = inputImage.at<Vec3b>(y, x);
            uchar grayscale = (pixel[0] + pixel[1] + pixel[2]) / 3;
            grayscaleImage.at<uchar>(y, x) = grayscale;
        }
    }
}

// Funcție pentru redimensionarea imaginii pixel cu pixel
void resizeImage(const Mat& inputImage, Mat& resizedImage, int startRow, int endRow, float scaleX, float scaleY) {
    for (int y = startRow; y < endRow; y++) {
        for (int x = 0; x < resizedImage.cols; x++) {
            int originX = scaleX * x;
            int originY = scaleY * y;

            Vec3b& pixel = resizedImage.at<Vec3b>(y, x);
            pixel = inputImage.at<Vec3b>(originY, originX);
        }
    }
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

    float scaleX = (float)image.cols / newWidth;
    float scaleY = (float)image.rows / newHeight;
    Mat resizedImage;

    // Măsurarea timpului de redimensionare
    auto start = chrono::high_resolution_clock::now();

    // Numărul de fire de execuție
    int numThreads = thread::hardware_concurrency();
    if (numThreads == 0) numThreads = 4; // fallback la 4 dacă hardware_concurrency nu reușește să detecteze corect
    vector<thread> threads;
    // Determină intervalele de rânduri pentru fiecare fir de execuție pentru redimensionare
    int rowsPerThread = newHeight / numThreads;
    int remainingRows = newHeight % numThreads;


    int currentRow = 0;
    for (int i = 0; i < numThreads; i++) {
        int startRow = currentRow;
        int endRow = startRow + rowsPerThread + (i < remainingRows ? 1 : 0);
        threads.push_back(thread(resizeImage, cref(image), ref(resizedImage), startRow, endRow, scaleX, scaleY));
        currentRow = endRow;
    }

    // Așteaptă finalizarea firelor de execuție pentru redimensionare
    for (auto& t : threads) {
        t.join();
    }



    // Imagine alb-negru, 8-bit per pixel
    Mat grayscaleImage;
    grayscaleImage.create(newHeight, newWidth, CV_8UC1);

    // Golim vectorul de fire și reîmpărțim rândurile pentru conversia la alb-negru
    threads.clear();
    currentRow = 0;
    for (int i = 0; i < numThreads; i++) {
        int startRow = currentRow;
        int endRow = startRow + rowsPerThread + (i < remainingRows ? 1 : 0);
        threads.push_back(thread(convertToGrayscale, cref(resizedImage), ref(grayscaleImage), startRow, endRow));
        currentRow = endRow;
    }



    // Așteaptă finalizarea firelor de execuție pentru conversia la alb-negru
    for (auto& t : threads) {
        t.join();
    }



    // Salvează imaginea rezultată
    imwrite("output.jpg", grayscaleImage);

    cout << "Imaginea a fost redimensionata și convertita în alb-negru cu succes!\n";

    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> Time = end - start;
    cout << "Timpul de executie: " << Time.count() << " secunde\n";
    return 0;
}
