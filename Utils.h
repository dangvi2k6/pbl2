#ifndef UTILS_H
#define UTILS_H

#define WIN32_LEAN_AND_MEAN
#define NOMIMAX

#include <windows.h>
#include <iostream>
#include <string>
#include <ctime>
#include "MyVector.h"
#include <conio.h>

using namespace std;

class Utils {
public:
    static void gotoxy(int x, int y)
    {
        COORD c;
        c.X = x;
        c.Y = y;
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),c);
    }

    static void setColor(int color) {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
    }

    static void printHeader(const string& title) {
        setColor(10);
        cout << "=== " << title << " ===" << endl;
        setColor(7);
    }

    static void pause() {
        cout << "\nNhan phim bat ky de tiep tuc...";
        _getch();
    }

    static bool getInputWithESC(string& input, const string& prompt = "") {
        if (! prompt.empty()) {
            cout << prompt;
        }
        
        input = "";
        char ch;
        while (true) {
            ch = _getch();
            
            if (ch == 27) {  // ESC pressed
                return false;
            }
            
            if (ch == '\r' || ch == '\n') {  // Enter pressed
                cout << endl;
                return true;
            }
            
            if (ch == 8 && input.length() > 0) {  // Backspace
                input. pop_back();
                cout << "\b \b";
            }
            else if (ch >= 32 && ch <= 126) {  // Printable characters
                input += ch;
                cout << ch;
            }
        }
    }

    static string layThoiGianHienTai() {
        time_t now = time(0);
        tm* ltm = localtime(&now);
        char buffer[100];
        sprintf(buffer, "%04d-%02d-%02d %02d:%02d:%02d",
                1900 + ltm->tm_year,
                1 + ltm->tm_mon,
                ltm->tm_mday,
                ltm->tm_hour,
                ltm->tm_min,
                ltm->tm_sec);
        return string(buffer);
    }

    static string nhapMatKhauAn() {
        string password = "";
        char ch;
        while ((ch = _getch()) != 13) { 
            if (ch == 8 && !password.empty()) { 
                password.pop_back();
                cout << "\b \b";
            }
            else if (ch >= 32 && ch <= 126) {
                password += ch;
                cout << "*";
            }
        }
        cout << endl;
        return password;
    }

    static int calculateMenuWidth(const string& title, const MyVector<string>& items, const string& hint)
    {
        int maxLen=title.length() + 16;

        for(int i=0; i<items.size(); i++){
            int itemLen=items[i].length() + 3;
            if (itemLen > maxLen) maxLen = itemLen;
        }

        int hintLen = hint.length() + 12; // +12 cho "Huong dan: "
        if(hintLen > maxLen) maxLen=hintLen;

        return maxLen;
    }

    static void drawMenuBox(int left, int top, int width, int height)
    {
        int right=left+width-1;
        int bottom=top+height-1;

        setColor(12);

        gotoxy(left, top);
        cout<<"╔";

        gotoxy(right, top);
        cout << "╗";
        
        gotoxy(left, bottom);
        cout << "╚";

        gotoxy(right, bottom);
        cout << "╝";

        for (int x = left + 1; x < right; x++) {
            gotoxy(x, top);
            cout << "═";
            gotoxy(x, bottom);
            cout << "═";
        }

        for (int y = top + 1; y < bottom; y++) {
            gotoxy(left, y);
            cout << "║";
            gotoxy(right, y);
            cout << "║";
        }

        setColor(7);
    }

    static int showMenu(const string& title, const MyVector<string>& items, 
                       const string& hint = "Mui ten Len/Xuong de di chuyen, Enter de chon, ESC de quay lai. So 1-9 de chon nhanh.") {
        int selected = 0;
        while(true) {
            system("cls");
            int width = calculateMenuWidth(title, items, hint)+4;
            int height=items.size()+6;
            int left=5;
            int top=2;

            drawMenuBox(left, top, width, height);

            int titleY=top+1;
            int titleX=left+(width-(title.length()+8))/2;
            setColor(14);
            gotoxy(titleX, titleY);
            cout<<"***"<<title<<"***";

            int menuStartY=top+2;
            for(int i=0;i<(int)items.size(); i++){
                gotoxy(left+2, menuStartY+i);
                if(i==selected){
                    setColor(11);
                    cout<<">>"<<items[i]; 
                }
                else{
                    setColor(7);
                    cout<<" "<<items[i];
                }
            }

            int separatorY=menuStartY+items.size();

            setColor(10);
            gotoxy(left+2, separatorY);
            cout<<"Huong dan: "<<hint;

            setColor(7);

            int ch = _getch();
            if(ch == 224 || ch == 0) {
                int code = _getch();
                if(code == 72) { 
                    selected = (selected - 1 + (int)items.size()) % (int)items.size();
                }
                else if(code == 80) {
                    selected = (selected + 1) % (int)items.size();
                }
            }
            else if(ch == 13) { 
                return selected;
            }
            else if(ch == 27) { 
                return -1;
            }
            else if(ch >= '1' && ch <= '9') {
                int idx = ch - '1';
                if(idx >= 0 && idx < (int)items.size()) return idx;
            }
        }
    }
};

#endif