#include <iostream>
#include <Windows.h>
#include <conio.h>
#include <vector>
#include <string>

bool gameOver;
const int wight = 20;
const int height = 20;
int headX, headY, fruitX, fruitY, score;
std::vector<int> tailX = { 0 };
std::vector<int> tailY = { 0 };
std::string board;

enum eDireck
{
	STOP = 0,
	LEFT,
	RIGHT,
	UP,
	DOWN
};
eDireck dir;

void Setup()
{
	tailX.clear();
	tailY.clear();
	gameOver = FALSE;
	dir = STOP;
	headX = wight / 2;
	headY = height / 2;
	srand(time(nullptr));
	fruitX = rand() % wight;
	fruitY = rand() % height;
	score = 0;
}

void Draw()
{
	board.clear();
	for (size_t i = 0; i <= wight + 2; i++)
	{
		board += "#";
	}
	board += "\n";
	for (size_t i = 0; i < height; i++)
	{
		for (size_t j = 0; j <= wight + 1; j++)
		{
			if (j == 0 || j == wight + 1)
			{
				board += "#";
			}

			if (i == headY && j == headX)
			{
				board += "O";
			}
			else if (i == fruitY && j == fruitX)
			{
				board += "F";
			}
			else
			{
				bool print = FALSE;

				for (int k = 0; k < tailX.size(); k++)
				{
					if (tailX[k] == j && tailY[k] == i)
					{
						board += "o";
						print = true;
					}
				}

				if (!print)
				{
					board += " ";
				}
			}
		}
		board += "\n";
	}

	for (size_t i = 0; i <= wight + 2; i++)
	{
		board += "#";
	}

	system("cls");
	std::cout << board << std::endl;
	std::cout << "\nScore: " << score << std::endl;
}

void Input()
{
	if (_kbhit())
	{
		switch (_getch())
		{
		case 'w':
			dir = UP;
			break;
		case 'a':
			dir = LEFT;
			break;
		case 's':
			dir = DOWN;
			break;
		case 'd':
			dir = RIGHT;
			break;
		case 'q':
			gameOver = TRUE;
			break;
		}

	}
}

void Logic()
{
	int prevX(0), prevY(0), prev2X(0), prev2Y(0);
	if (tailX.size() > 0)
	{
		prevX = tailX[0];
		prevY = tailY[0];
		tailX[0] = headX;
		tailY[0] = headY;

		for (size_t i = 1; i < tailX.size(); i++)
		{
			prev2X = tailX[i];
			prev2Y = tailY[i];
			tailX[i] = prevX;
			tailY[i] = prevY;
			prevX = prev2X;
			prevY = prev2Y;
		}
	}

	switch (dir)
	{
	case LEFT:
		headX--;
		break;
	case RIGHT:
		headX++;
		break;
	case UP:
		headY--;
		break;
	case DOWN:
		headY++;
		break;
	default:
		break;
	}

	if (headX > wight || headX < 0 || headY < 0 || headY > height)
	{
		gameOver = TRUE;
	}

	for (size_t i = 0; i < tailX.size(); i++)
	{
		if (tailX[i] == headX && tailY[i] == headY)
		{
			gameOver = TRUE;
		}
	}

	if (headX == fruitX && headY == fruitY)
	{
		score += 10;
		fruitX = rand() % wight;
		fruitY = rand() % height;
		tailX.push_back(headX);
		tailY.push_back(headY);
	}

}



int main()
{
	Setup();
	while (!gameOver)
	{
		Draw();
		Input();
		Logic();
		Sleep(150);
	}

}

