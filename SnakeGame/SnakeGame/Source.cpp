//#include<iostream>
//#include<conio.h>
//#include<string>
//#include<Windows.h>
//using namespace std;
//enum Direction { Up, Down, Right, Left };
//class DrawMap
//{
//private:
//	int width, height, score = 0, snakeLength = 0, snakePartPosX[50], snakePartPosY[50], fruitX, fruitY;
//	int playerX = 10, playerY = 10, playerCharCount;
//	char playerChar, fruitChar, borderChar, bodyChar;
//	bool start = false, printDebug = false, pauseGame = false, isGameOver = false;
//	Direction playerDir;
//		
//public:
//	DrawMap(int width, int height, char borChar, char PlChar, char fChar, char body)
//	{
//		this->width = width;
//		this->height = height;
//		borderChar = borChar;
//		playerChar = PlChar;
//		fruitChar = fChar;
//		bodyChar = body;
//	}
//	void DrawTheMap()
//	{
//		changeFruitLocation();
//		while (true)
//		{
//			for (int h = 0; h < height; h++)
//			{
//				for (int w = 0; w < width; w++)
//				{
//					if (w == 0)
//					{
//						cout << borderChar;
//					}
//					else if (w == width - 1)
//					{
//						cout << borderChar;
//					}
//					else if (h == 0)
//					{
//						cout << borderChar;
//					}
//					else if (h == height - 1)
//					{
//						cout << borderChar;
//					}
//					else
//					{
//						if (w == playerX && h == playerY)
//							cout << playerChar;
//						else if (w == fruitX && h == fruitY)
//							cout << fruitChar;
//						else
//						{
//							bool drawSpace = true;
//							for (int pos = 0; pos < snakeLength; pos++)
//							{
//								if (snakePartPosX[pos] == w && snakePartPosY[pos] == h)
//								{
//									cout << bodyChar;
//									drawSpace = false;
//								}
//								if (playerX == snakePartPosX[pos] && playerY == snakePartPosY[pos])
//								{
//									GameOver("you collapsed into yourself!!");
//									isGameOver = true;
//									break;
//								}
//							}
//							if (drawSpace)
//								cout << " ";
//						}
//					}
//					if (isGameOver)
//						break;
//				}				
//				cout << endl;
//				if (isGameOver)
//					break;
//			}
//			if (playerX == 0 || playerX == width - 1 || playerY == 0 || playerY == height - 1)
//			{
//				GameOver("you hit the wall");
//				isGameOver = true;
//				break;
//			}
//			else
//			{
//				if (_kbhit())
//				{
//
//					int key = _getch();
//					if (!start)
//					{
//						start = true;
//					}
//					if (key == 'w')// && (!playerDir == Down))
//						playerDir = Up;
//					else if (key == 's')// && (!playerDir == Up))
//						playerDir = Down;
//					else if (key == 'd')// && (!playerDir == Left))
//						playerDir = Right;
//					else if (key == 'a')// && (!playerDir == Right))
//						playerDir = Left;
//					else if (key == char(27))
//					{
//						printDebugInfo();
//						cout << "Exited Game!!";
//						break;
//					}
//					else if (key == char(32))
//					{
//						pauseGame = true;
//					}
//				}
//				if (start)
//				{
//					if (playerDir == Up)
//					{
//						playerY--;
//					}
//					else if (playerDir == Down)
//					{
//						playerY++;
//					}
//					else if (playerDir == Right)
//					{
//						playerX++;
//					}
//					else if (playerDir == Left)
//					{
//						playerX--;
//					}
//				}
//				if (playerX == fruitX && playerY == fruitY)
//				{
//					score += 10;
//					changeFruitLocation();
//					snakeLength++;
//				}
//				moveSnakeBody();
//				//Sleep(0.2);
//				printDebugInfo();
//
//				if (pauseGame)
//				{
//					cout << "Game Paused!!" << endl << "Press any key to Resume!!";
//					_getch();
//					pauseGame = false;
//				}
//				if (isGameOver)
//					break;
//				printScore();				
//				system("cls");
//				
//
//			}
//		}
//	}
//	void changeFruitLocation()
//	{
//		fruitX = rand() % (width - 1);
//		fruitY = rand() % (height - 1);
//		if (fruitX == 0 || fruitY == 0)
//			changeFruitLocation();
//	}
//	void printDebugInfo()
//	{
//		if (printDebug)
//		{
//			cout << "FX: " << fruitX << " FY: " << fruitY << endl;
//			cout << "Snake Length: " << snakeLength << endl;
//			cout << "PosX:" << playerX << " PosY: " << playerY << endl;
//			for (int i = 0; i < snakeLength; i++)
//			{
//				cout << "bx[" << i << "] = " << snakePartPosX[i] << endl;
//				cout << "by[" << i << "] = " << snakePartPosY[i] << endl;
//			}
//		}
//	}
//	void printScore()
//	{
//		cout << "Score: " << score;
//	}
//	void moveSnakeBody()
//	{
//		int tempX = 1, tempY = 1, tempX1 = 1, tempY1 = 1;
//
//		for (int i = 0; i < snakeLength; i++)
//		{
//			if (i == 0) {
//				tempX = snakePartPosX[i];
//				tempY = snakePartPosY[i];
//				if (playerDir == Left)
//				{
//					snakePartPosX[i] = playerX + 1;
//					snakePartPosY[i] = playerY;
//				}
//				else if (playerDir == Right)
//				{
//					snakePartPosX[i] = playerX - 1;
//					snakePartPosY[i] = playerY;
//				}
//				else if (playerDir == Up)
//				{
//					snakePartPosX[i] = playerX;
//					snakePartPosY[i] = playerY + 1;
//				}
//				else if (playerDir == Down)
//				{
//					snakePartPosX[i] = playerX;
//					snakePartPosY[i] = playerY - 1;
//				}
//
//			}
//			else {
//				tempX1 = snakePartPosX[i];
//				tempY1 = snakePartPosY[i];
//
//				snakePartPosX[i] = tempX;
//				snakePartPosY[i] = tempY;
//
//				tempX = tempX1;
//				tempY = tempY1;
//			}
//		}
//	}
//	void GameOver(string reason)
//	{
//		printDebugInfo();
//		cout << "Game Over because: " << reason << "."<<endl;
//		cout << "Your score was " << score << "!";
//
//	}
//};
//int main()
//{
//	DrawMap dm = DrawMap(50, 20, '#', char(153), 'Q', char(254));
//	dm.DrawTheMap();
//	//USE GetCursorPosition from Windows API to Make printing smooth.
//	_getch();
//	return 0;
//}

////#include <windows.h>
////#include <iostream>
////using namespace std;
////int main(int argc, char* argv[])
////{
////	cout << "Green Text on Red Backgound?\n";
////	HANDLE hOutput = ::GetStdHandle(STD_OUTPUT_HANDLE);
////
////	COORD coord = { 0,0 };
////	DWORD dwWritten;
////	FillConsoleOutputAttribute(hOutput, FOREGROUND_GREEN | BACKGROUND_RED, 300, coord, &dwWritten);
////	return 0;
////}