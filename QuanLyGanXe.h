#ifndef QUANLYGANXE_H
#define QUANLYGANXE_H

#include "MyVector.h"
#include <unordered_map>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <sstream>
#include "TaiXe.h"
#include "TaXi.h"
#include "Utils.h"

using namespace std;

class QuanLyGanXe {
private:
    string currentAdmin;
    unordered_map<string, TaiXe*>* pTaiXeByID;
    unordered_map<string, TaXi*>* pTaxiByID;
    MyVector<TaXi>* pDsTaxi;

    string taoMaGhiNhan();
    void ghiLog(const string&, const string&);
    void ghiLichSuChiTiet(const string&, const string&, const string&,
                          const string&, const string&, const string&,
                          const string&, const string&, const string&, int,
                          const string&, const string& = "");
    

public:

    QuanLyGanXe(const string&,
                unordered_map<string, TaiXe*>* = nullptr,
                unordered_map<string, TaXi*>* = nullptr,
                MyVector<TaXi>* = nullptr);
    ~QuanLyGanXe();
    void setCurrentAdmin(const string&);
    void setTaiXeByID(unordered_map<string, TaiXe*>*);
    void setTaxiByID(unordered_map<string, TaXi*>*);
    void setDsTaxi(MyVector<TaXi>*);
    void ganTaiXeChoXe();
    void huyGanTaiXeChoXe();
    void xemLog();
    void xemLichSuChiTiet();
    
};

#endif