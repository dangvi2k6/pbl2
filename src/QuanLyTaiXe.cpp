#include "QuanLyTaiXe.h"
#include "Utils_Sort.h"
#include <limits>

QuanLyTaiXe::QuanLyTaiXe(const string& admin, MyVector<TaXi>* dsTaxi) 
    : currentAdmin(admin), pDsTaxi(dsTaxi) {
    docTaiXe();
}
QuanLyTaiXe::~QuanLyTaiXe(){};

string QuanLyTaiXe::sinhIDTaiXe() {
    int maxID = 0;
    for (const auto& tx : dsTaiXe) {
        if (tx.IDTX.substr(0, 2) == "TX") {
            try {
                int num = stoi(tx.IDTX.substr(2));
                if (num > maxID) maxID = num;
            } catch(...) {}
        }
    }
    char buffer[10];
    sprintf(buffer, "TX%03d", maxID + 1);
    return string(buffer);
}

void QuanLyTaiXe::rebuildTaiXeMap() {
    taiXeByID.clear();
    for(auto& tx: dsTaiXe) {
        taiXeByID[tx.IDTX] = &tx;
    }
}

void QuanLyTaiXe::ghiLichSuTaiXe(const string& hanhDong, const TaiXe& tx, const string& ghiChu = "") {
    ofstream file("data/taixe_history.log", ios::app);
    if (!file.is_open()) return;
    
    file << "=== LICH SU TAI XE ===\n";
    file << "Thoi gian: " << Utils::layThoiGianHienTai() << "\n";
    file << "Nguoi thuc hien: " << currentAdmin << "\n";
    file << "Hanh dong: " << hanhDong << "\n";
    file << "--- Thong tin tai xe ---\n";
    file << "ID: " << tx.IDTX << "\n";
    file << "Ho ten: " << tx.hoDemTX << tx.tenTX << "\n";
    file << "Ngay sinh: " << tx.birth << "\n";
    file << "CCCD: " << tx.soCCCD << "\n";
    file << "Dia chi: " << tx.diaChi << "\n";
    file << "SDT: " << tx.sdt << "\n";
    file << "So GPLX: " << tx.soGPLX << "\n";
    file << "Hang GPLX: " << tx.hangGPLX << "\n";
    file << "Ngay gia nhap: " << tx.ngayGiaNhap << "\n";
    file << "Gioi tinh: " << (tx.gioiTinh ? "Nam" : "Nu") << "\n";
    file << "Trang thai: " << (tx.trangThaiTX ? "Ranh" : "Ban") << "\n";
    file << "Ghi chu: " << tx.note << "\n";
    if (!ghiChu.empty()) {
        file << "Ghi chu them: " << ghiChu << "\n";
    }
    file << string(60, '-') << "\n\n";
    file.close();
}

void QuanLyTaiXe::ghiLichSuHoatDong(const string& loaiHoatDong, const string& doiTuong, const string& chiTiet, const string& trangThai) {
    ofstream file("data/activity_history.log", ios::app);
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

void QuanLyTaiXe::setCurrentAdmin(const string& admin) {
    currentAdmin = admin;
}

void QuanLyTaiXe::setDSTaxi(MyVector<TaXi>* dsTaxi) {
    pDsTaxi = dsTaxi;
}

void QuanLyTaiXe::docTaiXe() {
    ifstream file("data/drivers.txt");
    if (!file.is_open()) {
        ofstream newFile("data/drivers.txt");
        newFile.close();
        return;
    }
    dsTaiXe.clear();
    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string id, hd, ten, birth, soCCCD, dc, sdt, soGPLX, hangGPLX, ngayGiaNhap, note;
        string gioiTinhStr, trangThaiStr;
        if (!getline(ss, id, '|')) continue;
        if (!getline(ss, hd, '|')) continue;
        if (!getline(ss, ten, '|')) continue;
        if (!getline(ss, birth, '|')) continue;
        if (!getline(ss, soCCCD, '|')) continue;
        if (!getline(ss, dc, '|')) continue;
        if (!getline(ss, sdt, '|')) continue;
        if (!getline(ss, soGPLX, '|')) continue;
        if (!getline(ss, hangGPLX, '|')) continue;
        if (!getline(ss, ngayGiaNhap, '|')) continue;
        if (!getline(ss, gioiTinhStr, '|')) continue;
        if (!getline(ss, trangThaiStr,'|')) continue;
        if (!getline(ss, note)) note = "";
        bool gioiTinh = (gioiTinhStr == "1" || gioiTinhStr == "true" || gioiTinhStr == "Nam");
        bool trangThai = (trangThaiStr == "1" || trangThaiStr == "true" || trangThaiStr == "Ranh");
        dsTaiXe.emplace_back(id, hd, ten, birth, soCCCD, dc, sdt, soGPLX, hangGPLX, ngayGiaNhap, gioiTinh, trangThai, note);
    }
    file.close();
    rebuildTaiXeMap();
}

void QuanLyTaiXe::ghiTaiXe() {
    ofstream file("data/drivers.txt");
    for (const auto& tx : dsTaiXe) {
        file << tx.IDTX << "|"
                << tx.hoDemTX << "|"
                << tx.tenTX << "|"
                << tx.birth << "|"
                << tx.soCCCD << "|"
                << tx.diaChi << "|"
                << tx.sdt << "|"
                << tx.soGPLX << "|"
                << tx.hangGPLX << "|"
                << tx.ngayGiaNhap << "|"
                << (tx.gioiTinh ? "Nam" : "Nu") << "|"
                << (tx.trangThaiTX ? "Ranh" : "Ban") << "|"
                << tx.note << endl;
    }
    file.close();
}

void QuanLyTaiXe::themTaiXe() {
    while (true) {
        system("cls");
        Utils::printHeader("THEM TAI XE");
        cout<<"(ESC de quay lai)"<<endl;
        
        string id = sinhIDTaiXe();
        cout << "ID Tai xe (tu dong): " << id << endl;

        string hd, ten, birth, soCCCD, dc, sdt, soGPLX, hangGPLX, ngayGN, note;
        int gioiTinhChoice, trangThaiChoice;

        if(! Utils::getInputWithESC(hd, "Nhap ho dem tai xe: ")) {
            return;
        }
        if(! Utils::getInputWithESC(ten, "Nhap ten tai xe: ")) {
            return;
        }
        if(! Utils::getInputWithESC(birth, "Nhap ngay sinh (dd/mm/yyyy): ")) {
            return;
        }
        if(! Utils::getInputWithESC(soCCCD, "Nhap so CCCD: ")) {
            return;
        }
        if(! Utils::getInputWithESC(dc, "Nhap dia chi: ")) {
            return;
        }
        if(! Utils::getInputWithESC(sdt, "Nhap so dien thoai: ")) {
            return;
        }
        if(! Utils::getInputWithESC(soGPLX, "Nhap so GPLX: ")) {
            return;
        }
        if(! Utils::getInputWithESC(hangGPLX, "Nhap hang GPLX (A1, A2, B1, B2, C, D, E, F): ")) {
            return;
        }
        if(! Utils::getInputWithESC(ngayGN, "Nhap ngay gia nhap (dd/mm/yyyy): ")) {
            return;
        }
        string gioiTinhStr;
        if(! Utils::getInputWithESC(gioiTinhStr, "Gioi tinh (1=Nam, 0=Nu): ")) {
            return;
        }

        // Xử lý exception khi chuyển đổi string sang int
        try {
            gioiTinhChoice = stoi(gioiTinhStr);
        } catch (const std:: invalid_argument&) {
            // Người dùng nhập ký tự không phải số
            Utils::setColor(12); 
            cout << "Loi: Ban phai nhap mot so nguyen hop le!\n"; 
            Utils::setColor(7); 
            Utils::pause(); 
            return;
        } catch (const std::out_of_range&) {
            // Số quá lớn
            Utils::setColor(12); 
            cout << "Loi: So ban nhap qua lon!\n"; 
            Utils:: setColor(7); 
            Utils::pause(); 
            return;
        }

        string trangThaiStr;
        if(! Utils::getInputWithESC(trangThaiStr, "Trang thai (1=Ranh, 0=Ban): ")) {
            return;
        }

        try {
            trangThaiChoice = stoi(trangThaiStr);
        } catch (const std:: invalid_argument&) {
            // Người dùng nhập ký tự không phải số
            Utils::setColor(12); 
            cout << "Loi: Ban phai nhap mot so nguyen hop le!\n"; 
            Utils::setColor(7); 
            Utils::pause(); 
            return;
        } catch (const std::out_of_range&) {
            // Số quá lớn
            Utils::setColor(12); 
            cout << "Loi: So ban nhap qua lon!\n"; 
            Utils:: setColor(7); 
            Utils::pause(); 
            return;
        }

        if(! Utils::getInputWithESC(note, "Nhap ghi chu: ")) {
            return;
        }

        bool gioiTinh = (gioiTinhChoice == 1);
        bool trangThai = (trangThaiChoice == 1);
        
        cout << "Nhap ghi chu: "; getline(cin, note);
        
        TaiXe txMoi(id, hd, ten, birth, soCCCD, dc, sdt, soGPLX, hangGPLX, ngayGN, gioiTinh, trangThai, note);
        dsTaiXe.push_back(txMoi);
        taiXeByID[id] = &dsTaiXe.back();
        ghiTaiXe();
        
        ghiLichSuTaiXe("THEM_MOI", txMoi);
        ghiLichSuHoatDong("THEM_TAI_XE", "Tai xe ID: " + id, 
                            "Ho va Ten: " + hd + ten + " | GPLX: " + hangGPLX, "THANH_CONG");
        
        Utils::setColor(10);
        cout << "\nThem tai xe thanh cong!\n";
        Utils::setColor(7);
        Utils::pause();
        return;
    }
}

void QuanLyTaiXe::suaTaiXe() {
    system("cls");
    Utils::printHeader("SUA THONG TIN TAI XE");
    cout<<"(ESC de quay lai)"<<endl;
    
    string id;
    if(! Utils::getInputWithESC(id, "Nhap ID tai xe can sua (VD: TX001, TX012,...): ")) {
        return;
    }
    
    auto itMap = taiXeByID.find(id);
    if (itMap == taiXeByID.end()) {
        Utils::setColor(12);
        cout << "Khong tim thay tai xe voi ID: " << id << "\n";
        Utils::setColor(7);
        
        ghiLichSuHoatDong("SUA_TAI_XE", "Tai xe ID: " + id, 
                            "Khong tim thay trong he thong", "THAT_BAI");
        
        Utils::pause();
        return;
    }
    
    TaiXe* tx = itMap->second;
    TaiXe txCu = *tx;
    stringstream thayDoiLog;
    
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    
    // ID
    cout << "ID hien tai: " << tx->IDTX << "\n";
    string newID;
    if(! Utils::getInputWithESC(newID, "Nhap ID moi (Enter de giu nguyen): ")) {
        return;
    }
    if (!newID.empty() && newID != tx->IDTX) {
        if (taiXeByID.count(newID)) {
            Utils::setColor(12);
            cout << "ID moi da ton tai!\n";
            Utils::setColor(7);
            Utils::pause();
            return;
        }
        thayDoiLog << "ID: " << tx->IDTX << " -> " << newID << "; ";
        
        // Cập nhật ID trong danh sách xe
        if (pDsTaxi) {
            for (auto& car : *pDsTaxi) {
                for (auto& drvID : car.dsTaiXe) {
                    if (drvID == tx->IDTX) drvID = newID;
                }
            }
        }
        
        taiXeByID.erase(itMap);
        tx->IDTX = newID;
        taiXeByID[newID] = tx;
    }
    
    // Ho dem
    cout << "Ho dem hien tai: " << tx->hoDemTX << "\n";
    string hd;
    if(! Utils::getInputWithESC(hd, "Nhap ho dem moi (Enter de giu nguyen): ")) {
        return;
    }
    if (!hd.empty() && hd != tx->hoDemTX) {
        thayDoiLog << "Ho dem: " << tx->hoDemTX << " -> " << hd << "; ";
        tx->hoDemTX = hd;
    }
    // Tên
    cout << "Ten hien tai: " << tx->tenTX << "\n";
    string ten; 
    if(! Utils::getInputWithESC(ten, "Nhap ten moi (Enter de giu nguyen): ")) {
        return;
    }
    if (!ten.empty() && ten != tx->tenTX) {
        thayDoiLog << "Ten: " << tx->tenTX << " -> " << ten << "; ";
        tx->tenTX = ten;
    }
    
    // Ngày sinh
    cout << "Ngay sinh hien tai: " << tx->birth << "\n";
    string birth;
    if(! Utils::getInputWithESC(birth, "Nhap ngay sinh (dd/mm/yyyy) (Enter de giu nguyen): ")) {
        return;
    }
    if (!birth.empty() && birth != tx->birth) {
        thayDoiLog << "Ngay sinh: " << tx->birth << " -> " << birth << "; ";
        tx->birth = birth;
    }
    
    // CCCD
    cout << "So CCCD hien tai: " << tx->soCCCD << "\n";
    string cccd;
    if(! Utils::getInputWithESC(cccd, "Nhap so CCCD moi (Enter de giu nguyen): ")) {
        return;
    }
    if (!cccd.empty() && cccd != tx->soCCCD) {
        thayDoiLog << "CCCD: " << tx->soCCCD << " -> " << cccd << "; ";
        tx->soCCCD = cccd;
    }
    
    // Địa chỉ
    cout << "Dia chi hien tai: " << tx->diaChi << "\n";
    string dc;
    if(! Utils::getInputWithESC(dc, "Nhap dia chi moi (Enter de giu nguyen): ")) {
        return;
    }
    if (!dc.empty() && dc != tx->diaChi) {
        thayDoiLog << "Dia chi: " << tx->diaChi << " -> " << dc << "; ";
        tx->diaChi = dc;
    }
    
    // SDT
    cout << "SDT hien tai: " << tx->sdt << "\n";
    string sdt;
    if(! Utils::getInputWithESC(sdt, "Nhap SDT moi (Enter de giu nguyen): ")) {
        return;
    }
    if (!sdt.empty() && sdt != tx->sdt) {
        thayDoiLog << "SDT: " << tx->sdt << " -> " << sdt << "; ";
        tx->sdt = sdt;
    }
    
    // GPLX
    cout << "So GPLX hien tai: " << tx->soGPLX << "\n";
    string gplx; 
    if(! Utils::getInputWithESC(gplx, "Nhap so GPLX moi (Enter de giu nguyen): ")) {
        return;
    }
    if (!gplx.empty() && gplx != tx->soGPLX) {
        thayDoiLog << "So GPLX: " << tx->soGPLX << " -> " << gplx << "; ";
        tx->soGPLX = gplx;
    }
    
    // Hạng GPLX
    cout << "Hang GPLX hien tai: " << tx->hangGPLX << "\n";
    string hang;
    if(! Utils::getInputWithESC(hang, "Nhap hang GPLX moi (Enter de giu nguyen): ")) {
        return;
    }
    if (!hang.empty() && hang != tx->hangGPLX) {
        thayDoiLog << "Hang GPLX: " << tx->hangGPLX << " -> " << hang << "; ";
        tx->hangGPLX = hang;
    }
    
    // Ngày gia nhập
    cout << "Ngay gia nhap hien tai: " << tx->ngayGiaNhap << "\n";
    string ngayGN;
    if(! Utils::getInputWithESC(ngayGN, "Nhap ngay gia nhap moi (dd/mm/yyyy) (Enter de giu nguyen): ")) {
        return;
    }
    if (!ngayGN.empty() && ngayGN != tx->ngayGiaNhap) {
        thayDoiLog << "Ngay gia nhap: " << tx->ngayGiaNhap << " -> " << ngayGN << "; ";
        tx->ngayGiaNhap = ngayGN;
    }
    
    // Giới tính
    cout << "Gioi tinh hien tai: " << (tx->gioiTinh ? "Nam" : "Nu") << "\n";
    string gt; 
    if(! Utils::getInputWithESC(gt, "Nhap gioi tinh (1=Nam, 0=Nu, Enter de giu nguyen): ")) {
        return;
    }
    if (!gt.empty()) {
        bool newGt = (gt == "1");
        if (newGt != tx->gioiTinh) {
            thayDoiLog << "Gioi tinh: " << (tx->gioiTinh ? "Nam" : "Nu") 
                        << " -> " << (newGt ? "Nam" : "Nu") << "; ";
            tx->gioiTinh = newGt;
        }
    }
    
    // Trạng thái
    cout << "Trang thai hien tai: " << (tx->trangThaiTX ? "Ranh" : "Ban") << "\n";
    string st; 
    if(! Utils::getInputWithESC(st, "Nhap trang thai (1=Ranh, 0=Ban, Enter de giu nguyen): ")) {
        return;
    }
    if (!st.empty()) {
        bool newSt = (st == "1");
        if (newSt != tx->trangThaiTX) {
            thayDoiLog << "Trang thai: " << (tx->trangThaiTX ? "Ranh" : "Ban") 
                        << " -> " << (newSt ? "Ranh" : "Ban") << "; ";
            tx->trangThaiTX = newSt;
        }
    }
    
    // Ghi chú
    cout << "Ghi chu hien tai: " << tx->note << "\n";
    string note; 
    if(! Utils::getInputWithESC(note, "Nhap ghi chu moi (Enter de giu nguyen): ")) {
        return;
    }
    if (!note.empty() && note != tx->note) {
        thayDoiLog << "Ghi chu: " << tx->note << " -> " << note << "; ";
        tx->note = note;
    }
    
    ghiTaiXe();
    
    string logThayDoi = thayDoiLog.str();
    if (logThayDoi.empty()) {
        logThayDoi = "Khong co thay doi nao";
    }
    
    ghiLichSuTaiXe("CAP_NHAT", txCu, "Thay doi: " + logThayDoi);
    ghiLichSuTaiXe("THONG_TIN_MOI", *tx);
    ghiLichSuHoatDong("SUA_TAI_XE", "Tai xe ID: " + tx->IDTX, 
                        logThayDoi, "THANH_CONG");
    
    Utils::setColor(10);
    cout << "\nCap nhat tai xe thanh cong!\n";
    Utils::setColor(7);
    Utils::pause();
}

void QuanLyTaiXe::xoaTaiXe() {
    system("cls");
    Utils::printHeader("XOA TAI XE");
    cout<<"(ESC de quay lai)"<<endl;
    
    string id;
    if(! Utils::getInputWithESC(id, "Nhap ID tai xe can xoa (VD: TX001, TX012,...): ")) {
        return;
    }
    
    auto itMap = taiXeByID.find(id);
    if (itMap == taiXeByID.end()) {
        Utils::setColor(12);
        cout << "Khong tim thay tai xe voi ID: " << id << "\n";
        Utils::setColor(7);
        
        ghiLichSuHoatDong("XOA_TAI_XE", "Tai xe ID: " + id, 
                            "Khong tim thay trong he thong", "THAT_BAI");
        
        Utils::pause();
        return;
    }
    
    TaiXe txXoa = *itMap->second;
    
    cout << "Ban co chac chan muon xoa tai xe " << id << "? (Y/N): ";
    char confirm;
    cin >> confirm;
    
    if (confirm != 'Y' && confirm != 'y') {
        cout << "Huy xoa!\n";
        
        ghiLichSuHoatDong("XOA_TAI_XE", "Tai xe ID: " + id, 
                            "Nguoi dung huy thao tac", "HUY_BO");
        
        Utils::pause();
        return;
    }
    
    // Xóa tài xế
    dsTaiXe.erase(remove_if(dsTaiXe.begin(), dsTaiXe.end(),
                            [&](const TaiXe& t){ return t.IDTX == id; }),
                    dsTaiXe.end());
    taiXeByID.erase(itMap);
    rebuildTaiXeMap();
    
    // Xóa khỏi danh sách xe
    int soXeBiAnhHuong = 0;
    if (pDsTaxi) {
        for (auto& car : *pDsTaxi) {
            auto oldSize = car.dsTaiXe.size();
            car.dsTaiXe.erase(remove(car.dsTaiXe.begin(), car.dsTaiXe.end(), id),
                                car.dsTaiXe.end());
            if (car.dsTaiXe.size() < oldSize) soXeBiAnhHuong++;
        }
    }
    
    ghiTaiXe();
    
    stringstream ghiChu;
    ghiChu << "So xe bi anh huong: " << soXeBiAnhHuong;
    ghiLichSuTaiXe("XOA", txXoa, ghiChu.str());
    ghiLichSuHoatDong("XOA_TAI_XE", "Tai xe ID: " + id, 
                        "Ho va Ten: " + txXoa.hoDemTX + txXoa.tenTX + " | Xe anh huong: " + to_string(soXeBiAnhHuong), 
                        "THANH_CONG");
    
    Utils::setColor(10);
    cout << "Xoa tai xe thanh cong!\n";
    Utils::setColor(7);
    Utils::pause();
}

void QuanLyTaiXe::hienThiTaiXe() {
    system("cls");
    Utils::printHeader("DANH SACH TAI XE");
    
    if (dsTaiXe.empty()) {
        Utils::setColor(12);
        cout << "Danh sach tai xe trong!\n";
        Utils::setColor(7);
        Utils::pause();
        return;
    }

    cout << left 
        << setw(10) << "ID"
        << setw(25) << "Ho Ten"
        << setw(15) << "Ngay sinh"
        << setw(18) << "CCCD"
        << setw(15) << "SDT"
        << setw(15) << "So GPLX"
        << setw(10) << "Hang"
        << setw(12) << "Gioi tinh"
        << setw(12) << "Trang thai" << endl;
    cout << string(132, '-') << endl;
    
    for (const auto& tx : dsTaiXe) {
        cout << left 
            << setw(10) << tx.IDTX 
            << setw(25) << tx.hoDemTX + " " + tx.tenTX
            << setw(15) << tx.birth
            << setw(18) << tx.soCCCD
            << setw(15) << tx.sdt
            << setw(15) << tx.soGPLX
            << setw(10) << tx.hangGPLX
            << setw(12) << (tx.gioiTinh ? "Nam" : "Nu")
            << setw(12) << (tx.trangThaiTX ? "Ranh" : "Ban") << endl;
    }
    
    cout << "\nTong so tai xe: " << dsTaiXe.size() << endl;
    Utils::pause();
}

void QuanLyTaiXe::timTaiXe() {
    system("cls");
    Utils::printHeader("TIM KIEM TAI XE");
    cout << "Chon tieu chi tim kiem:\n";
    cout << "1. Tim theo ID\n";
    cout << "2. Tim theo ten\n";
    cout << "3. Tim theo so CCCD\n";
    cout << "4. Tim theo so GPLX\n";
    cout << "5. Tim theo trang thai\n";
    cout << "6. Quay lai\n";
    cout << "Lua chon: ";
    
    int choice; 
    
    // Kiểm tra input hợp lệ
    if (!(cin >> choice)) {
        // Nếu input không phải số, clear error flag và buffer
        cin.clear();
        cin.ignore(numeric_limits<streamsize>:: max(), '\n');
        Utils::setColor(12);
        cout << "Lua chon khong hop le!\n";
        Utils::setColor(7);
        Utils::pause();
        return;
    }
    
    MyVector<TaiXe*> ketQua;
    
    switch(choice) {
        case 1: { 
            string id; 
            cout << "Nhap ID can tim (VD: TX001, TX012,...): "; 
            getline(cin, id); 
            for (auto& tx : dsTaiXe) 
                if (tx.IDTX.find(id) != string::npos) 
                    ketQua.push_back(&tx); 
            break; 
        }
        case 2: { 
            string ten; 
            cout << "Nhap ten can tim: "; 
            getline(cin, ten); 
            for (auto& tx : dsTaiXe) 
                if (tx.tenTX.find(ten) != string::npos) 
                    ketQua.push_back(&tx); 
            break; 
        }
        case 3: { 
            string cccd; 
            cout << "Nhap so CCCD can tim: "; 
            getline(cin, cccd); 
            for (auto& tx : dsTaiXe) 
                if (tx.soCCCD.find(cccd) != string::npos) 
                    ketQua.push_back(&tx); 
            break; 
        }
        case 4: { 
            string gplx; 
            cout << "Nhap so GPLX can tim: "; 
            getline(cin, gplx); 
            for (auto& tx : dsTaiXe) 
                if (tx.soGPLX.find(gplx) != string::npos) 
                    ketQua.push_back(&tx); 
            break; 
        }
        case 5: { 
            cout << "Tim tai xe ranh (1) hay ban (0)? "; 
            int tt; 
            cin >> tt; 
            bool trangThai = (tt == 1); 
            for (auto& tx : dsTaiXe) 
                if (tx.trangThaiTX == trangThai) 
                    ketQua.push_back(&tx); 
            break; 
        }
        case 6: 
            return;
        default: 
            Utils::setColor(12); 
            cout << "Lua chon khong hop le!\n"; 
            Utils::setColor(7); 
            Utils::pause(); 
            return;
    }
    
    system("cls");
    Utils::printHeader("KET QUA TIM KIEM");
    
    if (ketQua.empty()) { 
        Utils::setColor(12); 
        cout << "Khong tim thay tai xe phu hop!\n"; 
        Utils::setColor(7); 
        Utils::pause(); 
        return; 
    }
    
    cout << left 
        << setw(5) << "STT" 
        << setw(8) << "ID" 
        << setw(20) << "Ho Ten" 
        << setw(12) << "Ngay sinh" 
        << setw(15) << "CCCD" 
        << setw(12) << "SDT" 
        << setw(12) << "So GPLX" 
        << setw(8) << "Hang" 
        << setw(8) << "Gioi tinh" 
        << setw(10) << "Trang thai" << endl;
    cout << string(120, '-') << endl;
    
    int stt = 1;
    for (const auto& tx : ketQua) {
        cout << left 
            << setw(5) << stt++ 
            << setw(8) << tx->IDTX 
            << setw(20) << tx->hoDemTX + " " + tx->tenTX
            << setw(12) << tx->birth 
            << setw(15) << tx->soCCCD 
            << setw(12) << tx->sdt 
            << setw(12) << tx->soGPLX 
            << setw(8) << tx->hangGPLX 
            << setw(8) << (tx->gioiTinh ? "Nam" : "Nu") 
            << setw(10) << (tx->trangThaiTX ? "Ranh" : "Ban") << endl;
    }
    
    cout << "\nTim thay " << ketQua.size() << " tai xe.\n";
    cout << "\nBan co muon sua thong tin tai xe nao khong? (Y/N): ";
    char suaChoice; 
    cin >> suaChoice; 
    cin.ignore();
    
    if (suaChoice == 'Y' || suaChoice == 'y') {
        if (ketQua.size() == 1) {
            suaTaiXeByPointer(ketQua[0]);
        }
        else {
            cout << "Nhap STT tai xe can sua (1-" << ketQua.size() << "): ";
            int sttChon; 
            cin >> sttChon; 
            cin.ignore();
            if (sttChon >= 1 && sttChon <= (int)ketQua.size()) {
                suaTaiXeByPointer(ketQua[sttChon - 1]);
            }
            else { 
                Utils::setColor(12); 
                cout << "STT khong hop le!\n"; 
                Utils::setColor(7); 
                Utils::pause(); 
            }
        }
    } else {
        Utils::pause();
    }
}

void QuanLyTaiXe::suaTaiXeByPointer(TaiXe* tx) {
    system("cls");
    Utils::printHeader("SUA THONG TIN TAI XE");
    cout << "Thong tin hien tai:\n";
    cout << "ID: " << tx->IDTX << " | Ten: " << tx->hoDemTX << " " << tx->tenTX << endl;
    cout << string(60, '-') << endl;
    
    TaiXe txCu = *tx;
    stringstream thayDoiLog;
    
    cout << "ID hien tai: " << tx->IDTX << "\n";
    cout << "Nhap ID moi (Enter de giu nguyen): ";
    string newID; getline(cin, newID);
    if (!newID.empty() && newID != tx->IDTX) {
        if (taiXeByID.count(newID)) { 
            Utils::setColor(12); 
            cout << "ID moi da ton tai!\n"; 
            Utils::setColor(7); 
            Utils::pause(); 
            return; 
        }
        thayDoiLog << "ID: " << tx->IDTX << " -> " << newID << "; ";
        
        if (pDsTaxi) {
            for (auto& car : *pDsTaxi) 
                for (auto& drvID : car.dsTaiXe) 
                    if (drvID == tx->IDTX) drvID = newID;
        }
        
        taiXeByID.erase(tx->IDTX);
        tx->IDTX = newID;
        taiXeByID[newID] = tx;
    }
    
    cout << "Ho dem hien tai: " << tx->hoDemTX << "\n";
    cout << "Nhap ho dem moi (Enter de giu nguyen): ";
    string hd; getline(cin, hd);
    if (!hd.empty() && hd != tx->hoDemTX) {
        thayDoiLog << "Ho dem: " << tx->hoDemTX << " -> " << hd << "; ";
        tx->hoDemTX = hd;
    }

    cout << "Ten hien tai: " << tx->tenTX << "\n";
    cout << "Nhap ten moi (Enter de giu nguyen): ";
    string ten; getline(cin, ten); 
    if (!ten.empty() && ten != tx->tenTX) {
        thayDoiLog << "Ten: " << tx->tenTX << " -> " << ten << "; ";
        tx->tenTX = ten;
    }
    
    cout << "Ngay sinh hien tai: " << tx->birth << "\n";
    cout << "Nhap ngay sinh moi (Enter de giu nguyen): ";
    string birth; getline(cin, birth); 
    if (!birth.empty() && birth != tx->birth) {
        thayDoiLog << "Ngay sinh: " << tx->birth << " -> " << birth << "; ";
        tx->birth = birth;
    }
    
    cout << "So CCCD hien tai: " << tx->soCCCD << "\n";
    cout << "Nhap so CCCD moi (Enter de giu nguyen): ";
    string cccd; getline(cin, cccd); 
    if (!cccd.empty() && cccd != tx->soCCCD) {
        thayDoiLog << "CCCD: " << tx->soCCCD << " -> " << cccd << "; ";
        tx->soCCCD = cccd;
    }
    
    cout << "Dia chi hien tai: " << tx->diaChi << "\n";
    cout << "Nhap dia chi moi (Enter de giu nguyen): ";
    string dc; getline(cin, dc); 
    if (!dc.empty() && dc != tx->diaChi) {
        thayDoiLog << "Dia chi: " << tx->diaChi << " -> " << dc << "; ";
        tx->diaChi = dc;
    }
    
    cout << "SDT hien tai: " << tx->sdt << "\n";
    cout << "Nhap SDT moi (Enter de giu nguyen): ";
    string sdt; getline(cin, sdt); 
    if (!sdt.empty() && sdt != tx->sdt) {
        thayDoiLog << "SDT: " << tx->sdt << " -> " << sdt << "; ";
        tx->sdt = sdt;
    }
    
    cout << "So GPLX hien tai: " << tx->soGPLX << "\n";
    cout << "Nhap so GPLX moi (Enter de giu nguyen): ";
    string gplx; getline(cin, gplx); 
    if (!gplx.empty() && gplx != tx->soGPLX) {
        thayDoiLog << "So GPLX: " << tx->soGPLX << " -> " << gplx << "; ";
        tx->soGPLX = gplx;
    }
    
    cout << "Hang GPLX hien tai: " << tx->hangGPLX << "\n";
    cout << "Nhap hang GPLX moi (Enter de giu nguyen): ";
    string hang; getline(cin, hang); 
    if (!hang.empty() && hang != tx->hangGPLX) {
        thayDoiLog << "Hang GPLX: " << tx->hangGPLX << " -> " << hang << "; ";
        tx->hangGPLX = hang;
    }
    
    cout << "Ngay gia nhap hien tai: " << tx->ngayGiaNhap << "\n";
    cout << "Nhap ngay gia nhap moi (Enter de giu nguyen): ";
    string ngayGN; getline(cin, ngayGN); 
    if (!ngayGN.empty() && ngayGN != tx->ngayGiaNhap) {
        thayDoiLog << "Ngay gia nhap: " << tx->ngayGiaNhap << " -> " << ngayGN << "; ";
        tx->ngayGiaNhap = ngayGN;
    }
    
    cout << "Gioi tinh hien tai: " << (tx->gioiTinh ? "Nam" : "Nu") << "\n";
    cout << "Nhap gioi tinh (1=Nam, 0=Nu, Enter de giu nguyen): ";
    string gt; getline(cin, gt); 
    if (!gt.empty()) {
        bool newGt = (gt == "1");
        if (newGt != tx->gioiTinh) {
            thayDoiLog << "Gioi tinh: " << (tx->gioiTinh ? "Nam" : "Nu") 
                        << " -> " << (newGt ? "Nam" : "Nu") << "; ";
            tx->gioiTinh = newGt;
        }
    }
    
    cout << "Trang thai hien tai: " << (tx->trangThaiTX ? "Ranh" : "Ban") << "\n";
    cout << "Nhap trang thai (1=Ranh, 0=Ban, Enter de giu nguyen): ";
    string st; getline(cin, st); 
    if (!st.empty()) {
        bool newSt = (st == "1");
        if (newSt != tx->trangThaiTX) {
            thayDoiLog << "Trang thai: " << (tx->trangThaiTX ? "Ranh" : "Ban") 
                        << " -> " << (newSt ? "Ranh" : "Ban") << "; ";
            tx->trangThaiTX = newSt;
        }
    }
    
    cout << "Ghi chu hien tai: " << tx->note << "\n";
    cout << "Nhap ghi chu moi (Enter de giu nguyen): ";
    string note; getline(cin, note); 
    if (!note.empty() && note != tx->note) {
        thayDoiLog << "Ghi chu: " << tx->note << " -> " << note << "; ";
        tx->note = note;
    }
    
    ghiTaiXe();
    
    string logThayDoi = thayDoiLog.str();
    if (logThayDoi.empty()) {
        logThayDoi = "Khong co thay doi nao";
    }
    
    ghiLichSuTaiXe("CAP_NHAT", txCu, "Thay doi: " + logThayDoi);
    ghiLichSuTaiXe("THONG_TIN_MOI", *tx);
    ghiLichSuHoatDong("SUA_TAI_XE", "Tai xe ID: " + tx->IDTX, 
                        logThayDoi, "THANH_CONG");
    
    Utils::setColor(10); 
    cout << "\nCap nhat tai xe thanh cong!\n"; 
    Utils::setColor(7); 
    Utils::pause();
}

TaiXe* QuanLyTaiXe::timTaiXeByID(const string& id) {
    auto it = taiXeByID.find(id);
    if (it != taiXeByID.end()) {
        return it->second;
    }
    return nullptr;
}

MyVector<TaiXe>& QuanLyTaiXe::getDSTaiXe() {
    return dsTaiXe;
}

unordered_map<string, TaiXe*>& QuanLyTaiXe::getTaiXeByID() {
    return taiXeByID;
}

void QuanLyTaiXe::sapXepTaiXe() {
    if (dsTaiXe.empty()) {
        Utils::setColor(12);
        cout << "Danh sach tai xe trong!\n";
        Utils::setColor(7);
        Utils::pause();
        return;
    }
    
    system("cls");
    Utils::printHeader("SAP XEP TAI XE");
    
    cout << "Chon tieu chi sap xep:\n";
    cout << "1. Sap xep theo ID (tang dan)\n";
    cout << "2. Sap xep theo ID (giam dan)\n";
    cout << "3. Sap xep theo ten (A-Z)\n";
    cout << "4. Sap xep theo ten (Z-A)\n";
    cout << "5. Sap xep theo ngay gia nhap (cu -> moi)\n";
    cout << "6. Sap xep theo ngay gia nhap (moi -> cu)\n";
    cout << "7. Sap xep theo hang GPLX (A-Z)\n";
    cout << "8. Sap xep theo hang GPLX (Z-A)\n";
    cout << "9. Sap xep theo trang thai (Ranh truoc)\n";
    cout << "10. Sap xep theo trang thai (Ban truoc)\n";
    cout << "11. Quay lai\n";
    cout << "Lua chon: ";
    
    int choice;
    cin >> choice;
    cin.ignore();
    
    switch(choice) {
        case 1:
            Utils_Sort::sapXepTaiXeTheoID(dsTaiXe, true);
            cout << "\n✓ Da sap xep theo ID tang dan!\n";
            break;
            
        case 2:
            Utils_Sort::sapXepTaiXeTheoID(dsTaiXe, false);
            cout << "\n✓ Da sap xep theo ID giam dan!\n";
            break;
            
        case 3:
            Utils_Sort::sapXepTaiXeTheoTen(dsTaiXe, true);
            cout << "\n✓ Da sap xep theo ten A-Z!\n";
            break;
            
        case 4:
            Utils_Sort::sapXepTaiXeTheoTen(dsTaiXe, false);
            cout << "\n✓ Da sap xep theo ten Z-A!\n";
            break;
            
        case 5:
            Utils_Sort::sapXepTaiXeTheoNgayGiaNhap(dsTaiXe, true);
            cout << "\n✓ Da sap xep theo ngay gia nhap (cu -> moi)!\n";
            break;
            
        case 6:
            Utils_Sort::sapXepTaiXeTheoNgayGiaNhap(dsTaiXe, false);
            cout << "\n✓ Da sap xep theo ngay gia nhap (moi -> cu)!\n";
            break;
            
        case 7:
            Utils_Sort::sapXepTaiXeTheoHangGPLX(dsTaiXe, true);
            cout << "\n✓ Da sap xep theo hang GPLX (A-Z)!\n";
            break;
            
        case 8:
            Utils_Sort::sapXepTaiXeTheoHangGPLX(dsTaiXe, false);
            cout << "\n✓ Da sap xep theo hang GPLX (Z-A)!\n";
            break;
            
        case 9:
            Utils_Sort::sapXepTaiXeTheoTrangThai(dsTaiXe, true);
            cout << "\n✓ Da sap xep theo trang thai (Ranh truoc)!\n";
            break;
            
        case 10:
            Utils_Sort::sapXepTaiXeTheoTrangThai(dsTaiXe, false);
            cout << "\n✓ Da sap xep theo trang thai (Ban truoc)!\n";
            break;
            
        case 11:
            return;
            
        default:
            Utils::setColor(12);
            cout << "Lua chon khong hop le!\n";
            Utils::setColor(7);
            Utils::pause();
            return;
    }

    rebuildTaiXeMap();
    hienThiDanhSachDaSapXep();
    ghiTaiXe();
    
    ghiLichSuHoatDong("SAP_XEP_TAI_XE", 
                      "Tieu chi: " + to_string(choice), 
                      "So luong: " + to_string(dsTaiXe.size()), 
                      "THANH_CONG");
}

void QuanLyTaiXe::hienThiDanhSachDaSapXep() {
    system("cls");
    Utils::printHeader("DANH SACH TAI XE DA SAP XEP");
    
    cout << left 
        << setw(10) << "ID"
        << setw(25) << "Ho Ten"
        << setw(15) << "Ngay sinh"
        << setw(18) << "CCCD"
        << setw(15) << "SDT"
        << setw(15) << "So GPLX"
        << setw(10) << "Hang"
        << setw(12) << "Gioi tinh"
        << setw(12) << "Trang thai" << endl;
    cout << string(132, '-') << endl;
    
    for (const auto& tx : dsTaiXe) {
        cout << left 
            << setw(10) << tx.IDTX 
            << setw(25) << tx.hoDemTX + " " + tx.tenTX
            << setw(15) << tx.birth
            << setw(18) << tx.soCCCD
            << setw(15) << tx.sdt
            << setw(15) << tx.soGPLX
            << setw(10) << tx.hangGPLX
            << setw(12) << (tx.gioiTinh ?  "Nam" : "Nu")
            << setw(12) << (tx.trangThaiTX ? "Ranh" : "Ban") << endl;
    }
    
    cout << "\nTong so tai xe: " << dsTaiXe. size() << endl;
    Utils::pause();
}