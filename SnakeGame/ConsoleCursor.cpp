#include<iostream>
#include<conio.h>
#include<Windows.h>
#include<string>
#include "tchar.h"
#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77
using namespace std;
enum Direction { Up, Down, Right, Left };
class MainClass
{
private:
	int width, height, score, oldScore, snakeLength, snakePartPosX[50], snakePartPosY[50];
	char playerChar, fruitChar, borderChar, bodyChar;
	bool printDebug = false, pauseGame = false, isGameOver = false;

	Direction PlayerDir;
	COORD CursorCurrentPos, CursorDefaultPos, PlayerPos, FruitPos;
	HANDLE hOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO ConsoleScreenBufferInfo;
	SMALL_RECT windowSize;
	CONSOLE_FONT_INFOEX fonts;
	DWORD dwWritten;
	CONSOLE_CURSOR_INFO ConCurInfo;
public:
	//MainClass Constructor
	MainClass(char borChar, char PlChar, char fChar, char body)
	{
		borderChar = borChar;
		playerChar = PlChar;
		fruitChar = fChar;
		bodyChar = body;
		InitAll();
	}
	//Starts Game
	void StartGame()
	{
		InitAll();
		DrawMap();
		while (!isGameOver)
		{
			WindowSizeChanged();
			SpawnFruit(false);
			CheckUserInput();
			MovePlayer();
			MoveSnakeBody();
			CheckFruitSnakeCollid();
			CheckGameOver();
			if (ScoreChanged())
				DrawScore();
			Sleep(100);
		}
	}
	//Draws Map of the Game
	void DrawMap()
	{
		this->width = ConsoleScreenBufferInfo.dwSize.X - 1;
		this->height = ConsoleScreenBufferInfo.srWindow.Bottom - 5;
		ClearScreen();
		for (int H = 0; H < height; H++)
		{
			for (int W = 0; W < width; W++)
			{
				if (H == 0 || H == height - 1)
				{
					cout << borderChar;
				}
				else if (W == 0 || W == width - 1)
				{
					cout << borderChar;
				}
				else
					cout << char(32);
			}
			cout << endl;
		}
		DrawScore();
		SpawnFruit(true);
	}
	//Draws Score
	void DrawScore()
	{
		cout << '\r' << "SCORE: " << score;
		if (((score / 10) % 2 == 0) || score == 10 || score == 0)
		{
			FillConsoleOutputAttribute(hOutput, FOREGROUND_BLUE, 7 + to_string(score).length(),
				COORD{ CursorDefaultPos.X - (SHORT)(7 + (int)to_string(score).length()), CursorDefaultPos.Y }, &dwWritten);
		}
		else
		{
			FillConsoleOutputAttribute(hOutput, FOREGROUND_GREEN, 7 + to_string(score).length(),
				COORD{ CursorDefaultPos.X - (SHORT)(7 + (int)to_string(score).length()), CursorDefaultPos.Y }, &dwWritten);
		}
	}

	//Moves snake according to player input
	void DrawPlayer()
	{
		if (!isGameOver) {
			PrintAtXY(PlayerPos.X, PlayerPos.Y, string(1, playerChar));
			FillConsoleOutputAttribute(hOutput, FOREGROUND_GREEN | FOREGROUND_INTENSITY, 1, PlayerPos, &dwWritten);
		}
	}
	//Draws Fruit(Coin) according to COORD FruitPos
	void MovePlayer()
	{
		if (PlayerDir == Up) {
			PlayerPos.Y--;
		}
		if (PlayerDir == Down) {
			PlayerPos.Y++;
		}
		if (PlayerDir == Left) {
			PlayerPos.X--;
		}
		if (PlayerDir == Right) {
			PlayerPos.X++;
		}
		DrawPlayer();

	}
	//Draws snake's body
	void DrawSnakeBody()
	{
		if (!isGameOver)
		{
			for (int i = 0; i <= snakeLength; i++)
			{
				if (i != snakeLength)
				{
					if (snakePartPosX[i] != 0 && snakePartPosY[i] != 0)
					{
						if (i % 2 == 0)
						{
							PrintAtXY(snakePartPosX[i], snakePartPosY[i], string(1, bodyChar));
							FillConsoleOutputAttribute(hOutput, FOREGROUND_GREEN, 1, COORD{ (SHORT)snakePartPosX[i], (SHORT)snakePartPosY[i] }, &dwWritten);
						}
						else if (i % 3 == 0)
						{
							PrintAtXY(snakePartPosX[i], snakePartPosY[i], string(1, bodyChar));
							FillConsoleOutputAttribute(hOutput, FOREGROUND_BLUE, 1, COORD{ (SHORT)snakePartPosX[i], (SHORT)snakePartPosY[i] }, &dwWritten);
						}
						else
						{
							PrintAtXY(snakePartPosX[i], snakePartPosY[i], string(1, bodyChar));
							FillConsoleOutputAttribute(hOutput, FOREGROUND_RED, 1, COORD{ (SHORT)snakePartPosX[i], (SHORT)snakePartPosY[i] }, &dwWritten);
						}
					}
				}

				if (i == snakeLength)
					DrawBlank(snakePartPosX[i - 1], snakePartPosY[i - 1]);
			}
		}
	}
	//Moves snake's body begind its head
	void MoveSnakeBody()
	{
		int tempX = 1, tempY = 1, tempX1 = 1, tempY1 = 1;
		for (int i = 0; i < snakeLength; i++)
		{
			if (i == 0) {
				tempX = snakePartPosX[i];
				tempY = snakePartPosY[i];
				if (PlayerDir == Left)
				{
					snakePartPosX[i] = PlayerPos.X + 1;
					snakePartPosY[i] = PlayerPos.Y;
				}
				else if (PlayerDir == Right)
				{
					snakePartPosX[i] = PlayerPos.X - 1;
					snakePartPosY[i] = PlayerPos.Y;
				}
				else if (PlayerDir == Up)
				{
					snakePartPosX[i] = PlayerPos.X;
					snakePartPosY[i] = PlayerPos.Y + 1;
				}
				else if (PlayerDir == Down)
				{
					snakePartPosX[i] = PlayerPos.X;
					snakePartPosY[i] = PlayerPos.Y - 1;
				}
			}
			else {
				tempX1 = snakePartPosX[i];
				tempY1 = snakePartPosY[i];

				snakePartPosX[i] = tempX;
				snakePartPosY[i] = tempY;

				tempX = tempX1;
				tempY = tempY1;
			}
		}
		DrawSnakeBody();
	}
	//Check for user input
	void CheckUserInput()
	{
		if (_kbhit())
		{
			int key = _getch();
			if ((key == 'W' || key == 'w' || key == KEY_UP) && PlayerDir != Down)
				PlayerDir = Up;
			if ((key == 'S' || key == 's' || key == KEY_DOWN) && PlayerDir != Up)
				PlayerDir = Down;
			if ((key == 'D' || key == 'd' || key == KEY_RIGHT) && PlayerDir != Left)
				PlayerDir = Right;
			if ((key == 'A' || key == 'a' || key == KEY_LEFT) && PlayerDir != Right)
				PlayerDir = Left;
			else if (key == char(27))//Escape Key
			{
				GameOver("", true);
			}
			else if (key == char(32))//Spacebar key
			{
				PauseGame();
			}
		}
	}
	//Draws snake according to COORD PlayerPos
	void DrawFruit() {
		if (!isGameOver)
		{
			if (FruitPos.X < width && FruitPos.Y < height)
			{
				PrintAtXY(FruitPos.X, FruitPos.Y, string(1, fruitChar));
				FillConsoleOutputAttribute(hOutput, FOREGROUND_RED, 1, FruitPos, &dwWritten);
			}
			else
			{
				SpawnFruit(false);
			}
		}
	}
	//Spawns a fruit, randomly on the screen
	void SpawnFruit(BOOL ForceDraw)
	{
		if (ScoreChanged() || ForceDraw)
		{
			int a = (int)malloc(sizeof(int));
			srand(a);
			FruitPos.X = rand() % width - 1;
			FruitPos.Y = rand() % height - 1;
			if (FruitPos.X <= 1 || FruitPos.Y <= 1 || FruitPos.X > width - 1 || FruitPos.Y > height - 1)
				SpawnFruit(true);
			else
				DrawFruit();

		}
	}
	//Checks if player took the Fruit(Coin)
	void CheckFruitSnakeCollid()
	{
		if (FruitPos.X == PlayerPos.X && FruitPos.Y == PlayerPos.Y)
		{
			score += 10;
			snakeLength++;
			DrawScore();
			SpawnFruit(true);
		}
	}

	//Checks if game is over
	void CheckGameOver()
	{
		if (PlayerPos.X <= 0 || PlayerPos.X >= width - 1 || PlayerPos.Y <= 0 || PlayerPos.Y >= height - 1)
		{
			GameOver("You hit the wall", false);
		}
		else if (PlayerHitBody())
		{
			GameOver("You tried to eat yourself ?!", false);
		}
	}
	//Stops Game
	void GameOver(string reason, BOOL userExited)
	{
		isGameOver = true;
		if (!userExited)
		{
			SetFonts(13, 13);
			cout << endl << "GAME OVER!!" << endl << "Reason: " << reason << endl;
			cout << "Press Enter to Restart the Game, any other key to exit" << endl;
			int key = _getch();
			if (key == '\x0D')
				RestartGame();
			else {
				SendKeyEvent((WORD)0x57);
			}
		}
		else if (userExited)
		{
			cout << endl << "Exited!! " << endl << "Press Enter to Restart the Game, any other key to exit";
			int key = _getch();
			if (key == '\x0D')
				RestartGame();
			else
				SendKeyEvent((WORD)0x57);
		}
	}
	//Pauses Game
	void PauseGame()
	{
		string str = "GAME PAUSED!!Press any key to continue.";
		cout << str;		if (_getch())
		{
			for (int i = 0; i < (int)str.length(); i++)
			{
				DrawBlank(CursorDefaultPos.X - i, CursorDefaultPos.Y);
			}
			CursorDefaultPos.X -= (SHORT)str.length();
		}
	}
	//Restarts Game
	void RestartGame()
	{
		StartGame();
	}

	//Sets Cursor Position
	void SetCursorPos(int X, int Y)
	{
		InitOldCursorPos();
		CursorCurrentPos.X = X;
		CursorCurrentPos.Y = Y;
		SetConsoleCursorPosition(hOutput, CursorCurrentPos);
	}
	//Sets cursor poition at the end of the drawing
	void SetCursorDefaultPos()
	{
		SetConsoleCursorPosition(hOutput, CursorDefaultPos);
	}
	//Sets Font
	void SetFonts(int fWidth, int fHeight)
	{
		CONSOLE_FONT_INFOEX cfi;
		cfi.cbSize = sizeof cfi;
		cfi.nFont = 0;
		cfi.dwFontSize.X = fWidth;
		cfi.dwFontSize.Y = fHeight;
		cfi.FontFamily = FF_DONTCARE;
		cfi.FontWeight = FW_NORMAL;
		SetCurrentConsoleFontEx(hOutput, false, &cfi);
	}
	//Stores Cursor's Default Position in COORD CursorDefaultPos
	void InitOldCursorPos()
	{
		GetConsoleScreenBufferInfo(hOutput, &ConsoleScreenBufferInfo);
		CursorDefaultPos.X = ConsoleScreenBufferInfo.dwCursorPosition.X;
		CursorDefaultPos.Y = ConsoleScreenBufferInfo.dwCursorPosition.Y;
	}
	//Prints str to X, Y Coordinates
	void PrintAtXY(int X, int Y, string str)
	{
		SetCursorPos(X, Y);
		cout << str;
		SetCursorDefaultPos();
	}
	//Draws a space(blank) on X, Y coordinates
	void DrawBlank(int X, int Y)
	{
		if (X != 0 && Y != 0)
		{
			SetCursorPos(X, Y);
			cout << char(32);
			SetCursorDefaultPos();
		}
	}
	//Initializes All needed variables
	void InitAll()
	{
		SetFonts(13, 13);
		MaximizeWindow();
		InitWindowSize();
		HideCursor();
		snakeLength = 3;
		PlayerDir = Right;
		PlayerPos.X = 10;
		PlayerPos.Y = 10;
		score = 0;
		oldScore = 0;
		isGameOver = false;
		pauseGame = false;
		for (int i = 0; i < 50; i++)
		{
			snakePartPosX[i] = NULL;
			snakePartPosY[i] = NULL;
		}

	}
	//Initializes windowSize
	void InitWindowSize()
	{
		GetConsoleScreenBufferInfo(hOutput, &ConsoleScreenBufferInfo);
		this->width = ConsoleScreenBufferInfo.dwSize.X - 2;
		this->height = ConsoleScreenBufferInfo.srWindow.Bottom - 5;
		windowSize = ConsoleScreenBufferInfo.srWindow;
	}
	//Maximizes Window
	void MaximizeWindow()
	{
		HWND hWnd;
		SetConsoleTitle(_T("Snake Game"));
		hWnd = FindWindow(NULL, _T("Snake Game"));
		HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
		COORD NewSBSize = GetLargestConsoleWindowSize(hOut);
		SMALL_RECT DisplayArea = { 0, 0, 0, 0 };
		SetConsoleScreenBufferSize(hOut, NewSBSize);
		DisplayArea.Right = NewSBSize.X - 1;
		DisplayArea.Bottom = NewSBSize.Y - 1;
		SetConsoleWindowInfo(hOut, TRUE, &DisplayArea);
		ShowWindow(hWnd, SW_MAXIMIZE);
	}
	//Returns true if window size changed, false otherwise
	void WindowSizeChanged()
	{
		GetConsoleScreenBufferInfo(hOutput, &ConsoleScreenBufferInfo);
		if (windowSize.Bottom == ConsoleScreenBufferInfo.srWindow.Bottom && windowSize.Left == ConsoleScreenBufferInfo.srWindow.Left && windowSize.Right == ConsoleScreenBufferInfo.srWindow.Right && this->windowSize.Top == ConsoleScreenBufferInfo.srWindow.Top);
		else
		{
			ClearScreen();
			SetFonts(13, 13);
			cout << "Window Size changed, have to restart the game. press any key to restart, ESC to exit.";
			int key = _getch();
			if (key == char(27))
			{
				GameOver("", true);
			}
			else
			{
				RestartGame();
			}
		}
	}

	//Clears Console Screen
	void ClearScreen()
	{
		system("cls");
	}
	//Sends KeyEvent
	void SendKeyEvent(WORD w)
	{
		INPUT input;
		WORD vkey = w; // see link below
		input.type = INPUT_KEYBOARD;
		input.ki.wScan = MapVirtualKey(vkey, MAPVK_VK_TO_VSC);
		input.ki.time = 0;
		input.ki.dwExtraInfo = 0;
		input.ki.wVk = vkey;
		input.ki.dwFlags = 0; // there is no KEYEVENTF_KEYDOWN
		SendInput(1, &input, sizeof(INPUT));

		input.ki.dwFlags = KEYEVENTF_KEYUP;
		SendInput(1, &input, sizeof(INPUT));
	}
	//Hides Cursor
	void HideCursor()
	{
		GetConsoleCursorInfo(hOutput, &ConCurInfo);
		ConCurInfo.bVisible = false;
		SetConsoleCursorInfo(hOutput, &ConCurInfo);
	}
	//Returns true if player hits its body
	BOOL PlayerHitBody()
	{
		for (int i = 0; i < snakeLength; i++)
			if (PlayerPos.X == snakePartPosX[i] && PlayerPos.Y == snakePartPosY[i])
				return true;
		return false;
	}
	//Returns true if score changed, false otherwise
	BOOL ScoreChanged()
	{
		if (score == oldScore)
			return false;
		else
		{
			oldScore = score;
			return true;
		}
	}
};
int main()
{
	MainClass MC = MainClass(char(178), char(153), char(234), char(219));
	MC.StartGame();
}