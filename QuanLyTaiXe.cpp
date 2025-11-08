#include "QuanLyTaiXe.h"

QuanLyTaiXe::QuanLyTaiXe(const string& admin, vector<TaXi>* dsTaxi) 
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
    ofstream file("taixe_history.log", ios::app);
    if (!file.is_open()) return;
    
    file << "=== LICH SU TAI XE ===\n";
    file << "Thoi gian: " << Utils::layThoiGianHienTai() << "\n";
    file << "Nguoi thuc hien: " << currentAdmin << "\n";
    file << "Hanh dong: " << hanhDong << "\n";
    file << "--- Thong tin tai xe ---\n";
    file << "ID: " << tx.IDTX << "\n";
    file << "Ho ten: " << tx.tenTaiXe << "\n";
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

void QuanLyTaiXe::setCurrentAdmin(const string& admin) {
    currentAdmin = admin;
}

void QuanLyTaiXe::setDSTaxi(vector<TaXi>* dsTaxi) {
    pDsTaxi = dsTaxi;
}

void QuanLyTaiXe::docTaiXe() {
    ifstream file("drivers.txt");
    if (!file.is_open()) {
        ofstream newFile("drivers.txt");
        newFile.close();
        return;
    }
    dsTaiXe.clear();
    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string id, ten, birth, soCCCD, dc, sdt, soGPLX, hangGPLX, ngayGiaNhap, note;
        string gioiTinhStr, trangThaiStr;
        if (!getline(ss, id, '|')) continue;
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
        dsTaiXe.emplace_back(id, ten, birth, soCCCD, dc, sdt, soGPLX, hangGPLX, ngayGiaNhap, gioiTinh, trangThai, note);
    }
    file.close();
    rebuildTaiXeMap();
}

void QuanLyTaiXe::ghiTaiXe() {
    ofstream file("drivers.txt");
    for (const auto& tx : dsTaiXe) {
        file << tx.IDTX << "|"
                << tx.tenTaiXe << "|"
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
        
        string id = sinhIDTaiXe();
        cout << "ID Tai xe (tu dong): " << id << endl;

        string ten, birth, soCCCD, dc, sdt, soGPLX, hangGPLX, ngayGN, note;
        int gioiTinhChoice, trangThaiChoice;

        string m;
        cout << "Nhap '0' de quay lai: ";
        cin >> m;
        cin.ignore();
        
        if (m == "0") return;
        
        cout << "Nhap ten tai xe: "; getline(cin, ten);
        cout << "Nhap ngay sinh (dd/mm/yyyy): "; getline(cin, birth);
        cout << "Nhap so CCCD: "; getline(cin, soCCCD);
        cout << "Nhap dia chi: "; getline(cin, dc);
        cout << "Nhap so dien thoai: "; getline(cin, sdt);
        cout << "Nhap so GPLX: "; getline(cin, soGPLX);
        cout << "Nhap hang GPLX (A1, A2, B1, B2, C, D, E, F): "; getline(cin, hangGPLX);
        cout << "Nhap ngay gia nhap (dd/mm/yyyy): "; getline(cin, ngayGN);
        cout << "Gioi tinh (1=Nam, 0=Nu): "; cin >> gioiTinhChoice;
        cout << "Trang thai (1=Ranh, 0=Ban): "; cin >> trangThaiChoice;
        cin.ignore();
        
        bool gioiTinh = (gioiTinhChoice == 1);
        bool trangThai = (trangThaiChoice == 1);
        
        cout << "Nhap ghi chu: "; getline(cin, note);
        
        TaiXe txMoi(id, ten, birth, soCCCD, dc, sdt, soGPLX, hangGPLX, ngayGN, gioiTinh, trangThai, note);
        dsTaiXe.push_back(txMoi);
        taiXeByID[id] = &dsTaiXe.back();
        ghiTaiXe();
        
        ghiLichSuTaiXe("THEM_MOI", txMoi);
        ghiLichSuHoatDong("THEM_TAI_XE", "Tai xe ID: " + id, 
                            "Ten: " + ten + " | GPLX: " + hangGPLX, "THANH_CONG");
        
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
    
    string id;
    cout << "Nhap ID tai xe can sua: ";
    cin >> id;
    
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
    
    // Tên
    cout << "Ten hien tai: " << tx->tenTaiXe << "\n";
    cout << "Nhap ten moi (Enter de giu nguyen): ";
    string ten; getline(cin, ten);
    if (!ten.empty() && ten != tx->tenTaiXe) {
        thayDoiLog << "Ten: " << tx->tenTaiXe << " -> " << ten << "; ";
        tx->tenTaiXe = ten;
    }
    
    // Ngày sinh
    cout << "Ngay sinh hien tai: " << tx->birth << "\n";
    cout << "Nhap ngay sinh moi (Enter de giu nguyen): ";
    string birth; getline(cin, birth);
    if (!birth.empty() && birth != tx->birth) {
        thayDoiLog << "Ngay sinh: " << tx->birth << " -> " << birth << "; ";
        tx->birth = birth;
    }
    
    // CCCD
    cout << "So CCCD hien tai: " << tx->soCCCD << "\n";
    cout << "Nhap so CCCD moi (Enter de giu nguyen): ";
    string cccd; getline(cin, cccd);
    if (!cccd.empty() && cccd != tx->soCCCD) {
        thayDoiLog << "CCCD: " << tx->soCCCD << " -> " << cccd << "; ";
        tx->soCCCD = cccd;
    }
    
    // Địa chỉ
    cout << "Dia chi hien tai: " << tx->diaChi << "\n";
    cout << "Nhap dia chi moi (Enter de giu nguyen): ";
    string dc; getline(cin, dc);
    if (!dc.empty() && dc != tx->diaChi) {
        thayDoiLog << "Dia chi: " << tx->diaChi << " -> " << dc << "; ";
        tx->diaChi = dc;
    }
    
    // SDT
    cout << "SDT hien tai: " << tx->sdt << "\n";
    cout << "Nhap SDT moi (Enter de giu nguyen): ";
    string sdt; getline(cin, sdt);
    if (!sdt.empty() && sdt != tx->sdt) {
        thayDoiLog << "SDT: " << tx->sdt << " -> " << sdt << "; ";
        tx->sdt = sdt;
    }
    
    // GPLX
    cout << "So GPLX hien tai: " << tx->soGPLX << "\n";
    cout << "Nhap so GPLX moi (Enter de giu nguyen): ";
    string gplx; getline(cin, gplx);
    if (!gplx.empty() && gplx != tx->soGPLX) {
        thayDoiLog << "So GPLX: " << tx->soGPLX << " -> " << gplx << "; ";
        tx->soGPLX = gplx;
    }
    
    // Hạng GPLX
    cout << "Hang GPLX hien tai: " << tx->hangGPLX << "\n";
    cout << "Nhap hang GPLX moi (Enter de giu nguyen): ";
    string hang; getline(cin, hang);
    if (!hang.empty() && hang != tx->hangGPLX) {
        thayDoiLog << "Hang GPLX: " << tx->hangGPLX << " -> " << hang << "; ";
        tx->hangGPLX = hang;
    }
    
    // Ngày gia nhập
    cout << "Ngay gia nhap hien tai: " << tx->ngayGiaNhap << "\n";
    cout << "Nhap ngay gia nhap moi (Enter de giu nguyen): ";
    string ngayGN; getline(cin, ngayGN);
    if (!ngayGN.empty() && ngayGN != tx->ngayGiaNhap) {
        thayDoiLog << "Ngay gia nhap: " << tx->ngayGiaNhap << " -> " << ngayGN << "; ";
        tx->ngayGiaNhap = ngayGN;
    }
    
    // Giới tính
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
    
    // Trạng thái
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
    
    // Ghi chú
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

void QuanLyTaiXe::xoaTaiXe() {
    system("cls");
    Utils::printHeader("XOA TAI XE");
    
    string id;
    cout << "Nhap ID tai xe can xoa: ";
    cin >> id;
    
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
                        "Ten: " + txXoa.tenTaiXe + " | Xe anh huong: " + to_string(soXeBiAnhHuong), 
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
            << setw(25) << tx.tenTaiXe
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
    cin >> choice; 
    cin.ignore();
    
    vector<TaiXe*> ketQua;
    
    switch(choice) {
        case 1: { 
            string id; 
            cout << "Nhap ID can tim: "; 
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
                if (tx.tenTaiXe.find(ten) != string::npos) 
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
            << setw(20) << tx->tenTaiXe 
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
    cout << "ID: " << tx->IDTX << " | Ten: " << tx->tenTaiXe << endl;
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
    
    cout << "Ten hien tai: " << tx->tenTaiXe << "\n";
    cout << "Nhap ten moi (Enter de giu nguyen): ";
    string ten; getline(cin, ten); 
    if (!ten.empty() && ten != tx->tenTaiXe) {
        thayDoiLog << "Ten: " << tx->tenTaiXe << " -> " << ten << "; ";
        tx->tenTaiXe = ten;
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

vector<TaiXe>& QuanLyTaiXe::getDSTaiXe() {
    return dsTaiXe;
}

unordered_map<string, TaiXe*>& QuanLyTaiXe::getTaiXeByID() {
    return taiXeByID;
}