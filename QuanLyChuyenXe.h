#ifndef QUANLYCHUYENXE_H
#define QUANLYCHUYENXE_H

#include "MyVector.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <algorithm>
#include "ChuyenXe.h"
#include "TaiXe.h"
#include "TaXi.h"
#include "Utils.h"
#include <unordered_map>

using namespace std;

class QuanLyChuyenXe {
private:
    MyVector<ChuyenXe> dsChuyenXe;
    string currentAdmin;
    unordered_map<string, TaiXe*>* pTaiXeByID;
    unordered_map<string, TaXi*>* pTaxiByID;

    string sinhIDChuyenXe();
    void ghiLichSuChuyenXe(const string&, const ChuyenXe&, const string& = "");
    void ghiLichSuHoatDong(const string&, const string&,
                            const string&, const string& = "THANH_CONG");
    double tinhCuocPhi(double khoangCach, double thoiGian, const string& thoiDiem);

    

public:
    QuanLyChuyenXe(const string&, 
                   unordered_map<string, TaiXe*>* = nullptr,
                   unordered_map<string, TaXi*>* = nullptr); 
    ~QuanLyChuyenXe();
    void setCurrentAdmin(const string&);
    void setTaiXeByID(unordered_map<string, TaiXe*>*);
    void setTaxiByID(unordered_map<string, TaXi*>*);

    void docChuyenXe();
    void ghiChuyenXe();
    void themChuyenXe();
    void suaChuyenXe();
    void xoaChuyenXe();
    void timChuyenXe();
    void hienThiChuyenXe();

    MyVector<ChuyenXe>& getDSChuyenXe();
};

#endif