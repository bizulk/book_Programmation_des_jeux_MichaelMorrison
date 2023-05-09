#include "gameapp.hpp"
#include "gameengine.hpp"
#include "skeleton.hpp"
#include "resource.hpp"

// Handle to the game engine
GameEngine* _pGame = NULL;

BOOL GameInitialize(HINSTANCE hInstance)
{
    // Create motor engine
    _pGame = new GameEngine(hInstance, TEXT("Game Skeleton"), TEXT("Game Skeleton"), IDI_SKELETON, IDI_SKELETON_SM);
    if( _pGame == NULL)
    {
        return FALSE;
    }

    // Adjust game cycle frequency
    _pGame->SetFrameRate(15);

    return TRUE;
}

void GameStart(HWND hWindow)
{
    UNUSED(hWindow);
    // Initialize random generator for the game cycle app
    srand(GetTickCount());
}

void GameEnd(void)
{
    // Clean
    delete _pGame;
}

void GameActivate(HWND hWindow)
{
    HDC hDC;
    RECT rect;

    // Notify activation on window
    GetClientRect( hWindow, &rect);
    hDC = GetDC(hWindow);

    // Need to clear the window area otherwise old characters remain
    HBRUSH hBrush = (HBRUSH)GetClassLongPtr(hWindow, GCLP_HBRBACKGROUND);
    FillRect(hDC, &rect, hBrush);
    DeleteObject(hBrush);

    DrawText(hDC, TEXT("Activated !"), -1, &rect, 
                DT_SINGLELINE | DT_CENTER | DT_VCENTER);
    ReleaseDC(hWindow, hDC);
}

void GameDeactivate(HWND hWindow)
{
    HDC hDC;
    RECT    rect;

    // Notify Deactivation
    GetClientRect( hWindow, &rect);
    hDC = GetDC(hWindow);

    // Need to clear the window area otherwise old characters remain
    HBRUSH hBrush = (HBRUSH)GetClassLongPtr(hWindow, GCLP_HBRBACKGROUND);
    FillRect(hDC, &rect, hBrush);
    DeleteObject(hBrush);

    DrawText(hDC, TEXT("Deactivated !"), -1, &rect, 
                DT_SINGLELINE | DT_CENTER | DT_VCENTER);
    ReleaseDC(hWindow, hDC);    
}

void GamePaint(HDC hDC)
{
    // nop
    UNUSED(hDC);
}

void GameCycle()
{
    HDC hDC;
    HWND hWindow = _pGame->GetWindow();
    // Randomly display sketelon
    hDC = GetDC(hWindow);
    HICON hIcon;


    // note : author did cast as (HICON)(WORD) but that is incorrect.
    hIcon = (HICON)GetClassLongPtr(hWindow, GCLP_HICON);
    if (hIcon == NULL) 
    {
        // Handle the error
        return;
    }
#ifdef DEBUG_ICON
    // Try loading image file that should be next to the binary
    hIcon = (HICON)LoadImage(NULL, "skeleton.ico", IMAGE_ICON, 0, 0, LR_LOADFROMFILE);
    if (hIcon == NULL)
    {
        // Handle the error
        DWORD error = GetLastError();
        (void)error;
        return;
    }
    // Get the window size
    RECT windowRect;
    GetClientRect(hWindow, &windowRect);

    // Get the icon size
    ICONINFO iconInfo;
    if( ! GetIconInfo(hIcon, &iconInfo) )
    {
        // Get the error code
        DWORD error = GetLastError();
        (void)error;
        // Handle the error
        return;
    }
    int iconWidth = iconInfo.xHotspot * 2;
    int iconHeight = iconInfo.yHotspot * 2;

    // Calculate the position to draw the icon
    int x = (windowRect.right - windowRect.left - iconWidth) / 2;
    int y = (windowRect.bottom - windowRect.top - iconHeight) / 2;

    // Draw the icon
    DrawIcon(hDC, x, y, hIcon); 
#else
    DrawIcon(   hDC, 
                rand() % _pGame->GetWidth(), 
                rand() % _pGame->GetHeight(), 
                hIcon);
#endif





    ReleaseDC(hWindow, hDC);
}