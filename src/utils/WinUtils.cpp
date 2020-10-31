#include "WinUtils.h"

#include <windows.h>

#include <iostream>
#include <algorithm>

std::vector< cv::Rect> WinUtils::getAllWindows() {
    std::vector<std::wstring> titles;
    std::vector<cv::Rect> windows = {cv::Rect(0, 0, 100, 200)};

    EnumWindows(&WinUtils::saveWindow, reinterpret_cast<LPARAM>(&titles));

    // At this point, titles if fully populated and could be displayed, e.g.:
    for (const auto& title : titles) {
        std::wcout << L"Title: " << title << std::endl;
    }


    return windows;
}

WINBOOL WinUtils::saveWindow(HWND hwnd, LPARAM lParam) {
    const DWORD TITLE_SIZE = 1024;
    WCHAR windowTitle[TITLE_SIZE];

    GetWindowTextW(hwnd, windowTitle, TITLE_SIZE);

    int length = ::GetWindowTextLength(hwnd);
    std::wstring title(&windowTitle[0]);

    if (!IsWindowVisible(hwnd) || length == 0 || title == L"Program Manager") {
        return TRUE;
    }

    // Retrieve the pointer passed into this callback, and re-'type' it.
    // The only way for a C API to pass arbitrary data is by means of a void*.
    std::vector<std::wstring>& titles =
        *reinterpret_cast<std::vector<std::wstring>*>(lParam);
    titles.push_back(title);

    return TRUE;

}
