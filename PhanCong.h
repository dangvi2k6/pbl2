#ifndef PHANCONG_H
#define PHANCONG_H

#include <string>
#include <fstream>
#include <stdexcept>
#include "TaiXe.h"
#include "Taxi.h"

using namespace std;

class PhanCong {
public:
    string IDPC;
    string IDTX;
    string IDXe;
    string ngayLamViec;     // "15/12/2025" - CHỈ 1 NGÀY (ưu tiên)
    string caLamViec;       // "CA_SANG", "CA_CHIEU", "CA_DEM", "THEO_THANG", "LINH HOAT"
    string gioVao;          // "06:00" hoặc "01/12/2025 00:00"
    string gioRa;           // "14:00" hoặc "31/12/2025 23:59"
    string loaiPhanCong;    // "THEO_CA" hoặc "THEO_THANG"
    bool daHoanThanh;
    float doanhThu;
    float soKmChay;
    string note;
public:
    PhanCong(const string& idpc = "", const string& idtx = "", const string& idxe = "", 
             const string& st = "", const string& et = "", const string& note = "")
        : IDPC(idpc), IDTX(idtx), IDXe(idxe), StartTime(st), EndTime(et), Note(note) {}

    ~PhanCong() {}

    void saveToFile(const string& filename = "phancong.txt") const {
        if (!TaiXe::exists(IDTX))
            throw runtime_error("Loi: Tai xe " + IDTX + " khong ton tai!");
        if (!TaXi::exists(IDXe))
            throw runtime_error("Loi: Xe " + IDXe + " khong ton tai!");

        ofstream fout(filename, ios::app);
        if (!fout.is_open())
            throw runtime_error("Khong mo duoc file phancong.txt de ghi!");

        fout << IDPC << "|" << IDTX << "|" << IDXe << "|" << StartTime << "|"
            << EndTime << "|" << Note << "\n";
        fout.close();
    }
};

#endif