//#include<iostream>
//#include<conio.h>
//#include<Windows.h>
//#include<string>
//#include "ConsoleCursor.cpp"
//#define KEY_UP 72
//#define KEY_DOWN 80
//#define KEY_LEFT 75
//#define KEY_RIGHT 77
//using namespace std;
//
//class UI
//{
//private:
//	int width, height;
//	HANDLE hOutput = GetStdHandle(STD_OUTPUT_HANDLE);
//	CONSOLE_SCREEN_BUFFER_INFO ConsoleScreenBufferInfo;
//	CONSOLE_SCREEN_BUFFER_INFOEX DefaultConsoleScreenBufferInfo;
//	DWORD dwWritten;
//	SMALL_RECT windowSize;
//	BOOL ForceDraw = true, Exit = false;
//	COORD CursorCurrentPos;
//	BOOL StartSelected = true;
//	CONSOLE_FONT_INFOEX ConsoleDefaultFontsInfoEx;
//	CONSOLE_CURSOR_INFO ConCurInfo;
//	MainClass MC = MainClass(char(178), char(153), char(154), char(219));
//
//public:
//	UI()
//	{		
//		GetConsoleScreenBufferInfoEx(hOutput, &DefaultConsoleScreenBufferInfo);
//		GetCurrentConsoleFontEx(hOutput, true, &ConsoleDefaultFontsInfoEx);
//		MC.SetFonts(15, 15);
//		MC.HideCursor();
//	}
//	//Shows Start menu of the Snake Game
//	void StartMenu()
//	{
//		MaximizeWindow();
//		InitWindowSize();
//		MC.ClearScreen();
//		while (!Exit)
//		{
//			if (WindowSizeChanged() || ForceDraw)
//			{
//				SetConsoleCursorInfo(hOutput, &ConCurInfo);
//				HighLightStart();
//				HighLightExit();
//				ForceDraw = false;
//			}
//				if (_kbhit())
//					CheckUserInput();
//		}
//		ResetConsoleConfigs();
//	}
//	//Highlights Start option
//	void HighLightStart()
//	{
//		MC.SetFonts(15, 15);
//		MC.ClearScreen();
//		SetConsoleCursorPosition(hOutput, GetMiddleOfTheScreen(width, height, "START"));
//		GetConsoleScreenBufferInfo(hOutput, &ConsoleScreenBufferInfo);
//		CursorCurrentPos = ConsoleScreenBufferInfo.dwCursorPosition;
//		cout << "START";
//		if (StartSelected)
//			FillConsoleOutputAttribute(hOutput, FOREGROUND_GREEN | BACKGROUND_BLUE, 5, GetMiddleOfTheScreen(width, height, "START"), &dwWritten);
//		else
//			FillConsoleOutputAttribute(hOutput, FOREGROUND_GREEN, 5, GetMiddleOfTheScreen(width, height, "START"), &dwWritten);
//	}
//	//Highlights Exit option
//	void HighLightExit()
//	{
//		SetConsoleCursorPosition(hOutput, COORD{ CursorCurrentPos.X, CursorCurrentPos.Y + 1 });
//		cout << "EXIT";
//		if (StartSelected)
//			FillConsoleOutputAttribute(hOutput, FOREGROUND_GREEN, 4, COORD{ CursorCurrentPos.X, CursorCurrentPos.Y + 1 }, &dwWritten);
//		else
//			FillConsoleOutputAttribute(hOutput, FOREGROUND_GREEN | BACKGROUND_BLUE, 4, COORD{ CursorCurrentPos.X, CursorCurrentPos.Y + 1 }, &dwWritten);
//	}
//	//Checks for user input
//	void CheckUserInput()
//	{
//		int key = _getch();
//		if (key == 'w' || key == 'W' || key == KEY_UP)
//		{
//			StartSelected = true;
//			ForceDraw = true;
//		}
//		if (key == 's' || key == 'S' || key == KEY_DOWN)
//		{
//			StartSelected = false;
//			ForceDraw = true;
//		}
//		if (key == '\x0D')
//		{
//			StartOrExitGame();
//		}
//
//	}
//	//Starts Game
//	void StartOrExitGame()
//	{
//		if (StartSelected)
//		{
//			SetConsoleCursorPosition(hOutput, GetMiddleOfTheScreen(width, height, "START"));
//			cout << "START";
//			FillConsoleOutputAttribute(hOutput, FOREGROUND_GREEN | BACKGROUND_RED, 5, GetMiddleOfTheScreen(width, height, "START"), &dwWritten);
//			MC.StartGame();
//		}
//		else
//		{
//			SetConsoleCursorPosition(hOutput, COORD{ CursorCurrentPos.X, CursorCurrentPos.Y + 1 });
//			cout << "EXIT";
//			FillConsoleOutputAttribute(hOutput, FOREGROUND_GREEN | BACKGROUND_RED, 4, COORD{ CursorCurrentPos.X, CursorCurrentPos.Y + 1 }, &dwWritten);
//			cout << endl << "Exitted Game";
//			MC.SetFonts(12, 17);
//			Exit = true;
//		}
//	}
//	//Maximizes Window
//	void MaximizeWindow()
//	{
//		HWND hWnd;
//		SetConsoleTitle(_T("Snake Game"));
//		Sleep(40);
//		hWnd = FindWindow(NULL, _T("Snake Game"));
//		HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
//		COORD NewSBSize = GetLargestConsoleWindowSize(hOut);
//		SMALL_RECT DisplayArea = { 0, 0, 0, 0 };
//		SetConsoleScreenBufferSize(hOut, NewSBSize);
//		DisplayArea.Right = NewSBSize.X - 1;
//		DisplayArea.Bottom = NewSBSize.Y - 1;
//		SetConsoleWindowInfo(hOut, TRUE, &DisplayArea);
//		ShowWindow(hWnd, SW_MAXIMIZE);
//	}
//	//Initializes WindowSize
//	void InitWindowSize()
//	{
//		GetConsoleScreenBufferInfo(hOutput, &ConsoleScreenBufferInfo);
//		this->width = ConsoleScreenBufferInfo.dwSize.X;
//		this->height = ConsoleScreenBufferInfo.srWindow.Bottom;
//		windowSize = ConsoleScreenBufferInfo.srWindow;
//	}
//	//Reset Configs
//	void ResetConsoleConfigs()
//	{
//		GetConsoleCursorInfo(hOutput, &ConCurInfo);
//		ConCurInfo.bVisible = true;
//		SetConsoleCursorInfo(hOutput, &ConCurInfo);
//		SetConsoleScreenBufferInfoEx(hOutput, &DefaultConsoleScreenBufferInfo);
//		
//	}
//	
//	//Reurns true if Window size changed.
//	BOOL WindowSizeChanged()
//	{
//		GetConsoleScreenBufferInfo(hOutput, &ConsoleScreenBufferInfo);
//		if (windowSize.Bottom == ConsoleScreenBufferInfo.srWindow.Bottom && windowSize.Left == ConsoleScreenBufferInfo.srWindow.Left && windowSize.Right == ConsoleScreenBufferInfo.srWindow.Right && this->windowSize.Top == ConsoleScreenBufferInfo.srWindow.Top)
//			return false;
//		else
//		{
//			this->width = ConsoleScreenBufferInfo.dwSize.X;
//			this->height = ConsoleScreenBufferInfo.srWindow.Bottom;
//			windowSize = ConsoleScreenBufferInfo.srWindow;
//			MC.ClearScreen();
//			return true;
//		}
//	}
//	//Returns COORD for the middle of the screen for a string str
//	COORD GetMiddleOfTheScreen(int winWidth, int winHeight, string str)
//	{
//		COORD returnCOORD;
//		returnCOORD.X = winWidth / 2 - str.length();
//		returnCOORD.Y = winHeight / 2 - 1;
//		return returnCOORD;
//	}
//};
//int main()
//{
//	UI ui = UI();
//	ui.StartMenu();
//}
