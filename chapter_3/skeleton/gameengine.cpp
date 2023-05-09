#include "gameengine.hpp"
#include "gameapp.hpp"


LRESULT CALLBACK WndProc(HWND hWindow, UINT msg, WPARAM wParam, LPARAM lParam);

GameEngine * GameEngine::m_pGameEngine = NULL;

GameEngine::GameEngine(HINSTANCE hInstance, LPSTR szWindowClass, LPSTR szTitle, WORD wIcon, WORD wSmallIcon, int iWidth, int iHeight)
{
    m_pGameEngine = this;
    m_hInstance = hInstance;
    m_hWindow = NULL;
    if( lstrlen(szWindowClass) > 0)
    {
        lstrcpy(m_szWindowClass, szWindowClass);
    }
    if( lstrlen(m_szTitle) > 0)
    {
        lstrcpy(m_szTitle, szTitle);
    }
    m_wIcon = wIcon;
    m_wSmallIcon = wSmallIcon;
    m_iWidth = iWidth;
    m_iHeight = iHeight;
    m_iFrameDelay = 50; // 20 FPS default
    m_bSleep = TRUE;
}

GameEngine::~GameEngine()
{
}

BOOL GameEngine::Initialize(int iCmdShow)
{
    WNDCLASSEX  wndclass;
 
    // Create the window class for the main window
    wndclass.cbSize         = sizeof(wndclass);
    wndclass.style          = CS_HREDRAW | CS_VREDRAW;
    // We cannot directly use out game engine event handler, it must be global context
    wndclass.lpfnWndProc    = WndProc;
    wndclass.cbClsExtra     = 0;
    wndclass.cbWndExtra     = 0;
    wndclass.hInstance      = m_hInstance;
    wndclass.hIcon          = LoadIcon(m_hInstance, MAKEINTRESOURCE(GetIcon()) );
    wndclass.hIconSm        = LoadIcon(m_hInstance, MAKEINTRESOURCE(GetSmallIcon()));
    wndclass.hCursor        = LoadCursor(NULL, IDC_ARROW);
    wndclass.hbrBackground  = (HBRUSH)(COLOR_WINDOW + 1);
    wndclass.lpszMenuName   = NULL;
    wndclass.lpszClassName  = m_szWindowClass;

    // Register the window class
    if( !RegisterClassEx(&wndclass))
        return FALSE;
    
    // Compute window dimension and position according to game dimensions

    // Window size is game size + frame border, and vertically we should add caption and menu if displayed
    int iWindowWidth = m_iWidth + GetSystemMetrics(SM_CXFIXEDFRAME) * 2;
    int iWindowHeight = m_iHeight + GetSystemMetrics(SM_CYFIXEDFRAME) * 2 + GetSystemMetrics(SM_CYCAPTION);
    if( wndclass.lpszMenuName != NULL)
    {
        iWindowHeight += GetSystemMetrics(SM_CYMENU);
    }

    // Center the window in the display
    int iXWindowPos = (GetSystemMetrics(SM_CXSCREEN) - iWindowWidth) / 2;
    int iYWindowPos = (GetSystemMetrics(SM_CYSCREEN) - iWindowHeight) / 2;

    // Create the window
    m_hWindow = CreateWindow(m_szWindowClass, m_szTitle,  WS_POPUPWINDOW | WS_CAPTION | WS_MINIMIZEBOX, 
                                                    iXWindowPos, iYWindowPos, iWindowWidth, iWindowHeight, 
                                                    NULL, NULL, m_hInstance, NULL);

    // Show and update the window
    ShowWindow(m_hWindow, iCmdShow);
    UpdateWindow(m_hWindow);
    return TRUE;
}

LRESULT GameEngine::HandleEvent(HWND hWindow, UINT msg, WPARAM wParam, LPARAM lParam)
{
    HDC         hDC;
    PAINTSTRUCT ps;

    // Process or redirect to game app function 
    switch(msg)
    {
        case WM_CREATE:
            // Configure window and start game
            SetWindow(hWindow);
            GameStart(hWindow);
            return 0;

        case WM_ACTIVATE:
            // (de)Activate game 
            if( wParam != WA_INACTIVE)
            {
                GameActivate(hWindow);
                // GameCycle will be executed
                SetSleep(FALSE);
            }
            else
            {
                GameDeactivate(hWindow);
                SetSleep(TRUE);
            }
            return 0;

        case WM_PAINT:
            // Draw some text centered in the main client area of the main window
            hDC = BeginPaint(hWindow, &ps);
            // Call game paint update
            GamePaint(hDC);
            EndPaint(hWindow, &ps);
            return 0;

        case WM_DESTROY:
            // end Game
            GameEnd();
            PostQuitMessage(0);
            return 0;
    }
    // Call default window handler
    return DefWindowProc(hWindow, msg, wParam, lParam);
}

LRESULT CALLBACK WndProc(HWND hWindow, UINT msg, WPARAM wParam, LPARAM lParam)
{
    // redirect everything to the engine event handler
    return GameEngine::GetEngine()->HandleEvent(hWindow, msg, wParam, lParam);
}
