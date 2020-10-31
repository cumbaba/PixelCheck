#ifndef WINUTILS_H
#define WINUTILS_H

#include <windows.h>
#include "opencv2/imgproc/types_c.h"

class WinUtils {
    public:
        static std::vector<cv::Rect> getAllWindows();
        static BOOL CALLBACK iterateWindows(HWND hwnd, LPARAM lParam);
};

#endif // WINUTILS_H
