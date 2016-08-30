/* A conio implementation for Mingw/Dev-C++.
 *
 * Written by:
 * Hongli Lai <hongli@telekabel.nl>
 * tkorrovi <tkorrovi@altavista.net> on 2002/02/26. 
 * Andrew Westcott <ajwestco@users.sourceforge.net>
 *
 * Offered for use in the public domain without any warranty.
 */

#ifndef _CONIO_C_
#define _CONIO_C_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <windows.h>
#include <string.h>
#include "conio.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef enum
{
    BLACK,
    BLUE,
    GREEN,
    CYAN,
    RED,
    MAGENTA,
    BROWN,
    LIGHTGRAY,
    DARKGRAY,
    LIGHTBLUE,
    LIGHTGREEN,
    LIGHTCYAN,
    LIGHTRED,
    LIGHTMAGENTA,
    YELLOW,
    WHITE
} COLORS;

static int __BACKGROUND = BLACK;
static int __FOREGROUND = LIGHTGRAY;


void
clrscr ()
{
    DWORD written;

    FillConsoleOutputAttribute (GetStdHandle (STD_OUTPUT_HANDLE),
      __FOREGROUND + (__BACKGROUND << 4), 2000, (COORD) {0, 0},
      &written);
      FillConsoleOutputCharacter (GetStdHandle
      (STD_OUTPUT_HANDLE), ' ',
      2000, (COORD) {0, 0}, &written);
    gotoxy (1, 1);
}


void
clreol ()
{
    COORD coord;
    DWORD written;
    CONSOLE_SCREEN_BUFFER_INFO info;

    GetConsoleScreenBufferInfo (GetStdHandle (STD_OUTPUT_HANDLE),
      &info);
    coord.X = info.dwCursorPosition.X;
    coord.Y = info.dwCursorPosition.Y;

    FillConsoleOutputCharacter (GetStdHandle (STD_OUTPUT_HANDLE),
      ' ', info.dwSize.X - info.dwCursorPosition.X, coord, &written);
    gotoxy (coord.X, coord.Y);
}


void
delline()
{
    COORD coord;
    DWORD written;
    CONSOLE_SCREEN_BUFFER_INFO info;

    GetConsoleScreenBufferInfo (GetStdHandle (STD_OUTPUT_HANDLE),
      &info);
    coord.X = info.dwCursorPosition.X;
    coord.Y = info.dwCursorPosition.Y;

    FillConsoleOutputCharacter (GetStdHandle (STD_OUTPUT_HANDLE),
      ' ', info.dwSize.X * info.dwCursorPosition.Y, coord, &written);
    gotoxy (info.dwCursorPosition.X + 1,
    info.dwCursorPosition.Y + 1);
}


int
_conio_gettext (int left, int top, int right, int bottom,
  char *str)
{
    int i, j, n;
    SMALL_RECT r;
    CHAR_INFO buffer[25][80];

    r = (SMALL_RECT) {left - 1, top - 1, right - 1, bottom - 1};
    ReadConsoleOutput (GetStdHandle (STD_OUTPUT_HANDLE),
      (PCHAR_INFO) buffer, (COORD) {80, 25}, (COORD) {0, 0}, &r);

    lstrcpy (str, "");
    for (i = n = 0; i <= bottom - top; i++)
    for (j = 0; j <= right - left; j++)
    {
        str[n] = buffer[i][j].Char.AsciiChar;
        n++;
    }
    str[n] = 0;
    return 1;
}


int gotoxy(int x, int y)
{
  COORD c;

  c.X = x - 1;
  c.Y = y - 1;
  SetConsoleCursorPosition (GetStdHandle(STD_OUTPUT_HANDLE), c);
  return 1;
}


void
puttext (int left, int top, int right, int bottom, char *str)
{ 
    int i, j, n;
    SMALL_RECT r;
    CHAR_INFO buffer[25][80];

    memset (buffer, 0, sizeof (buffer));
    r = (SMALL_RECT) {left - 1, top - 1, right - 1, bottom - 1};

    for (i = n = 0; i <= bottom - top; i++)
    for (j = 0; j <= right - left && str[n] != 0; j++)
    {
        buffer[i][j].Char.AsciiChar = str[n];
        buffer[i][j].Attributes = FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED;
        n++;
    }

    WriteConsoleOutput (GetStdHandle (STD_OUTPUT_HANDLE),
      (CHAR_INFO *) buffer, (COORD) {80, 25},
      (COORD) {0, 0}, &r);
}


void
_setcursortype (int type)
{
    CONSOLE_CURSOR_INFO Info;

    Info.dwSize = type;
    SetConsoleCursorInfo (GetStdHandle (STD_OUTPUT_HANDLE),
      &Info);
}


void
textattr (int _attr)
{
    SetConsoleTextAttribute (GetStdHandle(STD_OUTPUT_HANDLE), _attr);
}


void
textbackground (int color)
{
    __BACKGROUND = color;
    SetConsoleTextAttribute (GetStdHandle (STD_OUTPUT_HANDLE),
      __FOREGROUND + (color << 4));
}


void
textcolor (int color)
{
    __FOREGROUND = color;
    SetConsoleTextAttribute (GetStdHandle (STD_OUTPUT_HANDLE),
      color + (__BACKGROUND << 4));
}


int
wherex ()
{
    CONSOLE_SCREEN_BUFFER_INFO info;

    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
    return info.dwCursorPosition.X + 1;
}


int
wherey ()
{
    CONSOLE_SCREEN_BUFFER_INFO info;

    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
    return info.dwCursorPosition.Y + 1;
}


#ifdef __cplusplus
}
#endif

#endif /* _CONIO_C_ */
