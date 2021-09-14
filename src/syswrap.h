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
#include <filesystem>
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

#define PLATFORM_WINDOWS
#include <windows.h>
#include <conio.h>
HANDLE wHnd;
HANDLE rHnd;

#endif

using std::string;
namespace fs = std::filesystem;
using fs::path;

// GLOBAL VALUES, DO NOT MODIFY UNLESS NEEDED
#define WINDOW_WIDTH 80
#define WINDOW_HEIGHT 35


namespace PlatformSystem
{

#if defined(PLATFORM_LINUX)

#elif defined(PLATFORM_WINDOWS)
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

#endif

	void SetupDrawing()
	{
		#if defined(PLATFORM_LINUX)
			initscr();
			raw();
			keypad(stdscr, TRUE);
			noecho();
            curs_set(FALSE);
			// TODO: SETUP AN NCURSES WINDOW WITH WINDOW_WIDTH AND WINDOW_HEIGHT



		#elif defined(PLATFORM_WINDOWS)
			wHnd = GetStdHandle(STD_OUTPUT_HANDLE);
			rHnd = GetStdHandle(STD_INPUT_HANDLE);
			SetConsoleTitle(TEXT("some-rpg"));

			/* Set the window size */
			SetConsoleWindowInfo(wHnd, TRUE, &windowSize);
			/* Set the screen's buffer size */
			SetConsoleScreenBufferSize(wHnd, bufferSize);

			//for (int y = 0; y < WINDOW_HEIGHT; ++y)
			//{
			//	for (int x = 0; x < WINDOW_WIDTH; ++x)
			//	{
			//		consoleBuffer[x + WINDOW_WIDTH * y].Char.AsciiChar = (unsigned char)219;
			//		consoleBuffer[x + WINDOW_WIDTH * y].Attributes = rand() % 256;
			//	}
			//}


			/* Write our character buffer (a single character currently) to the console buffer */
			//WriteConsoleOutputA(wHnd, consoleBuffer, characterBufferSize, characterPosition, &consoleWriteArea);

		#endif
	}

	void MoveCursor(int x, int y)
	{
        #if defined(PLATFORM_LINUX)
            move(y, x);
        #endif // defined
	}

	void DrawAt(char chToDraw, int x, int y)
	{
		#if defined(PLATFORM_LINUX)
			// use ncurses to compile and draw
			mvaddch(y, x, chToDraw);

		#elif defined(PLATFORM_WINDOWS)
			// use WIN API to compile and draw
			consoleBuffer[x + WINDOW_WIDTH * y].Char.AsciiChar = chToDraw;
		#endif
	}

    #if defined(PLATFORM_LINUX)
    void DrawAt(char chToDraw, int x, int y, chtype attr)
    {
        mvaddch(y, x, chToDraw | attr);
    }

    #endif // defined

	void DrawString(string st, int x, int y)
	{
	    //lazy, would probably just use printw
	}

	#if defined(PLATFORM_LINUX)
        typedef std::unordered_map<int, bool> LinuxKeyMap;
        LinuxKeyMap linuxKeys;
        LinuxKeyMap linuxKeysJustDown;
	#elif defined(PLATFORM_WINDOWS)
		typedef std::unordered_map<WORD, bool> WindowsKeyMap;
        WindowsKeyMap windowsKeyMapOldFrame;
		WindowsKeyMap windowsKeyMapNewFrame;
	#endif

	void ReadInput()
	{
		#if defined(PLATFORM_LINUX)
			int ch = getch();
            linuxKeysJustDown[ch] = true;
		#elif defined(PLATFORM_WINDOWS)
			DWORD numEventsRead = GetInput(&eventBuffer);

			if (numEventsRead)
			{
				for (int i = 0; i < numEventsRead; ++i)
				{
					if (eventBuffer[i].EventType == KEY_EVENT)
					{
						windowsKeyMapNewFrame[eventBuffer[i].Event.KeyEvent.wVirtualKeyCode] = eventBuffer[i].Event.KeyEvent.bKeyDown;
					}
				}
				free(eventBuffer);
			}
		#endif

	}

	/**

	*/
	void Render()
	{
		#if defined(PLATFORM_LINUX)
			refresh();
		#elif defined(PLATFORM_WINDOWS)
			WriteConsoleOutputA(wHnd, consoleBuffer, characterBufferSize, characterPosition, &consoleWriteArea);
		#endif
	}

	bool IsKeyPressed(int ch)
	{
	    #if defined (PLATFORM_LINUX)
	    return linuxKeysJustDown[ch];
        #elif defined (PLATFORM_WINDOWS)
        // something to go here on dinwows
        #endif
	}

	void NewFrame()
	{
	    #if defined (PLATFORM_LINUX)
	    clear();
	    #endif
	}

	void EndFrame()
	{
        #if defined(PLATFORM_LINUX)
            // TODO: maybe correct this?
            for (auto& key : linuxKeysJustDown)
            {
                linuxKeys[key.first] = key.second;
                key.second = false;
            }
        #elif defined(PLATFORM_WINDOWS)

        #endif
	}
}
#endif // SYSWRAP_H
