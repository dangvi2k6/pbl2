#ifndef QUANLYPHANCONG_H
#define QUANLYPHANCONG_H

#include "MyVector.h"
#include <unordered_map>
#include <fstream>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <algorithm>
#include "PhanCong.h"
#include "TaiXe.h"
#include "TaXi.h"
#include "Utils.h"

using namespace std;

class QuanLyPhanCong {
private:
    MyVector<PhanCong> dsPhanCong;
    unordered_map<string, PhanCong*> phanCongByID;
    string currentAdmin;
    unordered_map<string, TaiXe*>* pTaiXeByID;
    unordered_map<string, TaXi*>* pTaxiByID;
    MyVector<TaXi>* pDsTaxi;

    string sinhIDPhanCong();
    void rebuildPhanCongMap();
    void ghiLichSuPhanCong(const string&, const PhanCong&, const string& = "");
    void ghiLichSuHoatDong(const string&, const string&,
                            const string&, const string& = "THANH_CONG");

public:
    QuanLyPhanCong(const string&,
                   unordered_map<string, TaiXe*>* = nullptr,
                   unordered_map<string, TaXi*>* = nullptr,
                   MyVector<TaXi>* = nullptr);
    ~QuanLyPhanCong();

    void setCurrentAdmin(const string&);
    void setTaiXeByID(unordered_map<string, TaiXe*>*);
    void setTaxiByID(unordered_map<string, TaXi*>*);
    void docPhanCong();
    void ghiPhanCong();
    void themPhanCong();
    void suaPhanCong();
    void xoaPhanCong();
    void hienThiPhanCong();
    void timPhanCong();

    MyVector<PhanCong>& getDSPhanCong();

    void sapXepPhanCong();
    void hienThiDanhSachPhanCongDaSapXep();
    void setDsTaxi(MyVector<TaXi>* dsTaxi) { pDsTaxi=dsTaxi; }
};

#endif