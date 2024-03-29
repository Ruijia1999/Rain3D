// Game.cpp : Defines the entry point for the application.
//

#include "framework.h"
#include "Game.h"
#include "Rain3DGame.h"
#include "Input/Mouse.h"
#include "Input/Keyboard.h"
#include "Application/Rain3DGame.h"
#define CRTDBG_MAP_ALLOC
#define MAX_LOADSTRING 100
namespace {
    Rain::Rain3DGame mainGame;
}
// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Place code here.

    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_GAME, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_GAME));

    MSG msg;

    // Main message loop:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_GAME));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_GAME);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Store instance handle in our global variable

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, 1600, 900, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);
   
   mainGame.Initialize(hWnd,1600, 900);
   return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE: Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Parse the menu selections:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: Add any drawing code that uses hdc here...
            EndPaint(hWnd, &ps);
        }
        break;
#pragma region Key
    case WM_KEYDOWN:
        Rain::Input::KeyBoard::OnKeyDown(wParam);
        break;
    case WM_KEYUP:
        Rain::Input::KeyBoard::OnKeyUp(wParam);
        break;
#pragma endregion
#pragma region Mouse
    case WM_MOUSEMOVE:
    {
        const POINTS pt = MAKEPOINTS(lParam);
         Rain::Input::Mouse::OnMouseMove(pt.x,pt.y);

        //// in client region -> log move, and log enter + capture mouse (if not previously in window)
        //if (pt.x >= 0 && pt.x < width && pt.y >= 0 && pt.y < height)
        //{
        //    Rain::Input::Mouse::OnMouseLeftUp(); mouse.OnMouseMove(pt.x, pt.y);
        //    if (!mouse.IsInWindow())
        //    {
        //        SetCapture(hWnd);
        //        mouse.OnMouseEnter();
        //    }
        //}
        //// not in client -> log move / maintain capture if button down
        //else
        //{
        //    if (wParam & (MK_LBUTTON | MK_RBUTTON))
        //    {
        //        mouse.OnMouseMove(pt.x, pt.y);
        //    }
        //    // button up -> release capture / log event for leaving
        //    else
        //    {
        //        ReleaseCapture();
        //        mouse.OnMouseLeave();
        //    }
        //}
        break;
    }
    case WM_LBUTTONDOWN:
    {
        const POINTS pt = MAKEPOINTS(lParam);
        Rain::Input::Mouse::OnMouseLeftDown();
        break;
    }
    case WM_RBUTTONDOWN:
    {

        const POINTS pt = MAKEPOINTS(lParam);
        Rain::Input::Mouse::OnMouseRightDown();
        break;
    }
    case WM_LBUTTONUP:
    {
        // stifle this mouse message if imgui wants to capture

        const POINTS pt = MAKEPOINTS(lParam);
        Rain::Input::Mouse::OnMouseLeftUp();
        // release mouse if outside of window
       /* if (pt.x < 0 || pt.x >= width || pt.y < 0 || pt.y >= height)
        {
            ReleaseCapture();
            mouse.OnMouseLeave();
        }*/
        break;
    }
    case WM_RBUTTONUP:
    {
        // stifle this mouse message if imgui wants to capture

        const POINTS pt = MAKEPOINTS(lParam);
        Rain::Input::Mouse::OnMouseRightDown();
        // release mouse if outside of window
        /*if (pt.x < 0 || pt.x >= width || pt.y < 0 || pt.y >= height)
        {
            ReleaseCapture();
            mouse.OnMouseLeave();
        }*/
        break;
    }
    //case WM_MOUSEWHEEL:
    //{
    //    // stifle this mouse message if imgui wants to capture

    //    const POINTS pt = MAKEPOINTS(lParam);
    //    const int delta = GET_WHEEL_DELTA_WPARAM(wParam);
    //    mouse.OnWheelDelta(pt.x, pt.y, delta);
    //    break;
    //}
#pragma endregion
    case WM_DESTROY:
        mainGame.ExitGame();
        PostQuitMessage(0);
        //_CrtDumpMemoryLeaks();
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
