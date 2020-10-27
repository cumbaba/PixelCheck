#include "ImageUtils.h"

#include "Converter.h"

#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"

#include <iostream>

QPixmap ImageUtils::compare(const QPixmap& base, const QPixmap& sample, const QSize& contentSize) {
    //    auto baseMat = Converter::QPixmapToCvMat(QPixmap("base.png"));
    auto sampleMat = Converter::QPixmapToCvMat(QPixmap("sample.png"));

    auto lines = detectLines(sampleMat);

    const int magic = 1000000;

    // Draw the lines
    for (size_t i = 0; i < lines.first.size(); i++) {
        std::cout << "x: " <<  lines.first.at(i) << std::endl;
    }

    // Draw the lines
    for (size_t i = 0; i < lines.second.size(); i++) {
        std::cout << "y: " <<  lines.second.at(i) << std::endl;
    }




    cv::imshow("lines", sampleMat);
    //    auto baseRect = findContentPosition(baseMat, cv::Size(contentSize.width(), contentSize.height()));
    //    auto sampleRect = findContentPosition(sampleMat, cv::Size(contentSize.width(), contentSize.height()));

    //    auto croppedBase = baseMat(cv::Rect(baseRect.x, baseRect.y, contentSize.width(), contentSize.height()));
    //    auto croppedSample = sampleMat(cv::Rect(sampleRect.x, sampleRect.y, contentSize.width(), contentSize.height()));

    //    cv::imshow("croppedBase", croppedBase);
    //    cv::imshow("croppedSample", croppedSample);

}

cv::Point ImageUtils::findContentPosition(const cv::Mat& image, const cv::Size& size) {

    // CanyEdge
    auto filtered = applyCannyEdge(image);

    //    cv::namedWindow("sample", cv::WINDOW_AUTOSIZE);
    //    cv::imshow("sample", filtered);


    //    std::cout << "original: " << filtered.at<cv::Vec3b>(cv::Point(120, 42)) << std::endl;
    //    std::cout << filtered.size() << " channels: " << filtered.channels() << std::endl;
    //    std::cout << size.width << size.height << std::endl;


    for (int i = 0; i < filtered.rows; i++) {
        for (int j = 0; j < filtered.cols; j++) {

            const cv::Point candidatePoint(j, i);

            if (filtered.at<uchar>(candidatePoint) > 200) {

                //                std::cout << "TRYING x: " << candidatePoint.x << " y: " << candidatePoint.y << std::endl;

                if (tryRectengale(filtered, candidatePoint, size)) {
                    //                    std::cout << "WOOOOWW x: " << candidatePoint.x << " y: " << candidatePoint.y << std::endl;
                    return candidatePoint;
                }

            }
        }
    }


    return cv::Point(0, 0);
}

bool ImageUtils::tryRectengale(const cv::Mat& image, const cv::Point& startPoint, const cv::Size& size) {

    const cv::Point endPoint(startPoint.x + size.width, startPoint.y + size.height);

    if (startPoint.x > image.cols || startPoint.y > image.rows
        || endPoint.x > image.cols || endPoint.y > image.rows
        || startPoint.x > endPoint.x || startPoint.y > endPoint.y) {
        // Not possible

        //        std::cout << "tryRectengale::Not possible rectengale: "
        //                  << "\n start x: " << startPoint.x
        //                  << "\t start y" << startPoint.y
        //                  << "\n end x: " << endPoint.x
        //                  << "\t end y" << endPoint.y
        //                  << "\n image width" << image.cols
        //                  << "\t image height" << image.rows << std::endl;
        return false;
    }

    const auto grayValue = [image](const int i, const int j) {
        return image.at<uchar>(cv::Point(i, j));
    };


    auto constantlyExpectedGrayValue = image.at<uchar>(startPoint);

    const int toleranceInGrayValue = 10;
    const int maxNoiseByPixel = 10;
    const int splitCount = 10;

    auto minValue = constantlyExpectedGrayValue - toleranceInGrayValue;
    auto maxValue = constantlyExpectedGrayValue + toleranceInGrayValue;

    const auto hasAcceptableValue = [minValue, maxValue](const int val) {
        return !(val < minValue || val > maxValue);
    };

    ///// fast check and ref value finding for the top of the rectengale
    std::vector<int> candidateRefValues;

    // check and ref value finding for top
    int step = (endPoint.x - startPoint.x) / splitCount;

    // At least 1 pixel step
    if (step == 0) {
        step++;
    }

    for (int i = startPoint.x ; i < endPoint.x; i = i + step) {

        auto candidateRefValue = grayValue(i, startPoint.y);

        if (hasAcceptableValue(candidateRefValue)) {
            candidateRefValues.push_back(candidateRefValue);
            continue;
        }
        else {

            for (int noiseDelta = 1; noiseDelta <= maxNoiseByPixel; noiseDelta++) {
                auto posNoisyValue = grayValue(i + noiseDelta, startPoint.y);
                auto negNoisyValue = grayValue(i - noiseDelta, startPoint.y);

                if (hasAcceptableValue(posNoisyValue)) {
                    candidateRefValue = posNoisyValue;
                    candidateRefValues.push_back(candidateRefValue);
                    break;
                }
                else if (hasAcceptableValue(negNoisyValue)) {
                    candidateRefValue = negNoisyValue;
                    candidateRefValues.push_back(candidateRefValue);
                    break;
                }

                if (noiseDelta == maxNoiseByPixel) {
                    // Not acceptable rectangle, very noisy
                    //                    std::cout << "tryRectengale::Not possible rectengale: top is very noisy" << std::endl;
                    return false;
                }
            }
        }
    }

    int constantlyExpectedGrayValueForTop = constantlyExpectedGrayValue;
    int maxInHistogram = 0;

    for (auto& candidateRefValue : candidateRefValues) {
        const int count  = std::count(candidateRefValues.begin(), candidateRefValues.end(), candidateRefValue);

        if (count > maxInHistogram) {
            maxInHistogram = count;

            constantlyExpectedGrayValueForTop = candidateRefValue;
        }
    }

    ///// fast check and ref value finding for the left of the rectengale
    candidateRefValues.clear();

    // check and ref value finding for top
    step = (endPoint.y - startPoint.y) / splitCount;

    // At least 1 pixel step
    if (step == 0) {
        step++;
    }

    for (int j = startPoint.y ; j < endPoint.y; j = j + step) {

        auto candidateRefValue = grayValue(startPoint.x, j);

        if (hasAcceptableValue(candidateRefValue)) {
            candidateRefValues.push_back(candidateRefValue);
            continue;
        }
        else {

            for (int noiseDelta = 1; noiseDelta <= maxNoiseByPixel; noiseDelta++) {
                auto posNoisyValue = grayValue(startPoint.x, j + noiseDelta);
                auto negNoisyValue = grayValue(startPoint.x, j - noiseDelta);

                if (hasAcceptableValue(posNoisyValue)) {
                    candidateRefValue = posNoisyValue;
                    candidateRefValues.push_back(candidateRefValue);
                    break;
                }
                else if (hasAcceptableValue(negNoisyValue)) {
                    candidateRefValue = negNoisyValue;
                    candidateRefValues.push_back(candidateRefValue);
                    break;
                }

                if (noiseDelta == maxNoiseByPixel) {
                    // Not acceptable rectangle, very noisy
                    //                    std::cout << "tryRectengale::Not possible rectengale: LEFT is very noisy" << std::endl;
                    return false;
                }
            }
        }
    }


    int constantlyExpectedGrayValueForLeft = constantlyExpectedGrayValue;
    maxInHistogram = 0;

    for (auto& candidateRefValue : candidateRefValues) {
        const int count  = std::count(candidateRefValues.begin(), candidateRefValues.end(), candidateRefValue);

        if (count > maxInHistogram) {
            maxInHistogram = count;

            constantlyExpectedGrayValueForLeft = candidateRefValue;
        }
    }


    //    std::cout << "tryRectengale::Candidate value int: " << (int)constantlyExpectedGrayValue << std::endl;
    //    std::cout << "tryRectengale::Candidate value char: " << constantlyExpectedGrayValue << std::endl;

    //    std::cout << "tryRectengale::Candidate value top int: " << (int)constantlyExpectedGrayValueForTop << std::endl;
    //    std::cout << "tryRectengale::Candidate value top char: " << constantlyExpectedGrayValueForTop << std::endl;


    minValue = constantlyExpectedGrayValueForTop - toleranceInGrayValue;
    maxValue = constantlyExpectedGrayValueForTop + toleranceInGrayValue;

    for (int i = startPoint.x; i < startPoint.x + size.width; i++) {

        const auto follower = grayValue(i, startPoint.y);

        //        std::cout << "XXX-INFO check uchar " << follower << "\tint " << (int)follower << std::endl;

        if (hasAcceptableValue(follower)) {
            continue;
        }
        else {
            for (int noiseDelta = 1; noiseDelta <= maxNoiseByPixel; noiseDelta++) {
                auto posNoisyValue = grayValue(i + noiseDelta, startPoint.y);

                if (hasAcceptableValue(posNoisyValue)) {
                    i += noiseDelta;
                    break;
                }

                if (noiseDelta == maxNoiseByPixel) {

                    // Not acceptable rectangle, very noisy
                    //                    std::cout << "tryRectengale::XXX Unexpected value: "
                    //                              "point x: " << i << " y: " <<  startPoint.y <<
                    //                              " expectedValue: " << (int) constantlyExpectedGrayValue <<
                    //                              " BUT points value: " << (int) follower << std::endl;
                    return false;
                }
            }
        }
    }

    //    std::cout << "tryRectengale::Candidate value left int: " << (int)constantlyExpectedGrayValueForLeft << std::endl;

    minValue = constantlyExpectedGrayValueForLeft - toleranceInGrayValue;
    maxValue = constantlyExpectedGrayValueForLeft + toleranceInGrayValue;

    // TODO fix -1 bug if necessary
    for (int j = startPoint.y; j < startPoint.y + size.height; j++) {

        const auto follower = grayValue(startPoint.x, j);

        //        std::cout << "XXX-INFO check uchar " << follower << "\tint " << (int)follower << std::endl;

        if (hasAcceptableValue(follower)) {
            continue;
        }
        else {
            for (int noiseDelta = 1; noiseDelta <= maxNoiseByPixel; noiseDelta++) {
                auto posNoisyValue = grayValue(startPoint.x, j + noiseDelta);

                if (hasAcceptableValue(posNoisyValue)) {
                    j += noiseDelta;
                    break;
                }

                if (noiseDelta == maxNoiseByPixel) {

                    // Not acceptable rectangle, very noisy
                    //                    std::cout << "tryRectengale::YYY Unexpected value: "
                    //                              "point x: " << j << " y: " <<  startPoint.y <<
                    //                              " expectedValue: " << (int) constantlyExpectedGrayValue <<
                    //                              " BUT points value: " << (int) follower << std::endl;
                    return false;
                }
            }
        }
    }

    return true;
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
