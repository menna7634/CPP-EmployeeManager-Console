#include "Employee.h"
#include "Console.h"
#include <iostream>
using namespace std;

int main(){
    const string menu[] = {"Add Employee","Display Employees","Exit"};
    const int menuSize = 3;

    int selected = 0;
    int prevSelected = 0;

    bool running = true;

    while(running){
        console::clearScreen();
        console::setColorHeader();
        cout << "===== EMPLOYEE MANAGEMENT SYSTEM =====\n\n";
        console::resetColor();

        for(int i=0;i<menuSize;i++){
            if(i==selected) console::setColorSelected();
            cout << "   " << menu[i] << "\n";
            console::resetColor();
        }
        prevSelected = selected;

       bool inMenu = true;
        while(inMenu){
            console::Key key = console::readKey();

            if(key==console::KeyUp) selected = (selected-1+menuSize)%menuSize;
            else if(key==console::KeyDown) selected = (selected+1)%menuSize;
            else if(key==console::KeyEnter){
                inMenu = false; 
            }
            else if(key==console::KeyEsc){
                running=false;
                break;
            }

            if(prevSelected!=selected){
                console::goToXY(0, 2 + prevSelected);
                cout << "   " << menu[prevSelected];
                console::goToXY(0, 2 + selected);
                console::setColorSelected();
                cout << "   " << menu[selected];
                console::resetColor();
                prevSelected = selected;
            }
        }

        if(!running) break;

        console::clearScreen(); 
        if(selected==0) addEmployee();
        else if(selected==1) displayEmployees();
        else running=false;
    }

    console::clearScreen();
    cout << "Goodbye!\n";
    return 0;
}
