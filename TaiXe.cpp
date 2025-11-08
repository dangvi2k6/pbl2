#include "TaiXe.h"
TaiXe::TaiXe(const string& id = "", const string& ten = "", const string& b = "", 
          const string& CCCD = "", const string& dc = "", const string& dt = "", 
          const string& gplx = "", const string& hang = "", const string& ngayGN = "", 
          bool gt = true, bool tt = true, const string& ghiChu = "")
        : IDTX(id), tenTaiXe(ten), birth(b), soCCCD(CCCD), diaChi(dc), sdt(dt),
          soGPLX(gplx), hangGPLX(hang), ngayGiaNhap(ngayGN), gioiTinh(gt), 
          trangThaiTX(tt), note(ghiChu) {}

TaiXe::~TaiXe() {}

bool TaiXe::exists(const string& idTX, const string& filename = "drivers.txt") {
    ifstream fin(filename);
    if (!fin.is_open()) return false;
    string line;
    while (getline(fin, line)) {
        stringstream ss(line);
        string id;
        getline(ss, id, '|');
        if (id == idTX) {
            fin.close();
            return true;
        }
    }
    fin.close();
    return false;
}