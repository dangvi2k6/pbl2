
#ifndef QUANLYTAIXE_H
#define QUANLYTAIXE_H

#include "MyVector.h"
#include <unordered_map>
#include <fstream>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <limits>
#include "TaiXe.h"
#include "TaXi.h"
#include "Utils.h"

using namespace std;

class QuanLyTaiXe {
private:
    MyVector<TaiXe> dsTaiXe;
    unordered_map<string, TaiXe*> taiXeByID;
    string currentAdmin;
    MyVector<TaXi>* pDsTaxi; // Pointer đến danh sách taxi để cập nhật khi xóa tài xế

    string sinhIDTaiXe();
    void rebuildTaiXeMap();
    void ghiLichSuTaiXe(const string&, const TaiXe&, const string&);
    void ghiLichSuHoatDong(const string&, const string&, 
                           const string&, const string& = "THANH_CONG");
    
public:

    QuanLyTaiXe(const string&, MyVector<TaXi>* = nullptr);
    ~QuanLyTaiXe();
    void setCurrentAdmin(const string&);
    void setDSTaxi(MyVector<TaXi>*);
    void docTaiXe();
    void ghiTaiXe();
    void themTaiXe();
    void suaTaiXe();
    void xoaTaiXe();
    void hienThiTaiXe();
    void timTaiXe();
    void suaTaiXeByPointer(TaiXe*);
    TaiXe* timTaiXeByID(const string&);
    MyVector<TaiXe>& getDSTaiXe();
    unordered_map<string, TaiXe*>& getTaiXeByID();

};

#endif