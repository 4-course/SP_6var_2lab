#include <windows.h>

LRESULT CALLBACK WindowProc (HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
        case WM_CLOSE:
            exit(0);
            break;
        default:
            return DefWindowProc(hWnd, uMsg, wParam, lParam);
    }
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
        mainWindowWidth = 500,
        mainWindowHeight = 250;
    MSG uMsg;
    WNDCLASSEX mainWindowClass;
    HWND mainWindow;
    memset(&mainWindowClass, 0, sizeof(WNDCLASSEX));
    mainWindowClass.cbSize = sizeof(WNDCLASSEX);
    mainWindowClass.hbrBackground = (HBRUSH)COLOR_WINDOW;
    mainWindowClass.hCursor = LoadCursor(NULL, IDC_ARROW);
    mainWindowClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    mainWindowClass.hInstance = hInst;
    mainWindowClass.lpfnWndProc = WindowProc;
    mainWindowClass.lpszClassName = L"mainWindow";

    checkIsCLassRegistered(mainWindowClass);

    mainWindow = CreateWindow(mainWindowClass.lpszClassName, L"Кондиционер", WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_THICKFRAME | WS_MINIMIZEBOX | WS_MAXIMIZEBOX,
                              (screenWidth - mainWindowWidth) / 2, (screenHeight - mainWindowHeight) / 2, mainWindowWidth, mainWindowHeight, NULL, NULL, hInst, NULL);

    checkIsWindowCreated(mainWindow);

    ShowWindow(mainWindow, nCommandShow);

    while (GetMessage(&uMsg, NULL, NULL, NULL)) {
        TranslateMessage(&uMsg);
        DispatchMessage(&uMsg);
    }
    return uMsg.wParam;
}