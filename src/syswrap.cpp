#include "syswrap.h"
/**

*/
void PlatformSystem::SetupDrawing()
{
#if defined(PLATFORM_LINUX)
	initscr();
	raw();
	keypad(stdscr, TRUE);
	noecho();
	curs_set(FALSE);
	cbreak();
	timeout(0);
	// TODO: SETUP AN NCURSES WINDOW WITH WINDOW_WIDTH AND WINDOW_HEIGHT
	mainWindow = newwin(WINDOW_WIDTH, WINDOW_HEIGHT, 0, 0);

#elif defined(PLATFORM_WINDOWS)
	wHnd = GetStdHandle(STD_OUTPUT_HANDLE);
	rHnd = GetStdHandle(STD_INPUT_HANDLE);
	SetConsoleTitle(TEXT("some-rpg"));

	/* Set the window size */
	SetConsoleWindowInfo(wHnd, TRUE, &windowSize);
	/* Set the screen's buffer size */
	SetConsoleScreenBufferSize(wHnd, bufferSize);

	for (int y = 0; y < WINDOW_HEIGHT; ++y)
	{
		for (int x = 0; x < WINDOW_WIDTH; ++x)
		{
			consoleBuffer[x + WINDOW_WIDTH * y].Char.AsciiChar = (unsigned char)32;
			consoleBuffer[x + WINDOW_WIDTH * y].Attributes = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE;
		}
	}
	WriteConsoleOutputA(wHnd, consoleBuffer, characterBufferSize, characterPosition, &consoleWriteArea);

#endif
}
void PlatformSystem::DrawAt(char chToDraw, int x, int y)
{
	// this if check is to see if the whole string would fit within the window
	if (x >= WINDOW_WIDTH || x < 0 || y >= WINDOW_HEIGHT || y < 0)
	{
		return;
	}
#if defined(PLATFORM_LINUX)
	// use ncurses to compile and draw
	mvaddch(y, x, chToDraw);

#elif defined(PLATFORM_WINDOWS)
	// use WIN API to compile and draw
	consoleBuffer[y * WINDOW_WIDTH + x].Char.AsciiChar = chToDraw;
#endif
}
void PlatformSystem::DrawString(string st, int x, int y)
{
#if defined (PLATFORM_LINUX)
	for (ssize_t i = 0; i < st.length(); ++i)
	{
		mvaddch(y, x + i, st[i]);
	}
#elif defined (PLATFORM_WINDOWS)
	// TODO: THIS
	for (size_t i = 0; i < st.length(); ++i)
	{
		//mvaddch(y, x + i, st[i]);
		DrawAt(st[i], x + i, y);
	}
#endif
}

//TODO: POSSIBLE REDO KEY HANDLING FOR LINUX SIDE
void PlatformSystem::ReadInput()
{
#if defined(PLATFORM_LINUX)
	int ch;
	while ((ch = getch()) != ERR)
		linuxKeysJustDown[ch] = true;
#elif defined(PLATFORM_WINDOWS)
	// what the heck was i doing with this back then this looks vibe-coded as hayle :wilted_rose:

	//DWORD numEventsRead = GetInput(&eventBuffer);

	//if (numEventsRead)
	//{
	//	for (int i = 0; i < numEventsRead; ++i)
	//	{
	//		if (eventBuffer[i].EventType == KEY_EVENT)
	//		{
	//			windowsKeyMapNewFrame[eventBuffer[i].Event.KeyEvent.wVirtualKeyCode] = eventBuffer[i].Event.KeyEvent.bKeyDown;
	//		}
	//	}
	//	free(eventBuffer);
	//}


#endif

}
void PlatformSystem::Render()
{
#if defined(PLATFORM_LINUX)
	refresh();
#elif defined(PLATFORM_WINDOWS)
	WriteConsoleOutputA(wHnd, consoleBuffer, characterBufferSize, characterPosition, &consoleWriteArea);
#endif
}


bool PlatformSystem::IsKeyPressed(int ch)
{
#if defined (PLATFORM_LINUX)
	return linuxKeysJustDown[ch];
#elif defined (PLATFORM_WINDOWS)
	return ((GetAsyncKeyState(ch) & 0x8001) != 0);
	//return windowsKeyMapOldFrame[ch] != windowsKeyMapNewFrame[ch];
#endif
}


void PlatformSystem::NewFrame()
{
#if defined (PLATFORM_LINUX)
	clear();
#elif defined (PLATFORM_WINDOWS)
	// something to go here on dinwows
	// GetInput();
#endif
}

void PlatformSystem::EndFrame()
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

void PlatformSystem::ExitGame()
{
#if defined(PLATFORM_LINUX)
	endwin();
#elif defined(PLATFORM_WINDOWS)
	// TODO: WINDOWS CLEANUP
#endif
}
