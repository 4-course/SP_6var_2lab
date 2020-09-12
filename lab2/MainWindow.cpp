#include <windows.h>
#include "Conditioner.h"

Conditioner *conditioner;

HWND powerButton, workButton, modeButton;

LRESULT CALLBACK WindowProc (HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    HDC hdc;
    HINSTANCE hInst;
    HFONT font, timerFont;
    HBRUSH rectBrush;
    PAINTSTRUCT ps;
    RECT window;
    switch (uMsg) {
        case WM_CREATE:
            hInst = ((LPCREATESTRUCT)lParam)->hInstance;
            powerButton = CreateWindow(L"button", L"выключено",
                                WS_CHILD | WS_VISIBLE | WS_BORDER,
                                120, 85, 85, 30, hWnd, 0, hInst, NULL);
            ShowWindow(powerButton, SW_SHOWNORMAL);
            workButton = CreateWindow(L"button", L"+1 мин",
                                WS_CHILD | WS_VISIBLE | WS_BORDER,
                                80, 140, 75, 30, hWnd, 0, hInst, NULL);
            EnableWindow(workButton, FALSE);
            ShowWindow(workButton, SW_SHOWNORMAL);
            modeButton = CreateWindow(L"button", L"холодный",
                                WS_CHILD | WS_VISIBLE | WS_BORDER,
                                110, 195, 90, 30, hWnd, 0, hInst, NULL);
            ShowWindow(modeButton, SW_SHOWNORMAL);
            break;
        case WM_PAINT:
            hdc = BeginPaint(hWnd, &ps);

            rectBrush = CreateSolidBrush(RGB(0, 0, 0));

            SetRect(&window, 5, 10, 230, 55);
            FillRect(hdc, &window, rectBrush);

            timerFont = CreateFont(44, 20, 0, 0, FW_NORMAL, false, false, false, DEFAULT_CHARSET, 
                                   OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, L"Consolas");
            SelectObject(hdc, timerFont);

            SetBkColor(hdc, RGB(0,0,0));
            SetTextColor(hdc, RGB(0, 255, 0));
            wchar_t istr[256];
            _itow_s(conditioner->getTime(), istr, 10);
            TextOut(hdc, 10, 10, istr, 1);

            SetBkColor(hdc, RGB(255, 255, 255));
            SetTextColor(hdc, RGB(0, 0, 0));
            font = CreateFont(22, 9, 0, 0, FW_NORMAL, false, false, false, DEFAULT_CHARSET, 
                              OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, L"Arial");
            SelectObject(hdc, font);
            TextOut(hdc, 30, 90, L"Питание:", 8);
            TextOut(hdc, 30, 200, L"Режим:", 6);

            DeleteObject(font);
            DeleteObject(timerFont);
            DeleteObject(rectBrush);

            EndPaint(hWnd, &ps);
            break;
        case WM_COMMAND:
            if (lParam == (LPARAM)powerButton) {
                if (conditioner->isTurnedOn()) {
                    conditioner->changePower();

                    SetWindowText(powerButton, L"выключено");
                    EnableWindow(workButton, FALSE);
                    EnableWindow(modeButton, TRUE);
                }
                else {
                    conditioner->changePower();

                    SetWindowText(powerButton, L"включено");
                    EnableWindow(workButton, TRUE);
                    EnableWindow(modeButton, FALSE);
                }
            }
            else if (lParam == (LPARAM)workButton) {

            }
            else if (lParam == (LPARAM)modeButton) {
                conditioner->changeMode();
                if (conditioner->isColdMode())
                    SetWindowText(modeButton, L"холодный");
                else
                    SetWindowText(modeButton, L"горячий");
            }
            break;
        case WM_CLOSE:
            PostQuitMessage(0);
            break;
    }
    return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

void checkIsCLassRegistered (WNDCLASSEX windowClass) {
    if (!RegisterClassEx (&windowClass)) {
        MessageBox (NULL, L"Не удалось создать класс окна. Ошибка " + GetLastError (), L"Создание класса окна", MB_ICONERROR);
        exit (0);
    }
}

void checkIsWindowCreated (HWND window) {
    if (!window) {
        MessageBox (NULL, L"Не удалось создать окно. Ошибка " + GetLastError (), L"Создание окна", MB_ICONERROR);
        exit (0);
    }
}

int WINAPI WinMain(HINSTANCE hInst,
                   HINSTANCE hPreviousInst,
                   LPSTR lpCommandLine,
                   int nCommandShow) {
    int screenWidth = GetSystemMetrics(SM_CXSCREEN),
        screenHeight = GetSystemMetrics(SM_CYSCREEN),
        mainWindowWidth = 250,
        mainWindowHeight = 300;
    conditioner = new Conditioner();
    MSG uMsg;
    WNDCLASSEX mainWindowClass;
    HWND mainWindow;

    memset(&mainWindowClass, 0, sizeof(WNDCLASSEX));
    mainWindowClass.cbSize = sizeof(WNDCLASSEX);
    mainWindowClass.hbrBackground = (HBRUSH)WHITE_BRUSH;
    mainWindowClass.hCursor = LoadCursor(NULL, IDC_ARROW);
    mainWindowClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    mainWindowClass.hInstance = hInst;
    mainWindowClass.lpfnWndProc = WindowProc;
    mainWindowClass.lpszClassName = L"mainWindow";

    checkIsCLassRegistered(mainWindowClass);

    //mainWindow = CreateWindow(mainWindowClass.lpszClassName, L"Пульт", WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_THICKFRAME | WS_MINIMIZEBOX | WS_MAXIMIZEBOX,
                              //(screenWidth - mainWindowWidth) / 2, (screenHeight - mainWindowHeight) / 2, mainWindowWidth, mainWindowHeight, NULL, NULL, hInst, NULL);
    mainWindow = CreateWindow(mainWindowClass.lpszClassName, L"Пульт", WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU,
                              (screenWidth - mainWindowWidth) / 2, (screenHeight - mainWindowHeight) / 2, mainWindowWidth, mainWindowHeight, NULL, NULL, hInst, NULL);

    checkIsWindowCreated(mainWindow);

    ShowWindow(mainWindow, nCommandShow);

    while (GetMessage(&uMsg, NULL, NULL, NULL)) {
        TranslateMessage(&uMsg);
        DispatchMessage(&uMsg);
    }
    delete conditioner;
    return uMsg.wParam;
}