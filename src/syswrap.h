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

#if defined(__unix__)
// ncurses reference: https://pubs.opengroup.org/onlinepubs/7908799/xcurses/curses.h.html
// ref:
//		https://www.linuxjournal.com/content/creating-adventure-game-terminal-ncurses
//		https://www.viget.com/articles/game-programming-in-c-with-the-ncurses-library/

#define PLATFORM_LINUX
#include <ncurses.h>
#include <curses.h>

#elif defined(_WIN32)
// ref and/or src:
//		https://www.randygaul.net/2012/07/03/windows-console-game-asciiengine/
//		https://www.benryves.com/tutorials/winconsole/

#define PLATFORM_WINDOWS
#include <windows.h>
#include <conio.h>

#endif

using std::string;

// GLOBAL VALUES, DO NOT MODIFY UNLESS NEEDED
// WIDTH AND HEIGHT ARE BASED ON NUMBER OF CHARACTERS
#define WINDOW_WIDTH 80
#define WINDOW_HEIGHT 35

/**
	\class PlatformSystem
	A Singleton class to abstract away functions to work on either platforms.
*/
class PlatformSystem
{
private:
	PlatformSystem()
	{
	}

	PlatformSystem(const PlatformSystem& copy) = delete;
	PlatformSystem& operator=(const PlatformSystem& copy) = delete;

public:

	static PlatformSystem& Get()
	{
		static PlatformSystem p;
		return p;
	}

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
	/* A CHAR_INFO structure containing data about a single character */
	CHAR_INFO consoleBuffer[WINDOW_WIDTH * WINDOW_HEIGHT];

	INPUT_RECORD* eventBuffer;

	/* Read console input buffer and return malloc'd INPUT_RECORD array */
	DWORD GetInput(INPUT_RECORD** eventBuffer)
	{
		/* Variable for holding the number of current events, and a point to it */
		DWORD numEvents = 0;

		/* Variable for holding how many events were read */
		DWORD numEventsRead = 0;

		/* Put the number of console input events into numEvents */
		GetNumberOfConsoleInputEvents(rHnd, &numEvents);

		if (numEvents) /* if there's an event */
		{
			/* Allocate the correct amount of memory to store the events */
			*eventBuffer = (INPUT_RECORD*)malloc(sizeof(INPUT_RECORD) * numEvents);
			/* Place the stored events into the eventBuffer pointer */
			ReadConsoleInput(rHnd, *eventBuffer, numEvents, &numEventsRead);
		}
		/* Return the amount of events successfully read */
		return numEventsRead;
	}
	typedef std::unordered_map<WORD, bool> WindowsKeyMap;
	WindowsKeyMap windowsKeyMapOldFrame;
	WindowsKeyMap windowsKeyMapNewFrame;

#endif

	void SetupDrawing();
	void DrawAt(char chToDraw, int x, int y);
	void DrawString(string st, int x, int y);

	void ReadInput();
	void Render();
	bool IsKeyPressed(int ch);
	void NewFrame();
	void EndFrame();
	void ExitGame();
};
#endif // SYSWRAP_H
