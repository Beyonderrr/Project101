#include <stdio.h>
#include <windows.h>
#include <time.h>
#include<conio.h>
#include<stdbool.h>

#define screen_x 120
#define screen_y 45
#define countofobj1 80
#define countofbullet 80

HANDLE rHnd;
HANDLE wHnd;
DWORD fdwMode;
COORD bufferSize = { screen_x,screen_y};
SMALL_RECT windowSize = { 0,0,screen_x - 1,screen_y - 1 };
COORD characterPos = { 0,0 };
CHAR_INFO consoleBuffer[screen_x * screen_y];
COORD obj1[countofobj1];
COORD bullet[countofbullet];

int posx;
int posy;
int color_ship = 1;
bool play = true;
int firestate[countofbullet];
int score = 0;

int setMode()
{
	rHnd = GetStdHandle(STD_INPUT_HANDLE);
	fdwMode = ENABLE_EXTENDED_FLAGS | ENABLE_WINDOW_INPUT |
		ENABLE_MOUSE_INPUT;
	SetConsoleMode(rHnd, fdwMode);
	return 0;
}

int setConsole(int x, int y)
{
	wHnd = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleWindowInfo(wHnd, TRUE, &windowSize);
	SetConsoleScreenBufferSize(wHnd, bufferSize);
	return 0;
}

void clear_buffer()
{
	for (int y = 0; y < screen_y; ++y) {
		for (int x = 0; x < screen_x; ++x) {
			consoleBuffer[x + screen_x * y].Char.AsciiChar = ' ';
			consoleBuffer[x + screen_x * y].Attributes = 7;
		}
	}
}

void fill_buffer_to_console()
{
	WriteConsoleOutputA(wHnd, consoleBuffer, bufferSize, characterPos,
		&windowSize);
}

void fill_smallship_to_buffer()
{

	consoleBuffer[posx - 2 + screen_x * posy].Char.AsciiChar = '<';
	consoleBuffer[posx - 2 + screen_x * posy].Attributes = color_ship;
	consoleBuffer[posx - 1 + screen_x * posy].Char.AsciiChar = '-';
	consoleBuffer[posx - 1 + screen_x * posy].Attributes = color_ship;
	consoleBuffer[posx + screen_x * posy].Char.AsciiChar = 'O';
	consoleBuffer[posx + screen_x * posy].Attributes = color_ship;
	consoleBuffer[posx + 1 + screen_x * posy].Char.AsciiChar = '-';
	consoleBuffer[posx + 1 + screen_x * posy].Attributes = color_ship;
	consoleBuffer[posx + 2 + screen_x * posy].Char.AsciiChar = '>';
	consoleBuffer[posx + 2 + screen_x * posy].Attributes = color_ship;
	
}

void init_ship()
{

	posx = 40;
	posy = 42;

}


void bullet_fly()
{
	for (int i = 0; i < countofbullet; i++)
	{
		if (firestate[i] == 1)
		{
			if (bullet[i].Y < 0)
			{
				firestate[i] = 0;
			}
			else
			{
				bullet[i].Y --;
			}
		}
	}
}

void draw_line_score()
{
	for (int i = 0; i < screen_y; i++)
	{
		consoleBuffer[90 + screen_x * i].Char.AsciiChar = '|';
		consoleBuffer[90 + screen_x * i].Attributes = 7;
	}
}

void fill_bullet_to_buffer()
{
	for (int i = 0; i < countofbullet; ++i)
	{

		consoleBuffer[bullet[i].X + screen_x * bullet[i].Y].Char.AsciiChar = '^';
		consoleBuffer[bullet[i].X + screen_x * bullet[i].Y].Attributes = 2;

	}
}

void fill_Score_to_buffer()
{
	consoleBuffer[100 + screen_x * 5].Char.AsciiChar = 'S';
	consoleBuffer[100 + screen_x * 5].Attributes = 7;
	consoleBuffer[101 + screen_x * 5].Char.AsciiChar = 'C';
	consoleBuffer[101 + screen_x * 5].Attributes = 7;
	consoleBuffer[102 + screen_x * 5].Char.AsciiChar = 'O';
	consoleBuffer[102 + screen_x * 5].Attributes = 7;
	consoleBuffer[103 + screen_x * 5].Char.AsciiChar = 'R';
	consoleBuffer[103 + screen_x * 5].Attributes = 7;
	consoleBuffer[104 + screen_x * 5].Char.AsciiChar = 'E';
	consoleBuffer[104 + screen_x * 5].Attributes = 7;
	consoleBuffer[100 + screen_x * 6].Char.AsciiChar = 'A'-17+score;
	consoleBuffer[100 + screen_x * 6].Attributes = 7;
}

void init_obj1()
{

	for (int i = 0; i < countofobj1; i++)
	{
		int randy = rand();
		int randx = rand();
		randx %= 90;
		randy %= screen_y;
		obj1[i].X = randx;
		obj1[i].Y = randy;

	}

}

void obj1_fall()
{
	int i;
	for (i = 0; i < countofobj1; i++) {
		if (obj1[i].Y >= screen_y - 1) {
			obj1[i] = { rand() %90,1 };
		}
		else {
			obj1[i] = { obj1[i].X,obj1[i].Y + 1 };
		}

	}
}

void fill_obj1_to_buffer()
{

	for (int i = 0; i < countofobj1; ++i)
	{
		consoleBuffer[obj1[i].X + screen_x * obj1[i].Y].Char.AsciiChar = '*';
		consoleBuffer[obj1[i].X + screen_x * obj1[i].Y].Attributes = 7;
	}
}

void test_colision()
{
	for (int i = 0; i < countofbullet; ++i)
	{
		for (int j = 0; j < countofobj1; ++j)
		{
			if (bullet[i].X == obj1[j].X && bullet[i].Y == obj1[j].Y)
			{
				obj1[j] = { rand() % 90,1 };
				firestate[i]=0;
				bullet[i].Y = -1;
				score++;
			}
		}
	}



}


int main()
{
	srand(time(NULL));
	DWORD numEvents = 0;
	DWORD numEventsRead = 0;
	setConsole(screen_x, screen_y);
	setMode();
	init_ship();
	init_obj1();


	while (play)
	{
		GetNumberOfConsoleInputEvents(rHnd, &numEvents);
		COORD characterPos = { 0,0 };
		if (numEvents != 0) {
			INPUT_RECORD* eventBuffer = new INPUT_RECORD[numEvents];
			ReadConsoleInput(rHnd, eventBuffer, numEvents, &numEventsRead);
			for (DWORD i = 0; i < numEventsRead; ++i)
			{
				if (eventBuffer[i].EventType == KEY_EVENT &&
					eventBuffer[i].Event.KeyEvent.bKeyDown == true)
				{
					if (eventBuffer[i].Event.KeyEvent.wVirtualKeyCode == VK_ESCAPE)
					{
						play = false;
					}
					if (eventBuffer[i].Event.KeyEvent.uChar.AsciiChar == 'a' && posx > 3)
					{
						posx--;
					}
					else if (eventBuffer[i].Event.KeyEvent.uChar.AsciiChar == 'd' && posx < 87)
					{
						posx++;
					}
					else if (eventBuffer[i].Event.KeyEvent.uChar.AsciiChar == 's' && posy < 42)
					{
						posy++;
					}
					else if (eventBuffer[i].Event.KeyEvent.uChar.AsciiChar == 'w' && posy > 0)
					{
						posy--;
					}
					else if (eventBuffer[i].Event.KeyEvent.uChar.AsciiChar == ' ')
					{
						for (int Count = 0; Count < countofbullet; Count++)
						{
							if (firestate[Count] != 1)
							{
								firestate[Count] = 1;
								bullet[Count].X = posx;
								bullet[Count].Y = posy;
								break;

							}
						}
					}

					//printf("press : %c\n", eventBuffer[i].Event.KeyEvent.uChar.AsciiChar);
				}

			}
			delete[] eventBuffer;
		}

		fill_smallship_to_buffer();
		obj1_fall();
		fill_obj1_to_buffer();
		bullet_fly();
		fill_bullet_to_buffer();
		draw_line_score();
		test_colision();
		fill_Score_to_buffer();
		fill_buffer_to_console();
		clear_buffer();
		Sleep(100);
		
	}

	return 0;
}