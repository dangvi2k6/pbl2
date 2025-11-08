#ifndef UTILS_H
#define UTILS_H

#define WIN32_LEAN_AND_MEAN
#define NOMIMAX

#include <windows.h>
#include <iostream>
#include <string>
#include <ctime>
#include <vector>
#include <conio.h>

using namespace std;

class Utils {
public:
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

    static int showMenu(const string& title, const vector<string>& items, 
                       const string& hint = "Mui ten Len/Xuong de di chuyen, Enter de chon, ESC de quay lai. So 1-9 de chon nhanh.") {
        int selected = 0;
        while(true) {
            system("cls");
            printHeader(title);

            for(int i = 0; i < (int)items.size(); ++i) {
                if(i == selected) {
                    setColor(11);
                    cout << ">> " << items[i] << "\n";
                    setColor(7);
                }
                else {
                    cout << "   " << items[i] << "\n";
                }
            }
            cout << "\nHuong dan: " << hint << "\n";

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