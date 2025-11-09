#ifndef QUANLYTAXI_H
#define QUANLYTAXI_H

#include "MyVector.h"
#include <unordered_map>
#include <fstream>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <limits>
#include "TaXi.h"
#include "TaiXe.h"
#include "Utils.h"

using namespace std;

class QuanLyTaXi {
private:
    MyVector<TaXi> dsTaxi;
    unordered_map<string, TaXi*> taxiByID;
    string currentAdmin;
    unordered_map<string, TaiXe*>* pTaiXeByID; // Pointer để check tài xế tồn tại

    string sinhIDXe();
    void rebuildTaxiMap();
    void ghiLichSuTaxi(const string&, const TaXi&, const string& = "");
    void ghiLichSuHoatDong(const string&, const string&, 
                           const string&, const string& = "THANH_CONG");
    

public:
    QuanLyTaXi(const string&, unordered_map<string, TaiXe*>* = nullptr);
    ~QuanLyTaXi() {}
    void setCurrentAdmin(const string&);
    void setTaiXeByID(unordered_map<string, TaiXe*>*);
    void docTaxi();
    void ghiTaxi();
    void themTaxi();
    void suaTaxi();
    void xoaTaxi();
    void hienThiTaxi();
    void timTaxi();
    void xemChiTietTaxi();
    TaXi* timTaxiByID(const string&);
    MyVector<TaXi>& getDSTaxi();
    unordered_map<string, TaXi*>& getTaxiByID();

};

#endif