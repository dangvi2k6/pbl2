#include "QuanLyChuyenXe.h"

QuanLyChuyenXe::QuanLyChuyenXe(const string& admin, 
                unordered_map<string, TaiXe*>* taiXeByID,
                unordered_map<string, TaXi*>* taxiByID) : currentAdmin(admin), pTaiXeByID(taiXeByID), pTaxiByID(taxiByID) {
    docChuyenXe();
}
QuanLyChuyenXe::~QuanLyChuyenXe() {}

string QuanLyChuyenXe::sinhIDChuyenXe() {
    int maxID = 0;
    for (const auto& cx : dsChuyenXe) {
        if (cx.IDChuyen.substr(0, 2) == "CX") {
            try {
                int num = stoi(cx.IDChuyen.substr(2));
                if (num > maxID) maxID = num;
            } catch(...) {}
        }
    }
    char buffer[10];
    sprintf(buffer, "CX%04d", maxID + 1);
    return string(buffer);
}

void QuanLyChuyenXe::ghiLichSuChuyenXe(const string& hanhDong, const ChuyenXe& cx, const string& ghiChu) {
    ofstream file("chuyenxe_history.log", ios::app);
    if (!file.is_open()) return;
    
    file << "=== LICH SU CHUYEN XE ===\n";
    file << "Thoi gian: " << Utils::layThoiGianHienTai() << "\n";
    file << "Nguoi thuc hien: " << currentAdmin << "\n";
    file << "Hanh dong: " << hanhDong << "\n";
    file << "--- Thong tin chuyen xe ---\n";
    file << "ID Chuyen: " << cx.IDChuyen << "\n";
    file << "ID Tai xe: " << cx.IDTX << "\n";
    file << "ID Xe: " << cx.IDXe << "\n";
    file << "Ten khach hang: " << cx.tenKhach << "\n";
    file << "SDT khach: " << cx.sdtKhach << "\n";
    file << "Thoi diem: " << cx.thoiDiem << "\n";
    file << "Khoang cach: " << fixed << setprecision(2) << cx.khoangCach << " km\n";
    file << "Thoi gian: " << fixed << setprecision(2) << cx.thoiGian << " gio\n";
    file << "Cuoc phi: " << fixed << setprecision(0) << cx.cuocPhi << " VND\n";
    if (!ghiChu.empty()) {
        file << "Ghi chu them: " << ghiChu << "\n";
    }
    file << string(60, '-') << "\n\n";
    file.close();
}

void QuanLyChuyenXe::ghiLichSuHoatDong(const string& loaiHoatDong, const string& doiTuong, 
                        const string& chiTiet, const string& trangThai) {
    ofstream file("activity_history.log", ios::app);
    if (!file.is_open()) return;
    
    file << "==========================================\n";
    file << "Thoi gian: " << Utils::layThoiGianHienTai() << "\n";
    file << "Nguoi thuc hien: " << currentAdmin << "\n";
    file << "Loai hoat dong: " << loaiHoatDong << "\n";
    file << "Doi tuong: " << doiTuong << "\n";
    file << "Chi tiet: " << chiTiet << "\n";
    file << "Trang thai: " << trangThai << "\n";
    file << "==========================================\n\n";
    
    file.close();
}

void QuanLyChuyenXe::setCurrentAdmin(const string& admin) {
    currentAdmin = admin;
}

void QuanLyChuyenXe::setTaiXeByID(unordered_map<string, TaiXe*>* taiXeByID) {
    pTaiXeByID = taiXeByID;
}

void QuanLyChuyenXe::setTaxiByID(unordered_map<string, TaXi*>* taxiByID) {
    pTaxiByID = taxiByID;
}

void QuanLyChuyenXe::docChuyenXe() {
    ifstream file("chuyenxe.txt");
    if (!file.is_open()) return;
    dsChuyenXe.clear();
    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string idChuyen, idTX, idXe, tenKhach, sdtKhach, thoiDiem;
        double khoangCach = 0, thoiGian = 0, cuocPhi = 0;
        getline(ss, idChuyen, '|');
        getline(ss, idTX, '|');
        getline(ss, idXe, '|');
        getline(ss, tenKhach, '|');
        getline(ss, sdtKhach, '|');
        getline(ss, thoiDiem, '|');
        ss >> khoangCach;
        ss.ignore(1);
        ss >> thoiGian;
        ss.ignore(1);
        ss >> cuocPhi;
        dsChuyenXe.emplace_back(idChuyen, idTX, idXe, tenKhach, sdtKhach, thoiDiem, khoangCach, thoiGian, cuocPhi);
    }
    file.close();
}

void QuanLyChuyenXe::ghiChuyenXe() {
    ofstream file("chuyenxe.txt");
    for (const auto& cx : dsChuyenXe) {
        file << cx.IDChuyen << "|" 
                << cx.IDTX << "|" 
                << cx.IDXe << "|"
                << cx.tenKhach << "|" 
                << cx.sdtKhach << "|" 
                << cx.thoiDiem << "|"
                << cx.khoangCach << "|" 
                << cx.thoiGian << "|" 
                << cx.cuocPhi << endl;
    }
    file.close();
}

double QuanLyChuyenXe::tinhCuocPhi(double khoangCach, double thoiGian, const string& thoiDiem) {
    if (khoangCach <= 0) return 0;
    
    double cuocPhi = 0;
    
    //B1: Tính cước phí cơ bản
    // 2km dau tien: 10,000 VND
    if (khoangCach <= 2) {
        cuocPhi = 10000;
    }
    // Tu 2-30km: 10,000 + (khoangCach - 2) * 12,000
    else if (khoangCach <= 30) {
        cuocPhi = 10000 + (khoangCach - 2) * 12000;
    }
    // Tren 30km: 10,000 + 28*12,000 + (khoangCach - 30) * 10,000
    else {
        cuocPhi = 10000 + 28 * 12000 + (khoangCach - 30) * 10000;
    }
    
    // B2: Tính phụ phí giờ cao điểm và đêm
    // =========================================
    // Lay gio tu thoiDiem (format: dd/mm/yyyy HH:MM)
    int gio = 0;
    size_t pos = thoiDiem.find(' ');
    if (pos != string::npos && pos + 3 <= thoiDiem.length()) {
        try {
            string gioStr = thoiDiem.substr(pos + 1, 2);
            gio = stoi(gioStr);
        } catch(...) {
            gio = 12; // Mac dinh gio binh thuong
        }
    }
    
    double phuPhiGio = 0;
    
    // Gio cao diem sang: 6h-9h (+20%)
    if (gio >= 6 && gio < 9) {
        phuPhiGio = cuocPhi * 0.20;
        cout << "\n[+] Phu phi gio cao diem sang (6h-9h): +" 
             << fixed << setprecision(0) << phuPhiGio << " VND (+20%)\n";
    }
    // Gio cao diem chieu: 16h-20h (+20%)
    else if (gio >= 16 && gio < 20) {
        phuPhiGio = cuocPhi * 0.20;
        cout << "\n[+] Phu phi gio cao diem chieu (16h-20h): +" 
             << fixed << setprecision(0) << phuPhiGio << " VND (+20%)\n";
    }
    // Gio dem: 22h-5h (+30%)
    else if (gio >= 22 || gio < 5) {
        phuPhiGio = cuocPhi * 0.30;
        cout << "\n[+] Phu phi gio dem (22h-5h): +" 
             << fixed << setprecision(0) << phuPhiGio << " VND (+30%)\n";
    }
    
    cuocPhi += phuPhiGio;
    
    // BUOC 3: TINH PHU PHI THOI GIAN CHO
    // ===================================
    // Neu van toc trung binh < 40km/h thi tinh phu phi cho
    double vanTocTrungBinh = (thoiGian > 0) ? (khoangCach / thoiGian) : 40;
    
    if (vanTocTrungBinh < 40 && thoiGian > 0) {
        // Thoi gian cho = thoi gian thuc te - thoi gian ly thuyet
        double thoiGianLyThuyet = khoangCach / 40.0; // gio
        double thoiGianCho = thoiGian - thoiGianLyThuyet;
        
        if (thoiGianCho > 0) {
            // Tinh phu phi: 5,000 VND / 10 phut = 30,000 VND / gio
            double phuPhiCho = (thoiGianCho * 60) / 10 * 5000;
            cuocPhi += phuPhiCho;
            
            cout << "[+] Phu phi thoi gian cho (" 
                 << fixed << setprecision(1) << (thoiGianCho * 60) 
                 << " phut): +" << fixed << setprecision(0) 
                 << phuPhiCho << " VND\n";
        }
    }
    
    return cuocPhi;
}

void QuanLyChuyenXe::themChuyenXe() {
    while (true) {
        system("cls");
        Utils::printHeader("THEM CHUYEN XE");
        cout<<"(ESC de quay lai)"<<endl;

        string idChuyen = sinhIDChuyenXe();
        cout << "ID phan cong (tu dong): " << idChuyen << endl;
        
        string idTaiXe, idXe, tenKhach, sdtKhach, thoiDiem;
        double khoangCach, thoiGian, cuocPhi;
        
        if(! Utils::getInputWithESC(idTaiXe, "Nhap ID tai xe (VD: TX001, TX012,...): ")) {
            return;
        }
        // Kiểm tra tài xế tồn tại
        if (pTaiXeByID) {
            auto itTaiXe = pTaiXeByID->find(idTaiXe);
            if (itTaiXe == pTaiXeByID->end()) {
                Utils::setColor(12);
                cout << "Tai xe khong ton tai!\n";
                Utils::setColor(7);
                
                ghiLichSuHoatDong("THEM_CHUYEN_XE", "Chuyen xe ID: " + idChuyen, 
                                    "Tai xe " + idTaiXe + " khong ton tai", "THAT_BAI");
                
                Utils::pause();
                continue;
            }
            
            // Kiểm tra tài xế rảnh
            if (!itTaiXe->second->trangThaiTX) {
                Utils::setColor(12);
                cout << "Tai xe dang ban!\n";
                Utils::setColor(7);
                
                ghiLichSuHoatDong("THEM_CHUYEN_XE", "Chuyen xe ID: " + idChuyen, 
                                    "Tai xe " + idTaiXe + " dang ban", "THAT_BAI");
                
                Utils::pause();
                continue;
            }
        }
        
        cout << "Nhap ID xe: "; 
        if (! Utils::getInputWithESC(idXe, "Nhap ID xe (VD: XE001, XE012,...): ")) {
            return;
        }
        
        // Kiểm tra xe tồn tại
        if (pTaxiByID) {
            auto itXe = pTaxiByID->find(idXe);
            if (itXe == pTaxiByID->end()) {
                Utils::setColor(12);
                cout << "Xe khong ton tai!\n";
                Utils::setColor(7);
                
                ghiLichSuHoatDong("THEM_CHUYEN_XE", "Chuyen xe ID: " + idChuyen, 
                                    "Xe " + idXe + " khong ton tai", "THAT_BAI");
                
                Utils::pause();
                continue;
            }
            
            // Kiểm tra tài xế đã được gắn cho xe này chưa
            auto& dsTX = itXe->second->dsTaiXe;
            if (find(dsTX.begin(), dsTX.end(), idTaiXe) == dsTX.end()) {
                Utils::setColor(12);
                cout << "Tai xe chua duoc gan cho xe nay!\n";
                Utils::setColor(7);
                
                ghiLichSuHoatDong("THEM_CHUYEN_XE", "Chuyen xe ID: " + idChuyen, 
                                    "Tai xe " + idTaiXe + " chua duoc gan cho xe " + idXe, "THAT_BAI");
                
                Utils::pause();
                continue;
            }
        }
        
        cout << "Nhap ten khach: "; 
        if (! Utils::getInputWithESC(tenKhach, "Nhap ten khach: ")) {
            return;
        }
        cout << "Nhap SDT khach: "; 
        if (! Utils::getInputWithESC(sdtKhach, "Nhap SDT khach: ")) {
            return;
        }
        cout << "Nhap thoi diem (dd/mm/yyyy HH:MM): "; 
        if (! Utils::getInputWithESC(thoiDiem, "Nhap thoi diem (dd/mm/yyyy HH:MM): ")) {
            return;
        }
        
        string khoangCachStr;
        if (! Utils::getInputWithESC(khoangCachStr, "Nhap khoang cach (km): ")) {
            return;
        }
        khoangCach = stod(khoangCachStr);

        string thoiGianStr;
        if (! Utils::getInputWithESC(thoiGianStr, "Nhap thoi gian (gio): ")) {
            return;
        }
        thoiGian = stod(thoiGianStr);
        
        double cuocPhiTuDong = tinhCuocPhi(khoangCach, thoiGian, thoiDiem);
        cuocPhi = cuocPhiTuDong;
        Utils::setColor(10);
        cout << "Cuoc phi: " << fixed << setprecision(0) << cuocPhi << " VND\n";
        Utils::setColor(7);

        ChuyenXe cxMoi(idChuyen, idTaiXe, idXe, tenKhach, sdtKhach, thoiDiem, khoangCach, thoiGian, cuocPhi);
        dsChuyenXe.push_back(cxMoi);
        
        // Cập nhật trạng thái tài xế thành bận
        if (pTaiXeByID) {
            auto itTaiXe = pTaiXeByID->find(idTaiXe);
            if (itTaiXe != pTaiXeByID->end()) {
                itTaiXe->second->trangThaiTX = false;
            }
        }
        
        ghiChuyenXe();
        
        // Ghi lịch sử
        ghiLichSuChuyenXe("THEM_MOI", cxMoi);
        stringstream chiTiet;
        chiTiet << "Khach: " << tenKhach << " | KC: " << khoangCach 
                << "km | Phi: " << cuocPhi << "VND";
        ghiLichSuHoatDong("THEM_CHUYEN_XE", "Chuyen xe ID: " + idChuyen, 
                            chiTiet.str(), "THANH_CONG");
        
        Utils::setColor(10);
        cout << "\nThem chuyen xe thanh cong!\n";
        Utils::setColor(7);
        Utils::pause();
        return;
    }
}

void QuanLyChuyenXe::suaChuyenXe() {
    system("cls");
    Utils::printHeader("SUA CHUYEN XE");
    cout<<"(ESC de quay lai)"<<endl;

    string id;
    if(! Utils::getInputWithESC(id, "Nhap ID chuyen xe can sua (VD: CX001, CX012,...): ")) {
        return;
    }
    
    bool found = false;
    for (auto &cx : dsChuyenXe) {
        if (cx.IDChuyen == id) {
            found = true;
            
            ChuyenXe cxCu = cx;
            stringstream thayDoiLog;
            
            cout << "Nhap thong tin moi (Enter de giu nguyen):\n";
            
            // Tên khách
            cout << "Ten khach hien tai: " << cx.tenKhach << "\n";
            string ten;
            if(! Utils::getInputWithESC(ten, "Ten khach moi: ")) {
                return;
            }
            if (!ten.empty() && ten != cx.tenKhach) {
                thayDoiLog << "Ten khach: " << cx.tenKhach << " -> " << ten << "; ";
                cx.tenKhach = ten;
            }
            
            // SDT
            cout << "SDT hien tai: " << cx.sdtKhach << "\n";
            string sdt;
            if(! Utils::getInputWithESC(sdt, "SDT moi: ")) {
                return;
            }
            if (!sdt.empty() && sdt != cx.sdtKhach) {
                thayDoiLog << "SDT: " << cx.sdtKhach << " -> " << sdt << "; ";
                cx.sdtKhach = sdt;
            }
            
            // Khoảng cách
            cout << "Khoang cach hien tai: " << cx.khoangCach << " km\n";
            string kc; 
            if (! Utils::getInputWithESC(kc, "Khoang cach moi (km, Enter de giu nguyen): ")) {
                return;
            }
            if (!kc.empty()) {
                try {
                    double newKc = stod(kc);
                    if (newKc != cx.khoangCach) {
                        thayDoiLog << "Khoang cach: " << cx.khoangCach << " -> " << newKc << "km; ";
                        cx.khoangCach = newKc;
                    }
                } catch(...) {}
            }
            
            // Thời gian
            cout << "Thoi gian hien tai: " << cx.thoiGian << " gio\n";
            string tg;
            if (! Utils::getInputWithESC(tg, "Thoi gian moi (gio, Enter de giu nguyen): ")) {
                return;
            }
            if (!tg.empty()) {
                try {
                    double newTg = stod(tg);
                    if (newTg != cx.thoiGian) {
                        thayDoiLog << "Thoi gian: " << cx.thoiGian << " -> " << newTg << "h; ";
                        cx.thoiGian = newTg;
                    }
                } catch(...) {}
            }
            
            // Cước phí
            cout << "Cuoc phi hien tai: " << cx.cuocPhi << " VND\n";
            string cp;
            if (! Utils::getInputWithESC(cp, "Cuoc phi moi (VND, Enter de giu nguyen): ")) {
                return;
            }
            if (!cp.empty()) {
                try {
                    double newCp = stod(cp);
                    if (newCp != cx.cuocPhi) {
                        thayDoiLog << "Cuoc phi: " << cx.cuocPhi << " -> " << newCp << "VND; ";
                        cx.cuocPhi = newCp;
                    }
                } catch(...) {}
            }
            
            ghiChuyenXe();
            
            // Ghi lịch sử
            string logThayDoi = thayDoiLog.str();
            if (logThayDoi.empty()) {
                logThayDoi = "Khong co thay doi nao";
            }
            
            ghiLichSuChuyenXe("CAP_NHAT", cxCu, "Thay doi: " + logThayDoi);
            ghiLichSuChuyenXe("THONG_TIN_MOI", cx);
            ghiLichSuHoatDong("SUA_CHUYEN_XE", "Chuyen xe ID: " + id, 
                                logThayDoi, "THANH_CONG");
            
            Utils::setColor(10);
            cout << "Da cap nhat chuyen xe!\n";
            Utils::setColor(7);
            Utils::pause();
            break;
        }
    }
    
    if (!found) {
        Utils::setColor(12);
        cout << "Khong tim thay chuyen xe co ID nay!\n";
        Utils::setColor(7);
        
        ghiLichSuHoatDong("SUA_CHUYEN_XE", "Chuyen xe ID: " + id, 
                            "Khong tim thay trong he thong", "THAT_BAI");
        
        Utils::pause();
    }
}

void QuanLyChuyenXe::xoaChuyenXe() {
    system("cls");
    Utils::printHeader("XOA CHUYEN XE");
    cout<<"(ESC de quay lai)"<<endl;
    
    string id;
    if(! Utils::getInputWithESC(id, "Nhap ID chuyen xe can xoa (VD: CX001, CX012,...): ")) {
        return;
    }
    
    auto it = find_if(dsChuyenXe.begin(), dsChuyenXe.end(), 
                        [&](const ChuyenXe &cx) { return cx.IDChuyen == id; });
    
    if (it == dsChuyenXe.end()) {
        Utils::setColor(12);
        cout << "Khong tim thay chuyen xe!\n";
        Utils::setColor(7);
        
        ghiLichSuHoatDong("XOA_CHUYEN_XE", "Chuyen xe ID: " + id, 
                            "Khong tim thay trong he thong", "THAT_BAI");
        
        Utils::pause();
        return;
    }
    
    ChuyenXe cxXoa = *it;
    
    cout << "Ban co chac chan muon xoa chuyen xe " << id << "? (Y/N): ";
    char confirm;
    cin >> confirm;
    
    if (confirm != 'Y' && confirm != 'y') {
        cout << "Huy xoa!\n";
        
        ghiLichSuHoatDong("XOA_CHUYEN_XE", "Chuyen xe ID: " + id, 
                            "Nguoi dung huy thao tac", "HUY_BO");
        
        Utils::pause();
        return;
    }
    
    dsChuyenXe.erase(it);
    ghiChuyenXe();
    
    // Ghi lịch sử
    ghiLichSuChuyenXe("XOA", cxXoa);
    stringstream chiTiet;
    chiTiet << "Khach: " << cxXoa.tenKhach << " | KC: " << cxXoa.khoangCach 
            << "km | Phi: " << cxXoa.cuocPhi << "VND";
    ghiLichSuHoatDong("XOA_CHUYEN_XE", "Chuyen xe ID: " + id, 
                        chiTiet.str(), "THANH_CONG");
    
    Utils::setColor(10);
    cout << "Da xoa chuyen xe thanh cong!\n";
    Utils::setColor(7);
    Utils::pause();
}

void QuanLyChuyenXe::timChuyenXe() {
    system("cls");
    Utils::printHeader("TIM KIEM CHUYEN XE");
    
    cout << "Chon tieu chi tim kiem:\n";
    cout << "1. Tim theo ma chuyen\n";
    cout << "2. Tim theo ID tai xe\n";
    cout << "3. Tim theo ID xe\n";
    cout << "4. Tim theo ten khach hang\n";
    cout << "5. Tim theo so dien thoai khach\n";
    cout << "6. Tim theo ngay (dd/mm/yyyy)\n";
    cout << "7. Tim theo khoang cuoc phi\n";
    cout << "8. Quay lai\n";
    cout << "Lua chon: ";
    
    int choice;
    cin >> choice;
    cin.ignore();
    
    MyVector<ChuyenXe*> ketQua;
    
    switch(choice) {
        case 1: {
            string id;
            cout << "Nhap ma chuyen can tim (VD: CX001, CX012,...): ";
            getline(cin, id);
            for (auto& cx : dsChuyenXe) {
                if (cx.IDChuyen.find(id) != string::npos) {
                    ketQua.push_back(&cx);
                }
            }
            break;
        }
        case 2: {
            string idTX;
            cout << "Nhap ID tai xe can tim (VD: TX001, TX012,...): ";
            getline(cin, idTX);
            for (auto& cx : dsChuyenXe) {
                if (cx.IDTX.find(idTX) != string::npos) {
                    ketQua.push_back(&cx);
                }
            }
            break;
        }
        case 3: {
            string idXe;
            cout << "Nhap ID xe can tim (VD: XE001, XE012,...): ";
            getline(cin, idXe);
            for (auto& cx : dsChuyenXe) {
                if (cx.IDXe.find(idXe) != string::npos) {
                    ketQua.push_back(&cx);
                }
            }
            break;
        }
        case 4: {
            string ten;
            cout << "Nhap ten khach hang can tim: ";
            getline(cin, ten);
            for (auto& cx : dsChuyenXe) {
                if (cx.tenKhach.find(ten) != string::npos) {
                    ketQua.push_back(&cx);
                }
            }
            break;
        }
        case 5: {
            string sdt;
            cout << "Nhap so dien thoai khach can tim: ";
            getline(cin, sdt);
            for (auto& cx : dsChuyenXe) {
                if (cx.sdtKhach.find(sdt) != string::npos) {
                    ketQua.push_back(&cx);
                }
            }
            break;
        }
        case 6: {
            string ngay;
            cout << "Nhap ngay can tim (dd/mm/yyyy): ";
            getline(cin, ngay);
            for (auto& cx : dsChuyenXe) {
                if (cx.thoiDiem.find(ngay) != string::npos) {
                    ketQua.push_back(&cx);
                }
            }
            break;
        }
        case 7: {
            double minPhi, maxPhi;
            cout << "Nhap cuoc phi toi thieu: ";
            cin >> minPhi;
            cout << "Nhap cuoc phi toi da: ";
            cin >> maxPhi;
            for (auto& cx : dsChuyenXe) {
                if (cx.cuocPhi >= minPhi && cx.cuocPhi <= maxPhi) {
                    ketQua.push_back(&cx);
                }
            }
            break;
        }
        case 8:
            return;
        default:
            Utils::setColor(12);
            cout << "Lua chon khong hop le!\n";
            Utils::setColor(7);
            Utils::pause();
            return;
    }
    
    system("cls");
    Utils::printHeader("KET QUA TIM KIEM CHUYEN XE");
    
    if (ketQua.empty()) {
        Utils::setColor(12);
        cout << "Khong tim thay chuyen xe phu hop!\n";
        Utils::setColor(7);
        Utils::pause();
        return;
    }
    
    // Hiển thị kết quả
    cout << left 
        << setw(5) << "STT"
        << setw(12) << "Ma chuyen" 
        << setw(12) << "ID Tai xe"
        << setw(12) << "ID Xe"
        << setw(20) << "Ten khach"
        << setw(15) << "SDT khach"
        << setw(18) << "Thoi diem"
        << setw(10) << "KC (km)"
        << setw(10) << "TG (h)"
        << setw(12) << "Cuoc phi" << endl;
    cout << string(140, '-') << endl;
    
    int stt = 1;
    double tongCuocPhi = 0;
    double tongKhoangCach = 0;
    double tongThoiGian = 0;
    
    for (const auto& cx : ketQua) {
        cout << left    
            << setw(5) << stt++
            << setw(12) << cx->IDChuyen  
            << setw(12) << cx->IDTX      
            << setw(12) << cx->IDXe     
            << setw(20) << cx->tenKhach
            << setw(15) << cx->sdtKhach
            << setw(18) << cx->thoiDiem
            << setw(10) << fixed << setprecision(1) << cx->khoangCach
            << setw(10) << fixed << setprecision(1) << cx->thoiGian
            << setw(12) << fixed << setprecision(0) << cx->cuocPhi << endl;
        
        tongCuocPhi += cx->cuocPhi;
        tongKhoangCach += cx->khoangCach;
        tongThoiGian += cx->thoiGian;
    }
    
    cout << string(140, '-') << endl;
    cout << "\n=== THONG KE ===\n";
    cout << "Tim thay: " << ketQua.size() << " chuyen xe\n";
    cout << "Tong khoang cach: " << fixed << setprecision(1) << tongKhoangCach << " km\n";
    cout << "Tong thoi gian: " << fixed << setprecision(1) << tongThoiGian << " gio\n";
    cout << "Tong cuoc phi: " << fixed << setprecision(0) << tongCuocPhi << " VND\n";
    
    if (ketQua.size() > 0) {
        cout << "Trung binh cuoc phi/chuyen: " << fixed << setprecision(0) 
                << tongCuocPhi / ketQua.size() << " VND\n";
    }
    
    Utils::pause();
}

void QuanLyChuyenXe::hienThiChuyenXe() {
    system("cls");
    Utils::printHeader("DANH SACH CHUYEN XE");
    if(dsChuyenXe.empty()) { 
        Utils::setColor(12); 
        cout << "Danh sach chuyen xe trong!\n"; 
        Utils::setColor(7); 
        Utils::pause(); 
        return; 
    }
    cout << left 
        << setw(12) << "Ma chuyen" 
        << setw(12) << "ID Tai xe" 
        << setw(12) << "ID Xe" 
        << setw(20) << "Ten khach" 
        << setw(15) << "SDT khach" 
        << setw(18) << "Thoi diem" 
        << setw(10) << "KC (km)" 
        << setw(10) << "TG (h)" 
        << setw(12) << "Cuoc phi" << endl;
    cout << string(120, '-') << endl;
    for (const auto& cx : dsChuyenXe) {
        cout << left 
            << setw(12) << cx.IDChuyen 
            << setw(12) << cx.IDTX 
            << setw(12) << cx.IDXe 
            << setw(20) << cx.tenKhach 
            << setw(15) << cx.sdtKhach 
            << setw(18) << cx.thoiDiem 
            << setw(10) << fixed << setprecision(1) << cx.khoangCach 
            << setw(10) << fixed << setprecision(1) << cx.thoiGian 
            << setw(12) << fixed << setprecision(0) << cx.cuocPhi << endl;
    }
    cout << "\nTong so chuyen xe: " << dsChuyenXe.size() << endl; 
    Utils::pause();
}

MyVector<ChuyenXe>& QuanLyChuyenXe::getDSChuyenXe() {
    return dsChuyenXe;
}

