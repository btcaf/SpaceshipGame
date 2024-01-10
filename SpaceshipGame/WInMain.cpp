#ifndef UNICODE
#define UNICODE
#endif

#include "WinMain.h"
#include "Animation.h"

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

INT WINAPI wWinMain(
_In_ [[maybe_unused]] HINSTANCE instance, 
_In_opt_ [[maybe_unused]] HINSTANCE prev_instance,
_In_ [[maybe_unused]] PWSTR cmd_line, 
_In_ [[maybe_unused]] INT cmd_show
) {
    const wchar_t CLASS_NAME[] = L"Sample Window Class";

    WNDCLASS wc = { };

    wc.lpfnWndProc = WindowProc;
    wc.hInstance = instance;
    wc.lpszClassName = CLASS_NAME;

    RegisterClass(&wc);

    HWND hwnd = CreateWindowEx(
        0,
        CLASS_NAME,
        L"SpaceshipGame",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
        NULL,
        NULL,
        instance,
        NULL
    );

    if (hwnd == NULL)
    {
        return 0;
    }

    ShowWindow(hwnd, cmd_show);

    SetTimer(hwnd, 1, 1000 / 60, (TIMERPROC)NULL);

    MSG msg = { };
    while (GetMessage(&msg, NULL, 0, 0) > 0)
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
    case WM_DESTROY:
        KillTimer(hwnd, 1);
        destroy();
        PostQuitMessage(0);
        return 0;

    case WM_TIMER:
    {
        InvalidateRect(hwnd, NULL, FALSE);
        break;
    }
    case WM_PAINT:
    {
        paint(hwnd);
    }
    return 0;

    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}
