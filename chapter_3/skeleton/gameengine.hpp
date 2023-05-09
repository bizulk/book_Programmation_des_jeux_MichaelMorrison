#ifndef __GAME_ENGINE__
#define __GAME_ENGINE__

#include <windows.h>


/// @brief Manage WinAPI abstraction to create window application and Event Engine
class GameEngine
{

public:
    /// @brief Game engine constructor
    /// Limit to create the object and initialize members
    /// @param hInstance Windows application instance
    /// @param szWindowClass window class name
    /// @param szTitle window title
    /// @param wIcon window icon
    /// @param wSmallIcon window small Icon
    /// @param iWidth window width 
    /// @param iEight window eight
    GameEngine(HINSTANCE hInstance, LPSTR szWindowClass, LPSTR szTitle, WORD wIcon, WORD wSmallIcon, int iWidth = 640, int iEight = 480);

    // Destructor
    virtual ~GameEngine();

    /// @brief Accessor to instance
    /// @return instance
    /// @note need better singleton init.
    static GameEngine * GetEngine() { return m_pGameEngine;}

    /// @brief FIXME This inits the window intialization
    BOOL Initialize( int iCmdShow);

    /// @brief Window Event Handler encapsulation for 
    /// @param hWindow 
    /// @param msg 
    /// @param wPAram 
    /// @param lParam 
    /// @return 
    LRESULT HandleEvent(HWND hWindow, UINT msg, WPARAM wPAram, LPARAM lParam);

    HINSTANCE   GetInstance(){ return m_hInstance; }
    HWND        GetWindow(){ return m_hWindow; }
    void        SetWindow(HWND hWindow){ m_hWindow = hWindow; }
    LPTSTR      GetTitle(){ return m_szTitle; }
    WORD        GetIcon(){ return m_wIcon; };
    WORD        GetSmallIcon(){ return m_wSmallIcon; }
    int         GetWidth() { return m_iWidth; }
    int         GetHeight() { return m_iHeight; }
    int         GetFrameDelay() { return m_iFrameDelay; }
    void        SetFrameRate(int iFrameRate){ m_iFrameDelay = 1000  / iFrameRate; }
    BOOL        GetSleep() { return m_bSleep; }
    void        SetSleep(BOOL bSleep) { m_bSleep = bSleep;}
    
protected:
        
    /// @brief Unique game engine instance
    static GameEngine * m_pGameEngine;
    HINSTANCE           m_hInstance;
    HWND                m_hWindow;
    TCHAR               m_szWindowClass[32];
    TCHAR               m_szTitle[32];
    WORD                m_wIcon, m_wSmallIcon;
    int                 m_iWidth, m_iHeight;
    int                 m_iFrameDelay;
    BOOL                m_bSleep;
};
#endif