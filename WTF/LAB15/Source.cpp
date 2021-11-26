#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <windows.h>
#include <time.h>
#include<conio.h>
#include<stdbool.h>
#include<string.h>

#define screen_x 120
#define screen_y 46
#define countofobj1 30
#define countofobj2 24
#define countofobj3x 30
#define countofobj3y 24
#define countofbullet 100
#define countofdonotfireobj1 5 
#define countofdonotfireobj2 5
#define countofdonotfireobj3 10
#define countofitem1 3
#define countofitem2 3
#define countofitem3 3

HANDLE rHnd;
HANDLE wHnd;
DWORD fdwMode;
COORD bufferSize = { screen_x,screen_y };
SMALL_RECT windowSize = { 0,0,screen_x - 1,screen_y - 1 };
COORD characterPos = { 0,0 };
CHAR_INFO consoleBuffer[screen_x * screen_y];
COORD obj1[countofobj1];
COORD obj2[countofobj2];
COORD obj3x[countofobj3x];
COORD obj3y[countofobj3y];
COORD donotfireobj1[countofdonotfireobj1];
COORD donotfireobj2[countofdonotfireobj2];
COORD donotfireobj3[countofdonotfireobj3];
COORD item1[countofitem1];
COORD item2[countofitem2];
COORD item3[countofitem3];

COORD bullet_normal1[countofbullet];
COORD bullet_normal2[countofbullet];
COORD bullet_item11[countofbullet];
COORD bullet_item12[countofbullet];
COORD bullet_item13[countofbullet];
COORD bullet_item14[countofbullet];
COORD bullet_item15[countofbullet];
COORD bullet_item16[countofbullet];
COORD bullet_item17[countofbullet];
COORD bullet_item18[countofbullet];
COORD bullet_item19[countofbullet];

COORD bullet_item21[countofbullet];
COORD bullet_item22[countofbullet];
COORD bullet_item23[countofbullet];
COORD bullet_item24[countofbullet];
COORD bullet_item25[countofbullet];

int State = 2;
int Exit = 0;
int posx;
int posy;
int color_ship = 11;
int color_lship = 9;
int color_bullet_normal = 1;
int color_bullet_item1 = 1;
int color_bullet_item2 = 1;
bool play = true;
int firestate_normal1[countofbullet];
int firestate_normal2[countofbullet];
int firestate_item11[countofbullet];
int firestate_item12[countofbullet];
int firestate_item13[countofbullet];
int firestate_item14[countofbullet];
int firestate_item15[countofbullet];
int firestate_item16[countofbullet];
int firestate_item17[countofbullet];
int firestate_item18[countofbullet];
int firestate_item19[countofbullet];
int firestate_item21[countofbullet];
int firestate_item22[countofbullet];
int firestate_item23[countofbullet];
int firestate_item24[countofbullet];
int firestate_item25[countofbullet];
int score_now = 0; //for count
int score_sum = 0;
int round_obj1 = 0;
int round_obj1_fall = 1;
int round_obj2 = 0;
int round_obj2_fall = 1;
int round_obj3 = 0;
int round_obj3y_fall = 1;
int random_item1 = -1;
int random_item2 = -1;
int random_item3 = -1;
int random_donotfireobj1 = 0;
int random_donotfireobj2 = 0;
int random_donotfireobj3 = 0;
int score[9] = { 0,0,0,0,0,0,0,0,0 };
int hightscore[5][9] = { { 0,0,0,0,0,0,0,0,0 }, { 0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0 }, { 0,0,0,0,0,0,0,0,0 }, { 0,0,0,0,0,0,0,0,0 } };
int hp_ship = 5;
int round_item1 = 0;
int round_item2 = 0;
int round_item3 = 0;
int round_donotfireobj1 = 0;
int round_donotfireobj2 = 0;
int round_donotfireobj3 = 0;
int check_item1 = 0;
int check_item2 = 0;
int check_item3 = 0;
bool item_1 = false;
bool item_2 = false;
char newname[50];
int sideofdonotfireobj2[countofdonotfireobj2] = { 2,2,2,2,2 };
int sideofdonotfireobj3[countofdonotfireobj3] = { 0,1,0,1,0,1,0,1,0,1 };
int sideofobj3x[countofobj3x];

struct player {
	char name[50];
	int score;
};
player p[5];

void gotoxy(int x, int y)
{
	COORD c = { x, y };
	SetConsoleCursorPosition(
		GetStdHandle(STD_OUTPUT_HANDLE), c);
}

int setMode()
{
	rHnd = GetStdHandle(STD_INPUT_HANDLE);
	fdwMode = ENABLE_EXTENDED_FLAGS | ENABLE_WINDOW_INPUT |
		ENABLE_MOUSE_INPUT | ENABLE_INSERT_MODE | ENABLE_LINE_INPUT | ENABLE_ECHO_INPUT;
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

	consoleBuffer[posx - 3 + screen_x * posy].Char.AsciiChar = '<';
	consoleBuffer[posx - 3 + screen_x * posy].Attributes = color_ship;
	consoleBuffer[posx - 2 + screen_x * posy].Char.AsciiChar = '(';
	consoleBuffer[posx - 2 + screen_x * posy].Attributes = color_ship;
	consoleBuffer[posx - 1 + screen_x * posy].Char.AsciiChar = '-';
	consoleBuffer[posx - 1 + screen_x * posy].Attributes = color_ship;
	consoleBuffer[posx + screen_x * posy].Char.AsciiChar = 'O';
	consoleBuffer[posx + screen_x * posy].Attributes = color_ship;
	consoleBuffer[posx + 1 + screen_x * posy].Char.AsciiChar = '-';
	consoleBuffer[posx + 1 + screen_x * posy].Attributes = color_ship;
	consoleBuffer[posx + 2 + screen_x * posy].Char.AsciiChar = ')';
	consoleBuffer[posx + 2 + screen_x * posy].Attributes = color_ship;
	consoleBuffer[posx + 3 + screen_x * posy].Char.AsciiChar = '>';
	consoleBuffer[posx + 3 + screen_x * posy].Attributes = color_ship;

}

void fill_largeship_to_buffer()
{
	consoleBuffer[posx + screen_x * (posy - 2)].Char.AsciiChar = '^';
	consoleBuffer[posx + screen_x * (posy - 2)].Attributes = color_lship;
	consoleBuffer[posx + screen_x * (posy - 1)].Char.AsciiChar = '|';
	consoleBuffer[posx + screen_x * (posy - 1)].Attributes = color_lship;
	consoleBuffer[posx - 2 + screen_x * posy].Char.AsciiChar = '/';
	consoleBuffer[posx - 2 + screen_x * posy].Attributes = color_lship;
	consoleBuffer[posx - 1 + screen_x * posy].Char.AsciiChar = '-';
	consoleBuffer[posx - 1 + screen_x * posy].Attributes = color_lship;
	consoleBuffer[posx + screen_x * posy].Char.AsciiChar = '+';
	consoleBuffer[posx + screen_x * posy].Attributes = color_lship;
	consoleBuffer[posx + 1 + screen_x * posy].Char.AsciiChar = '-';
	consoleBuffer[posx + 1 + screen_x * posy].Attributes = color_lship;
	consoleBuffer[posx + 2 + screen_x * posy].Char.AsciiChar = '\\';
	consoleBuffer[posx + 2 + screen_x * posy].Attributes = color_lship;
	consoleBuffer[posx - 1 + screen_x * (posy + 1)].Char.AsciiChar = ')';
	consoleBuffer[posx - 1 + screen_x * (posy + 1)].Attributes = color_lship;
	consoleBuffer[posx + screen_x * (posy + 1)].Char.AsciiChar = '|';
	consoleBuffer[posx + screen_x * (posy + 1)].Attributes = color_lship;
	consoleBuffer[posx + 1 + screen_x * (posy + 1)].Char.AsciiChar = '(';
	consoleBuffer[posx + 1 + screen_x * (posy + 1)].Attributes = color_lship;
	consoleBuffer[posx - 4 + screen_x * (posy + 2)].Char.AsciiChar = '<';
	consoleBuffer[posx - 4 + screen_x * (posy + 2)].Attributes = color_lship;
	consoleBuffer[posx - 3 + screen_x * (posy + 2)].Char.AsciiChar = '[';
	consoleBuffer[posx - 3 + screen_x * (posy + 2)].Attributes = color_lship;
	consoleBuffer[posx - 2 + screen_x * (posy + 2)].Char.AsciiChar = '_';
	consoleBuffer[posx - 2 + screen_x * (posy + 2)].Attributes = color_lship;
	consoleBuffer[posx - 1 + screen_x * (posy + 2)].Char.AsciiChar = '=';
	consoleBuffer[posx - 1 + screen_x * (posy + 2)].Attributes = color_lship;
	consoleBuffer[posx + screen_x * (posy + 2)].Char.AsciiChar = 'o';
	consoleBuffer[posx + screen_x * (posy + 2)].Attributes = color_lship;
	consoleBuffer[posx + 1 + screen_x * (posy + 2)].Char.AsciiChar = '=';
	consoleBuffer[posx + 1 + screen_x * (posy + 2)].Attributes = color_lship;
	consoleBuffer[posx + 2 + screen_x * (posy + 2)].Char.AsciiChar = '_';
	consoleBuffer[posx + 2 + screen_x * (posy + 2)].Attributes = color_lship;
	consoleBuffer[posx + 3 + screen_x * (posy + 2)].Char.AsciiChar = ']';
	consoleBuffer[posx + 3 + screen_x * (posy + 2)].Attributes = color_lship;
	consoleBuffer[posx + 4 + screen_x * (posy + 2)].Char.AsciiChar = '>';
	consoleBuffer[posx + 4 + screen_x * (posy + 2)].Attributes = color_lship;

}

void init_ship()
{

	posx = 40;
	posy = 42;

}

void bullet_normal_fly()
{
	for (int i = 0; i < countofbullet; i++)
	{
		if (firestate_normal1[i] == 1)
		{
			if (bullet_normal1[i].Y < 0)
			{
				firestate_normal1[i] = 0;
			}
			else
			{
				bullet_normal1[i].Y -= 2;
			}
		}
	}
	for (int i = 0; i < countofbullet; i++)
	{
		if (firestate_normal2[i] == 1)
		{
			if (bullet_normal2[i].Y < 0)
			{
				firestate_normal2[i] = 0;
			}
			else
			{
				bullet_normal2[i].Y -= 2;
			}
		}
	}
}

void bullet_item1_fly()
{
	for (int i = 0; i < countofbullet; i++)
	{
		if (firestate_item11[i] == 1)
		{
			if (bullet_item11[i].Y < 0)
			{
				firestate_item11[i] = 0;
				bullet_item11[i] = { rand() % 90,-1 };
			}
			else
			{
				bullet_item11[i].Y -= 2;
			}
		}
		else {
			bullet_item11[i] = { rand() % 90,-1 };
		}
	}
	for (int i = 0; i < countofbullet; i++)
	{
		if (firestate_item12[i] == 1)
		{
			if (bullet_item12[i].Y < 0)
			{
				firestate_item12[i] = 0;
				bullet_item12[i] = { rand() % 90,-1 };
			}
			else
			{
				bullet_item12[i].Y -= 2;
			}
		}
		else {
			bullet_item12[i] = { rand() % 90,-1 };
		}
	}
	for (int i = 0; i < countofbullet; i++)
	{
		if (firestate_item13[i] == 1)
		{
			if (bullet_item13[i].Y < 0)
			{
				firestate_item13[i] = 0;
				bullet_item13[i] = { rand() % 90,-1 };
			}
			else
			{
				bullet_item13[i].Y -= 2;
			}
		}
		else {
			bullet_item13[i] = { rand() % 90,-1 };
		}
	}
	for (int i = 0; i < countofbullet; i++)
	{
		if (firestate_item14[i] == 1)
		{
			if (bullet_item14[i].Y < 0)
			{
				firestate_item14[i] = 0;
				bullet_item14[i] = { rand() % 90,-1 };
			}
			else
			{
				bullet_item14[i].Y -= 2;
			}
		}
		else {
			bullet_item14[i] = { rand() % 90,-1 };
		}
	}
	for (int i = 0; i < countofbullet; i++)
	{
		if (firestate_item15[i] == 1)
		{
			if (bullet_item15[i].Y < 0)
			{
				firestate_item15[i] = 0;
				bullet_item15[i] = { rand() % 90,-1 };
			}
			else
			{
				bullet_item15[i].Y -= 2;
			}
		}
		else {
			bullet_item15[i] = { rand() % 90,-1 };
		}
	}
	for (int i = 0; i < countofbullet; i++)
	{
		if (firestate_item16[i] == 1)
		{
			if (bullet_item16[i].Y < 0)
			{
				firestate_item16[i] = 0;
				bullet_item16[i] = { rand() % 90,-1 };
			}
			else
			{
				bullet_item16[i].Y -= 2;
			}
		}
		else {
			bullet_item16[i] = { rand() % 90,-1 };
		}
	}
	for (int i = 0; i < countofbullet; i++)
	{
		if (firestate_item17[i] == 1)
		{
			if (bullet_item17[i].Y < 0)
			{
				firestate_item17[i] = 0;
				bullet_item17[i] = { rand() % 90,-1 };
			}
			else
			{
				bullet_item17[i].Y -= 2;
			}
		}
		else {
			bullet_item17[i] = { rand() % 90,-1 };
		}
	}
	for (int i = 0; i < countofbullet; i++)
	{
		if (firestate_item18[i] == 1)
		{
			if (bullet_item18[i].Y < 0)
			{
				firestate_item18[i] = 0;
				bullet_item18[i] = { rand() % 90,-1 };
			}
			else
			{
				bullet_item18[i].Y -= 2;
			}
		}
		else {
			bullet_item18[i] = { rand() % 90,-1 };
		}
	}
	for (int i = 0; i < countofbullet; i++)
	{
		if (firestate_item19[i] == 1)
		{
			if (bullet_item19[i].Y < 0)
			{
				firestate_item19[i] = 0;
				bullet_item19[i] = { rand() % 90,-1 };
			}
			else
			{
				bullet_item19[i].Y -= 2;
			}
		}
		else {
			bullet_item19[i] = { rand() % 90,-1 };
		}
	}

}

void bullet_item2_fly()
{
	for (int i = 0; i < countofbullet; i++)
	{
		if (firestate_item21[i] == 1)
		{
			if ((bullet_item21[i].Y < 0 || bullet_item21[i].X < 3))// && (bullet_item21[i].X != 1))
			{
				firestate_item21[i] = 0;
				bullet_item21[i] = { rand() % 90,-1 };
			}
			else
			{
				bullet_item21[i].Y -= 2;
				bullet_item21[i].X -= 2;
			}
		}
	}
	for (int i = 0; i < countofbullet; i++)
	{
		if (firestate_item22[i] == 1)
		{
			if (bullet_item22[i].Y < 0)
			{
				firestate_item22[i] = 0;
				bullet_item22[i] = { rand() % 90,-1 };
			}
			else
			{
				bullet_item22[i].Y -= 2;
			}
		}
	}
	for (int i = 0; i < countofbullet; i++)
	{
		if (firestate_item23[i] == 1)
		{
			if ((bullet_item23[i].Y < 0 || bullet_item23[i].X > 86))// && (bullet_item21[i].X != 88))
			{
				firestate_item23[i] = 0;
				bullet_item23[i] = { rand() % 90,-1 };
			}
			else
			{
				bullet_item23[i].Y -= 2;
				bullet_item23[i].X += 2;
			}
		}
	}
	for (int i = 0; i < countofbullet; i++)
	{
		if (firestate_item24[i] == 1)
		{
			if ((bullet_item24[i].Y < 0 || bullet_item24[i].X < 3))// && (bullet_item21[i].X != 1))
			{
				firestate_item24[i] = 0;
				bullet_item24[i] = { rand() % 90,-1 };
			}
			else
			{
				bullet_item24[i].Y -= 2;
				bullet_item24[i].X -= 3;
			}
		}
	}
	for (int i = 0; i < countofbullet; i++)
	{
		if (firestate_item25[i] == 1)
		{
			if ((bullet_item25[i].Y < 0 || bullet_item25[i].X > 86))// && (bullet_item21[i].X != 88))
			{
				firestate_item25[i] = 0;
				bullet_item25[i] = { rand() % 90,-1 };
			}
			else
			{
				bullet_item25[i].Y -= 2;
				bullet_item25[i].X += 3;
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

void fill_bullet_normal_to_buffer()
{
	for (int i = 0; i < countofbullet; ++i)
	{
		if (bullet_normal1[i].X != 0 && bullet_normal1[i].Y != 0)
		{
			consoleBuffer[bullet_normal1[i].X + screen_x * bullet_normal1[i].Y].Char.AsciiChar = '^';
			consoleBuffer[bullet_normal1[i].X + screen_x * bullet_normal1[i].Y].Attributes = color_bullet_normal;
		}
	}
	for (int i = 0; i < countofbullet; ++i)
	{
		if (bullet_normal2[i].X != 0 && bullet_normal2[i].Y != 0)
		{
			consoleBuffer[bullet_normal2[i].X + screen_x * bullet_normal2[i].Y].Char.AsciiChar = '^';
			consoleBuffer[bullet_normal2[i].X + screen_x * bullet_normal2[i].Y].Attributes = color_bullet_normal;
		}
	}
}

void fill_bullet_item1_to_buffer()
{
	for (int i = 0; i < countofbullet; ++i)
	{
		if (bullet_item11[i].X != 0 && bullet_item11[i].Y != 0)
		{
			consoleBuffer[bullet_item11[i].X + screen_x * bullet_item11[i].Y].Char.AsciiChar = '^';
			consoleBuffer[bullet_item11[i].X + screen_x * bullet_item11[i].Y].Attributes = color_bullet_item1;
		}
	}
	for (int i = 0; i < countofbullet; ++i)
	{
		if (bullet_item12[i].X != 0 && bullet_item12[i].Y != 0)
		{
			consoleBuffer[bullet_item12[i].X + screen_x * bullet_item12[i].Y].Char.AsciiChar = '^';
			consoleBuffer[bullet_item12[i].X + screen_x * bullet_item12[i].Y].Attributes = color_bullet_item1;
		}
	}
	for (int i = 0; i < countofbullet; ++i)
	{
		if (bullet_item13[i].X != 0 && bullet_item13[i].Y != 0)
		{
			consoleBuffer[bullet_item13[i].X + screen_x * bullet_item13[i].Y].Char.AsciiChar = '^';
			consoleBuffer[bullet_item13[i].X + screen_x * bullet_item13[i].Y].Attributes = color_bullet_item1;
		}
	}
	for (int i = 0; i < countofbullet; ++i)
	{
		if (bullet_item14[i].X != 0 && bullet_item14[i].Y != 0)
		{
			consoleBuffer[bullet_item14[i].X + screen_x * bullet_item14[i].Y].Char.AsciiChar = '^';
			consoleBuffer[bullet_item14[i].X + screen_x * bullet_item14[i].Y].Attributes = color_bullet_item1;
		}
	}
	for (int i = 0; i < countofbullet; ++i)
	{
		if (bullet_item15[i].X != 0 && bullet_item15[i].Y != 0)
		{
			consoleBuffer[bullet_item15[i].X + screen_x * bullet_item15[i].Y].Char.AsciiChar = '^';
			consoleBuffer[bullet_item15[i].X + screen_x * bullet_item15[i].Y].Attributes = color_bullet_item1;
		}
	}
	for (int i = 0; i < countofbullet; ++i)
	{
		if (bullet_item16[i].X != 0 && bullet_item16[i].Y != 0)
		{
			consoleBuffer[bullet_item16[i].X + screen_x * bullet_item16[i].Y].Char.AsciiChar = '^';
			consoleBuffer[bullet_item16[i].X + screen_x * bullet_item16[i].Y].Attributes = color_bullet_item1;
		}
	}
	for (int i = 0; i < countofbullet; ++i)
	{
		if (bullet_item17[i].X != 0 && bullet_item17[i].Y != 0)
		{
			consoleBuffer[bullet_item17[i].X + screen_x * bullet_item17[i].Y].Char.AsciiChar = '^';
			consoleBuffer[bullet_item17[i].X + screen_x * bullet_item17[i].Y].Attributes = color_bullet_item1;
		}
	}
	for (int i = 0; i < countofbullet; ++i)
	{
		if (bullet_item18[i].X != 0 && bullet_item18[i].Y != 0)
		{
			consoleBuffer[bullet_item18[i].X + screen_x * bullet_item18[i].Y].Char.AsciiChar = '^';
			consoleBuffer[bullet_item18[i].X + screen_x * bullet_item18[i].Y].Attributes = color_bullet_item1;
		}
	}
	for (int i = 0; i < countofbullet; ++i)
	{
		if (bullet_item19[i].X != 0 && bullet_item19[i].Y != 0)
		{
			consoleBuffer[bullet_item19[i].X + screen_x * bullet_item19[i].Y].Char.AsciiChar = '^';
			consoleBuffer[bullet_item19[i].X + screen_x * bullet_item19[i].Y].Attributes = color_bullet_item1;
		}
	}
}

void fill_bullet_item2_to_buffer()
{
	for (int i = 0; i < countofbullet; ++i)
	{
		if (bullet_item21[i].X != 0 && bullet_item21[i].Y != 0)
		{
			consoleBuffer[bullet_item21[i].X + screen_x * bullet_item21[i].Y].Char.AsciiChar = '^';
			consoleBuffer[bullet_item21[i].X + screen_x * bullet_item21[i].Y].Attributes = color_bullet_item2;
		}
	}
	for (int i = 0; i < countofbullet; ++i)
	{
		if (bullet_item22[i].X != 0 && bullet_item22[i].Y != 0)
		{
			consoleBuffer[bullet_item22[i].X + screen_x * bullet_item22[i].Y].Char.AsciiChar = '^';
			consoleBuffer[bullet_item22[i].X + screen_x * bullet_item22[i].Y].Attributes = color_bullet_item2;
		}
	}
	for (int i = 0; i < countofbullet; ++i)
	{
		if (bullet_item23[i].X != 0 && bullet_item23[i].Y != 0)
		{
			consoleBuffer[bullet_item23[i].X + screen_x * bullet_item23[i].Y].Char.AsciiChar = '^';
			consoleBuffer[bullet_item23[i].X + screen_x * bullet_item23[i].Y].Attributes = color_bullet_item2;
		}
	}
	for (int i = 0; i < countofbullet; ++i)
	{
		if (bullet_item24[i].X != 0 && bullet_item24[i].Y != 0)
		{
			consoleBuffer[bullet_item24[i].X + screen_x * bullet_item24[i].Y].Char.AsciiChar = '^';
			consoleBuffer[bullet_item24[i].X + screen_x * bullet_item24[i].Y].Attributes = color_bullet_item2;
		}
	}
	for (int i = 0; i < countofbullet; ++i)
	{
		if (bullet_item25[i].X != 0 && bullet_item25[i].Y != 0)
		{
			consoleBuffer[bullet_item25[i].X + screen_x * bullet_item25[i].Y].Char.AsciiChar = '^';
			consoleBuffer[bullet_item25[i].X + screen_x * bullet_item25[i].Y].Attributes = color_bullet_item2;
		}
	}
}

void fill_Score_to_buffer()
{
	int i = 0;
	int count = 0;
	consoleBuffer[103 + screen_x * 5].Char.AsciiChar = 'S';
	consoleBuffer[103 + screen_x * 5].Attributes = 7;
	consoleBuffer[104 + screen_x * 5].Char.AsciiChar = 'C';
	consoleBuffer[104 + screen_x * 5].Attributes = 7;
	consoleBuffer[105 + screen_x * 5].Char.AsciiChar = 'O';
	consoleBuffer[105 + screen_x * 5].Attributes = 7;
	consoleBuffer[106 + screen_x * 5].Char.AsciiChar = 'R';
	consoleBuffer[106 + screen_x * 5].Attributes = 7;
	consoleBuffer[107 + screen_x * 5].Char.AsciiChar = 'E';
	consoleBuffer[107 + screen_x * 5].Attributes = 7;

	score_sum += score_now;
	int score_check = score_sum;

	while (score_check > 9)
	{
		if (score_check % 10 != 0)
		{
			i++;
			score_check--;
		}
		else if (score_check % 10 == 0)
		{
			score_check /= 10;
			score[count] += i;
			count++;
			i = 0;
		}
	}

	score[count] += score_check;

	for (int j = 0; j < 9; j++)
	{
		consoleBuffer[109 - j + screen_x * 7].Char.AsciiChar = 48 + score[j];
		consoleBuffer[109 - j + screen_x * 7].Attributes = 7;
	}
	for (int k = 0; k < 9; k++)
	{
		score[k] = 0;
	}

}

void fill_highestscore_to_buffer()
{
	consoleBuffer[100 + screen_x * 12].Char.AsciiChar = 'H';
	consoleBuffer[100 + screen_x * 12].Attributes = 7;
	consoleBuffer[101 + screen_x * 12].Char.AsciiChar = 'I';
	consoleBuffer[101 + screen_x * 12].Attributes = 7;
	consoleBuffer[102 + screen_x * 12].Char.AsciiChar = 'G';
	consoleBuffer[102 + screen_x * 12].Attributes = 7;
	consoleBuffer[103 + screen_x * 12].Char.AsciiChar = 'H';
	consoleBuffer[103 + screen_x * 12].Attributes = 7;
	consoleBuffer[104 + screen_x * 12].Char.AsciiChar = 'E';
	consoleBuffer[104 + screen_x * 12].Attributes = 7;
	consoleBuffer[105 + screen_x * 12].Char.AsciiChar = 'S';
	consoleBuffer[105 + screen_x * 12].Attributes = 7;
	consoleBuffer[106 + screen_x * 12].Char.AsciiChar = 'T';
	consoleBuffer[106 + screen_x * 12].Attributes = 7;
	consoleBuffer[107 + screen_x * 12].Char.AsciiChar = 'S';
	consoleBuffer[107 + screen_x * 12].Attributes = 7;
	consoleBuffer[108 + screen_x * 12].Char.AsciiChar = 'C';
	consoleBuffer[108 + screen_x * 12].Attributes = 7;
	consoleBuffer[109 + screen_x * 12].Char.AsciiChar = 'O';
	consoleBuffer[109 + screen_x * 12].Attributes = 7;
	consoleBuffer[110 + screen_x * 12].Char.AsciiChar = 'R';
	consoleBuffer[110 + screen_x * 12].Attributes = 7;
	consoleBuffer[111 + screen_x * 12].Char.AsciiChar = 'E';
	consoleBuffer[111 + screen_x * 12].Attributes = 7;

	FILE* showdata;
	showdata = fopen("Top5Player.txt", "r");
	for (int i = 0; i < 5; i++)
	{
		fscanf(showdata, "%s  %d\n", p[i].name, &p[i].score);
	}
	fclose(showdata);

	char* readname;
	int yaxis = 15;
	int xaxisname = 95;
	int number = 49;
	int count = 0;
	int j = 0;

	for (int i = 0; i < 5; i++)
	{

		readname = p[i].name;
		consoleBuffer[93 + screen_x * yaxis].Char.AsciiChar = number;
		consoleBuffer[93 + screen_x * yaxis].Attributes = 7;
		while (*readname != '\0')
		{
			consoleBuffer[xaxisname + screen_x * yaxis].Char.AsciiChar = *readname;
			consoleBuffer[xaxisname + screen_x * yaxis].Attributes = 7;
			xaxisname++;
			readname++;
		}
		xaxisname = 95;
		int score_check = p[i].score;


		while (score_check > 9)
		{
			if (score_check % 10 != 0)
			{
				j++;
				score_check--;
			}
			else if (score_check % 10 == 0)
			{
				score_check /= 10;
				hightscore[i][count] += j;
				count++;
				j = 0;
			}
		}

		hightscore[i][count] += score_check;

		for (int j = 0; j < 9; j++)
		{
			consoleBuffer[116 - j + screen_x * yaxis].Char.AsciiChar = 48 + hightscore[i][j];
			consoleBuffer[116 - j + screen_x * yaxis].Attributes = 7;
		}
		for (int k = 0; k < 9; k++)
		{
			hightscore[i][k] = 0;
		}
		yaxis += 3;
		number++;
		count = 0;
	}

}

void check_hightscore()
{
	int scorenow = score_sum;
	char newname[50];

	for (int i = 4; i >= 0; i--)
	{
		if (scorenow > p[i].score && scorenow < p[i - 1].score)
		{
			for (int j = 4; j > i; j--)
			{
				p[i + 1].score = p[i].score;
				strcpy(p[i + 1].name, p[i].name);
			}
			p[i].score = scorenow;
			for (int k = 0; k < 23; k++)
			{
				printf("\n");
			}
			for (int k = 0; k < 50; k++)
			{
				printf(" ");
			}
			printf("!!! NEW HIGHSCORE !!!\n\n");
			for (int k = 0; k < 50; k++)
			{
				printf(" ");
			}
			printf("Enter your name : ");
			scanf("%s", newname);
			strcpy(p[i].name, newname);
		}
		else if (scorenow == p[i].score)
		{
			/*if (scorenow == p[i - 1].score)
			{
				printf("222222");
				printf("Enter your name : ");
				scanf("%s", newname);
				strcpy(p[i].name, p[i-1].name);
				strcpy(p[-1].name, p[i-2].name);
				strcpy(p[i-2].name, newname);
			}*/

			for (int j = 4; j > i; j--)
			{
				p[j].score = p[j - 1].score;
				strcpy(p[j].name, p[j - 1].name);
			}
			for (int k = 0; k < 23; k++)
			{
				printf("\n");
			}
			for (int k = 0; k < 50; k++)
			{
				printf(" ");
			}
			p[i].score = scorenow;
			printf("!!! NEW HIGHSCORE !!!\n\n");
			for (int k = 0; k < 50; k++)
			{
				printf(" ");
			}
			printf("Enter your name : ");
			scanf("%s", newname);
			strcpy(p[i].name, newname);

		}
	}
	if (scorenow > p[0].score)
	{
		for (int i = 3; i >= 0; i--)
		{
			p[i + 1].score = p[i].score;
			strcpy(p[i + 1].name, p[i].name);
		}
		p[0].score = scorenow;
		for (int k = 0; k < 23; k++)
		{
			printf("\n");
		}
		for (int k = 0; k < 50; k++)
		{
			printf(" ");
		}
		printf("!!! NEW HIGHSCORE!!! \n\n");
		for (int k = 0; k < 50; k++)
		{
			printf(" ");
		}
		printf("Enter your name : ");
		scanf("%s", newname);
		strcpy(p[0].name, newname);
	}


	FILE* savedata;
	savedata = fopen("Top5Player.txt", "w");
	for (int i = 0; i < 5; i++)
	{
		fprintf(savedata, "%s  ", p[i].name);
		fprintf(savedata, "%d\n", p[i].score);
	};
	fclose(savedata);
}


void fill_howtoplay_to_buffer()
{
	consoleBuffer[100 + screen_x * 31].Char.AsciiChar = 'H';
	consoleBuffer[100 + screen_x * 31].Attributes = 7;
	consoleBuffer[101 + screen_x * 31].Char.AsciiChar = 'O';
	consoleBuffer[101 + screen_x * 31].Attributes = 7;
	consoleBuffer[102 + screen_x * 31].Char.AsciiChar = 'W';
	consoleBuffer[102 + screen_x * 31].Attributes = 7;
	consoleBuffer[104 + screen_x * 31].Char.AsciiChar = 'T';
	consoleBuffer[104 + screen_x * 31].Attributes = 7;
	consoleBuffer[105 + screen_x * 31].Char.AsciiChar = 'O';
	consoleBuffer[105 + screen_x * 31].Attributes = 7;
	consoleBuffer[107 + screen_x * 31].Char.AsciiChar = 'P';
	consoleBuffer[107 + screen_x * 31].Attributes = 7;
	consoleBuffer[108 + screen_x * 31].Char.AsciiChar = 'L';
	consoleBuffer[108 + screen_x * 31].Attributes = 7;
	consoleBuffer[109 + screen_x * 31].Char.AsciiChar = 'A';
	consoleBuffer[109 + screen_x * 31].Attributes = 7;
	consoleBuffer[110 + screen_x * 31].Char.AsciiChar = 'Y';
	consoleBuffer[110 + screen_x * 31].Attributes = 7;

	consoleBuffer[95 + screen_x * 34].Char.AsciiChar = 'W';
	consoleBuffer[95 + screen_x * 34].Attributes = 7;
	consoleBuffer[97 + screen_x * 34].Char.AsciiChar = 'A';
	consoleBuffer[97 + screen_x * 34].Attributes = 7;
	consoleBuffer[99 + screen_x * 34].Char.AsciiChar = 'S';
	consoleBuffer[99 + screen_x * 34].Attributes = 7;
	consoleBuffer[101 + screen_x * 34].Char.AsciiChar = 'D';
	consoleBuffer[101 + screen_x * 34].Attributes = 7;
	consoleBuffer[108 + screen_x * 34].Char.AsciiChar = 'M';
	consoleBuffer[108 + screen_x * 34].Attributes = 7;
	consoleBuffer[109 + screen_x * 34].Char.AsciiChar = 'O';
	consoleBuffer[109 + screen_x * 34].Attributes = 7;
	consoleBuffer[110 + screen_x * 34].Char.AsciiChar = 'V';
	consoleBuffer[110 + screen_x * 34].Attributes = 7;
	consoleBuffer[111 + screen_x * 34].Char.AsciiChar = 'E';
	consoleBuffer[111 + screen_x * 34].Attributes = 7;

	consoleBuffer[95 + screen_x * 36].Char.AsciiChar = 'S';
	consoleBuffer[95 + screen_x * 36].Attributes = 7;
	consoleBuffer[96 + screen_x * 36].Char.AsciiChar = 'P';
	consoleBuffer[96 + screen_x * 36].Attributes = 7;
	consoleBuffer[97 + screen_x * 36].Char.AsciiChar = 'A';
	consoleBuffer[97 + screen_x * 36].Attributes = 7;
	consoleBuffer[98 + screen_x * 36].Char.AsciiChar = 'C';
	consoleBuffer[98 + screen_x * 36].Attributes = 7;
	consoleBuffer[99 + screen_x * 36].Char.AsciiChar = 'E';
	consoleBuffer[99 + screen_x * 36].Attributes = 7;
	consoleBuffer[100 + screen_x * 36].Char.AsciiChar = 'B';
	consoleBuffer[100 + screen_x * 36].Attributes = 7;
	consoleBuffer[101 + screen_x * 36].Char.AsciiChar = 'A';
	consoleBuffer[101 + screen_x * 36].Attributes = 7;
	consoleBuffer[102 + screen_x * 36].Char.AsciiChar = 'R';
	consoleBuffer[102 + screen_x * 36].Attributes = 7;
	consoleBuffer[108 + screen_x * 36].Char.AsciiChar = 'S';
	consoleBuffer[108 + screen_x * 36].Attributes = 7;
	consoleBuffer[109 + screen_x * 36].Char.AsciiChar = 'H';
	consoleBuffer[109 + screen_x * 36].Attributes = 7;
	consoleBuffer[110 + screen_x * 36].Char.AsciiChar = 'O';
	consoleBuffer[110 + screen_x * 36].Attributes = 7;
	consoleBuffer[111 + screen_x * 36].Char.AsciiChar = 'O';
	consoleBuffer[111 + screen_x * 36].Attributes = 7;
	consoleBuffer[112 + screen_x * 36].Char.AsciiChar = 'T';
	consoleBuffer[112 + screen_x * 36].Attributes = 7;

	consoleBuffer[95 + screen_x * 38].Char.AsciiChar = 'E';
	consoleBuffer[95 + screen_x * 38].Attributes = 7;
	consoleBuffer[96 + screen_x * 38].Char.AsciiChar = 'S';
	consoleBuffer[96 + screen_x * 38].Attributes = 7;
	consoleBuffer[97 + screen_x * 38].Char.AsciiChar = 'C';
	consoleBuffer[97 + screen_x * 38].Attributes = 7;
	consoleBuffer[108 + screen_x * 38].Char.AsciiChar = 'Q';
	consoleBuffer[108 + screen_x * 38].Attributes = 7;
	consoleBuffer[109 + screen_x * 38].Char.AsciiChar = 'U';
	consoleBuffer[109 + screen_x * 38].Attributes = 7;
	consoleBuffer[110 + screen_x * 38].Char.AsciiChar = 'I';
	consoleBuffer[110 + screen_x * 38].Attributes = 7;
	consoleBuffer[111 + screen_x * 38].Char.AsciiChar = 'T';
	consoleBuffer[111 + screen_x * 38].Attributes = 7;
}

void fill_gameover_to_buffer()
{
	consoleBuffer[55 + screen_x * 23].Char.AsciiChar = 'G';
	consoleBuffer[55 + screen_x * 23].Attributes = 4;
	consoleBuffer[56 + screen_x * 23].Char.AsciiChar = 'A';
	consoleBuffer[56 + screen_x * 23].Attributes = 4;
	consoleBuffer[57 + screen_x * 23].Char.AsciiChar = 'M';
	consoleBuffer[57 + screen_x * 23].Attributes = 4;
	consoleBuffer[58 + screen_x * 23].Char.AsciiChar = 'E';
	consoleBuffer[58 + screen_x * 23].Attributes = 4;

	consoleBuffer[60 + screen_x * 23].Char.AsciiChar = 'O';
	consoleBuffer[60 + screen_x * 23].Attributes = 4;
	consoleBuffer[61 + screen_x * 23].Char.AsciiChar = 'V';
	consoleBuffer[61 + screen_x * 23].Attributes = 4;
	consoleBuffer[62 + screen_x * 23].Char.AsciiChar = 'E';
	consoleBuffer[62 + screen_x * 23].Attributes = 4;
	consoleBuffer[63 + screen_x * 23].Char.AsciiChar = 'R';
	consoleBuffer[63 + screen_x * 23].Attributes = 4;
}

void fill_pressanykey_to_buffer()
{

	consoleBuffer[45 + screen_x * 25].Char.AsciiChar = 'P';
	consoleBuffer[45 + screen_x * 25].Attributes = 7;
	consoleBuffer[46 + screen_x * 25].Char.AsciiChar = 'R';
	consoleBuffer[46 + screen_x * 25].Attributes = 7;
	consoleBuffer[47 + screen_x * 25].Char.AsciiChar = 'E';
	consoleBuffer[47 + screen_x * 25].Attributes = 7;
	consoleBuffer[48 + screen_x * 25].Char.AsciiChar = 'S';
	consoleBuffer[48 + screen_x * 25].Attributes = 7;
	consoleBuffer[49 + screen_x * 25].Char.AsciiChar = 'S';
	consoleBuffer[49 + screen_x * 25].Attributes = 7;

	consoleBuffer[51 + screen_x * 25].Char.AsciiChar = 'A';
	consoleBuffer[51 + screen_x * 25].Attributes = 7;
	consoleBuffer[52 + screen_x * 25].Char.AsciiChar = 'N';
	consoleBuffer[52 + screen_x * 25].Attributes = 7;
	consoleBuffer[53 + screen_x * 25].Char.AsciiChar = 'Y';
	consoleBuffer[53 + screen_x * 25].Attributes = 7;

	consoleBuffer[55 + screen_x * 25].Char.AsciiChar = 'K';
	consoleBuffer[55 + screen_x * 25].Attributes = 7;
	consoleBuffer[56 + screen_x * 25].Char.AsciiChar = 'E';
	consoleBuffer[56 + screen_x * 25].Attributes = 7;
	consoleBuffer[57 + screen_x * 25].Char.AsciiChar = 'Y';
	consoleBuffer[57 + screen_x * 25].Attributes = 7;

	consoleBuffer[59 + screen_x * 25].Char.AsciiChar = 'T';
	consoleBuffer[59 + screen_x * 25].Attributes = 7;
	consoleBuffer[60 + screen_x * 25].Char.AsciiChar = 'O';
	consoleBuffer[60 + screen_x * 25].Attributes = 7;

	consoleBuffer[62 + screen_x * 25].Char.AsciiChar = 'C';
	consoleBuffer[62 + screen_x * 25].Attributes = 7;
	consoleBuffer[63 + screen_x * 25].Char.AsciiChar = 'O';
	consoleBuffer[63 + screen_x * 25].Attributes = 7;
	consoleBuffer[64 + screen_x * 25].Char.AsciiChar = 'N';
	consoleBuffer[64 + screen_x * 25].Attributes = 7;
	consoleBuffer[65 + screen_x * 25].Char.AsciiChar = 'T';
	consoleBuffer[65 + screen_x * 25].Attributes = 7;
	consoleBuffer[66 + screen_x * 25].Char.AsciiChar = 'I';
	consoleBuffer[66 + screen_x * 25].Attributes = 7;
	consoleBuffer[67 + screen_x * 25].Char.AsciiChar = 'N';
	consoleBuffer[67 + screen_x * 25].Attributes = 7;
	consoleBuffer[68 + screen_x * 25].Char.AsciiChar = 'U';
	consoleBuffer[68 + screen_x * 25].Attributes = 7;
	consoleBuffer[69 + screen_x * 25].Char.AsciiChar = 'E';
	consoleBuffer[69 + screen_x * 25].Attributes = 7;

	consoleBuffer[71 + screen_x * 25].Char.AsciiChar = '.';
	consoleBuffer[71 + screen_x * 25].Attributes = 7;
	consoleBuffer[73 + screen_x * 25].Char.AsciiChar = '.';
	consoleBuffer[73 + screen_x * 25].Attributes = 7;
	consoleBuffer[75 + screen_x * 25].Char.AsciiChar = '.';
	consoleBuffer[75 + screen_x * 25].Attributes = 7;
}

void init_obj1()
{
	int j = round_obj1;
	if (round_obj1 < 60 && round_obj1 % 2 != 0)
	{
		for (int i = j - round_obj1_fall; i < j - round_obj1_fall + 1 * 1; i++)
		{
			int randy = 0;
			int randx = rand();
			randx %= 89;
			randx += 1;
			obj1[i].X = randx;
			obj1[i].Y = randy;
			round_obj1_fall++;
		}
	}
}

void init_obj2()
{
	int j = round_obj2;
	if (round_obj2 < 48 && round_obj2 % 4 == 3)
	{
		int randy = 0;
		int randx = rand();
		for (int i = j - (round_obj2_fall * 3) + (round_obj2_fall - 1); i < j - (round_obj2_fall * 3) + (round_obj2_fall - 1) + 2; i += 2)
		{
			randx %= 88;
			randx += 1;
			obj2[i].X = randx;
			obj2[i].Y = randy;

			obj2[i + 1].X = randx + 1; //itemcohesion
			obj2[i + 1].Y = randy;
			round_obj2_fall++;
		}
	}
}

void init_obj3x()
{
	int j = round_obj3;
	if (round_obj3 < 60 && round_obj3 % 2 == 0)
	{
		for (int i = (round_obj3 / 2); i <= (round_obj3 / 2); i++)
		{
			int randy = rand();
			int randx = rand();
			randy %= 42;
			randy += 1;
			randx %= 2;
			if (randx == 0)
			{
				randx = 1;
				sideofobj3x[i] = 0;
			}
			else if (randx == 1)
			{
				randx = 89;
				sideofobj3x[i] = 1;
			}
			obj3x[i].X = randx;
			obj3x[i].Y = randy;
			//round_obj1_fall++;
		}
	}
}

void init_obj3y()
{
	int j = round_obj3;
	if (round_obj3 < 48 && round_obj3 % 4 == 3)
	{
		int randy = 0;
		int randx = rand();
		for (int i = j - (round_obj3y_fall * 3) + (round_obj3y_fall - 1); i < j - (round_obj3y_fall * 3) + (round_obj3y_fall - 1) + 2; i += 2)
		{
			randx %= 88;
			randx += 1;
			obj3y[i].X = randx;
			obj3y[i].Y = randy;

			obj3y[i + 1].X = randx + 1; //itemcohesion
			obj3y[i + 1].Y = randy;
			round_obj3y_fall++;
		}
	}
}

void obj1_fall()
{
	int i;
	for (i = 0; i < countofobj1; i++) {
		if (obj1[i].Y >= screen_y - 4) {
			obj1[i] = { (rand() % 89) + 1,1 };
		}
		else {
			obj1[i] = { obj1[i].X,obj1[i].Y += 1 };
			if (((obj1[i].X - posx) < 18 && (obj1[i].X - posx) > 8) && (posy - obj1[i].Y) < 5)
			{
				obj1[i].X -= 1;
			}
			else if (((posx - obj1[i].X) < 18) && ((posx - obj1[i].X) > 8) && ((posy - obj1[i].Y) < 5))
			{
				obj1[i].X += 1;

			}
		}

	}
}

void obj2_fall()
{
	int i;
	int j = rand();
	for (i = 0; i < countofobj2; i += 2) {
		int j = rand();
		if (obj2[i].Y == -1 && obj2[i + 1].Y == -1) //ÂÔ§â´¹·Ñé§¤Ùè 
		{
			obj2[i] = { (j % 88) + 1,1 };
			obj2[i + 1] = { (j % 88) + 2,1 };
		}
		else if (obj2[i].Y >= screen_y - 4) { //µ¡¾ÃéÍÁ¡Ñ¹ ÂÔ§äÁèâ´¹
			obj2[i] = { (j % 88) + 1,1 };
			obj2[i + 1] = { (j % 88) + 2,1 };
		}
		else if (obj2[i + 1].Y >= screen_y - 4 && obj2[i].Y == -1) //ÂÔ§â´¹«éÒÂ áµè¢ÇÒÃÍµ¡
		{
			obj2[i] = { (j % 88) + 1,1 };
			obj2[i + 1] = { (j % 88) + 2,1 };
		}
		else if (obj2[i].Y >= screen_y - 4 && obj2[i + 1].Y == -1) //ÂÔ§â´¹¢ÇÒ áµè«éÒÂÃÍµ¡
		{
			obj2[i] = { (j % 88) + 1,1 };
			obj2[i + 1] = { (j % 88) + 2,1 };
		}
		else if (obj2[i + 1].Y >= 0 && obj2[i].Y == -1) // ÂÔ§â´¹«éÒÂ ¢ÇÒÃÍµ¡
		{
			obj2[i + 1].Y++;
		}
		else if (obj2[i].Y >= 0 && obj2[i + 1].Y == -1) // ÂÔ§â´¹¢ÇÒ «éÒÂÃÍµ¡
		{
			obj2[i].Y++;
		}
		else
		{
			obj2[i] = { obj2[i].X,obj2[i].Y += 1 };
			obj2[i + 1] = { obj2[i + 1].X,obj2[i + 1].Y += 1 };
			if (obj2[i].X > posx && posy - obj2[i].Y < 5)
			{
				if (obj2[i].X - posx < 8)
				{
					obj2[i].X--;
					obj2[i + 1].X--;
				}

			}
			else if (obj2[i].X < posx && posy - obj2[i].Y < 5)
			{
				if (posx - obj2[i].X < 8)
				{
					obj2[i].X++;
					obj2[i + 1].X++;
				}

			}
		}

	}
}

void obj3x_fall()
{
	int i;
	for (i = 0; i < countofobj1; i++) {
		if (sideofobj3x[i] == 0 && obj3x[i].X >= 89) {
			obj3x[i] = { obj3x[i].X = 1,obj3x[i].Y = (rand() % 42) + 1 };
		}
		if (sideofobj3x[i] == 1 && obj3x[i].X <= 3) {
			obj3x[i] = { obj3x[i].X = 89,obj3x[i].Y = (rand() % 42) + 1 };
		}
		else if (sideofobj3x[i] == 0)
		{
			obj3x[i].X++;
		}
		else if (sideofobj3x[i] == 1)
		{
			obj3x[i].X--;
		}

	}
}

void obj3y_fall()
{
	int i;
	int j = rand();
	for (i = 0; i < countofobj3y; i += 2) {
		int j = rand();
		if (obj3y[i].Y == -1 && obj3y[i + 1].Y == -1) //ÂÔ§â´¹·Ñé§¤Ùè 
		{
			obj3y[i] = { (j % 88) + 1,1 };
			obj3y[i + 1] = { (j % 88) + 2,1 };
		}
		else if (obj3y[i].Y >= screen_y - 4) { //µ¡¾ÃéÍÁ¡Ñ¹ ÂÔ§äÁèâ´¹
			obj3y[i] = { (j % 88) + 1,1 };
			obj3y[i + 1] = { (j % 88) + 2,1 };
		}
		else if (obj3y[i + 1].Y >= screen_y - 4 && obj3y[i].Y == -1) //ÂÔ§â´¹«éÒÂ áµè¢ÇÒÃÍµ¡
		{
			obj3y[i] = { (j % 88) + 1,1 };
			obj3y[i + 1] = { (j % 88) + 2,1 };
		}
		else if (obj3y[i].Y >= screen_y - 4 && obj3y[i + 1].Y == -1) //ÂÔ§â´¹¢ÇÒ áµè«éÒÂÃÍµ¡
		{
			obj3y[i] = { (j % 88) + 1,1 };
			obj3y[i + 1] = { (j % 88) + 2,1 };
		}
		else if (obj3y[i + 1].Y >= 0 && obj3y[i].Y == -1) // ÂÔ§â´¹«éÒÂ ¢ÇÒÃÍµ¡
		{
			obj3y[i + 1].Y++;
		}
		else if (obj3y[i].Y >= 0 && obj3y[i + 1].Y == -1) // ÂÔ§â´¹¢ÇÒ «éÒÂÃÍµ¡
		{
			obj3y[i].Y++;
		}
		else
		{
			obj3y[i] = { obj3y[i].X,obj3y[i].Y += 1 };
			obj3y[i + 1] = { obj3y[i + 1].X,obj3y[i + 1].Y += 1 };
			if (obj3y[i].X > posx && posy - obj3y[i].Y < 5)
			{
				if (obj3y[i].X - posx < 8)
				{
					obj3y[i].X--;
					obj3y[i + 1].X--;
				}

			}
			else if (obj3y[i].X < posx && posy - obj3y[i].Y < 5)
			{
				if (posx - obj3y[i].X < 8)
				{
					obj3y[i].X++;
					obj3y[i + 1].X++;
				}

			}
		}

	}
}

void fill_obj1_to_buffer()
{

	for (int i = 0; i < countofobj1; ++i)
	{
		if (obj1[i].X != 0)
		{
			consoleBuffer[obj1[i].X + screen_x * obj1[i].Y].Char.AsciiChar = '*';
			consoleBuffer[obj1[i].X + screen_x * obj1[i].Y].Attributes = 7;
		}
	}
}

void fill_obj2_to_buffer()
{

	for (int i = 0; i < countofobj2; ++i)
	{
		if (obj2[i].X != 0)
		{
			consoleBuffer[obj2[i].X + screen_x * obj2[i].Y].Char.AsciiChar = '*';
			consoleBuffer[obj2[i].X + screen_x * obj2[i].Y].Attributes = 7;
		}
	}
}

void fill_obj3x_to_buffer()
{
	for (int i = 0; i < countofobj3x; ++i)
	{
		if (obj3x[i].X != 0)
		{
			consoleBuffer[obj3x[i].X + screen_x * obj3x[i].Y].Char.AsciiChar = '*';
			consoleBuffer[obj3x[i].X + screen_x * obj3x[i].Y].Attributes = 7;
		}
	}
}

void fill_obj3y_to_buffer()
{
	for (int i = 0; i < countofobj3x; ++i)
	{
		if (obj3y[i].X != 0)
		{
			consoleBuffer[obj3y[i].X + screen_x * obj3y[i].Y].Char.AsciiChar = '*';
			consoleBuffer[obj3y[i].X + screen_x * obj3y[i].Y].Attributes = 7;
		}
	}
}

void init_donotfireobj1() //O
{
	int j = round_obj1;
	if (round_obj1 == 0)
	{
		random_donotfireobj1 = rand();
		random_donotfireobj1 %= 60; //item1_1 is 0-60 60-120 120-180 180-240 240-300
		for (int i = 0; i < countofdonotfireobj1; i++)
		{
			donotfireobj1[i].Y = 0;
		}

	}
	if (round_obj1 == random_donotfireobj1)
	{
		int randy = 2;
		int randx = rand();
		randx %= 89;
		randx += 1;
		donotfireobj1[round_donotfireobj1].X = randx;
		donotfireobj1[round_donotfireobj1].Y = randy;
		round_donotfireobj1++;
		random_donotfireobj1 = rand();
		random_donotfireobj1 %= 60;
		random_donotfireobj1 += (60 * (round_donotfireobj1));

	}




}

void init_donotfireobj2() //O
{
	int j = round_obj2;
	if (round_obj2 == 0)
	{
		random_donotfireobj2 = rand();
		random_donotfireobj2 %= 60; //item2_1 is 0-60 60-120 120-180 180-240 240-300
		for (int i = 0; i < countofdonotfireobj2; i++)
		{
			donotfireobj2[i].Y = 0;
		}

	}
	if (round_obj2 == random_donotfireobj2)
	{
		int randy = 2;
		int randx = rand();
		randx %= 2;
		if (randx == 0)
		{
			randx = 1;
			sideofdonotfireobj2[round_donotfireobj2] = 0;
		}
		else if (randx == 1)
		{
			randx = 89;
			sideofdonotfireobj2[round_donotfireobj2] = 1;

		}
		donotfireobj2[round_donotfireobj2].X = randx;
		donotfireobj2[round_donotfireobj2].Y = randy;
		round_donotfireobj2++;
		random_donotfireobj2 = rand();
		random_donotfireobj2 %= 60;
		random_donotfireobj2 += (60 * (round_donotfireobj2));

	}




}

void init_donotfireobj3()
{
	int j = round_obj3;
	if (round_obj3 == 0)
	{
		random_donotfireobj3 = rand();
		random_donotfireobj3 %= 60; //item2_1 is 0-60 60-120 120-180 180-240 240-300
		for (int i = 3; i < countofdonotfireobj3; i++)
		{
			donotfireobj3[i].Y = -1; //BUG
		}

	}
	if (round_obj3 == random_donotfireobj3)
	{
		donotfireobj3[round_donotfireobj3].X = 1;
		donotfireobj3[round_donotfireobj3].Y = 2;
		round_donotfireobj3++;
		donotfireobj3[round_donotfireobj3].X = 89;
		donotfireobj3[round_donotfireobj3].Y = 2;
		round_donotfireobj3++;
		random_donotfireobj3 = rand();
		random_donotfireobj3 %= 60;
		random_donotfireobj3 += (60 * (round_donotfireobj3));

	}
}

void donotfireobj1_fall()
{
	int i;
	for (i = 0; i < countofdonotfireobj1; i++) {
		if (donotfireobj1[i].Y >= screen_y - 4) {
			donotfireobj1[i] = { (rand() % 89) + 1,-1 };
		}
		else if (donotfireobj1[i].Y >= 2)
		{
			donotfireobj1[i] = { donotfireobj1[i].X,donotfireobj1[i].Y += 1 };
		}

	}
}

void donotfireobj2_fall()
{
	int i;
	for (i = 0; i < countofdonotfireobj2; i++) {
		if (donotfireobj2[i].Y >= screen_y - 4) {
			donotfireobj2[i] = { (rand() % 89) + 1,-2 };
		}
		else if (sideofdonotfireobj2[i] == 0 && donotfireobj2[i].Y >= 1)
		{
			donotfireobj2[i] = { donotfireobj2[i].X += 2,donotfireobj2[i].Y += 1 };
		}
		else if (sideofdonotfireobj2[i] == 1 && donotfireobj2[i].Y >= 1)
		{
			donotfireobj2[i] = { donotfireobj2[i].X -= 2,donotfireobj2[i].Y += 1 };
		}
	}
}

void donotfireobj3_fall()
{
	int i;
	for (i = 0; i < countofdonotfireobj3; i++) {
		if (donotfireobj3[i].Y >= screen_y - 4) {
			donotfireobj3[i] = { (rand() % 89) + 1,-2 };
		}
		else if (sideofdonotfireobj3[i] == 0 && donotfireobj3[i].Y >= 1)
		{
			donotfireobj3[i] = { donotfireobj3[i].X += 2,donotfireobj3[i].Y += 1 };
		}
		else if (sideofdonotfireobj3[i] == 1 && donotfireobj3[i].Y >= 1)
		{
			donotfireobj3[i] = { donotfireobj3[i].X -= 2,donotfireobj3[i].Y += 1 };
		}
	}
}

void fill_donotfireobj1_to_buffer()
{
	for (int i = 0; i < countofdonotfireobj1; ++i)
	{

		if (donotfireobj1[i].X != 0)
		{
			consoleBuffer[donotfireobj1[i].X + screen_x * donotfireobj1[i].Y].Char.AsciiChar = '#';
			consoleBuffer[donotfireobj1[i].X + screen_x * donotfireobj1[i].Y].Attributes = 4;
		}
	}
}

void fill_donotfireobj2_to_buffer()
{
	for (int i = 0; i < countofdonotfireobj2; ++i)
	{

		if (donotfireobj2[i].X != 0)
		{
			consoleBuffer[donotfireobj2[i].X + screen_x * donotfireobj2[i].Y].Char.AsciiChar = '#';
			consoleBuffer[donotfireobj2[i].X + screen_x * donotfireobj2[i].Y].Attributes = 4;
		}
	}
}

void fill_donotfireobj3_to_buffer()
{
	for (int i = 0; i < countofdonotfireobj3; ++i)
	{

		if (donotfireobj3[i].X != 0)
		{
			consoleBuffer[donotfireobj3[i].X + screen_x * donotfireobj3[i].Y].Char.AsciiChar = '#';
			consoleBuffer[donotfireobj3[i].X + screen_x * donotfireobj3[i].Y].Attributes = 4;
		}
	}
}

void test_colision_bullet_normal()
{
	if (State == 0)
	{
		for (int i = 0; i < countofobj1; ++i)
		{
			for (int j = 0; j < countofbullet; ++j)
			{
				if (bullet_normal1[j].X == obj1[i].X && bullet_normal1[j].Y == obj1[i].Y || bullet_normal1[j].X == obj1[i].X && bullet_normal1[j].Y == obj1[i].Y + 1)
				{
					obj1[i] = { rand() % 90,1 };
					bullet_normal1[j].Y = -1;
					firestate_normal1[j] = 0;
					score_now += 65;
				}

			}
		}
		for (int i = 0; i < countofdonotfireobj1; ++i)
		{
			for (int j = 0; j < countofbullet; ++j)
			{
				if (bullet_normal1[j].X == donotfireobj1[i].X && bullet_normal1[j].Y == donotfireobj1[i].Y || bullet_normal1[j].X == donotfireobj1[i].X && bullet_normal1[j].Y == donotfireobj1[i].Y + 1)
				{
					donotfireobj1[i] = { rand() % 90,-1 };
					bullet_normal1[j].Y = -1;
					firestate_normal1[j] = 0;
					hp_ship -= 1;
				}

			}
		}
		for (int i = 0; i < countofobj1; ++i)
		{
			for (int j = 0; j < countofbullet; ++j)
			{
				if (bullet_normal2[j].X == obj1[i].X && bullet_normal2[j].Y == obj1[i].Y || bullet_normal2[j].X == obj1[i].X && bullet_normal2[j].Y == obj1[i].Y + 1)
				{
					obj1[i] = { rand() % 90,1 };
					bullet_normal2[j].Y = -1;
					firestate_normal2[j] = 0;
					score_now += 65;
				}

			}
		}
		for (int i = 0; i < countofdonotfireobj1; ++i)
		{
			for (int j = 0; j < countofbullet; ++j)
			{
				if (bullet_normal2[j].X == donotfireobj1[i].X && bullet_normal2[j].Y == donotfireobj1[i].Y || bullet_normal2[j].X == donotfireobj1[i].X && bullet_normal2[j].Y == donotfireobj1[i].Y + 1)
				{
					donotfireobj1[i] = { rand() % 90,-1 };
					bullet_normal2[j].Y = -1;
					firestate_normal2[j] = 0;
					hp_ship -= 1;
				}

			}
		}
	}
	else if (State == 1)
	{
		for (int i = 0; i < countofobj2; ++i)
		{
			for (int j = 0; j < countofbullet; ++j)
			{
				if (i % 2 == 0)
				{
					if (bullet_normal1[j].X == obj2[i].X && bullet_normal1[j].Y == obj2[i].Y || bullet_normal1[j].X == obj2[i].X && bullet_normal1[j].Y == obj2[i].Y + 1)
					{
						obj2[i] = { rand() % 90,-1 };
						bullet_normal1[j].Y = -1;
						firestate_normal1[j] = 0;
						score_now += 65;
					}
				}
				else if (i % 2 != 0)
				{
					if (bullet_normal1[j].X == obj2[i].X && bullet_normal1[j].Y == obj2[i].Y || bullet_normal1[j].X == obj2[i].X && bullet_normal1[j].Y == obj2[i].Y + 1)
					{
						obj2[i] = { rand() % 90,-1 };
						bullet_normal1[j].Y = -1;
						firestate_normal1[j] = 0;
						score_now += 65;
					}
				}

			}
		}
		for (int i = 0; i < countofdonotfireobj2; ++i)
		{
			for (int j = 0; j < countofbullet; ++j)
			{
				if ((bullet_normal1[j].X == donotfireobj2[i].X && bullet_normal1[j].Y == donotfireobj2[i].Y || bullet_normal1[j].X == donotfireobj2[i].X && bullet_normal1[j].Y == donotfireobj2[i].Y + 1) && bullet_normal1[j].Y > 0)
				{
					donotfireobj2[i] = { rand() % 90,-2 };
					bullet_normal1[j].Y = -1;
					firestate_normal1[j] = 0;
					hp_ship -= 1;

				}

			}
		}
		for (int i = 0; i < countofobj2; ++i)
		{
			for (int j = 0; j < countofbullet; ++j)
			{
				if (i % 2 == 0)
				{
					if (bullet_normal2[j].X == obj2[i].X && bullet_normal2[j].Y == obj2[i].Y || bullet_normal2[j].X == obj2[i].X && bullet_normal2[j].Y == obj2[i].Y + 1)
					{
						obj2[i] = { rand() % 90,-1 };
						bullet_normal2[j].Y = -1;
						firestate_normal2[j] = 0;
						score_now += 65;
					}
				}
				if (i % 2 != 0)
				{
					if (bullet_normal2[j].X == obj2[i].X && bullet_normal2[j].Y == obj2[i].Y || bullet_normal2[j].X == obj2[i].X && bullet_normal2[j].Y == obj2[i].Y + 1)
					{
						obj2[i] = { rand() % 90,-1 };
						bullet_normal2[j].Y = -1;
						firestate_normal2[j] = 0;
						score_now += 65;
					}
				}

			}
		}
		for (int i = 0; i < countofdonotfireobj2; ++i)
		{
			for (int j = 0; j < countofbullet; ++j)
			{
				if ((bullet_normal2[j].X == donotfireobj2[i].X && bullet_normal2[j].Y == donotfireobj2[i].Y || bullet_normal2[j].X == donotfireobj2[i].X && bullet_normal2[j].Y == donotfireobj2[i].Y + 1) && bullet_normal2[j].Y > 0)
				{
					donotfireobj2[i] = { rand() % 90,-2 };
					bullet_normal2[j].Y = -1;
					firestate_normal2[j] = 0;
					hp_ship -= 1;
				}

			}
		}
	}
	else if (State == 2)
	{
		for (int i = 0; i < countofobj3y; ++i)
		{
			for (int j = 0; j < countofbullet; ++j)
			{
				if (i % 2 == 0)
				{
					if (bullet_normal1[j].X == obj3y[i].X && bullet_normal1[j].Y == obj3y[i].Y || bullet_normal1[j].X == obj3y[i].X && bullet_normal1[j].Y == obj3y[i].Y + 1)
					{
						obj3y[i] = { rand() % 90,-1 };
						bullet_normal1[j].Y = -1;
						firestate_normal1[j] = 0;
						score_now += 65;
					}
				}
				else if (i % 2 != 0)
				{
					if (bullet_normal1[j].X == obj3y[i].X && bullet_normal1[j].Y == obj3y[i].Y || bullet_normal1[j].X == obj3y[i].X && bullet_normal1[j].Y == obj3y[i].Y + 1)
					{
						obj3y[i] = { rand() % 90,-1 };
						bullet_normal1[j].Y = -1;
						firestate_normal1[j] = 0;
						score_now += 65;
					}
				}

			}
		}
		for (int i = 0; i < countofobj3x; ++i)
		{
			for (int j = 0; j < countofbullet; ++j)
			{
				if (bullet_normal1[j].X == obj3x[i].X && bullet_normal1[j].Y == obj3x[i].Y || bullet_normal1[j].X == obj3x[i].X && bullet_normal1[j].Y == obj3x[i].Y + 1)
				{
					if (sideofobj3x[i] == 0)
					{
						obj3x[i] = { 1,(rand() % 42 + 1) };
						bullet_normal1[j].Y = -1;
						firestate_normal1[j] = 0;
						score_now += 65;
					}
					else if (sideofobj3x[i] == 1)
					{
						obj3x[i] = { 89,(rand() % 42 + 1) };
						bullet_normal1[j].Y = -1;
						firestate_normal1[j] = 0;
						score_now += 65;
					}
				}

			}
		}
		for (int i = 0; i < countofdonotfireobj3; ++i)
		{
			for (int j = 0; j < countofbullet; ++j)
			{
				if ((bullet_normal1[j].X == donotfireobj3[i].X && bullet_normal1[j].Y == donotfireobj3[i].Y || bullet_normal1[j].X == donotfireobj3[i].X && bullet_normal1[j].Y == donotfireobj3[i].Y + 1) && bullet_normal1[j].Y > 0)
				{
					donotfireobj3[i] = { rand() % 90,-2 };
					bullet_normal1[j].Y = -1;
					firestate_normal1[j] = 0;
					hp_ship -= 1;

				}

			}
		}
		for (int i = 0; i < countofobj3y; ++i)
		{
			for (int j = 0; j < countofbullet; ++j)
			{
				if (i % 2 == 0)
				{
					if (bullet_normal2[j].X == obj3y[i].X && bullet_normal2[j].Y == obj3y[i].Y || bullet_normal2[j].X == obj3y[i].X && bullet_normal2[j].Y == obj3y[i].Y + 1)
					{
						obj3y[i] = { rand() % 90,-1 };
						bullet_normal2[j].Y = -1;
						firestate_normal2[j] = 0;
						score_now += 65;
					}
				}
				if (i % 2 != 0)
				{
					if (bullet_normal2[j].X == obj3y[i].X && bullet_normal2[j].Y == obj3y[i].Y || bullet_normal2[j].X == obj3y[i].X && bullet_normal2[j].Y == obj3y[i].Y + 1)
					{
						obj3y[i] = { rand() % 90,-1 };
						bullet_normal2[j].Y = -1;
						firestate_normal2[j] = 0;
						score_now += 65;
					}
				}

			}
		}
		for (int i = 0; i < countofobj3x; ++i)
		{
			for (int j = 0; j < countofbullet; ++j)
			{
				if (bullet_normal2[j].X == obj3x[i].X && bullet_normal2[j].Y == obj3x[i].Y || bullet_normal2[j].X == obj3x[i].X && bullet_normal2[j].Y == obj3x[i].Y + 1)
				{
					if (sideofobj3x[i] == 0)
					{
						obj3x[i] = { 1,(rand() % 42 + 1) };
						bullet_normal2[j].Y = -1;
						firestate_normal1[j] = 0;
						score_now += 65;
					}
					else if (sideofobj3x[i] == 1)
					{
						obj3x[i] = { 89,(rand() % 42 + 1) };
						bullet_normal2[j].Y = -1;
						firestate_normal1[j] = 0;
						score_now += 65;
					}
				}

			}
		}
		for (int i = 0; i < countofdonotfireobj3; ++i)
		{
			for (int j = 0; j < countofbullet; ++j)
			{
				if ((bullet_normal2[j].X == donotfireobj3[i].X && bullet_normal2[j].Y == donotfireobj3[i].Y || bullet_normal2[j].X == donotfireobj3[i].X && bullet_normal2[j].Y == donotfireobj3[i].Y + 1) && bullet_normal2[j].Y > 0)
				{
					donotfireobj3[i] = { rand() % 90,-2 };
					bullet_normal2[j].Y = -1;
					firestate_normal2[j] = 0;
					hp_ship -= 1;
				}

			}
		}
	}


}

void test_colision_smallship() //Don't move foreward //O
{
	if (State == 0)
	{
		//shiptoobj1
		for (int j = 0; j < countofobj1; ++j)
		{
			if ((posx == obj1[j].X && posy == obj1[j].Y)
				|| ((posx - 1) == obj1[j].X && posy == obj1[j].Y)
				|| ((posx - 2) == obj1[j].X && posy == obj1[j].Y)
				|| ((posx - 3) == obj1[j].X && posy == obj1[j].Y)
				|| ((posx - 4) == obj1[j].X && posy == obj1[j].Y)
				|| ((posx + 1) == obj1[j].X && posy == obj1[j].Y)
				|| ((posx + 2) == obj1[j].X && posy == obj1[j].Y)
				|| ((posx + 3) == obj1[j].X && posy == obj1[j].Y)
				|| ((posx + 4) == obj1[j].X && posy == obj1[j].Y)
				)
			{
				hp_ship -= 1;
				score_now += 65;
				obj1[j] = { (rand() % 89) + 1,1 };
			}
		}
		//shiptodonotfireobj1
		for (int j = 0; j < countofdonotfireobj1; ++j)
		{
			if (posx == donotfireobj1[j].X && posy == donotfireobj1[j].Y
				|| ((posx - 1) == donotfireobj1[j].X && posy == donotfireobj1[j].Y)
				|| ((posx - 2) == donotfireobj1[j].X && posy == donotfireobj1[j].Y)
				|| ((posx - 3) == donotfireobj1[j].X && posy == donotfireobj1[j].Y)
				|| ((posx - 4) == donotfireobj1[j].X && posy == donotfireobj1[j].Y)
				|| ((posx + 1) == donotfireobj1[j].X && posy == donotfireobj1[j].Y)
				|| ((posx + 2) == donotfireobj1[j].X && posy == donotfireobj1[j].Y)
				|| ((posx + 3) == donotfireobj1[j].X && posy == donotfireobj1[j].Y)
				|| ((posx + 4) == donotfireobj1[j].X && posy == donotfireobj1[j].Y)
				)
			{
				hp_ship -= 1;
				donotfireobj1[j] = { (rand() % 89) + 1,-1 };
			}
		}
		//shipetoitem1 maybe +-1.Y
		for (int j = 0; j < countofitem1; ++j)
		{
			if (posx == item1[j].X && posy == item1[j].Y
				|| ((posx - 1) == item1[j].X && posy == item1[j].Y)
				|| ((posx - 2) == item1[j].X && posy == item1[j].Y)
				|| ((posx - 3) == item1[j].X && posy == item1[j].Y)
				|| ((posx - 4) == item1[j].X && posy == item1[j].Y)
				|| ((posx + 1) == item1[j].X && posy == item1[j].Y)
				|| ((posx + 2) == item1[j].X && posy == item1[j].Y)
				|| ((posx + 3) == item1[j].X && posy == item1[j].Y)
				|| ((posx + 4) == item1[j].X && posy == item1[j].Y)
				)
			{
				if (item_2 == false)
				{
					item_1 = true;
				}
				check_item1 = round_obj1;
				item1[j] = { (rand() % 89) + 1,-1 };
			}
		}

		//shipetoitem2 maybe +-1.Y
		for (int j = 0; j < countofitem2; ++j)
		{
			if (posx == item2[j].X && posy == item2[j].Y
				|| ((posx - 1) == item2[j].X && posy == item2[j].Y)
				|| ((posx - 2) == item2[j].X && posy == item2[j].Y)
				|| ((posx - 3) == item2[j].X && posy == item2[j].Y)
				|| ((posx - 4) == item2[j].X && posy == item2[j].Y)
				|| ((posx + 1) == item2[j].X && posy == item2[j].Y)
				|| ((posx + 2) == item2[j].X && posy == item2[j].Y)
				|| ((posx + 3) == item2[j].X && posy == item2[j].Y)
				|| ((posx + 4) == item2[j].X && posy == item2[j].Y)
				)
			{
				if (item_1 == false)
				{
					item_2 = true;
				}
				check_item2 = round_obj1;
				item2[j] = { (rand() % 89) + 1,-1 };
			}
		}

		//shipetoitem3 maybe +-1.Y
		for (int j = 0; j < countofitem3; ++j)
		{
			if (posx == item3[j].X && posy == item3[j].Y
				|| ((posx - 1) == item3[j].X && posy == item3[j].Y)
				|| ((posx - 2) == item3[j].X && posy == item3[j].Y)
				|| ((posx - 3) == item3[j].X && posy == item3[j].Y)
				|| ((posx - 4) == item3[j].X && posy == item3[j].Y)
				|| ((posx + 1) == item3[j].X && posy == item3[j].Y)
				|| ((posx + 2) == item3[j].X && posy == item3[j].Y)
				|| ((posx + 3) == item3[j].X && posy == item3[j].Y)
				|| ((posx + 4) == item3[j].X && posy == item3[j].Y)
				)
			{
				hp_ship += 4;
				item3[j] = { (rand() % 89) + 1,-1 };
			}
		}
	}
	else if (State == 1)
	{
		//shiptoobj2
		for (int j = 0; j < countofobj2; ++j)
		{
			if ((posx == obj2[j].X && posy == obj2[j].Y)
				|| ((posx - 1) == obj2[j].X && posy == obj2[j].Y)
				|| ((posx - 2) == obj2[j].X && posy == obj2[j].Y)
				|| ((posx - 3) == obj2[j].X && posy == obj2[j].Y)
				|| ((posx - 4) == obj2[j].X && posy == obj2[j].Y)
				|| ((posx + 1) == obj2[j].X && posy == obj2[j].Y)
				|| ((posx + 2) == obj2[j].X && posy == obj2[j].Y)
				|| ((posx + 3) == obj2[j].X && posy == obj2[j].Y)
				|| ((posx + 4) == obj2[j].X && posy == obj2[j].Y)
				)
			{
				hp_ship -= 1;
				score_now += 65;
				obj2[j] = { (rand() % 89) + 1,-1 };
			}
		}

		//shiptodonotfireobj2
		for (int j = 0; j < countofdonotfireobj2; ++j)
		{
			if (posx == donotfireobj2[j].X && posy == donotfireobj2[j].Y
				|| ((posx - 1) == donotfireobj2[j].X && posy == donotfireobj2[j].Y)
				|| ((posx - 2) == donotfireobj2[j].X && posy == donotfireobj2[j].Y)
				|| ((posx - 3) == donotfireobj2[j].X && posy == donotfireobj2[j].Y)
				|| ((posx - 4) == donotfireobj2[j].X && posy == donotfireobj2[j].Y)
				|| ((posx + 1) == donotfireobj2[j].X && posy == donotfireobj2[j].Y)
				|| ((posx + 2) == donotfireobj2[j].X && posy == donotfireobj2[j].Y)
				|| ((posx + 3) == donotfireobj2[j].X && posy == donotfireobj2[j].Y)
				|| ((posx + 4) == donotfireobj2[j].X && posy == donotfireobj2[j].Y)
				)
			{
				hp_ship -= 1;
				donotfireobj2[j] = { (rand() % 89) + 1,-1 };
			}
		}
		//shipetoitem1 maybe +-1.Y
		for (int j = 0; j < countofitem1; ++j)
		{
			if (posx == item1[j].X && posy == item1[j].Y
				|| ((posx - 1) == item1[j].X && posy == item1[j].Y)
				|| ((posx - 2) == item1[j].X && posy == item1[j].Y)
				|| ((posx - 3) == item1[j].X && posy == item1[j].Y)
				|| ((posx - 4) == item1[j].X && posy == item1[j].Y)
				|| ((posx + 1) == item1[j].X && posy == item1[j].Y)
				|| ((posx + 2) == item1[j].X && posy == item1[j].Y)
				|| ((posx + 3) == item1[j].X && posy == item1[j].Y)
				|| ((posx + 4) == item1[j].X && posy == item1[j].Y)
				)
			{
				if (item_2 == false)
				{
					item_1 = true;
				}
				check_item1 = round_obj2;
				item1[j] = { (rand() % 89) + 1,-1 };
			}
		}

		//shipetoitem2 maybe +-1.Y
		for (int j = 0; j < countofitem2; ++j)
		{
			if (posx == item2[j].X && posy == item2[j].Y
				|| ((posx - 1) == item2[j].X && posy == item2[j].Y)
				|| ((posx - 2) == item2[j].X && posy == item2[j].Y)
				|| ((posx - 3) == item2[j].X && posy == item2[j].Y)
				|| ((posx - 4) == item2[j].X && posy == item2[j].Y)
				|| ((posx + 1) == item2[j].X && posy == item2[j].Y)
				|| ((posx + 2) == item2[j].X && posy == item2[j].Y)
				|| ((posx + 3) == item2[j].X && posy == item2[j].Y)
				|| ((posx + 4) == item2[j].X && posy == item2[j].Y)
				)
			{
				if (item_1 == false)
				{
					item_2 = true;
				}
				check_item2 = round_obj2;
				item2[j] = { (rand() % 89) + 1,-1 };
			}
		}

		//shipetoitem3 maybe +-1.Y
		for (int j = 0; j < countofitem3; ++j)
		{
			if (posx == item3[j].X && posy == item3[j].Y
				|| ((posx - 1) == item3[j].X && posy == item3[j].Y)
				|| ((posx - 2) == item3[j].X && posy == item3[j].Y)
				|| ((posx - 3) == item3[j].X && posy == item3[j].Y)
				|| ((posx - 4) == item3[j].X && posy == item3[j].Y)
				|| ((posx + 1) == item3[j].X && posy == item3[j].Y)
				|| ((posx + 2) == item3[j].X && posy == item3[j].Y)
				|| ((posx + 3) == item3[j].X && posy == item3[j].Y)
				|| ((posx + 4) == item3[j].X && posy == item3[j].Y)
				)
			{
				hp_ship += 4;
				item3[j] = { (rand() % 89) + 1,-1 };
			}
		}
	}
	else if (State == 2)
	{
		//shiptoobj3x
		for (int j = 0; j < countofobj3x; ++j)
		{
			if ((posx == obj3x[j].X && posy == obj3x[j].Y)
				|| ((posx - 1) == obj3x[j].X && posy == obj3x[j].Y)
				|| ((posx - 2) == obj3x[j].X && posy == obj3x[j].Y)
				|| ((posx - 3) == obj3x[j].X && posy == obj3x[j].Y)
				|| ((posx - 4) == obj3x[j].X && posy == obj3x[j].Y)
				|| ((posx + 1) == obj3x[j].X && posy == obj3x[j].Y)
				|| ((posx + 2) == obj3x[j].X && posy == obj3x[j].Y)
				|| ((posx + 3) == obj3x[j].X && posy == obj3x[j].Y)
				|| ((posx + 4) == obj3x[j].X && posy == obj3x[j].Y)
				)
			{
				hp_ship -= 1;
				score_now += 65;
				if (sideofobj3x[j] == 0)
				{
					obj3x[j] = { 1,(rand() % 42 + 1) };
				}
				else if (sideofobj3x[j] == 1)
				{
					obj3x[j] = { 89,(rand() % 42 + 1) };
				}
			}
		}

		//shiptoobj3y
		for (int j = 0; j < countofobj3y; ++j)
		{
			if ((posx == obj3y[j].X && posy == obj3y[j].Y)
				|| ((posx - 1) == obj3y[j].X && posy == obj3y[j].Y)
				|| ((posx - 2) == obj3y[j].X && posy == obj3y[j].Y)
				|| ((posx - 3) == obj3y[j].X && posy == obj3y[j].Y)
				|| ((posx - 4) == obj3y[j].X && posy == obj3y[j].Y)
				|| ((posx + 1) == obj3y[j].X && posy == obj3y[j].Y)
				|| ((posx + 2) == obj3y[j].X && posy == obj3y[j].Y)
				|| ((posx + 3) == obj3y[j].X && posy == obj3y[j].Y)
				|| ((posx + 4) == obj3y[j].X && posy == obj3y[j].Y)
				)
			{
				hp_ship -= 1;
				score_now += 65;
				obj3y[j] = { (rand() % 89) + 1,-1 };
			}
		}
		//shiptodonotfireobj3
		for (int j = 0; j < countofdonotfireobj3; ++j)
		{
			if (posx == donotfireobj3[j].X && posy == donotfireobj3[j].Y
				|| ((posx - 1) == donotfireobj3[j].X && posy == donotfireobj3[j].Y)
				|| ((posx - 2) == donotfireobj3[j].X && posy == donotfireobj3[j].Y)
				|| ((posx - 3) == donotfireobj3[j].X && posy == donotfireobj3[j].Y)
				|| ((posx - 4) == donotfireobj3[j].X && posy == donotfireobj3[j].Y)
				|| ((posx + 1) == donotfireobj3[j].X && posy == donotfireobj3[j].Y)
				|| ((posx + 2) == donotfireobj3[j].X && posy == donotfireobj3[j].Y)
				|| ((posx + 3) == donotfireobj3[j].X && posy == donotfireobj3[j].Y)
				|| ((posx + 4) == donotfireobj3[j].X && posy == donotfireobj3[j].Y)
				)
			{
				hp_ship -= 1;
				donotfireobj3[j] = { (rand() % 89) + 1,-2 };
			}
		}
		//shipetoitem1 maybe +-1.Y
		for (int j = 0; j < countofitem1; ++j)
		{
			if (posx == item1[j].X && posy == item1[j].Y
				|| ((posx - 1) == item1[j].X && posy == item1[j].Y)
				|| ((posx - 2) == item1[j].X && posy == item1[j].Y)
				|| ((posx - 3) == item1[j].X && posy == item1[j].Y)
				|| ((posx - 4) == item1[j].X && posy == item1[j].Y)
				|| ((posx + 1) == item1[j].X && posy == item1[j].Y)
				|| ((posx + 2) == item1[j].X && posy == item1[j].Y)
				|| ((posx + 3) == item1[j].X && posy == item1[j].Y)
				|| ((posx + 4) == item1[j].X && posy == item1[j].Y)
				)
			{
				if (item_2 == false)
				{
					item_1 = true;
				}
				check_item1 = round_obj3;
				item1[j] = { (rand() % 89) + 1,-1 };
			}
		}

		//shipetoitem2 maybe +-1.Y
		for (int j = 0; j < countofitem2; ++j)
		{
			if (posx == item2[j].X && posy == item2[j].Y
				|| ((posx - 1) == item2[j].X && posy == item2[j].Y)
				|| ((posx - 2) == item2[j].X && posy == item2[j].Y)
				|| ((posx - 3) == item2[j].X && posy == item2[j].Y)
				|| ((posx - 4) == item2[j].X && posy == item2[j].Y)
				|| ((posx + 1) == item2[j].X && posy == item2[j].Y)
				|| ((posx + 2) == item2[j].X && posy == item2[j].Y)
				|| ((posx + 3) == item2[j].X && posy == item2[j].Y)
				|| ((posx + 4) == item2[j].X && posy == item2[j].Y)
				)
			{
				if (item_1 == false)
				{
					item_2 = true;
				}
				check_item2 = round_obj3;
				item2[j] = { (rand() % 89) + 1,-1 };
			}
		}

		//shipetoitem3 maybe +-1.Y
		for (int j = 0; j < countofitem3; ++j)
		{
			if (posx == item3[j].X && posy == item3[j].Y
				|| ((posx - 1) == item3[j].X && posy == item3[j].Y)
				|| ((posx - 2) == item3[j].X && posy == item3[j].Y)
				|| ((posx - 3) == item3[j].X && posy == item3[j].Y)
				|| ((posx - 4) == item3[j].X && posy == item3[j].Y)
				|| ((posx + 1) == item3[j].X && posy == item3[j].Y)
				|| ((posx + 2) == item3[j].X && posy == item3[j].Y)
				|| ((posx + 3) == item3[j].X && posy == item3[j].Y)
				|| ((posx + 4) == item3[j].X && posy == item3[j].Y)
				)
			{
				hp_ship += 4;
				item3[j] = { (rand() % 89) + 1,-1 };
			}
		}
	}
}

void test_collision_bullet_item1()
{
	if (State == 0)
	{
		for (int i = 0; i < countofobj1; ++i)
		{
			for (int j = 0; j < countofbullet; ++j)
			{
				if (bullet_item11[j].X == obj1[i].X && bullet_item11[j].Y == obj1[i].Y || bullet_item11[j].X == obj1[i].X && bullet_item11[j].Y == obj1[i].Y + 1)
				{
					obj1[i] = { rand() % 90,1 };
					bullet_item11[j].Y = -1;
					firestate_item11[j] = 0;
					score_now += 65;
				}

			}
		}
		for (int i = 0; i < countofobj1; ++i)
		{
			for (int j = 0; j < countofbullet; ++j)
			{
				if (bullet_item12[j].X == obj1[i].X && bullet_item12[j].Y == obj1[i].Y || bullet_item12[j].X == obj1[i].X && bullet_item12[j].Y == obj1[i].Y + 1)
				{
					obj1[i] = { rand() % 90,1 };
					bullet_item12[j].Y = -1;
					firestate_item12[j] = 0;
					score_now += 65;
				}

			}
		}
		for (int i = 0; i < countofobj1; ++i)
		{
			for (int j = 0; j < countofbullet; ++j)
			{
				if (bullet_item13[j].X == obj1[i].X && bullet_item13[j].Y == obj1[i].Y || bullet_item13[j].X == obj1[i].X && bullet_item13[j].Y == obj1[i].Y + 1)
				{
					obj1[i] = { rand() % 90,1 };
					bullet_item13[j].Y = -1;
					firestate_item13[j] = 0;
					score_now += 65;
				}

			}
		}
		for (int i = 0; i < countofobj1; ++i)
		{
			for (int j = 0; j < countofbullet; ++j)
			{
				if (bullet_item14[j].X == obj1[i].X && bullet_item14[j].Y == obj1[i].Y || bullet_item14[j].X == obj1[i].X && bullet_item14[j].Y == obj1[i].Y + 1)
				{
					obj1[i] = { rand() % 90,1 };
					bullet_item14[j].Y = -1;
					firestate_item14[j] = 0;
					score_now += 65;
				}

			}
		}
		for (int i = 0; i < countofobj1; ++i)
		{
			for (int j = 0; j < countofbullet; ++j)
			{
				if (bullet_item15[j].X == obj1[i].X && bullet_item15[j].Y == obj1[i].Y || bullet_item15[j].X == obj1[i].X && bullet_item15[j].Y == obj1[i].Y + 1)
				{
					obj1[i] = { rand() % 90,1 };
					bullet_item15[j].Y = -1;
					firestate_item15[j] = 0;
					score_now += 65;
				}

			}
		}
		for (int i = 0; i < countofobj1; ++i)
		{
			for (int j = 0; j < countofbullet; ++j)
			{
				if (bullet_item16[j].X == obj1[i].X && bullet_item16[j].Y == obj1[i].Y || bullet_item16[j].X == obj1[i].X && bullet_item16[j].Y == obj1[i].Y + 1)
				{
					obj1[i] = { rand() % 90,1 };
					bullet_item16[j].Y = -1;
					firestate_item16[j] = 0;
					score_now += 65;
				}

			}
		}for (int i = 0; i < countofobj1; ++i)
		{
			for (int j = 0; j < countofbullet; ++j)
			{
				if (bullet_item17[j].X == obj1[i].X && bullet_item17[j].Y == obj1[i].Y || bullet_item17[j].X == obj1[i].X && bullet_item17[j].Y == obj1[i].Y + 1)
				{
					obj1[i] = { rand() % 90,1 };
					bullet_item17[j].Y = -1;
					firestate_item17[j] = 0;
					score_now += 65;
				}

			}
		}
		for (int i = 0; i < countofobj1; ++i)
		{
			for (int j = 0; j < countofbullet; ++j)
			{
				if (bullet_item18[j].X == obj1[i].X && bullet_item18[j].Y == obj1[i].Y || bullet_item18[j].X == obj1[i].X && bullet_item18[j].Y == obj1[i].Y + 1)
				{
					obj1[i] = { rand() % 90,1 };
					bullet_item18[j].Y = -1;
					firestate_item18[j] = 0;
					score_now += 65;
				}

			}
		}
		for (int i = 0; i < countofobj1; ++i)
		{
			for (int j = 0; j < countofbullet; ++j)
			{
				if (bullet_item19[j].X == obj1[i].X && bullet_item19[j].Y == obj1[i].Y || bullet_item19[j].X == obj1[i].X && bullet_item19[j].Y == obj1[i].Y + 1)
				{
					obj1[i] = { rand() % 90,1 };
					bullet_item19[j].Y = -1;
					firestate_item19[j] = 0;
					score_now += 65;
				}

			}
		}
		for (int i = 0; i < countofdonotfireobj1; ++i)
		{
			for (int j = 0; j < countofbullet; ++j)
			{
				if (bullet_item11[j].X == donotfireobj1[i].X && bullet_item11[j].Y == donotfireobj1[i].Y || bullet_item11[j].X == donotfireobj1[i].X && bullet_item11[j].Y == donotfireobj1[i].Y + 1)
				{
					donotfireobj1[i] = { rand() % 90,-1 };
					bullet_item11[j].Y = -1;
					firestate_item11[j] = 0;
				}

			}
		}
		for (int i = 0; i < countofdonotfireobj1; ++i)
		{
			for (int j = 0; j < countofbullet; ++j)
			{
				if (bullet_item12[j].X == donotfireobj1[i].X && bullet_item12[j].Y == donotfireobj1[i].Y || bullet_item12[j].X == donotfireobj1[i].X && bullet_item12[j].Y == donotfireobj1[i].Y + 1)
				{
					donotfireobj1[i] = { rand() % 90,-1 };
					bullet_item12[j].Y = -1;
					firestate_item12[j] = 0;
				}

			}
		}
		for (int i = 0; i < countofdonotfireobj1; ++i)
		{
			for (int j = 0; j < countofbullet; ++j)
			{
				if (bullet_item13[j].X == donotfireobj1[i].X && bullet_item13[j].Y == donotfireobj1[i].Y || bullet_item13[j].X == donotfireobj1[i].X && bullet_item13[j].Y == donotfireobj1[i].Y + 1)
				{
					donotfireobj1[i] = { rand() % 90,-1 };
					bullet_item13[j].Y = -1;
					firestate_item13[j] = 0;
				}

			}
		}
		for (int i = 0; i < countofdonotfireobj1; ++i)
		{
			for (int j = 0; j < countofbullet; ++j)
			{
				if (bullet_item14[j].X == donotfireobj1[i].X && bullet_item14[j].Y == donotfireobj1[i].Y || bullet_item14[j].X == donotfireobj1[i].X && bullet_item14[j].Y == donotfireobj1[i].Y + 1)
				{
					donotfireobj1[i] = { rand() % 90,-1 };
					bullet_item14[j].Y = -1;
					firestate_item14[j] = 0;
				}

			}
		}
		for (int i = 0; i < countofdonotfireobj1; ++i)
		{
			for (int j = 0; j < countofbullet; ++j)
			{
				if (bullet_item15[j].X == donotfireobj1[i].X && bullet_item15[j].Y == donotfireobj1[i].Y || bullet_item15[j].X == donotfireobj1[i].X && bullet_item15[j].Y == donotfireobj1[i].Y + 1)
				{
					donotfireobj1[i] = { rand() % 90,-1 };
					bullet_item15[j].Y = -1;
					firestate_item13[j] = 0;
				}

			}
		}

		for (int i = 0; i < countofdonotfireobj1; ++i)
		{
			for (int j = 0; j < countofbullet; ++j)
			{
				if (bullet_item16[j].X == donotfireobj1[i].X && bullet_item16[j].Y == donotfireobj1[i].Y || bullet_item16[j].X == donotfireobj1[i].X && bullet_item16[j].Y == donotfireobj1[i].Y + 1)
				{
					donotfireobj1[i] = { rand() % 90,-1 };
					bullet_item16[j].Y = -1;
					firestate_item16[j] = 0;
				}

			}
		}
		for (int i = 0; i < countofdonotfireobj1; ++i)
		{
			for (int j = 0; j < countofbullet; ++j)
			{
				if (bullet_item17[j].X == donotfireobj1[i].X && bullet_item17[j].Y == donotfireobj1[i].Y || bullet_item17[j].X == donotfireobj1[i].X && bullet_item17[j].Y == donotfireobj1[i].Y + 1)
				{
					donotfireobj1[i] = { rand() % 90,-1 };
					bullet_item17[j].Y = -1;
					firestate_item17[j] = 0;
				}

			}
		}
		for (int i = 0; i < countofdonotfireobj1; ++i)
		{
			for (int j = 0; j < countofbullet; ++j)
			{
				if (bullet_item18[j].X == donotfireobj1[i].X && bullet_item18[j].Y == donotfireobj1[i].Y || bullet_item18[j].X == donotfireobj1[i].X && bullet_item18[j].Y == donotfireobj1[i].Y + 1)
				{
					donotfireobj1[i] = { rand() % 90,-1 };
					bullet_item18[j].Y = -1;
					firestate_item18[j] = 0;
				}

			}
			for (int i = 0; i < countofdonotfireobj1; ++i)
			{
				for (int j = 0; j < countofbullet; ++j)
				{
					if (bullet_item19[j].X == donotfireobj1[i].X && bullet_item19[j].Y == donotfireobj1[i].Y || bullet_item19[j].X == donotfireobj1[i].X && bullet_item19[j].Y == donotfireobj1[i].Y + 1)
					{
						donotfireobj1[i] = { rand() % 90,-1 };
						bullet_item19[j].Y = -1;
						firestate_item19[j] = 0;
					}

				}
			}
		}
	}
	else if (State == 1)
	{
		for (int i = 0; i < countofobj2; ++i)
		{
			for (int j = 0; j < countofbullet; ++j)
			{
				if (bullet_item11[j].X == obj2[i].X && bullet_item11[j].Y == obj2[i].Y || bullet_item11[j].X == obj2[i].X && bullet_item11[j].Y == obj2[i].Y + 1)
				{
					obj2[i] = { rand() % 90,-1 };
					bullet_item11[j].Y = -1;
					firestate_item11[j] = 0;
					score_now += 65;
				}

			}
		}
		for (int i = 0; i < countofobj2; ++i)
		{
			for (int j = 0; j < countofbullet; ++j)
			{
				if (bullet_item12[j].X == obj2[i].X && bullet_item12[j].Y == obj2[i].Y || bullet_item12[j].X == obj2[i].X && bullet_item12[j].Y == obj2[i].Y + 1)
				{
					obj2[i] = { rand() % 90,-1 };
					bullet_item12[j].Y = -1;
					firestate_item12[j] = 0;
					score_now += 65;
				}

			}
		}
		for (int i = 0; i < countofobj2; ++i)
		{
			for (int j = 0; j < countofbullet; ++j)
			{
				if (bullet_item13[j].X == obj2[i].X && bullet_item13[j].Y == obj2[i].Y || bullet_item13[j].X == obj2[i].X && bullet_item13[j].Y == obj2[i].Y + 1)
				{
					obj2[i] = { rand() % 90,-1 };
					bullet_item13[j].Y = -1;
					firestate_item13[j] = 0;
					score_now += 65;
				}

			}
		}
		for (int i = 0; i < countofobj2; ++i)
		{
			for (int j = 0; j < countofbullet; ++j)
			{
				if (bullet_item14[j].X == obj2[i].X && bullet_item14[j].Y == obj2[i].Y || bullet_item14[j].X == obj2[i].X && bullet_item14[j].Y == obj2[i].Y + 1)
				{
					obj2[i] = { rand() % 90,-1 };
					bullet_item14[j].Y = -1;
					firestate_item14[j] = 0;
					score_now += 65;
				}

			}
		}
		for (int i = 0; i < countofobj2; ++i)
		{
			for (int j = 0; j < countofbullet; ++j)
			{
				if (bullet_item15[j].X == obj2[i].X && bullet_item15[j].Y == obj2[i].Y || bullet_item15[j].X == obj2[i].X && bullet_item15[j].Y == obj2[i].Y + 1)
				{
					obj2[i] = { rand() % 90,-1 };
					bullet_item15[j].Y = -1;
					firestate_item15[j] = 0;
					score_now += 65;
				}

			}
		}
		for (int i = 0; i < countofobj2; ++i)
		{
			for (int j = 0; j < countofbullet; ++j)
			{
				if (bullet_item16[j].X == obj2[i].X && bullet_item16[j].Y == obj2[i].Y || bullet_item16[j].X == obj2[i].X && bullet_item16[j].Y == obj2[i].Y + 1)
				{
					obj2[i] = { rand() % 90,-1 };
					bullet_item16[j].Y = -1;
					firestate_item16[j] = 0;
					score_now += 65;
				}

			}
		}for (int i = 0; i < countofobj2; ++i)
		{
			for (int j = 0; j < countofbullet; ++j)
			{
				if (bullet_item17[j].X == obj2[i].X && bullet_item17[j].Y == obj2[i].Y || bullet_item17[j].X == obj2[i].X && bullet_item17[j].Y == obj2[i].Y + 1)
				{
					obj2[i] = { rand() % 90,-1 };
					bullet_item17[j].Y = -1;
					firestate_item17[j] = 0;
					score_now += 65;
				}

			}
		}
		for (int i = 0; i < countofobj2; ++i)
		{
			for (int j = 0; j < countofbullet; ++j)
			{
				if (bullet_item18[j].X == obj2[i].X && bullet_item18[j].Y == obj2[i].Y || bullet_item18[j].X == obj2[i].X && bullet_item18[j].Y == obj2[i].Y + 1)
				{
					obj2[i] = { rand() % 90,-1 };
					bullet_item18[j].Y = -1;
					firestate_item18[j] = 0;
					score_now += 65;
				}

			}
		}
		for (int i = 0; i < countofobj2; ++i)
		{
			for (int j = 0; j < countofbullet; ++j)
			{
				if (bullet_item19[j].X == obj2[i].X && bullet_item19[j].Y == obj2[i].Y || bullet_item19[j].X == obj2[i].X && bullet_item19[j].Y == obj2[i].Y + 1)
				{
					obj2[i] = { rand() % 90,-1 };
					bullet_item19[j].Y = -1;
					firestate_item19[j] = 0;
					score_now += 65;
				}

			}
		}
		for (int i = 0; i < countofdonotfireobj2; ++i)
		{
			for (int j = 0; j < countofbullet; ++j)
			{
				if (bullet_item11[j].X == donotfireobj2[i].X && bullet_item11[j].Y == donotfireobj2[i].Y || bullet_item11[j].X == donotfireobj2[i].X && bullet_item11[j].Y == donotfireobj2[i].Y + 1)
				{
					donotfireobj2[i] = { rand() % 90,-1 };
					bullet_item11[j].Y = -1;
					firestate_item11[j] = 0;
				}

			}
		}
		for (int i = 0; i < countofdonotfireobj2; ++i)
		{
			for (int j = 0; j < countofbullet; ++j)
			{
				if (bullet_item12[j].X == donotfireobj2[i].X && bullet_item12[j].Y == donotfireobj2[i].Y || bullet_item12[j].X == donotfireobj2[i].X && bullet_item12[j].Y == donotfireobj2[i].Y + 1)
				{
					donotfireobj2[i] = { rand() % 90,-1 };
					bullet_item12[j].Y = -1;
					firestate_item12[j] = 0;
				}

			}
		}
		for (int i = 0; i < countofdonotfireobj2; ++i)
		{
			for (int j = 0; j < countofbullet; ++j)
			{
				if (bullet_item13[j].X == donotfireobj2[i].X && bullet_item13[j].Y == donotfireobj2[i].Y || bullet_item13[j].X == donotfireobj2[i].X && bullet_item13[j].Y == donotfireobj2[i].Y + 1)
				{
					donotfireobj2[i] = { rand() % 90,-1 };
					bullet_item13[j].Y = -1;
					firestate_item13[j] = 0;
				}

			}
		}
		for (int i = 0; i < countofdonotfireobj2; ++i)
		{
			for (int j = 0; j < countofbullet; ++j)
			{
				if (bullet_item14[j].X == donotfireobj2[i].X && bullet_item14[j].Y == donotfireobj2[i].Y || bullet_item14[j].X == donotfireobj2[i].X && bullet_item14[j].Y == donotfireobj2[i].Y + 1)
				{
					donotfireobj2[i] = { rand() % 90,-1 };
					bullet_item14[j].Y = -1;
					firestate_item14[j] = 0;
				}

			}
		}
		for (int i = 0; i < countofdonotfireobj2; ++i)
		{
			for (int j = 0; j < countofbullet; ++j)
			{
				if (bullet_item15[j].X == donotfireobj2[i].X && bullet_item15[j].Y == donotfireobj2[i].Y || bullet_item15[j].X == donotfireobj2[i].X && bullet_item15[j].Y == donotfireobj2[i].Y + 1)
				{
					donotfireobj2[i] = { rand() % 90,-1 };
					bullet_item15[j].Y = -1;
					firestate_item13[j] = 0;
				}

			}
		}

		for (int i = 0; i < countofdonotfireobj2; ++i)
		{
			for (int j = 0; j < countofbullet; ++j)
			{
				if (bullet_item16[j].X == donotfireobj2[i].X && bullet_item16[j].Y == donotfireobj2[i].Y || bullet_item16[j].X == donotfireobj2[i].X && bullet_item16[j].Y == donotfireobj2[i].Y + 1)
				{
					donotfireobj2[i] = { rand() % 90,-1 };
					bullet_item16[j].Y = -1;
					firestate_item16[j] = 0;
				}

			}
		}
		for (int i = 0; i < countofdonotfireobj2; ++i)
		{
			for (int j = 0; j < countofbullet; ++j)
			{
				if (bullet_item17[j].X == donotfireobj2[i].X && bullet_item17[j].Y == donotfireobj2[i].Y || bullet_item17[j].X == donotfireobj2[i].X && bullet_item17[j].Y == donotfireobj2[i].Y + 1)
				{
					donotfireobj2[i] = { rand() % 90,-1 };
					bullet_item17[j].Y = -1;
					firestate_item17[j] = 0;
				}

			}
		}
		for (int i = 0; i < countofdonotfireobj2; ++i)
		{
			for (int j = 0; j < countofbullet; ++j)
			{
				if (bullet_item18[j].X == donotfireobj2[i].X && bullet_item18[j].Y == donotfireobj2[i].Y || bullet_item18[j].X == donotfireobj2[i].X && bullet_item18[j].Y == donotfireobj2[i].Y + 1)
				{
					donotfireobj2[i] = { rand() % 90,-1 };
					bullet_item18[j].Y = -1;
					firestate_item18[j] = 0;
				}

			}
			for (int i = 0; i < countofdonotfireobj2; ++i)
			{
				for (int j = 0; j < countofbullet; ++j)
				{
					if (bullet_item19[j].X == donotfireobj2[i].X && bullet_item19[j].Y == donotfireobj2[i].Y || bullet_item19[j].X == donotfireobj2[i].X && bullet_item19[j].Y == donotfireobj2[i].Y + 1)
					{
						donotfireobj2[i] = { rand() % 90,-1 };
						bullet_item19[j].Y = -1;
						firestate_item19[j] = 0;
					}

				}
			}
		}
	}
	else if (State == 2)
	{
		for (int i = 0; i < countofobj3x; ++i)
		{
			for (int j = 0; j < countofbullet; ++j)
			{
				if (bullet_item11[j].X == obj3x[i].X && bullet_item11[j].Y == obj3x[i].Y || bullet_item11[j].X == obj3x[i].X && bullet_item11[j].Y == obj3x[i].Y + 1)
				{
					if (sideofobj3x[i] == 0)
					{
						obj3x[i] = { 1,(rand() % 42 + 1) };
					}
					else if (sideofobj3x[i] == 1)
					{
						obj3x[i] = { 89,(rand() % 42 + 1) };
					}
					bullet_item11[j].Y = -1;
					firestate_item11[j] = 0;
					score_now += 65;
				}

			}
		}
		for (int i = 0; i < countofobj3x; ++i)
		{
			for (int j = 0; j < countofbullet; ++j)
			{
				if (bullet_item12[j].X == obj3x[i].X && bullet_item12[j].Y == obj3x[i].Y || bullet_item12[j].X == obj3x[i].X && bullet_item12[j].Y == obj3x[i].Y + 1)
				{
					if (sideofobj3x[i] == 0)
					{
						obj3x[i] = { 1,(rand() % 42 + 1) };
					}
					else if (sideofobj3x[i] == 1)
					{
						obj3x[i] = { 89,(rand() % 42 + 1) };
					}
					bullet_item12[j].Y = -1;
					firestate_item12[j] = 0;
					score_now += 65;
				}

			}
		}
		for (int i = 0; i < countofobj3x; ++i)
		{
			for (int j = 0; j < countofbullet; ++j)
			{
				if (bullet_item13[j].X == obj3x[i].X && bullet_item13[j].Y == obj3x[i].Y || bullet_item13[j].X == obj3x[i].X && bullet_item13[j].Y == obj3x[i].Y + 1)
				{
					if (sideofobj3x[i] == 0)
					{
						obj3x[i] = { 1,(rand() % 42 + 1) };
					}
					else if (sideofobj3x[i] == 1)
					{
						obj3x[i] = { 89,(rand() % 42 + 1) };
					}
					bullet_item13[j].Y = -1;
					firestate_item13[j] = 0;
					score_now += 65;
				}

			}
		}
		for (int i = 0; i < countofobj3x; ++i)
		{
			for (int j = 0; j < countofbullet; ++j)
			{
				if (bullet_item14[j].X == obj3x[i].X && bullet_item14[j].Y == obj3x[i].Y || bullet_item14[j].X == obj3x[i].X && bullet_item14[j].Y == obj3x[i].Y + 1)
				{
					if (sideofobj3x[i] == 0)
					{
						obj3x[i] = { 1,(rand() % 42 + 1) };
					}
					else if (sideofobj3x[i] == 1)
					{
						obj3x[i] = { 89,(rand() % 42 + 1) };
					}
					bullet_item14[j].Y = -1;
					firestate_item14[j] = 0;
					score_now += 65;
				}

			}
		}
		for (int i = 0; i < countofobj3x; ++i)
		{
			for (int j = 0; j < countofbullet; ++j)
			{
				if (bullet_item15[j].X == obj3x[i].X && bullet_item15[j].Y == obj3x[i].Y || bullet_item15[j].X == obj3x[i].X && bullet_item15[j].Y == obj3x[i].Y + 1)
				{
					if (sideofobj3x[i] == 0)
					{
						obj3x[i] = { 1,(rand() % 42 + 1) };
					}
					else if (sideofobj3x[i] == 1)
					{
						obj3x[i] = { 89,(rand() % 42 + 1) };
					}
					bullet_item15[j].Y = -1;
					firestate_item15[j] = 0;
					score_now += 65;
				}

			}
		}
		for (int i = 0; i < countofobj3x; ++i)
		{
			for (int j = 0; j < countofbullet; ++j)
			{
				if (bullet_item16[j].X == obj3x[i].X && bullet_item16[j].Y == obj3x[i].Y || bullet_item16[j].X == obj3x[i].X && bullet_item16[j].Y == obj3x[i].Y + 1)
				{
					if (sideofobj3x[i] == 0)
					{
						obj3x[i] = { 1,(rand() % 42 + 1) };
					}
					else if (sideofobj3x[i] == 1)
					{
						obj3x[i] = { 89,(rand() % 42 + 1) };
					}
					bullet_item16[j].Y = -1;
					firestate_item16[j] = 0;
					score_now += 65;
				}

			}
		}for (int i = 0; i < countofobj3x; ++i)
		{
			for (int j = 0; j < countofbullet; ++j)
			{
				if (bullet_item17[j].X == obj3x[i].X && bullet_item17[j].Y == obj3x[i].Y || bullet_item17[j].X == obj3x[i].X && bullet_item17[j].Y == obj3x[i].Y + 1)
				{
					if (sideofobj3x[i] == 0)
					{
						obj3x[i] = { 1,(rand() % 42 + 1) };
					}
					else if (sideofobj3x[i] == 1)
					{
						obj3x[i] = { 89,(rand() % 42 + 1) };
					}
					bullet_item17[j].Y = -1;
					firestate_item17[j] = 0;
					score_now += 65;
				}

			}
		}
		for (int i = 0; i < countofobj3x; ++i)
		{
			for (int j = 0; j < countofbullet; ++j)
			{
				if (bullet_item18[j].X == obj3x[i].X && bullet_item18[j].Y == obj3x[i].Y || bullet_item18[j].X == obj3x[i].X && bullet_item18[j].Y == obj3x[i].Y + 1)
				{
					if (sideofobj3x[i] == 0)
					{
						obj3x[i] = { 1,(rand() % 42 + 1) };
					}
					else if (sideofobj3x[i] == 1)
					{
						obj3x[i] = { 89,(rand() % 42 + 1) };
					}
					bullet_item18[j].Y = -1;
					firestate_item18[j] = 0;
					score_now += 65;
				}

			}
		}
		for (int i = 0; i < countofobj3x; ++i)
		{
			for (int j = 0; j < countofbullet; ++j)
			{
				if (bullet_item19[j].X == obj3x[i].X && bullet_item19[j].Y == obj3x[i].Y || bullet_item19[j].X == obj3x[i].X && bullet_item19[j].Y == obj3x[i].Y + 1)
				{
					if (sideofobj3x[i] == 0)
					{
						obj3x[i] = { 1,(rand() % 42 + 1) };
					}
					else if (sideofobj3x[i] == 1)
					{
						obj3x[i] = { 89,(rand() % 42 + 1) };
					}
					bullet_item19[j].Y = -1;
					firestate_item19[j] = 0;
					score_now += 65;
				}

			}
		}
		for (int i = 0; i < countofdonotfireobj2; ++i)
		{
			for (int j = 0; j < countofbullet; ++j)
			{
				if (bullet_item11[j].X == donotfireobj2[i].X && bullet_item11[j].Y == donotfireobj2[i].Y || bullet_item11[j].X == donotfireobj2[i].X && bullet_item11[j].Y == donotfireobj2[i].Y + 1)
				{
					donotfireobj2[i] = { rand() % 90,-1 };
					bullet_item11[j].Y = -1;
					firestate_item11[j] = 0;
				}

			}
		}
		for (int i = 0; i < countofdonotfireobj2; ++i)
		{
			for (int j = 0; j < countofbullet; ++j)
			{
				if (bullet_item12[j].X == donotfireobj2[i].X && bullet_item12[j].Y == donotfireobj2[i].Y || bullet_item12[j].X == donotfireobj2[i].X && bullet_item12[j].Y == donotfireobj2[i].Y + 1)
				{
					donotfireobj2[i] = { rand() % 90,-1 };
					bullet_item12[j].Y = -1;
					firestate_item12[j] = 0;
				}

			}
		}
		for (int i = 0; i < countofdonotfireobj2; ++i)
		{
			for (int j = 0; j < countofbullet; ++j)
			{
				if (bullet_item13[j].X == donotfireobj2[i].X && bullet_item13[j].Y == donotfireobj2[i].Y || bullet_item13[j].X == donotfireobj2[i].X && bullet_item13[j].Y == donotfireobj2[i].Y + 1)
				{
					donotfireobj2[i] = { rand() % 90,-1 };
					bullet_item13[j].Y = -1;
					firestate_item13[j] = 0;
				}

			}
		}
		for (int i = 0; i < countofdonotfireobj2; ++i)
		{
			for (int j = 0; j < countofbullet; ++j)
			{
				if (bullet_item14[j].X == donotfireobj2[i].X && bullet_item14[j].Y == donotfireobj2[i].Y || bullet_item14[j].X == donotfireobj2[i].X && bullet_item14[j].Y == donotfireobj2[i].Y + 1)
				{
					donotfireobj2[i] = { rand() % 90,-1 };
					bullet_item14[j].Y = -1;
					firestate_item14[j] = 0;
				}

			}
		}
		for (int i = 0; i < countofdonotfireobj2; ++i)
		{
			for (int j = 0; j < countofbullet; ++j)
			{
				if (bullet_item15[j].X == donotfireobj2[i].X && bullet_item15[j].Y == donotfireobj2[i].Y || bullet_item15[j].X == donotfireobj2[i].X && bullet_item15[j].Y == donotfireobj2[i].Y + 1)
				{
					donotfireobj2[i] = { rand() % 90,-1 };
					bullet_item15[j].Y = -1;
					firestate_item13[j] = 0;
				}

			}
		}

		for (int i = 0; i < countofdonotfireobj2; ++i)
		{
			for (int j = 0; j < countofbullet; ++j)
			{
				if (bullet_item16[j].X == donotfireobj2[i].X && bullet_item16[j].Y == donotfireobj2[i].Y || bullet_item16[j].X == donotfireobj2[i].X && bullet_item16[j].Y == donotfireobj2[i].Y + 1)
				{
					donotfireobj2[i] = { rand() % 90,-1 };
					bullet_item16[j].Y = -1;
					firestate_item16[j] = 0;
				}

			}
		}
		for (int i = 0; i < countofdonotfireobj2; ++i)
		{
			for (int j = 0; j < countofbullet; ++j)
			{
				if (bullet_item17[j].X == donotfireobj2[i].X && bullet_item17[j].Y == donotfireobj2[i].Y || bullet_item17[j].X == donotfireobj2[i].X && bullet_item17[j].Y == donotfireobj2[i].Y + 1)
				{
					donotfireobj2[i] = { rand() % 90,-1 };
					bullet_item17[j].Y = -1;
					firestate_item17[j] = 0;
				}

			}
		}
		for (int i = 0; i < countofdonotfireobj2; ++i)
		{
			for (int j = 0; j < countofbullet; ++j)
			{
				if (bullet_item18[j].X == donotfireobj2[i].X && bullet_item18[j].Y == donotfireobj2[i].Y || bullet_item18[j].X == donotfireobj2[i].X && bullet_item18[j].Y == donotfireobj2[i].Y + 1)
				{
					donotfireobj2[i] = { rand() % 90,-1 };
					bullet_item18[j].Y = -1;
					firestate_item18[j] = 0;
				}

			}
			for (int i = 0; i < countofdonotfireobj2; ++i)
			{
				for (int j = 0; j < countofbullet; ++j)
				{
					if (bullet_item19[j].X == donotfireobj2[i].X && bullet_item19[j].Y == donotfireobj2[i].Y || bullet_item19[j].X == donotfireobj2[i].X && bullet_item19[j].Y == donotfireobj2[i].Y + 1)
					{
						donotfireobj2[i] = { rand() % 90,-1 };
						bullet_item19[j].Y = -1;
						firestate_item19[j] = 0;
					}

				}
			}
		}
	}


}

void test_collision_bullet_item2()
{
	if (State == 0)
	{
		for (int i = 0; i < countofobj1; ++i)
		{
			for (int j = 0; j < countofbullet; ++j)
			{
				if (bullet_item21[j].X == obj1[i].X && bullet_item21[j].Y == obj1[i].Y || bullet_item21[j].X == obj1[i].X && bullet_item21[j].Y == obj1[i].Y + 1)
				{
					obj1[i] = { rand() % 90,1 };
					bullet_item21[j].Y = -1;
					firestate_item21[j] = 0;
					score_now += 65;
				}

			}
		}
		for (int i = 0; i < countofobj1; ++i)
		{
			for (int j = 0; j < countofbullet; ++j)
			{
				if (bullet_item22[j].X == obj1[i].X && bullet_item22[j].Y == obj1[i].Y || bullet_item22[j].X == obj1[i].X && bullet_item22[j].Y == obj1[i].Y + 1)
				{
					obj1[i] = { rand() % 90,1 };
					bullet_item22[j].Y = -1;
					firestate_item22[j] = 0;
					score_now += 65;
				}

			}
		}
		for (int i = 0; i < countofobj1; ++i)
		{
			for (int j = 0; j < countofbullet; ++j)
			{
				if (bullet_item23[j].X == obj1[i].X && bullet_item23[j].Y == obj1[i].Y || bullet_item23[j].X == obj1[i].X && bullet_item23[j].Y == obj1[i].Y + 1)
				{
					obj1[i] = { rand() % 90,1 };
					bullet_item23[j].Y = -1;
					firestate_item23[j] = 0;
					score_now += 65;
				}

			}
		}
		for (int i = 0; i < countofobj1; ++i)
		{
			for (int j = 0; j < countofbullet; ++j)
			{
				if (bullet_item24[j].X == obj1[i].X && bullet_item24[j].Y == obj1[i].Y || bullet_item24[j].X == obj1[i].X && bullet_item24[j].Y == obj1[i].Y + 1)
				{
					obj1[i] = { rand() % 90,1 };
					bullet_item24[j].Y = -1;
					firestate_item24[j] = 0;
					score_now += 65;
				}

			}
		}
		for (int i = 0; i < countofobj1; ++i)
		{
			for (int j = 0; j < countofbullet; ++j)
			{
				if (bullet_item25[j].X == obj1[i].X && bullet_item25[j].Y == obj1[i].Y || bullet_item25[j].X == obj1[i].X && bullet_item25[j].Y == obj1[i].Y + 1)
				{
					obj1[i] = { rand() % 90,1 };
					bullet_item25[j].Y = -1;
					firestate_item25[j] = 0;
					score_now += 65;
				}

			}
		}
		for (int i = 0; i < countofdonotfireobj1; ++i)
		{
			for (int j = 0; j < countofbullet; ++j)
			{
				if (bullet_item21[j].X == donotfireobj1[i].X && bullet_item21[j].Y == donotfireobj1[i].Y || bullet_item21[j].X == donotfireobj1[i].X && bullet_item21[j].Y == donotfireobj1[i].Y + 1)
				{
					donotfireobj1[i] = { rand() % 90,-1 };
					bullet_item21[j].Y = -1;
					firestate_item21[j] = 0;
				}

			}
		}
		for (int i = 0; i < countofdonotfireobj1; ++i)
		{
			for (int j = 0; j < countofbullet; ++j)
			{
				if (bullet_item22[j].X == donotfireobj1[i].X && bullet_item22[j].Y == donotfireobj1[i].Y || bullet_item22[j].X == donotfireobj1[i].X && bullet_item22[j].Y == donotfireobj1[i].Y + 1)
				{
					donotfireobj1[i] = { rand() % 90,-1 };
					bullet_item22[j].Y = -1;
					firestate_item22[j] = 0;
				}

			}
		}
		for (int i = 0; i < countofdonotfireobj1; ++i)
		{
			for (int j = 0; j < countofbullet; ++j)
			{
				if (bullet_item23[j].X == donotfireobj1[i].X && bullet_item23[j].Y == donotfireobj1[i].Y || bullet_item23[j].X == donotfireobj1[i].X && bullet_item23[j].Y == donotfireobj1[i].Y + 1)
				{
					donotfireobj1[i] = { rand() % 90,-1 };
					bullet_item23[j].Y = -1;
					firestate_item23[j] = 0;
				}

			}
		}
		for (int i = 0; i < countofdonotfireobj1; ++i)
		{
			for (int j = 0; j < countofbullet; ++j)
			{
				if (bullet_item24[j].X == donotfireobj1[i].X && bullet_item24[j].Y == donotfireobj1[i].Y || bullet_item24[j].X == donotfireobj1[i].X && bullet_item24[j].Y == donotfireobj1[i].Y + 1)
				{
					donotfireobj1[i] = { rand() % 90,-1 };
					bullet_item24[j].Y = -1;
					firestate_item24[j] = 0;
				}

			}
		}
		for (int i = 0; i < countofdonotfireobj1; ++i)
		{
			for (int j = 0; j < countofbullet; ++j)
			{
				if (bullet_item25[j].X == donotfireobj1[i].X && bullet_item25[j].Y == donotfireobj1[i].Y || bullet_item25[j].X == donotfireobj1[i].X && bullet_item25[j].Y == donotfireobj1[i].Y + 1)
				{
					donotfireobj1[i] = { rand() % 90,-1 };
					bullet_item25[j].Y = -1;
					firestate_item25[j] = 0;
				}

			}
		}
	}
	else if (State == 1)
	{
		for (int i = 0; i < countofobj2; ++i)
		{
			for (int j = 0; j < countofbullet; ++j)
			{
				if (bullet_item21[j].X == obj2[i].X && bullet_item21[j].Y == obj2[i].Y || bullet_item21[j].X == obj2[i].X && bullet_item21[j].Y == obj2[i].Y + 1)
				{
					obj2[i] = { rand() % 90,-1 };
					bullet_item21[j].Y = -1;
					firestate_item21[j] = 0;
					score_now += 65;
				}

			}
		}
		for (int i = 0; i < countofobj2; ++i)
		{
			for (int j = 0; j < countofbullet; ++j)
			{
				if (bullet_item22[j].X == obj2[i].X && bullet_item22[j].Y == obj2[i].Y || bullet_item22[j].X == obj2[i].X && bullet_item22[j].Y == obj2[i].Y + 1)
				{
					obj2[i] = { rand() % 90,-1 };
					bullet_item22[j].Y = -1;
					firestate_item22[j] = 0;
					score_now += 65;
				}

			}
		}
		for (int i = 0; i < countofobj2; ++i)
		{
			for (int j = 0; j < countofbullet; ++j)
			{
				if (bullet_item23[j].X == obj2[i].X && bullet_item23[j].Y == obj2[i].Y || bullet_item23[j].X == obj2[i].X && bullet_item23[j].Y == obj2[i].Y + 1)
				{
					obj2[i] = { rand() % 90,-1 };
					bullet_item23[j].Y = -1;
					firestate_item23[j] = 0;
					score_now += 65;
				}

			}
		}
		for (int i = 0; i < countofobj2; ++i)
		{
			for (int j = 0; j < countofbullet; ++j)
			{
				if (bullet_item24[j].X == obj2[i].X && bullet_item24[j].Y == obj2[i].Y || bullet_item24[j].X == obj2[i].X && bullet_item24[j].Y == obj2[i].Y + 1)
				{
					obj2[i] = { rand() % 90,-1 };
					bullet_item24[j].Y = -1;
					firestate_item24[j] = 0;
					score_now += 65;
				}

			}
		}
		for (int i = 0; i < countofobj2; ++i)
		{
			for (int j = 0; j < countofbullet; ++j)
			{
				if (bullet_item25[j].X == obj2[i].X && bullet_item25[j].Y == obj2[i].Y || bullet_item25[j].X == obj2[i].X && bullet_item25[j].Y == obj2[i].Y + 1)
				{
					obj2[i] = { rand() % 90,-1 };
					bullet_item25[j].Y = -1;
					firestate_item25[j] = 0;
					score_now += 65;
				}

			}
		}
		for (int i = 0; i < countofdonotfireobj2; ++i)
		{
			for (int j = 0; j < countofbullet; ++j)
			{
				if (bullet_item21[j].X == donotfireobj2[i].X && bullet_item21[j].Y == donotfireobj2[i].Y || bullet_item21[j].X == donotfireobj2[i].X && bullet_item21[j].Y == donotfireobj2[i].Y + 1)
				{
					donotfireobj2[i] = { rand() % 90,-1 };
					bullet_item21[j].Y = -1;
					firestate_item21[j] = 0;
				}

			}
		}
		for (int i = 0; i < countofdonotfireobj2; ++i)
		{
			for (int j = 0; j < countofbullet; ++j)
			{
				if (bullet_item22[j].X == donotfireobj2[i].X && bullet_item22[j].Y == donotfireobj2[i].Y || bullet_item22[j].X == donotfireobj2[i].X && bullet_item22[j].Y == donotfireobj2[i].Y + 1)
				{
					donotfireobj2[i] = { rand() % 90,-1 };
					bullet_item22[j].Y = -1;
					firestate_item22[j] = 0;
				}

			}
		}
		for (int i = 0; i < countofdonotfireobj2; ++i)
		{
			for (int j = 0; j < countofbullet; ++j)
			{
				if (bullet_item23[j].X == donotfireobj2[i].X && bullet_item23[j].Y == donotfireobj2[i].Y || bullet_item23[j].X == donotfireobj2[i].X && bullet_item23[j].Y == donotfireobj2[i].Y + 1)
				{
					donotfireobj2[i] = { rand() % 90,-1 };
					bullet_item23[j].Y = -1;
					firestate_item23[j] = 0;
				}

			}
		}
		for (int i = 0; i < countofdonotfireobj2; ++i)
		{
			for (int j = 0; j < countofbullet; ++j)
			{
				if (bullet_item24[j].X == donotfireobj2[i].X && bullet_item24[j].Y == donotfireobj2[i].Y || bullet_item24[j].X == donotfireobj2[i].X && bullet_item24[j].Y == donotfireobj2[i].Y + 1)
				{
					donotfireobj2[i] = { rand() % 90,-1 };
					bullet_item24[j].Y = -1;
					firestate_item24[j] = 0;
				}

			}
		}
		for (int i = 0; i < countofdonotfireobj2; ++i)
		{
			for (int j = 0; j < countofbullet; ++j)
			{
				if (bullet_item25[j].X == donotfireobj2[i].X && bullet_item25[j].Y == donotfireobj2[i].Y || bullet_item25[j].X == donotfireobj2[i].X && bullet_item25[j].Y == donotfireobj2[i].Y + 1)
				{
					donotfireobj2[i] = { rand() % 90,-1 };
					bullet_item25[j].Y = -1;
					firestate_item25[j] = 0;
				}

			}
		}
	}
}

void test_colision_largeship()
{
	if (State == 0)
	{
		//largeshiptoobj1
		for (int j = 0; j < countofobj1; ++j)
		{
			if (posx == obj1[j].X && posy == obj1[j].Y
				|| (posx == obj1[j].X && (posy - 2) == obj1[j].Y)
				|| (posx == obj1[j].X && (posy - 1) == obj1[j].Y)
				|| ((posx - 2) == obj1[j].X && posy == obj1[j].Y)
				|| ((posx - 1) == obj1[j].X && posy == obj1[j].Y)
				|| ((posx + 1) == obj1[j].X && posy == obj1[j].Y)
				|| ((posx + 2) == obj1[j].X && posy == obj1[j].Y)
				|| ((posx - 1) == obj1[j].X && (posy + 1) == obj1[j].Y)
				|| (posx == obj1[j].X && (posy + 1) == obj1[j].Y)
				|| ((posx + 1) == obj1[j].X && (posy + 1) == obj1[j].Y)
				|| ((posx - 4) == obj1[j].X && (posy + 2) == obj1[j].Y)
				|| ((posx - 3) == obj1[j].X && (posy + 2) == obj1[j].Y)
				|| ((posx - 2) == obj1[j].X && (posy + 2) == obj1[j].Y)
				|| ((posx - 1) == obj1[j].X && (posy + 2) == obj1[j].Y)
				|| (posx == obj1[j].X && (posy + 2) == obj1[j].Y)
				|| ((posx + 1) == obj1[j].X && (posy + 2) == obj1[j].Y)
				|| ((posx + 2) == obj1[j].X && (posy + 2) == obj1[j].Y)
				|| ((posx + 3) == obj1[j].X && (posy + 2) == obj1[j].Y)
				|| ((posx + 4) == obj1[j].X && (posy + 2) == obj1[j].Y)
				)
			{
				score_now += 65;
				obj1[j] = { (rand() % 89) + 1,1 };
			}
		}

		//largeshiptodonotfireobj1
		for (int j = 0; j < countofdonotfireobj1; ++j)
		{
			if (posx == obj1[j].X && posy == obj1[j].Y
				|| (posx == obj1[j].X && (posy - 2) == obj1[j].Y)
				|| (posx == obj1[j].X && (posy - 1) == obj1[j].Y)
				|| ((posx - 2) == obj1[j].X && posy == obj1[j].Y)
				|| ((posx - 1) == obj1[j].X && posy == obj1[j].Y)
				|| ((posx + 1) == obj1[j].X && posy == obj1[j].Y)
				|| ((posx + 2) == obj1[j].X && posy == obj1[j].Y)
				|| ((posx - 1) == obj1[j].X && (posy + 1) == obj1[j].Y)
				|| (posx == obj1[j].X && (posy + 1) == obj1[j].Y)
				|| ((posx + 1) == obj1[j].X && (posy + 1) == obj1[j].Y)
				|| ((posx - 4) == obj1[j].X && (posy + 2) == obj1[j].Y)
				|| ((posx - 3) == obj1[j].X && (posy + 2) == obj1[j].Y)
				|| ((posx - 2) == obj1[j].X && (posy + 2) == obj1[j].Y)
				|| ((posx - 1) == obj1[j].X && (posy + 2) == obj1[j].Y)
				|| (posx == obj1[j].X && (posy + 2) == obj1[j].Y)
				|| ((posx + 1) == obj1[j].X && (posy + 2) == obj1[j].Y)
				|| ((posx + 2) == obj1[j].X && (posy + 2) == obj1[j].Y)
				|| ((posx + 3) == obj1[j].X && (posy + 2) == obj1[j].Y)
				|| ((posx + 4) == obj1[j].X && (posy + 2) == obj1[j].Y)
				)
			{
				obj1[j] = { (rand() % 89) + 1,-1 };
			}
		}

		//largeshiptoitem1
		for (int j = 0; j < countofitem1; ++j)
		{
			if (posx == item1[j].X && posy == item1[j].Y
				|| (posx == item1[j].X && (posy - 2) == item1[j].Y)
				|| (posx == item1[j].X && (posy - 1) == item1[j].Y)
				|| ((posx - 2) == item1[j].X && posy == item1[j].Y)
				|| ((posx - 1) == item1[j].X && posy == item1[j].Y)
				|| ((posx + 1) == item1[j].X && posy == item1[j].Y)
				|| ((posx + 2) == item1[j].X && posy == item1[j].Y)
				|| ((posx - 1) == item1[j].X && (posy + 1) == item1[j].Y)
				|| (posx == item1[j].X && (posy + 1) == item1[j].Y)
				|| ((posx + 1) == item1[j].X && (posy + 1) == item1[j].Y)
				|| ((posx - 4) == item1[j].X && (posy + 2) == item1[j].Y)
				|| ((posx - 3) == item1[j].X && (posy + 2) == item1[j].Y)
				|| ((posx - 2) == item1[j].X && (posy + 2) == item1[j].Y)
				|| ((posx - 1) == item1[j].X && (posy + 2) == item1[j].Y)
				|| (posx == item1[j].X && (posy + 2) == item1[j].Y)
				|| ((posx + 1) == item1[j].X && (posy + 2) == item1[j].Y)
				|| ((posx + 2) == item1[j].X && (posy + 2) == item1[j].Y)
				|| ((posx + 3) == item1[j].X && (posy + 2) == item1[j].Y)
				|| ((posx + 4) == item1[j].X && (posy + 2) == item1[j].Y)
				)
			{
				if (item_2 == false)
				{
					item_1 = true;
					check_item1 = round_obj1;
					item1[j] = { (rand() % 89) + 1,-1 };
				}
				else if (item_2 == true)
				{
					item_2 = false;
					item_1 = true;
					check_item1 = round_obj1;
					item1[j] = { (rand() % 89) + 1,-1 };
				}
			}
		}

		//largeshiptoitem2
		for (int j = 0; j < countofitem2; ++j)
		{
			if (posx == item2[j].X && posy == item2[j].Y
				|| (posx == item2[j].X && (posy - 2) == item2[j].Y)
				|| (posx == item2[j].X && (posy - 1) == item2[j].Y)
				|| ((posx - 2) == item2[j].X && posy == item2[j].Y)
				|| ((posx - 1) == item2[j].X && posy == item2[j].Y)
				|| ((posx + 1) == item2[j].X && posy == item2[j].Y)
				|| ((posx + 2) == item2[j].X && posy == item2[j].Y)
				|| ((posx - 1) == item2[j].X && (posy + 1) == item2[j].Y)
				|| (posx == item2[j].X && (posy + 1) == item2[j].Y)
				|| ((posx + 1) == item2[j].X && (posy + 1) == item2[j].Y)
				|| ((posx - 4) == item2[j].X && (posy + 2) == item2[j].Y)
				|| ((posx - 3) == item2[j].X && (posy + 2) == item2[j].Y)
				|| ((posx - 2) == item2[j].X && (posy + 2) == item2[j].Y)
				|| ((posx - 1) == item2[j].X && (posy + 2) == item2[j].Y)
				|| (posx == item2[j].X && (posy + 2) == item2[j].Y)
				|| ((posx + 1) == item2[j].X && (posy + 2) == item2[j].Y)
				|| ((posx + 2) == item2[j].X && (posy + 2) == item2[j].Y)
				|| ((posx + 3) == item2[j].X && (posy + 2) == item2[j].Y)
				|| ((posx + 4) == item2[j].X && (posy + 2) == item2[j].Y)
				)
			{
				if (item_1 == false)
				{
					item_2 = true;
					check_item2 = round_obj1;
					item2[j] = { (rand() % 89) + 1,-1 };
				}
				else if (item_1 == true)
				{
					item_1 = false;
					item_2 = true;
					check_item2 = round_obj1;
					item2[j] = { (rand() % 89) + 1,-1 };
				}
			}
		}

		//largeshiptoitem3
		for (int j = 0; j < countofitem3; ++j)
		{
			if (posx == item3[j].X && posy == item3[j].Y
				|| (posx == item3[j].X && (posy - 2) == item3[j].Y)
				|| (posx == item3[j].X && (posy - 1) == item3[j].Y)
				|| ((posx - 2) == item3[j].X && posy == item3[j].Y)
				|| ((posx - 1) == item3[j].X && posy == item3[j].Y)
				|| ((posx + 1) == item3[j].X && posy == item3[j].Y)
				|| ((posx + 2) == item3[j].X && posy == item3[j].Y)
				|| ((posx - 1) == item3[j].X && (posy + 1) == item3[j].Y)
				|| (posx == item3[j].X && (posy + 1) == item3[j].Y)
				|| ((posx + 1) == item3[j].X && (posy + 1) == item3[j].Y)
				|| ((posx - 4) == item3[j].X && (posy + 2) == item3[j].Y)
				|| ((posx - 3) == item3[j].X && (posy + 2) == item3[j].Y)
				|| ((posx - 2) == item3[j].X && (posy + 2) == item3[j].Y)
				|| ((posx - 1) == item3[j].X && (posy + 2) == item3[j].Y)
				|| (posx == item3[j].X && (posy + 2) == item3[j].Y)
				|| ((posx + 1) == item3[j].X && (posy + 2) == item3[j].Y)
				|| ((posx + 2) == item3[j].X && (posy + 2) == item3[j].Y)
				|| ((posx + 3) == item3[j].X && (posy + 2) == item3[j].Y)
				|| ((posx + 4) == item3[j].X && (posy + 2) == item3[j].Y)
				)
			{
				hp_ship += 7;
			}
		}
	}
	else if (State == 1)
	{
		//largeshiptoobj2
		for (int j = 0; j < countofobj2; ++j)
		{
			if (posx == obj2[j].X && posy == obj2[j].Y
				|| (posx == obj2[j].X && (posy - 2) == obj2[j].Y)
				|| (posx == obj2[j].X && (posy - 1) == obj2[j].Y)
				|| ((posx - 2) == obj2[j].X && posy == obj2[j].Y)
				|| ((posx - 1) == obj2[j].X && posy == obj2[j].Y)
				|| ((posx + 1) == obj2[j].X && posy == obj2[j].Y)
				|| ((posx + 2) == obj2[j].X && posy == obj2[j].Y)
				|| ((posx - 1) == obj2[j].X && (posy + 1) == obj2[j].Y)
				|| (posx == obj2[j].X && (posy + 1) == obj2[j].Y)
				|| ((posx + 1) == obj2[j].X && (posy + 1) == obj2[j].Y)
				|| ((posx - 4) == obj2[j].X && (posy + 2) == obj2[j].Y)
				|| ((posx - 3) == obj2[j].X && (posy + 2) == obj2[j].Y)
				|| ((posx - 2) == obj2[j].X && (posy + 2) == obj2[j].Y)
				|| ((posx - 1) == obj2[j].X && (posy + 2) == obj2[j].Y)
				|| (posx == obj2[j].X && (posy + 2) == obj2[j].Y)
				|| ((posx + 1) == obj2[j].X && (posy + 2) == obj2[j].Y)
				|| ((posx + 2) == obj2[j].X && (posy + 2) == obj2[j].Y)
				|| ((posx + 3) == obj2[j].X && (posy + 2) == obj2[j].Y)
				|| ((posx + 4) == obj2[j].X && (posy + 2) == obj2[j].Y)
				)
			{
				score_now += 65;
				obj2[j] = { (rand() % 89) + 1,-1 };
			}
		}

		//largeshiptodonotfireobj2
		for (int j = 0; j < countofdonotfireobj2; ++j)
		{
			if (posx == obj2[j].X && posy == obj2[j].Y
				|| (posx == obj2[j].X && (posy - 2) == obj2[j].Y)
				|| (posx == obj2[j].X && (posy - 1) == obj2[j].Y)
				|| ((posx - 2) == obj2[j].X && posy == obj2[j].Y)
				|| ((posx - 1) == obj2[j].X && posy == obj2[j].Y)
				|| ((posx + 1) == obj2[j].X && posy == obj2[j].Y)
				|| ((posx + 2) == obj2[j].X && posy == obj2[j].Y)
				|| ((posx - 1) == obj2[j].X && (posy + 1) == obj2[j].Y)
				|| (posx == obj2[j].X && (posy + 1) == obj2[j].Y)
				|| ((posx + 1) == obj2[j].X && (posy + 1) == obj2[j].Y)
				|| ((posx - 4) == obj2[j].X && (posy + 2) == obj2[j].Y)
				|| ((posx - 3) == obj2[j].X && (posy + 2) == obj2[j].Y)
				|| ((posx - 2) == obj2[j].X && (posy + 2) == obj2[j].Y)
				|| ((posx - 1) == obj2[j].X && (posy + 2) == obj2[j].Y)
				|| (posx == obj2[j].X && (posy + 2) == obj2[j].Y)
				|| ((posx + 1) == obj2[j].X && (posy + 2) == obj2[j].Y)
				|| ((posx + 2) == obj2[j].X && (posy + 2) == obj2[j].Y)
				|| ((posx + 3) == obj2[j].X && (posy + 2) == obj2[j].Y)
				|| ((posx + 4) == obj2[j].X && (posy + 2) == obj2[j].Y)
				)
			{
				obj2[j] = { (rand() % 89) + 1,-1 };
			}
		}

		//largeshiptoitem1
		for (int j = 0; j < countofitem1; ++j)
		{
			if (posx == item1[j].X && posy == item1[j].Y
				|| (posx == item1[j].X && (posy - 2) == item1[j].Y)
				|| (posx == item1[j].X && (posy - 1) == item1[j].Y)
				|| ((posx - 2) == item1[j].X && posy == item1[j].Y)
				|| ((posx - 1) == item1[j].X && posy == item1[j].Y)
				|| ((posx + 1) == item1[j].X && posy == item1[j].Y)
				|| ((posx + 2) == item1[j].X && posy == item1[j].Y)
				|| ((posx - 1) == item1[j].X && (posy + 1) == item1[j].Y)
				|| (posx == item1[j].X && (posy + 1) == item1[j].Y)
				|| ((posx + 1) == item1[j].X && (posy + 1) == item1[j].Y)
				|| ((posx - 4) == item1[j].X && (posy + 2) == item1[j].Y)
				|| ((posx - 3) == item1[j].X && (posy + 2) == item1[j].Y)
				|| ((posx - 2) == item1[j].X && (posy + 2) == item1[j].Y)
				|| ((posx - 1) == item1[j].X && (posy + 2) == item1[j].Y)
				|| (posx == item1[j].X && (posy + 2) == item1[j].Y)
				|| ((posx + 1) == item1[j].X && (posy + 2) == item1[j].Y)
				|| ((posx + 2) == item1[j].X && (posy + 2) == item1[j].Y)
				|| ((posx + 3) == item1[j].X && (posy + 2) == item1[j].Y)
				|| ((posx + 4) == item1[j].X && (posy + 2) == item1[j].Y)
				)
			{
				if (item_2 == false)
				{
					item_1 = true;
					check_item1 = round_obj2;
					item1[j] = { (rand() % 89) + 1,-1 };
				}
				else if (item_2 == true)
				{
					item_2 = false;
					item_1 = true;
					check_item1 = round_obj2;
					item1[j] = { (rand() % 89) + 1,-1 };
				}
			}
		}

		//largeshiptoitem2
		for (int j = 0; j < countofitem2; ++j)
		{
			if (posx == item2[j].X && posy == item2[j].Y
				|| (posx == item2[j].X && (posy - 2) == item2[j].Y)
				|| (posx == item2[j].X && (posy - 1) == item2[j].Y)
				|| ((posx - 2) == item2[j].X && posy == item2[j].Y)
				|| ((posx - 1) == item2[j].X && posy == item2[j].Y)
				|| ((posx + 1) == item2[j].X && posy == item2[j].Y)
				|| ((posx + 2) == item2[j].X && posy == item2[j].Y)
				|| ((posx - 1) == item2[j].X && (posy + 1) == item2[j].Y)
				|| (posx == item2[j].X && (posy + 1) == item2[j].Y)
				|| ((posx + 1) == item2[j].X && (posy + 1) == item2[j].Y)
				|| ((posx - 4) == item2[j].X && (posy + 2) == item2[j].Y)
				|| ((posx - 3) == item2[j].X && (posy + 2) == item2[j].Y)
				|| ((posx - 2) == item2[j].X && (posy + 2) == item2[j].Y)
				|| ((posx - 1) == item2[j].X && (posy + 2) == item2[j].Y)
				|| (posx == item2[j].X && (posy + 2) == item2[j].Y)
				|| ((posx + 1) == item2[j].X && (posy + 2) == item2[j].Y)
				|| ((posx + 2) == item2[j].X && (posy + 2) == item2[j].Y)
				|| ((posx + 3) == item2[j].X && (posy + 2) == item2[j].Y)
				|| ((posx + 4) == item2[j].X && (posy + 2) == item2[j].Y)
				)
			{
				if (item_1 == false)
				{
					item_2 = true;
					check_item2 = round_obj2;
					item2[j] = { (rand() % 89) + 1,-1 };
				}
				else if (item_1 == true)
				{
					item_1 = false;
					item_2 = true;
					check_item2 = round_obj2;
					item2[j] = { (rand() % 89) + 1,-1 };
				}
			}
		}

		//largeshiptoitem3
		for (int j = 0; j < countofitem3; ++j)
		{
			if (posx == item3[j].X && posy == item3[j].Y
				|| (posx == item3[j].X && (posy - 2) == item3[j].Y)
				|| (posx == item3[j].X && (posy - 1) == item3[j].Y)
				|| ((posx - 2) == item3[j].X && posy == item3[j].Y)
				|| ((posx - 1) == item3[j].X && posy == item3[j].Y)
				|| ((posx + 1) == item3[j].X && posy == item3[j].Y)
				|| ((posx + 2) == item3[j].X && posy == item3[j].Y)
				|| ((posx - 1) == item3[j].X && (posy + 1) == item3[j].Y)
				|| (posx == item3[j].X && (posy + 1) == item3[j].Y)
				|| ((posx + 1) == item3[j].X && (posy + 1) == item3[j].Y)
				|| ((posx - 4) == item3[j].X && (posy + 2) == item3[j].Y)
				|| ((posx - 3) == item3[j].X && (posy + 2) == item3[j].Y)
				|| ((posx - 2) == item3[j].X && (posy + 2) == item3[j].Y)
				|| ((posx - 1) == item3[j].X && (posy + 2) == item3[j].Y)
				|| (posx == item3[j].X && (posy + 2) == item3[j].Y)
				|| ((posx + 1) == item3[j].X && (posy + 2) == item3[j].Y)
				|| ((posx + 2) == item3[j].X && (posy + 2) == item3[j].Y)
				|| ((posx + 3) == item3[j].X && (posy + 2) == item3[j].Y)
				|| ((posx + 4) == item3[j].X && (posy + 2) == item3[j].Y)
				)
			{
				hp_ship += 7;
			}
		}
	}
}

//check hp
void fill_hp_ship_to_buffer()
{
	consoleBuffer[1 + screen_x * 45].Char.AsciiChar = 'H';
	consoleBuffer[1 + screen_x * 45].Attributes = 5;
	consoleBuffer[2 + screen_x * 45].Char.AsciiChar = 'P';
	consoleBuffer[2 + screen_x * 45].Attributes = 5;
	consoleBuffer[4 + screen_x * 45].Char.AsciiChar = 48 + hp_ship;
	consoleBuffer[4 + screen_x * 45].Attributes = 5;
}

void check_hp()
{
	if (hp_ship <= 0)
	{
		play = false;
	}
}

void bullet_item1()
{
	for (int Count = 0; Count < countofbullet; Count++)
	{
		if (firestate_item11[Count] != 1)
		{
			firestate_item11[Count] = 1;
			bullet_item11[Count].X = posx - 4;
			bullet_item11[Count].Y = posy - 3;
			break;

		}
	}
	for (int Count = 0; Count < countofbullet; Count++)
	{
		if (firestate_item12[Count] != 1)
		{
			firestate_item12[Count] = 1;
			bullet_item12[Count].X = posx - 3;
			bullet_item12[Count].Y = posy - 4;
			break;

		}
	}
	for (int Count = 0; Count < countofbullet; Count++)
	{
		if (firestate_item13[Count] != 1)
		{
			firestate_item13[Count] = 1;
			bullet_item13[Count].X = posx - 2;
			bullet_item13[Count].Y = posy - 5;
			break;

		}
	}
	for (int Count = 0; Count < countofbullet; Count++)
	{
		if (firestate_item14[Count] != 1)
		{
			firestate_item14[Count] = 1;
			bullet_item14[Count].X = posx - 1;
			bullet_item14[Count].Y = posy - 6;
			break;

		}
	}
	for (int Count = 0; Count < countofbullet; Count++)
	{
		if (firestate_item15[Count] != 1)
		{
			firestate_item15[Count] = 1;
			bullet_item15[Count].X = posx;
			bullet_item15[Count].Y = posy - 7;
			break;

		}
	}
	for (int Count = 0; Count < countofbullet; Count++)
	{
		if (firestate_item16[Count] != 1)
		{
			firestate_item16[Count] = 1;
			bullet_item16[Count].X = posx + 1;
			bullet_item16[Count].Y = posy - 6;
			break;

		}
	}
	for (int Count = 0; Count < countofbullet; Count++)
	{
		if (firestate_item17[Count] != 1)
		{
			firestate_item17[Count] = 1;
			bullet_item17[Count].X = posx + 2;
			bullet_item17[Count].Y = posy - 5;
			break;

		}
	}
	for (int Count = 0; Count < countofbullet; Count++)
	{
		if (firestate_item18[Count] != 1)
		{
			firestate_item18[Count] = 1;
			bullet_item18[Count].X = posx + 3;
			bullet_item18[Count].Y = posy - 4;
			break;

		}
	}
	for (int Count = 0; Count < countofbullet; Count++)
	{
		if (firestate_item19[Count] != 1)
		{
			firestate_item19[Count] = 1;
			bullet_item19[Count].X = posx + 4;
			bullet_item19[Count].Y = posy - 3;
			break;

		}
	}
}
void bullet_item2()
{
	for (int Count = 0; Count < countofbullet; Count++)
	{
		if (firestate_item21[Count] != 1)
		{
			firestate_item21[Count] = 1;
			bullet_item21[Count].X = posx;
			bullet_item21[Count].Y = posy - 3;
			break;

		}
	}
	for (int Count = 0; Count < countofbullet; Count++)
	{
		if (firestate_item22[Count] != 1)
		{
			firestate_item22[Count] = 1;
			bullet_item22[Count].X = posx;
			bullet_item22[Count].Y = posy - 3;
			break;

		}
	}
	for (int Count = 0; Count < countofbullet; Count++)
	{
		if (firestate_item23[Count] != 1)
		{
			firestate_item23[Count] = 1;
			bullet_item23[Count].X = posx;
			bullet_item23[Count].Y = posy - 3;
			break;

		}
	}
	for (int Count = 0; Count < countofbullet; Count++)
	{
		if (firestate_item24[Count] != 1)
		{
			firestate_item24[Count] = 1;
			bullet_item24[Count].X = posx;
			bullet_item24[Count].Y = posy - 3;
			break;

		}
	}
	for (int Count = 0; Count < countofbullet; Count++)
	{
		if (firestate_item25[Count] != 1)
		{
			firestate_item25[Count] = 1;
			bullet_item25[Count].X = posx;
			bullet_item25[Count].Y = posy - 3;
			break;

		}
	}
}

void rand_item()
{
	if (State == 0)
	{
		int random_allitem;
		if (round_obj1 == 0)
		{
			random_allitem = rand();
			random_allitem %= 3;
			if (random_allitem == 0)
			{
				random_item1 = rand();
				random_item1 %= 50;
				random_item1 += 50;  //item1_1 is 50-100 100-200 200-300
			}
			else if (random_allitem == 1)
			{
				random_item2 = rand();
				random_item2 %= 50;
				random_item2 += 50;  //item2_1 is 50-100 100-200 200-300
			}
			else if (random_allitem == 2)
			{
				random_item3 = rand();
				random_item3 %= 50;
				random_item3 += 50;  //item3_1 is 50-100 100-200 200-300
			}
		}
		if (round_obj1 == random_item1)
		{
			int randy = 2;
			int randx = rand();
			randx %= 89;
			randx += 1;
			item1[round_item1].X = randx;
			item1[round_item1].Y = randy;
			round_item1++;
			random_allitem = rand();
			random_allitem %= 3;
			if (random_allitem == 0)
			{
				random_item1 = rand();
				random_item1 %= 100;
				random_item1 += (100 * (round_item1));
			}
			else if (random_allitem == 1)
			{
				random_item2 = rand();
				random_item2 %= 100;
				random_item2 += (100 * (round_item1));
			}
			else if (random_allitem == 2)
			{
				random_item3 = rand();
				random_item3 %= 100;
				random_item3 += (100 * (round_item1));
			}
		}
		else if (round_obj1 == random_item2)
		{
			int randy = 2;
			int randx = rand();
			randx %= 89;
			randx += 1;
			item2[round_item2].X = randx;
			item2[round_item2].Y = randy;
			round_item2++;
			random_allitem = rand();
			random_allitem %= 3;
			if (random_allitem == 0)
			{
				random_item1 = rand();
				random_item1 %= 100;
				random_item1 += (100 * (round_item2));
			}
			else if (random_allitem == 1)
			{
				random_item2 = rand();
				random_item2 %= 100;
				random_item2 += (100 * (round_item2));
			}
			else if (random_allitem == 2)
			{
				random_item3 = rand();
				random_item3 %= 100;
				random_item3 += (100 * (round_item2));
			}

		}
		else if (round_obj1 == random_item3)
		{
			int randy = 2;
			int randx = rand();
			randx %= 89;
			randx += 1;
			item3[round_item3].X = randx;
			item3[round_item3].Y = randy;
			round_item3++;
			random_allitem = rand();
			random_allitem %= 3;
			if (random_allitem == 0)
			{
				random_item1 = rand();
				random_item1 %= 100;
				random_item1 += (100 * (round_item3));
			}
			else if (random_allitem == 1)
			{
				random_item2 = rand();
				random_item2 %= 100;
				random_item2 += (100 * (round_item3));
			}
			else if (random_allitem == 2)
			{
				random_item3 = rand();
				random_item3 %= 100;
				random_item3 += (100 * (round_item3));
			}

		}
	}
	else if (State == 1)
	{
		int random_allitem;
		if (round_obj2 == 0)
		{
			random_allitem = rand();
			random_allitem %= 3;
			if (random_allitem == 0)
			{
				random_item1 = rand();
				random_item1 %= 50;
				random_item1 += 50;  //item1_1 is 50-100 100-200 200-300
			}
			else if (random_allitem == 1)
			{
				random_item2 = rand();
				random_item2 %= 50;
				random_item2 += 50;  //item2_1 is 50-100 100-200 200-300
			}
			else if (random_allitem == 2)
			{
				random_item3 = rand();
				random_item3 %= 50;
				random_item3 += 50;  //item3_1 is 50-100 100-200 200-300
			}
		}
		if (round_obj2 == random_item1)
		{
			int randy = 2;
			int randx = rand();
			randx %= 89;
			randx += 1;
			item1[round_item1].X = randx;
			item1[round_item1].Y = randy;
			round_item1++;
			random_allitem = rand();
			random_allitem %= 3;
			if (random_allitem == 0)
			{
				random_item1 = rand();
				random_item1 %= 100;
				random_item1 += (100 * (round_item1));
			}
			else if (random_allitem == 1)
			{
				random_item2 = rand();
				random_item2 %= 100;
				random_item2 += (100 * (round_item1));
			}
			else if (random_allitem == 2)
			{
				random_item3 = rand();
				random_item3 %= 100;
				random_item3 += (100 * (round_item1));
			}
		}
		else if (round_obj2 == random_item2)
		{
			int randy = 2;
			int randx = rand();
			randx %= 89;
			randx += 1;
			item2[round_item2].X = randx;
			item2[round_item2].Y = randy;
			round_item2++;
			random_allitem = rand();
			random_allitem %= 3;
			if (random_allitem == 0)
			{
				random_item1 = rand();
				random_item1 %= 100;
				random_item1 += (100 * (round_item2));
			}
			else if (random_allitem == 1)
			{
				random_item2 = rand();
				random_item2 %= 100;
				random_item2 += (100 * (round_item2));
			}
			else if (random_allitem == 2)
			{
				random_item3 = rand();
				random_item3 %= 100;
				random_item3 += (100 * (round_item2));
			}

		}
		else if (round_obj2 == random_item3)
		{
			int randy = 2;
			int randx = rand();
			randx %= 89;
			randx += 1;
			item3[round_item3].X = randx;
			item3[round_item3].Y = randy;
			round_item3++;
			random_allitem = rand();
			random_allitem %= 3;
			if (random_allitem == 0)
			{
				random_item1 = rand();
				random_item1 %= 100;
				random_item1 += (100 * (round_item3));
			}
			else if (random_allitem == 1)
			{
				random_item2 = rand();
				random_item2 %= 100;
				random_item2 += (100 * (round_item3));
			}
			else if (random_allitem == 2)
			{
				random_item3 = rand();
				random_item3 %= 100;
				random_item3 += (100 * (round_item3));
			}

		}

	}
}
void item_fall()
{
	int i;
	//item1
	for (i = 0; i < countofitem1; i++) {
		if (item1[i].Y >= screen_y - 4) {
			item1[i] = { (rand() % 89) + 1,-1 };
		}
		else if (item1[i].Y >= 1)
		{
			item1[i].Y += 1;
			//item1[i] = { item1[i].X,item1[i].Y += 0.2 };
		}

	}

	//item2
	for (i = 0; i < countofitem2; i++) {
		if (item2[i].Y >= screen_y - 4) {
			item2[i] = { (rand() % 89) + 1,-1 };
		}
		else if (item2[i].Y >= 1)
		{
			item2[i].Y += 1;
			//item2[i] = { item2[i].X,item2[i].Y += 0.2 };
		}

	}

	//item3
	for (i = 0; i < countofitem3; i++) {
		if (item3[i].Y >= screen_y - 4) {
			item3[i] = { (rand() % 89) + 1,-1 };
		}
		else if (item3[i].Y >= 1)
		{
			item3[i].Y += 1;
			//item3[i] = { item3[i].X,item3[i].Y += 0.2 };
		}

	}

}

void fill_item_to_buffer()
{
	//item1
	for (int i = 0; i < countofitem1; ++i)
	{
		if (item1[i].X != 0)
		{
			consoleBuffer[item1[i].X + screen_x * item1[i].Y].Char.AsciiChar = '?';
			consoleBuffer[item1[i].X + screen_x * item1[i].Y].Attributes = 25;
		}
	}

	//item2
	for (int i = 0; i < countofitem2; ++i)
	{
		if (item2[i].X != 0)
		{
			consoleBuffer[item2[i].X + screen_x * item2[i].Y].Char.AsciiChar = '?';
			consoleBuffer[item2[i].X + screen_x * item2[i].Y].Attributes = 18;
		}
	}

	//item3
	for (int i = 0; i < countofitem3; ++i)
	{
		if (item3[i].X != 0)
		{
			consoleBuffer[item3[i].X + screen_x * item3[i].Y].Char.AsciiChar = '?';
			consoleBuffer[item3[i].X + screen_x * item3[i].Y].Attributes = 27;
		}
	}

}


void setcursor(bool visible)
{
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO lpCursor;
	lpCursor.bVisible = visible;
	lpCursor.dwSize = 20;
	SetConsoleCursorInfo(console, &lpCursor);
}


int main()
{
	srand(time(NULL));

	init_ship();
	setcursor(0);
	DWORD numEvents = 0;
	DWORD numEventsRead = 0;
	setConsole(screen_x, screen_y);
	setMode();



	//Reset high score
	/*FILE* fp;
	fp = fopen("Top5Player.txt", "w");
	struct player {
		char name[50];
		int score;
	};
	player p[5], * ptr;
	ptr = p;
	for (int i = 0; i < 5; i++)
	{
		strcpy(p[i].name, "-----");
		p[i].score = 0;
		fprintf(fp, "%s  ", p[i].name);
		fprintf(fp, "%d\n", p[i].score);
	};
	fclose(fp);
	*/

	while (play)
	{
		while (State == 0)
		{
			init_obj1();
			init_donotfireobj1();
			rand_item();
			GetNumberOfConsoleInputEvents(rHnd, &numEvents);
			COORD characterPos = { 0,0 };
			if (numEvents != 0)
			{
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
							Exit = 1;
						}
						if (eventBuffer[i].Event.KeyEvent.uChar.AsciiChar == 'a' && posx > 3)
						{
							if (item_1 == false && item_2 == false)
							{
								posx--;
							}
							else if (item_1 == true && posx > 7)
							{
								posx -= 4;
							}
							else if (item_2 == true && posx > 7)
							{
								posx -= 4;
							}
						}
						else if (eventBuffer[i].Event.KeyEvent.uChar.AsciiChar == 'd' && posx < 86)
						{
							if (item_1 == false && item_2 == false)
							{
								posx++;
							}
							else if (item_1 == true && posx < 83)
							{
								posx += 4;
							}
							else if (item_2 == true && posx < 83)
							{
								posx += 4;
							}
						}
						else if (eventBuffer[i].Event.KeyEvent.uChar.AsciiChar == 's' && posy < 42)
						{
							if (item_1 == false && item_2 == false)
							{
								posy++;
							}
							else if (item_1 == true && posy < 40)
							{
								posy += 2;
							}
							else if (item_2 == true && posy < 40)
							{
								posy += 2;
							}
						}
						else if (eventBuffer[i].Event.KeyEvent.uChar.AsciiChar == 'w' && posy > 0)
						{
							if (item_1 == false && item_2 == false)
							{
								posy--;
							}
							else if (item_1 == true && posy > 2)
							{
								posy -= 2;
							}
							else if (item_2 == true && posy > 2)
							{
								posy -= 2;
							}
						}
						else if (eventBuffer[i].Event.KeyEvent.uChar.AsciiChar == ' ')
						{
							if (item_1 == false)
							{
								for (int Count = 0; Count < countofbullet; Count++)
								{
									if (firestate_normal1[Count] != 1)
									{
										firestate_normal1[Count] = 1;
										bullet_normal1[Count].X = posx - 1;
										bullet_normal1[Count].Y = posy;
										break;

									}
								}
								for (int Count = 0; Count < countofbullet; Count++)
								{
									if (firestate_normal2[Count] != 1)
									{
										firestate_normal2[Count] = 1;
										bullet_normal2[Count].X = posx + 1;
										bullet_normal2[Count].Y = posy;
										break;

									}
								}
							}

						}
					}

					//printf("press : %c\n", eventBuffer[i].Event.KeyEvent.uChar.AsciiChar);


				}
				delete[] eventBuffer;
			}
			obj1_fall();
			donotfireobj1_fall();
			item_fall();
			bullet_item1_fly();
			bullet_item2_fly();
			bullet_normal_fly();
			test_collision_bullet_item1();
			test_collision_bullet_item2();
			test_colision_bullet_normal();
			if (item_1 == false && item_2 == false)
			{
				test_colision_smallship();
				fill_smallship_to_buffer();
			}
			else if (item_1 == true && item_2 == false)
			{
				bullet_item1();
				fill_largeship_to_buffer();
				if (check_item1 + 40 == round_obj1)
				{
					item_1 = false;
					check_item1 = 0;
				}
			}
			else if (item_1 == false && item_2 == true)
			{
				bullet_item2();
				fill_largeship_to_buffer();
				if (check_item2 + 40 == round_obj1)
				{
					item_2 = false;
					check_item2 = 0;
				}
			}
			fill_bullet_normal_to_buffer();
			fill_bullet_item1_to_buffer();
			fill_bullet_item2_to_buffer();
			fill_obj1_to_buffer();
			fill_donotfireobj1_to_buffer();
			fill_item_to_buffer();
			draw_line_score();
			fill_howtoplay_to_buffer();
			fill_Score_to_buffer();
			fill_highestscore_to_buffer();
			fill_hp_ship_to_buffer();
			fill_buffer_to_console();
			//check_hp();
			clear_buffer();
			round_obj1++;
			if (round_obj1 == 300)
			{
				State = 1;
				//play = false;
			}
			score_now = 0;
			Sleep(200);
		}
		while (State == 1)
		{
			item_1 = false;
			item_2 = false;
			init_obj2();
			init_donotfireobj2();
			rand_item();
			GetNumberOfConsoleInputEvents(rHnd, &numEvents);
			COORD characterPos = { 0,0 };
			if (numEvents != 0)
			{
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
							Exit = 1;
						}
						if (eventBuffer[i].Event.KeyEvent.uChar.AsciiChar == 'a' && posx > 3)
						{
							if (item_1 == false && item_2 == false)
							{
								posx--;
							}
							else if (item_1 == true && posx > 7)
							{
								posx -= 4;
							}
							else if (item_2 == true && posx > 7)
							{
								posx -= 4;
							}
						}
						else if (eventBuffer[i].Event.KeyEvent.uChar.AsciiChar == 'd' && posx < 86)
						{
							if (item_1 == false && item_2 == false)
							{
								posx++;
							}
							else if (item_1 == true && posx < 83)
							{
								posx += 4;
							}
							else if (item_2 == true && posx < 83)
							{
								posx += 4;
							}
						}
						else if (eventBuffer[i].Event.KeyEvent.uChar.AsciiChar == 's' && posy < 42)
						{
							if (item_1 == false && item_2 == false)
							{
								posy++;
							}
							else if (item_1 == true && posy < 40)
							{
								posy += 2;
							}
							else if (item_2 == true && posy < 40)
							{
								posy += 2;
							}
						}
						else if (eventBuffer[i].Event.KeyEvent.uChar.AsciiChar == 'w' && posy > 0)
						{
							if (item_1 == false && item_2 == false)
							{
								posy--;
							}
							else if (item_1 == true && posy > 2)
							{
								posy -= 2;
							}
							else if (item_2 == true && posy > 2)
							{
								posy -= 2;
							}
						}
						else if (eventBuffer[i].Event.KeyEvent.uChar.AsciiChar == ' ')
						{
							if (item_1 == false)
							{
								for (int Count = 0; Count < countofbullet; Count++)
								{
									if (firestate_normal1[Count] != 1)
									{
										firestate_normal1[Count] = 1;
										bullet_normal1[Count].X = posx - 1;
										bullet_normal1[Count].Y = posy;
										break;

									}
								}
								for (int Count = 0; Count < countofbullet; Count++)
								{
									if (firestate_normal2[Count] != 1)
									{
										firestate_normal2[Count] = 1;
										bullet_normal2[Count].X = posx + 1;
										bullet_normal2[Count].Y = posy;
										break;

									}
								}
							}

						}
					}

					//printf("press : %c\n", eventBuffer[i].Event.KeyEvent.uChar.AsciiChar);


				}
				delete[] eventBuffer;
			}
			obj2_fall();
			donotfireobj2_fall();
			item_fall();
			bullet_item1_fly();
			bullet_item2_fly();
			bullet_normal_fly();
			test_collision_bullet_item1();
			test_collision_bullet_item2();
			test_colision_bullet_normal();
			if (item_1 == false && item_2 == false)
			{
				test_colision_smallship();
				fill_smallship_to_buffer();
			}
			else if (item_1 == true && item_2 == false)
			{
				bullet_item1();
				fill_largeship_to_buffer();
				if (check_item1 + 40 == round_obj2)
				{
					item_1 = false;
					check_item1 = 0;
				}
			}
			else if (item_1 == false && item_2 == true)
			{
				bullet_item2();
				fill_largeship_to_buffer();
				if (check_item2 + 40 == round_obj2)
				{
					item_2 = false;
					check_item2 = 0;
				}
			}
			fill_bullet_normal_to_buffer();
			fill_bullet_item1_to_buffer();
			fill_bullet_item2_to_buffer();
			fill_obj2_to_buffer();
			fill_donotfireobj2_to_buffer();
			fill_item_to_buffer();
			draw_line_score();
			fill_howtoplay_to_buffer();
			fill_Score_to_buffer();
			fill_highestscore_to_buffer();
			fill_hp_ship_to_buffer();
			fill_buffer_to_console();
			//check_hp();
			clear_buffer();
			round_obj2++;
			if (round_obj2 == 300)
			{
				State = 2;
				//play = false;
			}
			score_now = 0;
			Sleep(200);
		}
		while (State == 2)
		{
			item_1 = false;
			item_2 = false;
			init_obj3x();
			init_obj3y();
			init_donotfireobj3();
			GetNumberOfConsoleInputEvents(rHnd, &numEvents);
			COORD characterPos = { 0,0 };
			if (numEvents != 0)
			{
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
							Exit = 1;
						}
						if (eventBuffer[i].Event.KeyEvent.uChar.AsciiChar == 'a' && posx > 3)
						{
							if (item_1 == false && item_2 == false)
							{
								posx--;
							}
							else if (item_1 == true && posx > 7)
							{
								posx -= 4;
							}
							else if (item_2 == true && posx > 7)
							{
								posx -= 4;
							}
						}
						else if (eventBuffer[i].Event.KeyEvent.uChar.AsciiChar == 'd' && posx < 86)
						{
							if (item_1 == false && item_2 == false)
							{
								posx++;
							}
							else if (item_1 == true && posx < 83)
							{
								posx += 4;
							}
							else if (item_2 == true && posx < 83)
							{
								posx += 4;
							}
						}
						else if (eventBuffer[i].Event.KeyEvent.uChar.AsciiChar == 's' && posy < 42)
						{
							if (item_1 == false && item_2 == false)
							{
								posy++;
							}
							else if (item_1 == true && posy < 40)
							{
								posy += 2;
							}
							else if (item_2 == true && posy < 40)
							{
								posy += 2;
							}
						}
						else if (eventBuffer[i].Event.KeyEvent.uChar.AsciiChar == 'w' && posy > 0)
						{
							if (item_1 == false && item_2 == false)
							{
								posy--;
							}
							else if (item_1 == true && posy > 2)
							{
								posy -= 2;
							}
							else if (item_2 == true && posy > 2)
							{
								posy -= 2;
							}
						}
						else if (eventBuffer[i].Event.KeyEvent.uChar.AsciiChar == ' ')
						{
							if (item_1 == false)
							{
								for (int Count = 0; Count < countofbullet; Count++)
								{
									if (firestate_normal1[Count] != 1)
									{
										firestate_normal1[Count] = 1;
										bullet_normal1[Count].X = posx - 1;
										bullet_normal1[Count].Y = posy;
										break;

									}
								}
								for (int Count = 0; Count < countofbullet; Count++)
								{
									if (firestate_normal2[Count] != 1)
									{
										firestate_normal2[Count] = 1;
										bullet_normal2[Count].X = posx + 1;
										bullet_normal2[Count].Y = posy;
										break;

									}
								}
							}

						}
					}

					//printf("press : %c\n", eventBuffer[i].Event.KeyEvent.uChar.AsciiChar);


				}
				delete[] eventBuffer;
			}
			obj3x_fall();
			obj3y_fall();
			donotfireobj3_fall();
			bullet_normal_fly();
			test_colision_bullet_normal();



			test_colision_smallship();
			fill_smallship_to_buffer();

			fill_bullet_normal_to_buffer();

			fill_obj3x_to_buffer();
			fill_obj3y_to_buffer();
			fill_donotfireobj3_to_buffer();
			draw_line_score();
			fill_howtoplay_to_buffer();
			fill_Score_to_buffer();
			fill_highestscore_to_buffer();
			fill_hp_ship_to_buffer();
			fill_buffer_to_console();
			//check_hp();
			clear_buffer();
			round_obj3++;
			if (round_obj3 == 300)
			{
				State = 3;
				play = false;
			}
			score_now = 0;
			Sleep(200);
		}

	}
	if (Exit == 0)
	{
		fill_gameover_to_buffer();
		fill_buffer_to_console();
		Sleep(5000);
		fill_pressanykey_to_buffer();
		fill_buffer_to_console();
		char ch = _getch();
		clear_buffer();
		fill_buffer_to_console();
		//setcursor(1);
		check_hightscore();
	}
	return 0;
}


