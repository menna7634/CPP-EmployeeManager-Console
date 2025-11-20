#ifndef CONSOLE_H
#define CONSOLE_H

#include <utility>
using namespace std;

namespace console {

enum Key {
    KeyNone,
    KeyUp,
    KeyDown,
    KeyEnter,
    KeyEsc,
    KeyBackspace
};

void clearScreen();
void goToXY(int x,int y);
void setColorHeader();
void setColorSelected();
void resetColor();
void delayMs(int ms);
pair<int,int> getTerminalSize();
Key readKey();

}

#endif
