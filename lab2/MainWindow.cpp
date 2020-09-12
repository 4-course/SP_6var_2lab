#include <windows.h>

LRESULT CALLBACK WindowProc (HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    HDC hdc;
    HINSTANCE hInst;
    HFONT font;
    HWND powerButton, workButton, modeButton;
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
            ShowWindow(powerButton, SW_SHOWNORMAL);
            workButton = CreateWindow(L"button", L"холодный",
                                WS_CHILD | WS_VISIBLE | WS_BORDER,
                                110, 195, 90, 30, hWnd, 0, hInst, NULL);
            ShowWindow(powerButton, SW_SHOWNORMAL);
            break;
        case WM_PAINT:
            hdc = BeginPaint(hWnd, &ps);
            SetRect(&window, 10, 10, 230, 60);
            FillRect(hdc, &window, (HBRUSH)BLACK_BRUSH);

            font = CreateFont(22, 9, 0, 0, FW_NORMAL, false, false, false, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, L"Arial");
            SelectObject(hdc, font);
            TextOut(hdc, 30, 90, L"Питание:", 8);
            TextOut(hdc, 30, 200, L"Режим:", 6);
            EndPaint(hWnd, &ps);
            DeleteObject(font);
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
    mainWindow = CreateWindow(mainWindowClass.lpszClassName, L"Пульт", WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_THICKFRAME | WS_MINIMIZEBOX,
                              (screenWidth - mainWindowWidth) / 2, (screenHeight - mainWindowHeight) / 2, mainWindowWidth, mainWindowHeight, NULL, NULL, hInst, NULL);

    checkIsWindowCreated(mainWindow);

    ShowWindow(mainWindow, nCommandShow);

    while (GetMessage(&uMsg, NULL, NULL, NULL)) {
        TranslateMessage(&uMsg);
        DispatchMessage(&uMsg);
    }
    return uMsg.wParam;
}