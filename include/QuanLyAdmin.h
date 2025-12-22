#ifndef QUANLYADMIN_H
#define QUANLYADMIN_H

#include <unordered_map>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include "Utils.h"

using namespace std;

class QuanLyAdmin {
private:
    unordered_map<string, string> admins;
    string currentAdmin;

public:
    QuanLyAdmin(); 

    ~QuanLyAdmin();

    void docAdmins();
    void ghiAdmins();
    void dangKyAdmin();
    bool dangNhap();
    string getCurrentAdmin() const;
    void resetCurrentAdmin();
    void hienThiAdmin();
    void xoaAdmin();

};

#endif