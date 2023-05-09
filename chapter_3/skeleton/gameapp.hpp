#ifndef __GAME_APP__
#define __GAME_APP__
/**
 * Application must implement these functions called by underlying engine and winmain
 *  
*/
#include <windows.h>

/// @brief Call Application initialization, responsible to Init Engine with application data
/// @param hInstance 
/// @return TRUE is succeed
BOOL GameInitialize(HINSTANCE hInstance);

void GameStart(HWND hWindow);
/// @brief App function for cycle execution
/// @note no hWindow handler. Probably not intended here cf GamePaint()
void GameCycle(void);
/// @brief App function  for ending application
void GameEnd(void);

void GamePaint(HDC hDC);

/// @brief Application is notified when window is activated or not
/// @param hWindow 
void GameActivate(HWND hWindow);
void GameDeactivate(HWND hWindow);

#endif