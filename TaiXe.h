#ifndef TAIXE_H
#define TAIXE_H

#include <string>
#include <fstream>
#include <sstream>

using namespace std;

class TaiXe {
public:
    string IDTX;
    string tenTaiXe;
    string birth;
    string soCCCD;
    string diaChi;
    string sdt;
    string soGPLX;
    string hangGPLX;
    string ngayGiaNhap;
    bool gioiTinh;
    bool trangThaiTX;
    string note;

public:
    
    TaiXe(const string&, const string&, const string&, 
          const string&, const string&, const string&, 
          const string&, const string&, const string&, 
          bool, bool, const string&);
    ~TaiXe();
   
    static bool exists(const string&, const string& = "drivers.txt");   

    
};

#endif