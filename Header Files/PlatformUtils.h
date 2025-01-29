#pragma once

#ifdef _WIN32
    #include <windows.h>
    #include <conio.h>
#else
    #include <termios.h>
    #include <unistd.h>
    
    // Declare _getch for Unix systems
    int _getch();
#endif

// Key definitions
#ifdef _WIN32
    #define KEY_UP 72
    #define KEY_DOWN 80
    #define KEY_LEFT 75
    #define KEY_RIGHT 77
    #define KEY_ENTER 13
    #define KEY_ESC 27
#else
    #define KEY_UP 'w'
    #define KEY_DOWN 's'
    #define KEY_LEFT 'a'
    #define KEY_RIGHT 'd'
    #define KEY_ENTER 10
    #define KEY_ESC 27
#endif

// Platform-independent helper functions
void ClearScreen();
void CursorAppear(bool visible);
void Sleep(unsigned int milliseconds);

// Console color functions
void SetConsoleColor(bool highlighted);
void ResetConsoleColor(); 