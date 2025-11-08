#include "ChuyenXe.h"

ChuyenXe::ChuyenXe(const string& idc = "", const string& idtx = "", const string& idxe = "", 
             const string& tk = "", const string& sdt = "", const string& td = "",
             double kc = 0, double tg = 0, double cp = 0)
        : IDChuyen(idc), IDTX(idtx), IDXe(idxe),
          tenKhach(tk), sdtKhach(sdt), thoiDiem(td),
          khoangCach(kc), thoiGian(tg), cuocPhi(cp) {}

ChuyenXe::~ChuyenXe() {}