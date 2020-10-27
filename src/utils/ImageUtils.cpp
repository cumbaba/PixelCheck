#include "ImageUtils.h"

#include "Converter.h"

#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"

#include <iostream>

QPixmap ImageUtils::compare(const QPixmap& base, const QPixmap& sample, const QSize& contentSize) {
    //    auto baseMat = Converter::QPixmapToCvMat(QPixmap("base.png"));
    auto sampleMat = Converter::QPixmapToCvMat(QPixmap("sample.png"));

    //    auto lines = detectLines(sampleMat);

    //    // Draw the lines
    //    for (size_t i = 0; i < lines.first.size(); i++) {
    //        std::cout << "x: " <<  lines.first.at(i) << std::endl;
    //    }

    //    // Draw the lines
    //    for (size_t i = 0; i < lines.second.size(); i++) {
    //        std::cout << "y: " <<  lines.second.at(i) << std::endl;
    //    }


    //    cv::imshow("lines", sampleMat);
    //    auto baseRect = findContentPosition(baseMat, cv::Size(contentSize.width(), contentSize.height()));
    auto sampleRect = findContentPosition(sampleMat, cv::Size(contentSize.width(), contentSize.height()));

    std::cout <<  sampleRect.x << "::" << sampleRect.y << std::endl;
    //    auto croppedBase = baseMat(cv::Rect(baseRect.x, baseRect.y, contentSize.width(), contentSize.height()));
    auto croppedSample = sampleMat(cv::Rect(sampleRect.x, sampleRect.y, contentSize.width(), contentSize.height()));

    //        cv::imshow("croppedBase", croppedBase);
//    cv::imshow("croppedSample", croppedSample);

}

cv::Point ImageUtils::findContentPosition(const cv::Mat& image, const cv::Size& size) {
    auto lines = detectLines(image);

    // Draw the lines
    for (size_t i = 0; i < lines.first.size(); i++) {
        std::cout << "x: " <<  lines.first.at(i) << std::endl;
    }

    // Draw the lines
    for (size_t i = 0; i < lines.second.size(); i++) {
        std::cout << "y: " <<  lines.second.at(i) << std::endl;
    }

    auto xAxisLines = lines.first;
    auto yAxisLines = lines.second;

    auto x = 0, y = 0;

    //    for (auto i = 0; i < xAxisLines.size(); i++) {
    //        if (xAxisLines.size() > i + 1) {
    //            for (auto j = i + 1; j < xAxisLines.size(); j++) {
    //                if (xAxisLines.at(j) - xAxisLines.at(i) + 1 == size.width) {
    //                    x = xAxisLines.at(i);
    //                    break;
    //                }
    //            }
    //        }
    //    }

    //    for (auto i = 0; i < yAxisLines.size(); i++) {
    //        if (yAxisLines.size() > i + 1) {
    //            for (auto j = i + 1; j < yAxisLines.size(); j++) {
    //                if (yAxisLines.at(j) - yAxisLines.at(i) + 1 == size.height) {
    //                    y = yAxisLines.at(i);
    //                    break;
    //                }
    //            }
    //        }
    //    }

    //    if (x == 0 || y == 0) {
    //        throw std::invalid_argument("content not found");
    //    }

    return cv::Point(x, y);
}

std::pair<QList<int>, QList<int>> ImageUtils::detectLines(const cv::Mat& image) {
    // Declare the output variables
    cv::Mat image_gry, edgeImage, orginalImageWithHoughLines;

    // Loads an image
    cv::cvtColor(image, image_gry, cv::COLOR_BGR2GRAY);

    // Apply the Guassian Blur filter to smooth the image
    cv::Mat image_gaussian_processed;
    cv::GaussianBlur(image_gry, image_gaussian_processed, cv::Size(5, 5), 1);

    // Edge detection
    cv::Canny(image_gaussian_processed, edgeImage, 50, 120, 3);

    // Copy loaded image to the initial image so that will display the results in BGR
    cv::cvtColor(image_gry, orginalImageWithHoughLines, cv::COLOR_GRAY2BGR);

    // Declaring some constants for the parameters
    const int dis_reso = 1;
    const double theta = CV_PI / 180;
    const int threshold = 170;

    // Standard Hough Line Transform
    std::vector<cv::Vec2f> lines; // will hold the results of the detection
    cv::HoughLines(edgeImage, lines, dis_reso, theta, threshold, 0, 0); // runs the actual detection

    QList<int> xAxis, yAxis;
    const int magic = 48000000;

    // Draw the lines
    for (size_t i = 0; i < lines.size(); i++) {
        float rho = lines[i][0], theta = lines[i][1];
        cv::Point pt1, pt2;
        double a = cos(theta), b = sin(theta);
        double x0 = a * rho, y0 = b * rho;
        pt1.x = cvRound(x0 + magic * (-b));
        pt1.y = cvRound(y0 + magic * (a));
        pt2.x = cvRound(x0 - magic * (-b));
        pt2.y = cvRound(y0 - magic * (a));
        cv::line(image, pt1, pt2, cv::Scalar(0, 255, 00), 1, cv::LINE_AA);

        if (abs(pt1.x) == magic) {
            yAxis.push_back(pt1.y);
        }
        else {
            xAxis.push_back(pt1.x);
        }
    }

    cv::imshow("lines", image);

    return std::make_pair(xAxis, yAxis);
}

cv::Mat ImageUtils::applyCannyEdge(const cv::Mat& image) {
    const int threshold = 100;
    const int kernel_size = 3;
    const int ratio = 3;

    cv::Mat filtered, detected_edges, src_gray;

    filtered.create(image.size(), image.type());
    cv::cvtColor(image, src_gray, cv::COLOR_BGR2GRAY);

    cv::blur(src_gray, detected_edges, cv::Size(3, 3));
    cv::Canny(detected_edges, detected_edges, threshold, threshold * ratio, kernel_size);
    filtered = cv::Scalar::all(0);
    image.copyTo(filtered, detected_edges);

    cv::Mat filtered_gray;
    cv::cvtColor(filtered, filtered_gray, cv::COLOR_BGR2GRAY);
    return filtered_gray;
}
