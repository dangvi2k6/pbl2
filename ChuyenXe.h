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
    ChuyenXe(const string&, const string&, const string&, 
             const string&, const string&, const string&,
             double, double, double);
    

    ~ChuyenXe();
};

#endif