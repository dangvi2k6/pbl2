#ifndef CHUYENXE_H
#define CHUYENXE_H

#include <string>

using namespace std;

class ChuyenXe {
public:
    string IDChuyen;
    string IDTX;
    string IDXe;
    string tenKhach;
    string sdtKhach;
    string thoiDiem;
    double khoangCach;
    double thoiGian;
    double cuocPhi;

public:
    ChuyenXe(const string& idc = "", const string& idtx = "", const string& idxe = "", 
             const string& tk = "", const string& sdt = "", const string& td = "",
             double kc = 0, double tg = 0, double cp = 0)
        : IDChuyen(idc), IDTX(idtx), IDXe(idxe),
          tenKhach(tk), sdtKhach(sdt), thoiDiem(td),
          khoangCach(kc), thoiGian(tg), cuocPhi(cp) {}

    ~ChuyenXe() {}
};

#endif