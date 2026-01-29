#ifndef SYSWRAP_H
#define SYSWRAP_H
/**
    \file syswrap.h
    This header file contains wrapper functions
    for Linux and Windows.
    Since Windows uses a seperate comamnd line format
    from Linux, this file is used to provide
    funcctionality for both sides.
    The main issue lies in the fact that the Linux
    implementation utilizes a library called `ncurses`,
    whereas Windows uses their own API (`WinAPI`).
    `ncurses` has their own implementation of a
    "window", one that is different from Windows'.
    The functions are also completely different,
    with Windows utilizing double buffering to get
    their characters displayed onto the console,
    whereas Linux draws it directly.
*/

#include <iostream>
#include <vector>
#include <string>
#include <cstdint>
#include <cstdlib>
#include <fstream>
#include <random>
#include <ctime>
#include <unordered_map>

#include "mysysdef.h"

#ifdef PLATFORM_LINUX
// ncurses reference: https://pubs.opengroup.org/onlinepubs/7908799/xcurses/curses.h.html
// ref:
//		https://www.linuxjournal.com/content/creating-adventure-game-terminal-ncurses
//		https://www.viget.com/articles/game-programming-in-c-with-the-ncurses-library/

	#include <ncurses.h>
	#include <curses.h>

	#define COL_BLK COLOR_BLACK

	#define COL_RED COLOR_RED
	#define COL_GRN COLOR_GREEN
	#define COL_YLW COLOR_YELLOW

	#define COL_BLU COLOR_BLUE
	#define COL_MAG COLOR_MAGENTA
	#define COL_CYN COLOR_CYAN

	#define COL_WHT COLOR_WHITE
#endif
#ifdef PLATFORM_WINDOWS
// ref and/or src:
//		https://web.archive.org/web/20171205221811/https://www.randygaul.net/2012/07/03/windows-console-game-asciiengine/
//		https://web.archive.org/web/20171027152830/http://cecilsunkure.blogspot.com/2011/12/windows-console-game-painters-algorithm.html
//		https://github.com/RandyGaul/AsciiEngine/tree/master/AsciiEngine
//		https://www.benryves.com/tutorials/winconsole/

	#include <windows.h>
	#include <conio.h>

	#define COL_BLK 

	#define COL_RED FOREGROUND_RED
	#define COL_GRN FOREGROUND_GREEN 
	#define COL_BLU FOREGROUND_BLUE

	#define COL_MAG COL_RED | COL_BLU
	#define COL_YLW COL_RED | COL_GRN
	#define COL_CYN COL_BLU | COL_GRN

	#define COL_WHT COL_RED | COL_GRN | COL_BLU

#endif

using std::string;

// GLOBAL VALUES, DO NOT MODIFY UNLESS NEEDED
// WIDTH AND HEIGHT ARE BASED ON NUMBER OF CHARACTERS
#define WINDOW_WIDTH 80
#define WINDOW_HEIGHT 35

/**
	\class PlatformSystem
	\brief asdf
*/
class PlatformSystem
{
private:

	// PlatformSystem(const PlatformSystem& copy) = delete;
	// PlatformSystem& operator=(const PlatformSystem& copy) = delete;

public:

	PlatformSystem()
	{
	}
	// static PlatformSystem& Get()
	// {
	// 	static PlatformSystem p;
	// 	return p;
	// }

#if defined(PLATFORM_LINUX)
	WINDOW* mainWindow = nullptr;
        typedef std::unordered_map<int, bool> LinuxKeyMap;
        LinuxKeyMap linuxKeys;
        LinuxKeyMap linuxKeysJustDown;

#elif defined(PLATFORM_WINDOWS)
	HANDLE wHnd;
	HANDLE rHnd;
	SMALL_RECT windowSize = { 0, 0, WINDOW_WIDTH - 1, WINDOW_HEIGHT - 1 };
	COORD bufferSize = { WINDOW_WIDTH, WINDOW_HEIGHT };
	COORD characterBufferSize = { WINDOW_WIDTH, WINDOW_HEIGHT };
	COORD characterPosition = { 0, 0 };
	SMALL_RECT consoleWriteArea = { 0, 0, WINDOW_WIDTH - 1, WINDOW_HEIGHT - 1 };
	CHAR_INFO consoleBuffer[WINDOW_WIDTH * WINDOW_HEIGHT];

	typedef std::unordered_map<WORD, bool> WindowsKeyMap;
	WindowsKeyMap windowsKeyMapOldFrame;
	WindowsKeyMap windowsKeyMapNewFrame;

#endif
	/**
	* 
	*/
	void SetupDrawing();

	/**
	*
	*/
	void DrawAt(char chToDraw, int x, int y);
	
	/**
	*
	*/
	void DrawAt(char chToDraw, int fgColor, int x, int y);
	
	/**
	*
	*/
	void DrawAt(char chToDraw, int fgColor, int bgColor, int x, int y);
	
	/**
	*
	*/
	void DrawString(string st, int x, int y);


	/**
	* 
	*/
	void ReadInput();
	
	/**
	*
	*/
	void Render();

	/**
	*
	*/
	bool IsKeyPressed(int ch);

	/**
	*
	*/
	void NewFrame();

	/**
	*
	*/
	void EndFrame();

	/**
	*
	*/
	void ExitGame();
};
#endif // SYSWRAP_H
