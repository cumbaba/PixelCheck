 #include "ImageUtils.h"

#include "Converter.h"

#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"

#include <iostream>

QPixmap ImageUtils::compare(const QPixmap& base, const QPixmap& sample, const QSize& contentSize) {
    auto baseMat = Converter::QPixmapToCvMat(QPixmap("b1.png"));
    auto sampleMat = Converter::QPixmapToCvMat(QPixmap("s1.png"));

    cv::Point baseRect, sampleRect;
    cv::Size cvSize = Converter::toCvSize(contentSize);

    try {
        baseRect = findContentPosition(baseMat, cvSize);
        std::cout <<  "base:\t" << baseRect.x << "::" << baseRect.y << std::endl;
    }
    catch (std::invalid_argument& e) {
        std::cout << e.what() << "x: " << baseRect.x << " y: " << baseRect.y << std::endl;
    }

    try {
        sampleRect = findContentPosition(sampleMat, cvSize);
        std::cout <<  "sample:\t" << sampleRect.x << "::" << sampleRect.y << std::endl;
    }
    catch (std::invalid_argument& e) {
        std::cout << e.what() << "x: " << sampleRect.x << " y: " << sampleRect.y << std::endl;
    }

    cv::Mat croppedBase = baseMat(cv::Rect(baseRect.x, baseRect.y,  contentSize.width(), contentSize.height()));
    cv::Mat croppedSample = sampleMat(cv::Rect(sampleRect.x, sampleRect.y, contentSize.width(), contentSize.height()));

    if (croppedBase.size != croppedSample.size) {
        std::cout <<  "croppedBase w:\t" << croppedBase.cols << "\th:\t" << croppedBase.rows << std::endl;
        std::cout <<  "croppedSample w:\t" << croppedSample.cols << "\th:\t" << croppedSample.rows << std::endl;
        throw std::invalid_argument("cropped image sizes are not the same");
    }


    // TODO
    // Find text elements on both images. Afterwards ignre the areas containing texts.
    // Then compare the pixels left.


    cv::Mat diff = croppedSample.clone();

    for (auto x = 0; x < croppedBase.cols; ++x) {
        for (auto y = 0; y < croppedBase.rows; ++y) {

            auto p = cv::Point(x, y);

            if (checkPixel(croppedBase, croppedSample, p) == false) {

                markPixel(diff, p);
            }
        }
    }

    cv::imshow("croppedBase", croppedBase);
    cv::imshow("croppedSample", croppedSample);
    cv::imshow("result", diff);
}

bool ImageUtils::checkPixel(const cv::Mat& base, const cv::Mat& sample,
                            const cv::Point& point, const int toleranceInPixels) {

    auto same =  comparePixels(base, sample, point);

    if (same) {
        return true;
    }

    // Manipulate point to find the corresponding one for sample
    for (auto i = point.x - toleranceInPixels; i < point.x + toleranceInPixels; ++i) {
        if (i >= 0 && i < sample.cols) {
            for (auto j = point.y - toleranceInPixels; j < point.y + toleranceInPixels; ++j) {
                if (j >= 0 && j < sample.rows) {

                    if (comparePixels(base, sample, point, cv::Point(i, j))) {
                        return true;
                    }

                }
            }
        }
    }

    return false;
}

bool ImageUtils::comparePixels(const cv::Mat& base, const cv::Mat& sample,
                               const cv::Point& point,
                               const int colorComparisonTolerance) {
    return comparePixels(base, sample, point, point, colorComparisonTolerance);
}

bool ImageUtils::comparePixels(const cv::Mat& base, const cv::Mat& sample,
                               const cv::Point& basePoint, const cv::Point& samplePoint,
                               const int colorComparisonTolerance) {
    cv::Vec3b baseValue = base.at<cv::Vec3b>(basePoint);
    cv::Vec3b sampleValue = sample.at<cv::Vec3b>(samplePoint);


    return abs(baseValue.val[0] - sampleValue.val[0]) +
           abs(baseValue.val[1] - sampleValue.val[1]) +
           abs(baseValue.val[2] - sampleValue.val[2]) < colorComparisonTolerance + 1;
}


cv::Point ImageUtils::findContentPosition(const cv::Mat& image, const cv::Size& size) {
    auto lines = detectLines(image);

    // Draw the lines
    //    for (size_t i = 0; i < lines.first.size(); i++) {
    //        std::cout << "x: " <<  lines.first.at(i) << std::endl;
    //    }

    //    // Draw the lines
    //    for (size_t i = 0; i < lines.second.size(); i++) {
    //        std::cout << "y: " <<  lines.second.at(i) << std::endl;
    //    }

    auto xAxisLines = lines.first;
    auto yAxisLines = lines.second;

    auto x = 0, y = 0;

    const int pixelTolerance = 5;

    for (auto i = 0; i < xAxisLines.size(); i++) {
        if (xAxisLines.size() > i + 1) {
            for (auto j = i + 1; j < xAxisLines.size(); j++) {
                if (abs(abs(xAxisLines.at(j) - xAxisLines.at(i)) - size.width) <=  pixelTolerance) {
                    if (xAxisLines.at(i) > xAxisLines.at(j)) {
                        x = xAxisLines.at(j);
                    }
                    else {
                        x = xAxisLines.at(i);
                    }

                    break;
                }
            }
        }
    }

    for (auto i = 0; i < yAxisLines.size(); i++) {
        if (yAxisLines.size() > i + 1) {
            for (auto j = i + 1; j < yAxisLines.size(); j++) {
                if (abs(abs(yAxisLines.at(j) - yAxisLines.at(i)) - size.height) <=  pixelTolerance) {
                    if (yAxisLines.at(i) > yAxisLines.at(j)) {
                        y = yAxisLines.at(j);
                    }
                    else {
                        y = yAxisLines.at(i);
                    }

                    break;
                }
            }
        }
    }

    if (x == 0 || y == 0) {
        throw std::invalid_argument("content not found");
    }

    return cv::Point(x, y);
}

std::pair<QList<int>, QList<int>> ImageUtils::detectLines(const cv::Mat& image) {
    // Declare the output variables
    cv::Mat image_gry, edgeImage, originalImage, orginalImageWithHoughLines;

    originalImage = image.clone();

    cv::cvtColor(originalImage, image_gry, cv::COLOR_BGR2GRAY);

    // Apply the Guassian Blur filter to smooth the image
    cv::Mat image_gaussian_processed;
    cv::GaussianBlur(image_gry, image_gaussian_processed, cv::Size(5, 5), 1);

    // Edge detection
    edgeImage = applyCannyEdge(image_gaussian_processed);

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
    const int magic = 10000;

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
        cv::line(originalImage, pt1, pt2, cv::Scalar(0, 255, 00), 1, cv::LINE_AA);

        if (abs(pt1.x) == magic || abs(pt2.x) == magic) {
            if (pt1.y > 0) {
                yAxis.push_back(pt1.y);
            }
        }
        else {
            if (pt1.x > 0) {
                xAxis.push_back(pt1.x);
            }
        }
    }

    //    cv::imshow(std::to_string(originalImage.cols), originalImage);

    return std::make_pair(xAxis, yAxis);
}

cv::Mat ImageUtils::applyCannyEdge(const cv::Mat& image_gray) {
    const int threshold = 100;
    const int kernel_size = 3;
    const int ratio = 3;

    cv::Mat filtered, detected_edges, image;

    filtered.create(image.size(), image.type());
    cv::cvtColor(image_gray, image, cv::COLOR_GRAY2BGR);

    cv::blur(image_gray, detected_edges, cv::Size(3, 3));
    cv::Canny(detected_edges, detected_edges, threshold, threshold * ratio, kernel_size);
    filtered = cv::Scalar::all(0);
    image.copyTo(filtered, detected_edges);

    cv::Mat filtered_gray;
    cv::cvtColor(filtered, filtered_gray, cv::COLOR_BGR2GRAY);
    return filtered_gray;
}

void ImageUtils::markPixel(cv::Mat& image, const cv::Point& markPoint) {
    image.at<cv::Vec3b>(markPoint)[0] = 0;
    image.at<cv::Vec3b>(markPoint)[1] = 128;
    image.at<cv::Vec3b>(markPoint)[2] = 225;
}
