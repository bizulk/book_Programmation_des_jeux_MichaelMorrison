/** Application main entry point
 *  The application will call the Game Engine initialization and forward to it event
 *  The game app functions are directly called from here.
 *  @warning The author is aware this implementation is not compliante with object oriented design.
 * 
*/

// Includes
#include <iostream>
#include "gameengine.hpp"
#include "gameapp.hpp"

// Globals Declaration



/// @brief Control main loop execution
static volatile BOOL _bLoop = TRUE;

// Global Functions
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR szCmdLine, int iCmdShow) {

    MSG msg = {0};

    // Use to control application cycle execution
    static int iTickTrigger = 0;
    int         iTickCount;

    (void)hPrevInstance;
    (void)szCmdLine;
    
    if( !GameInitialize(hInstance) )
    {
        GameEnd();
        return TRUE;
    }

    if( ! GameEngine::GetEngine()->Initialize(iCmdShow))
    {
        return FALSE;
    }

    // Enter the main message loop
    while (_bLoop)
    {
        // FIXME: Author move from GetMessage to PeekMessage without explanation
        // I guessed it is a non blocking function to allow Game Cycle execution
        if( PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) )
        {
            // Process the message
            if( msg.message == WM_QUIT)
                break;
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        else
        {
            if( !GameEngine::GetEngine()->GetSleep() )
            {
                // Manage game lifecycle Using the system tick
                iTickCount = GetTickCount();
                if( iTickCount > iTickTrigger)
                {
                    iTickTrigger = iTickCount + GameEngine::GetEngine()->GetFrameDelay();
                    GameCycle();
                }
            }
        }
    }
    // Will return this in case WM_QUIT
    return (int)msg.wParam;
}
