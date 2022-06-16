#include "windows.h"
#include "stdio.h"
#include "stdlib.h"
void Clr() {
        COORD coordScreen = { 0, 0 };
        DWORD cCharsWritten;
        CONSOLE_SCREEN_BUFFER_INFO csbi;
        DWORD dwConSize;
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

        GetConsoleScreenBufferInfo(hConsole, &csbi);
        dwConSize = csbi.dwSize.X * csbi.dwSize.Y;
        FillConsoleOutputCharacter(hConsole, TEXT(' '),  dwConSize,  coordScreen, &cCharsWritten);
        GetConsoleScreenBufferInfo(hConsole, &csbi);
        FillConsoleOutputAttribute(hConsole, csbi.wAttributes, dwConSize,  coordScreen,  &cCharsWritten);
        SetConsoleCursorPosition(hConsole, coordScreen);
}

int main(void){
    printf("sdfafafaffsf\nafrwefaf\nWRAFAWWEF\nwfefeew");
    getchar();
    Clr;
    return 0;
}
