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
    TaXi(const string& id = "", const string& bs = "", const string& mau = "", 
         const string& hang = "", const string& nam = "", const string& khoang = "", 
         const string& ngayBD = "", int sc = 0, bool tt = 1)
        : IDXe(id), bienSo(bs), mauXe(mau), hangXe(hang), namSX(nam),
          dungTichKhoangHanhLy(khoang), ngayBaoDuongGanNhat(ngayBD),
          sucChua(sc), trangThaiXe(tt) {}

    ~TaXi() {}

    static bool exists(const string& idXe, const string& filename = "cars.txt") {
        ifstream fin(filename);
        if (!fin.is_open()) return false;
        string line;
        while (getline(fin, line)) {
            stringstream ss(line);
            string id;
            getline(ss, id, '|');
            if (id == idXe) {
                    fin.close();
                    return true;
                }
            }
        fin.close();
        return false;
    }
};

#endif