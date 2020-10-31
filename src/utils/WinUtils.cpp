#include "WinUtils.h"

#include <windows.h>

#include <iostream>
#include <algorithm>

std::vector< cv::Rect> WinUtils::getAllWindows() {
    std::vector<std::pair<std::wstring, cv::Rect>> wins;
    std::vector<cv::Rect> windows = {cv::Rect(0, 0, 100, 200)};

    EnumWindows(&WinUtils::iterateWindows, reinterpret_cast<LPARAM>(&wins));

    for (const auto& win2 : wins) {
        auto rect = win2.second;

        std::wcout << "\n\t\t" << win2.first << std::endl;
        std::cout << "x:\t" << rect.x << "\ty:\t" << rect.y << std::endl;
        std::cout << "width:\t" << rect.width << "\theight:\t" << rect.height << std::endl;
    }


    return windows;
}

WINBOOL WinUtils::iterateWindows(HWND hwnd, LPARAM lParam) {
    const DWORD TITLE_SIZE = 1024;
    WCHAR windowTitle[TITLE_SIZE];
    GetWindowTextW(hwnd, windowTitle, TITLE_SIZE);
    int length = ::GetWindowTextLength(hwnd);
    std::wstring title(&windowTitle[0]);

    if (!IsWindowVisible(hwnd) || length == 0 || title == L"Program Manager") {
        return TRUE;
    }

    RECT rect;
    ::GetWindowRect(hwnd, &rect);

    // Retrieve the pointer passed into this callback, and re-'type' it.
    // The only way for a C API to pass arbitrary data is by means of a void*.
    std::vector<std::pair<std::wstring, cv::Rect>>& rects =
                *reinterpret_cast < std::vector<std::pair<std::wstring, cv::Rect>>* >(lParam);

    rects.push_back(std::make_pair(title,
                                   cv::Rect(cv::Point(rect.left, rect.top), cv::Point(rect.right, rect.bottom))));

    return TRUE;

}
