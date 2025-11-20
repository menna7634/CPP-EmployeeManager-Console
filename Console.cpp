#include "Console.h"
#include <iostream>
#ifdef _WIN32
#include <windows.h>
#include <conio.h>
#else
#include <termios.h>
#include <unistd.h>
#include <sys/ioctl.h>
#endif

using namespace std;

namespace console {

// Clear screen
void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    cout << "\033[2J\033[H" << flush;
#endif
}

// Go to XY
void goToXY(int x,int y){
#ifdef _WIN32
    COORD c{(SHORT)x,(SHORT)y};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),c);
#else
    cout << "\033[" << (y+1) << ";" << (x+1) << "H";
#endif
}

// Colors
void setColorHeader(){
#ifdef _WIN32
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11); // Aqua
#else
    cout << "\033[1;36m";
#endif
}

void setColorSelected(){
#ifdef _WIN32
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10); // Green
#else
    cout << "\033[42;30m"; 
#endif
}

void resetColor(){
#ifdef _WIN32
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
#else
    cout << "\033[0m";
#endif
}

// Delay
void delayMs(int ms){
#ifdef _WIN32
    Sleep(ms);
#else
    usleep(ms*1000);
#endif
}

// Terminal size
pair<int,int> getTerminalSize(){
#ifdef _WIN32
    CONSOLE_SCREEN_BUFFER_INFO csbi{};
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    return {csbi.srWindow.Right - csbi.srWindow.Left + 1,
            csbi.srWindow.Bottom - csbi.srWindow.Top + 1};
#else
    winsize w{};
    ioctl(STDOUT_FILENO, TIOCGWINSZ,&w);
    return {w.ws_col,w.ws_row};
#endif
}

// Read key
console::Key readKey(){
#ifdef _WIN32
    int c = _getch();
    if(c==0 || c==224){ c=_getch();
        switch(c){
            case 72: return KeyUp;
            case 80: return KeyDown;
        }
    }
    if(c==13) return KeyEnter;
    if(c==27) return KeyEsc;
    if(c==8) return KeyBackspace;
#else
    termios oldt,newt;
    tcgetattr(STDIN_FILENO,&oldt);
    newt=oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO,TCSANOW,&newt);

    int c = getchar();
    tcsetattr(STDIN_FILENO,TCSANOW,&oldt);

    if(c==27){
        int n1=getchar();
        if(n1=='['){
            int n2=getchar();
            switch(n2){
                case 'A': return KeyUp;
                case 'B': return KeyDown;
            }
        }
        return KeyEsc;
    }
    if(c==10) return KeyEnter;
    if(c==127) return KeyBackspace;
#endif
    return KeyNone;
}

}
