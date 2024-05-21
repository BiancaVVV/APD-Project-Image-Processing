#include <opencv2/opencv.hpp>
#include <iostream>
#include <chrono>

int main() {
    // Începe cronometrarea
    auto start = std::chrono::high_resolution_clock::now();

    // Numele fișierului de intrare
    std::string imagePath = "12.jpg";

    // Citește imaginea de la calea specificată
    cv::Mat image = cv::imread(imagePath, cv::IMREAD_COLOR);

    // Verifică dacă imaginea a fost încărcată corect
    if (image.empty()) {
        std::cerr << "Could not open or find the image" << std::endl;
        return -1;
    }

    // Redimensionează imaginea la 600x200
    cv::Mat resizedImage;
    cv::resize(image, resizedImage, cv::Size(600, 200), 0, 0, cv::INTER_LINEAR);

    // Convertește imaginea redimensionată în greyscale
    cv::Mat greyImage;
    cv::cvtColor(resizedImage, greyImage, cv::COLOR_BGR2GRAY);

    // Salvează imaginea procesată
    std::string outputPath = "output_image.jpg";
    cv::imwrite(outputPath, greyImage);

    // Sfârșește cronometrarea
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;

    // Afișează timpul de execuție
    std::cout << "Image processed and saved as " << outputPath << std::endl;
    std::cout << "Execution time: " << duration.count() << " seconds" << std::endl;

    return 0;
}
