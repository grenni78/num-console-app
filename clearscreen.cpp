#include "stdafx.h"
#include <windows.h>
#include "clearscreen.h"


void ClearScreen()
  {
  HANDLE                     hStdOut;
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    DWORD                      count;
    DWORD                      cellCount;
    COORD                      homeCoords = {0, 0};

    hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hStdOut == INVALID_HANDLE_VALUE)
        return;
    // Get the number of cells in the current buffer:
    if (!(GetConsoleScreenBufferInfo(hStdOut, &csbi)))
        return;

    cellCount = csbi.dwSize.X *csbi.dwSize.Y;

    // Fill the buffer with empty whitespace :P

    if (!(FillConsoleOutputCharacter(hStdOut,
                                    (TCHAR) ' ',
                                     cellCount,
                                     homeCoords,
                                     &count)))
        return;

    // Fill the buffer with the current colours and attributes:
    if (!(FillConsoleOutputAttribute(hStdOut,
                                     csbi.wAttributes,
                                     cellCount,
                                     homeCoords,
                                     &count)))
        return;
    // Now place the console cursor to the first position in the console:
    SetConsoleCursorPosition(hStdOut, homeCoords);

}