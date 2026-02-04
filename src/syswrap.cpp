#include "syswrap.h"

void PlatformSystem::SetupDrawing()
{
#ifdef PLATFORM_LINUX
	initscr();
	raw();
	keypad(stdscr, TRUE);
	noecho();
	curs_set(FALSE);
	cbreak();
	timeout(0);
	
	if (has_colors())
		start_color();

	// TODO: ncurses color pairs


	// TODO: SETUP AN NCURSES WINDOW WITH WINDOW_WIDTH AND WINDOW_HEIGHT
	mainWindow = newwin(WINDOW_WIDTH, WINDOW_HEIGHT, 0, 0);
#endif
#ifdef PLATFORM_WINDOWS
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
			consoleBuffer[x + WINDOW_WIDTH * y].Attributes = COL_WHT;
		}
	}
	WriteConsoleOutputA(wHnd, consoleBuffer, characterBufferSize, characterPosition, &consoleWriteArea);

#endif
}

void PlatformSystem::Clear()
{
#ifdef PLATFORM_LINUX

#endif
#ifdef PLATFORM_WINDOWS
	CHAR_INFO clear;
	clear.Char.AsciiChar = ' ';
	clear.Attributes = COL_WHT;
	std::fill(std::begin(consoleBuffer), std::end(consoleBuffer), clear);
#endif
}

void PlatformSystem::DrawAt(char chToDraw, int x, int y)
{
	// this if check is to see if the whole string would fit within the window
	if (x >= WINDOW_WIDTH || x < 0 || y >= WINDOW_HEIGHT || y < 0)
	{
		return;
	}
#ifdef PLATFORM_LINUX
	// use ncurses to compile and draw
	mvaddch(y, x, chToDraw);
#endif
#ifdef PLATFORM_WINDOWS
	// use WIN API to compile and draw
	consoleBuffer[y * WINDOW_WIDTH + x].Char.AsciiChar = chToDraw;
#endif
}

void PlatformSystem::DrawAt(char chToDraw, int color, int x, int y)
{
#ifdef PLATFORM_LINUX
	// TODO: ncurses
#endif
#ifdef PLATFORM_WINDOWS
	consoleBuffer[y * WINDOW_WIDTH + x].Char.AsciiChar = chToDraw;
	consoleBuffer[y * WINDOW_WIDTH + x].Attributes = color;
#endif
}

void PlatformSystem::DrawString(string st, int x, int y)
{
#ifdef PLATFORM_LINUX
	for (ssize_t i = 0; i < st.length(); ++i)
	{
		mvaddch(y, x + i, st[i]);
	}
#endif
#ifdef PLATFORM_WINDOWS
	// TODO: THIS
	for (size_t i = 0; i < st.length(); ++i)
	{
		DrawAt(st[i], x + i, y);
	}
#endif
}

//TODO: POSSIBLE REDO KEY HANDLING FOR LINUX SIDE
void PlatformSystem::ReadInput()
{
#ifdef PLATFORM_LINUX
	int ch;
	while ((ch = getch()) != ERR)
		linuxKeysJustDown[ch] = true;
#endif
#ifdef PLATFORM_WINDOWS
	// what the heck was i doing with this back then this looks vibe-coded as hayle :wilted_rose:

#endif
}

void PlatformSystem::Render()
{
#ifdef PLATFORM_LINUX
	refresh();
#endif
#ifdef PLATFORM_WINDOWS
	WriteConsoleOutputA(wHnd, consoleBuffer, characterBufferSize, characterPosition, &consoleWriteArea);
#endif
}


bool PlatformSystem::IsKeyPressed(int ch)
{
#ifdef PLATFORM_LINUX
	return linuxKeysJustDown[ch];
#endif
#ifdef PLATFORM_WINDOWS

	int chr = ch;
	if (chr >= 65 && chr <= 90)
	{
		chr += 32;
	}
	else if (chr >= 97 && chr <= 122)
	{
		chr -= 32;
	}

	return ((GetAsyncKeyState(chr) & 0x8001) != 0);
	//return windowsKeyMapOldFrame[ch] != windowsKeyMapNewFrame[ch];
#endif
}


void PlatformSystem::NewFrame()
{
#ifdef PLATFORM_LINUX
	clear();
#endif
#ifdef PLATFORM_WINDOWS
	// something to go here on dinwows
	// GetInput();
#endif
}

void PlatformSystem::EndFrame()
{
#ifdef PLATFORM_LINUX
	// TODO: maybe correct this?
	for (auto& key : linuxKeysJustDown)
	{
		linuxKeys[key.first] = key.second;
		key.second = false;
	}
#endif
#ifdef PLATFORM_WINDOWS

#endif
}

void PlatformSystem::ExitGame()
{
#ifdef PLATFORM_LINUX
	endwin();
#endif
#ifdef PLATFORM_WINDOWS
	// TODO: WINDOWS CLEANUP
#endif
}
