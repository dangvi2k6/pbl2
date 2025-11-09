#ifndef TAXI_H
#define TAXI_H

#include <string>
#include "MyVector.h"
#include <fstream>
#include <sstream>

using namespace std;

class TaXi {
public:
    string IDXe;
    string bienSo;
    string mauXe;
    string hangXe;
    string namSX;
    string dungTichKhoangHanhLy;
    string ngayBaoDuongGanNhat;
    int sucChua;
    bool trangThaiXe;
    MyVector<string> dsTaiXe;

public:
    TaXi(const string&, const string&, const string&, 
         const string&, const string&, const string&, 
         const string&, int, bool);
           
    ~TaXi();

    static bool exists(const string&, const string& = "cars.txt");
};

#endif