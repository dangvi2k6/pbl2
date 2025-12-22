#include "QuanLyTaXi.h"
#include "Utils_Sort.h"
#include <limits>

QuanLyTaXi::QuanLyTaXi(const string& admin, unordered_map<string, TaiXe*>* taiXeByID) 
    : currentAdmin(admin), pTaiXeByID(taiXeByID) {
    docTaxi();
}

string QuanLyTaXi::sinhIDXe() {
    int maxID = 0;
    for (const auto& xe : dsTaxi) {
        if (xe.IDXe.substr(0, 2) == "XE") {
            try {
                int num = stoi(xe.IDXe.substr(2));
                if (num > maxID) maxID = num;
            } catch(...) {}
        }
    }
    char buffer[10];
    sprintf(buffer, "XE%03d", maxID + 1);
    return string(buffer);
}

void QuanLyTaXi::rebuildTaxiMap() {
    taxiByID.clear();
    for(auto& tx: dsTaxi) {
        taxiByID[tx.IDXe] = &tx;
    }
}

void QuanLyTaXi::ghiLichSuTaxi(const string& hanhDong, const TaXi& tx, const string& ghiChu) {
    ofstream file("data/taxi_history.log", ios::app);
    if (!file.is_open()) return;
    
    file << "=== LICH SU TAXI ===\n";
    file << "Thoi gian: " << Utils::layThoiGianHienTai() << "\n";
    file << "Nguoi thuc hien: " << currentAdmin << "\n";
    file << "Hanh dong: " << hanhDong << "\n";
    file << "--- Thong tin xe ---\n";
    file << "ID Xe: " << tx.IDXe << "\n";
    file << "Bien so: " << tx.bienSo << "\n";
    file << "Mau xe: " << tx.mauXe << "\n";
    file << "Hang xe: " << tx.hangXe << "\n";
    file << "Nam san xuat: " << tx.namSX << "\n";
    file << "Suc chua: " << tx.sucChua << " cho\n";
    file << "Dung tich khoang hanh ly: " << tx.dungTichKhoangHanhLy << " lit\n";
    file << "Ngay bao duong gan nhat: " << tx.ngayBaoDuongGanNhat << "\n";
    file << "Trang thai: " << (tx.trangThaiXe ? "Hoat dong" : "Bao tri") << "\n";
    file << "Danh sach tai xe: ";
    if (tx.dsTaiXe.empty()) {
        file << "(Chua co)\n";
    } else {
        for (size_t i = 0; i < tx.dsTaiXe.size(); ++i) {
            file << tx.dsTaiXe[i];
            if (i < tx.dsTaiXe.size() - 1) file << ", ";
        }
        file << "\n";
    }
    if (!ghiChu.empty()) {
        file << "Ghi chu them: " << ghiChu << "\n";
    }
    file << string(60, '-') << "\n\n";
    file.close();
}

void QuanLyTaXi::ghiLichSuHoatDong(const string& loaiHoatDong, const string& doiTuong, 
                           const string& chiTiet, const string& trangThai) {
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

void QuanLyTaXi::setCurrentAdmin(const string& admin) {
    currentAdmin = admin;
}

void QuanLyTaXi::setTaiXeByID(unordered_map<string, TaiXe*>* taiXeByID) {
    pTaiXeByID = taiXeByID;
}

void QuanLyTaXi::docTaxi() {
    ifstream file("data/cars.txt");
    if (!file.is_open()) {
        ofstream newFile("data/cars.txt");
        newFile.close();
        return;
    }
    dsTaxi.clear();
    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string id, bienSo, mau, hang, nam, khoang, ngayBD, trangThaiStr, dsTaiXeStr;
        int sucChua;
        if (!getline(ss, id, '|')) continue;
        if (!getline(ss, bienSo, '|')) continue;
        if (!getline(ss, mau, '|')) continue;
        if (!getline(ss, hang, '|')) continue;
        if (!getline(ss, nam, '|')) continue;
        if (!getline(ss, khoang, '|')) continue;
        if (!getline(ss, ngayBD, '|')) continue;
        string sucChuaStr;
        if (!getline(ss, sucChuaStr, '|')) continue;
        try { sucChua = stoi(sucChuaStr); } catch(...) { sucChua = 0; }
        if (!getline(ss, trangThaiStr, '|')) continue;
        if (!getline(ss, dsTaiXeStr)) dsTaiXeStr = "";
        bool trangThai = (trangThaiStr == "1");
        TaXi taxi(id, bienSo, mau, hang, nam, khoang, ngayBD, sucChua, trangThai);
        if (!dsTaiXeStr.empty()) {
            stringstream ssTaiXe(dsTaiXeStr);
            string idTX;
            while (getline(ssTaiXe, idTX, ',')) {
                if (!idTX.empty()) taxi.dsTaiXe.push_back(idTX);
            }
        }
        dsTaxi.push_back(taxi);
    }
    file.close();
    rebuildTaxiMap();
}

void QuanLyTaXi::ghiTaxi() {
    ofstream file("data/cars.txt");
    if (!file.is_open()) {
        Utils::setColor(12);
        cout << "Loi: Khong the mo file cars.txt de ghi!\n";
        Utils::setColor(7);
        return;
    }
    for (const auto& tx : dsTaxi) {
        file << tx.IDXe << "|"
                << tx.bienSo << "|"
                << tx.mauXe << "|"
                << tx.hangXe << "|"
                << tx.namSX << "|"
                << tx.dungTichKhoangHanhLy << "|"
                << tx.ngayBaoDuongGanNhat << "|"
                << tx.sucChua << "|"
                << (tx.trangThaiXe ? "1" : "0") << "|";
        for (size_t i = 0; i < tx.dsTaiXe.size(); ++i) {
            file << tx.dsTaiXe[i];
            if (i < tx.dsTaiXe.size() - 1) file << ",";
        }
        file << endl;
    }
    file.close();
}

void QuanLyTaXi::themTaxi() {
    while (true) {
        system("cls");
        Utils::printHeader("THEM TAXI");
        cout<< "(ESC de quay lai)" << endl;

        string id = sinhIDXe();
        cout << "ID Xe (tu dong): " << id << endl;

        string bienSo, mau, hang, nam, khoang, ngayBD;
        int sucChua, trangThaiChoice;
        
        
        if(! Utils::getInputWithESC(bienSo, "Nhap bien so xe: ")) {
            return;
        }
        
        // Kiểm tra biển số trùng
        bool bienSoTrung = false;
        for (const auto& tx : dsTaxi) {
            if (tx.bienSo == bienSo) {
                bienSoTrung = true;
                break;
            }
        }
        
        if (bienSoTrung) {
            Utils::setColor(12);
            cout << "Bien so xe da ton tai!\n";
            Utils::setColor(7);
            
            ghiLichSuHoatDong("THEM_TAXI", "Taxi bien so: " + bienSo, 
                                "Bien so da ton tai trong he thong", "THAT_BAI");
            
            Utils::pause();
            continue;
        }
        
        if(! Utils::getInputWithESC(mau, "Nhap mau xe: ")) {
            return;
        }
        if(! Utils::getInputWithESC(hang, "Nhap hang xe (VD: Toyota, Honda, Vinfast...): ")) {
            return;
        }
        if(! Utils::getInputWithESC(nam, "Nhap nam san xuat: ")) {
            return;
        }
        if(! Utils::getInputWithESC(khoang, "Nhap dung tich khoang hanh ly (lit): ")) {
            return;
        }
        if(! Utils::getInputWithESC(ngayBD, "Nhap ngay bao duong gan nhat (dd/mm/yyyy): ")) {
            return;
        }
        string sucChuaStr;
        if(! Utils::getInputWithESC(sucChuaStr, "Nhap suc chua (so cho ngoi): ")) {
            return;
        }

        try {
            sucChua = stoi(sucChuaStr);
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
        if(! Utils::getInputWithESC(trangThaiStr, "Trang thai xe (1=Hoat dong, 0=Bao tri): ")) {
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
        
        bool trangThai = (trangThaiChoice == 1);
        
        TaXi txMoi(id, bienSo, mau, hang, nam, khoang, ngayBD, sucChua, trangThai);
        dsTaxi.push_back(txMoi);
        taxiByID[id] = &dsTaxi.back();
        ghiTaxi();
        
        ghiLichSuTaxi("THEM_MOI", txMoi);
        ghiLichSuHoatDong("THEM_TAXI", "Taxi ID: " + id, 
                            "Bien so: " + bienSo + " | Hang: " + hang + " | Suc chua: " + to_string(sucChua), 
                            "THANH_CONG");
        
        Utils::setColor(10);
        cout << "\nThem taxi thanh cong!\n";
        Utils::setColor(7);
        Utils::pause();
        return;
    }
}

void QuanLyTaXi::suaTaxi() {
    system("cls");
    Utils::printHeader("SUA THONG TIN TAXI");
    cout<<"(ESC de quay lai)"<<endl;

    string id;
    
    if(! Utils::getInputWithESC(id, "Nhap ID xe can sua (VD: XE001, XE012,...): ")) {
        return;
    }
    
    auto itMap = taxiByID.find(id);
    if (itMap == taxiByID.end()) {
        Utils::setColor(12);
        cout << "Khong tim thay xe voi ID: " << id << "\n";
        Utils::setColor(7);
        
        ghiLichSuHoatDong("SUA_TAXI", "Taxi ID: " + id, 
                            "Khong tim thay trong he thong", "THAT_BAI");
        
        Utils::pause();
        return;
    }
    
    TaXi* tx = itMap->second;
    TaXi txCu = *tx;
    stringstream thayDoiLog;
    
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    
    // ID xe
    cout << "ID xe hien tai: " << tx->IDXe << "\n";
    string newID; 
    if(! Utils::getInputWithESC(newID, "Nhap ID xe moi (Enter de giu nguyen): ")) {
        return;
    }
    if (!newID.empty() && newID != tx->IDXe) {
        if (taxiByID.count(newID)) {
            Utils::setColor(12);
            cout << "ID moi da ton tai!\n";
            Utils::setColor(7);
            Utils::pause();
            return;
        }
        thayDoiLog << "ID: " << tx->IDXe << " -> " << newID << "; ";
        taxiByID.erase(itMap);
        tx->IDXe = newID;
        taxiByID[newID] = tx;
    }
    
    // Biển số
    cout << "Bien so hien tai: " << tx->bienSo << "\n";
    string bienSo;
    if(! Utils::getInputWithESC(bienSo, "Nhap bien so moi (Enter de giu nguyen): ")) {
        return;
    }
    if (!bienSo.empty() && bienSo != tx->bienSo) {
        bool trung = false;
        for (const auto& t : dsTaxi) {
            if (t.bienSo == bienSo && t.IDXe != tx->IDXe) {
                trung = true;
                break;
            }
        }
        if (trung) {
            Utils::setColor(12);
            cout << "Bien so da ton tai!\n";
            Utils::setColor(7);
            Utils::pause();
            return;
        }
        thayDoiLog << "Bien so: " << tx->bienSo << " -> " << bienSo << "; ";
        tx->bienSo = bienSo;
    }
    
    // Màu xe
    cout << "Mau xe hien tai: " << tx->mauXe << "\n";
    string mau;
    if(! Utils::getInputWithESC(mau, "Nhap mau xe moi (Enter de giu nguyen): ")) {
        return;
    }
    if (!mau.empty() && mau != tx->mauXe) {
        thayDoiLog << "Mau: " << tx->mauXe << " -> " << mau << "; ";
        tx->mauXe = mau;
    }
    
    // Hãng xe
    cout << "Hang xe hien tai: " << tx->hangXe << "\n";
    string hang;
    if(! Utils::getInputWithESC(hang, "Nhap hang xe moi (Enter de giu nguyen): ")) {
        return;
    }
    if (!hang.empty() && hang != tx->hangXe) {
        thayDoiLog << "Hang: " << tx->hangXe << " -> " << hang << "; ";
        tx->hangXe = hang;
    }
    
    // Năm sản xuất
    cout << "Nam san xuat hien tai: " << tx->namSX << "\n";
    string nam;
    if(! Utils::getInputWithESC(nam, "Nhap nam san xuat moi (Enter de giu nguyen): ")) {
        return;
    }
    if (!nam.empty() && nam != tx->namSX) {
        thayDoiLog << "Nam SX: " << tx->namSX << " -> " << nam << "; ";
        tx->namSX = nam;
    }
    
    // Dung tích khoang hành lý
    cout << "Dung tich khoang hanh ly hien tai: " << tx->dungTichKhoangHanhLy << "\n";
    string khoang;
    if(! Utils::getInputWithESC(khoang, "Nhap dung tich khoang hanh ly moi (Enter de giu nguyen): ")) {
        return;
    }
    if (!khoang.empty() && khoang != tx->dungTichKhoangHanhLy) {
        thayDoiLog << "Khoang hanh ly: " << tx->dungTichKhoangHanhLy << " -> " << khoang << "; ";
        tx->dungTichKhoangHanhLy = khoang;
    }
    
    // Ngày bảo dưỡng
    cout << "Ngay bao duong gan nhat hien tai: " << tx->ngayBaoDuongGanNhat << "\n";
    string ngayBD;
    if(! Utils::getInputWithESC(ngayBD, "Nhap ngay bao duong moi (dd/mm/yyyy) (Enter de giu nguyen): ")) {
        return;
    }
    if (!ngayBD.empty() && ngayBD != tx->ngayBaoDuongGanNhat) {
        thayDoiLog << "Ngay bao duong: " << tx->ngayBaoDuongGanNhat << " -> " << ngayBD << "; ";
        tx->ngayBaoDuongGanNhat = ngayBD;
    }
    
    // Sức chứa
    cout << "Suc chua hien tai: " << tx->sucChua << "\n";
    string sc;
    if(! Utils::getInputWithESC(sc, "Nhap suc chua moi (so cho ngoi) (Enter de giu nguyen): ")) {
        return;
    }
    if (!sc.empty()) {
        try {
            int sucChua = stoi(sc);
            if (sucChua > 0 && sucChua != tx->sucChua) {
                thayDoiLog << "Suc chua: " << tx->sucChua << " -> " << sucChua << "; ";
                tx->sucChua = sucChua;
            }
        } catch (...) {
            Utils::setColor(12);
            cout << "Gia tri khong hop le!\n";
            Utils::setColor(7);
        }
    }
    
    // Trạng thái
    cout << "Trang thai hien tai: " << (tx->trangThaiXe ? "Hoat dong" : "Bao tri") << "\n";
    string st;
    if(! Utils::getInputWithESC(st, "Nhap trang thai (1=Hoat dong, 0=Bao tri, Enter de giu nguyen): ")) {
        return;
    }
    if (!st.empty()) {
        bool newSt = (st == "1");
        if (newSt != tx->trangThaiXe) {
            thayDoiLog << "Trang thai: " << (tx->trangThaiXe ? "Hoat dong" : "Bao tri") 
                        << " -> " << (newSt ? "Hoat dong" : "Bao tri") << "; ";
            tx->trangThaiXe = newSt;
        }
    }
    
    ghiTaxi();
    
    string logThayDoi = thayDoiLog.str();
    if (logThayDoi.empty()) {
        logThayDoi = "Khong co thay doi nao";
    }
    
    ghiLichSuTaxi("CAP_NHAT", txCu, "Thay doi: " + logThayDoi);
    ghiLichSuTaxi("THONG_TIN_MOI", *tx);
    ghiLichSuHoatDong("SUA_TAXI", "Taxi ID: " + tx->IDXe, 
                        logThayDoi, "THANH_CONG");
    
    Utils::setColor(10);
    cout << "\nCap nhat taxi thanh cong!\n";
    Utils::setColor(7);
    Utils::pause();
}

void QuanLyTaXi::xoaTaxi() {
    system("cls");
    Utils::printHeader("XOA TAXI");
    cout<<"(ESC de quay lai)"<<endl;

    string id;
    if(! Utils::getInputWithESC(id, "Nhap ID xe can xoa (VD: XE001, XE012,...): ")) {
        return;
    }
    
    auto itMap = taxiByID.find(id);
    if (itMap == taxiByID.end()) {
        Utils::setColor(12);
        cout << "Khong tim thay xe voi ID: " << id << "\n";
        Utils::setColor(7);
        
        ghiLichSuHoatDong("XOA_TAXI", "Taxi ID: " + id, 
                            "Khong tim thay trong he thong", "THAT_BAI");
        
        Utils::pause();
        return;
    }
    
    TaXi txXoa = *itMap->second;
    
    cout << "Ban co chac chan muon xoa xe " << id << "? (Y/N): ";
    char confirm;
    cin >> confirm;
    
    if (confirm != 'Y' && confirm != 'y') {
        cout << "Huy xoa!\n";
        
        ghiLichSuHoatDong("XOA_TAXI", "Taxi ID: " + id, 
                            "Nguoi dung huy thao tac", "HUY_BO");
        
        Utils::pause();
        return;
    }
    
    dsTaxi.erase(remove_if(dsTaxi.begin(), dsTaxi.end(),
                            [&](const TaXi& t){ return t.IDXe == id; }),
                    dsTaxi.end());
    taxiByID.erase(itMap);
    ghiTaxi();
    
    stringstream ghiChu;
    ghiChu << "So tai xe bi anh huong: " << txXoa.dsTaiXe.size();
    ghiLichSuTaxi("XOA", txXoa, ghiChu.str());
    ghiLichSuHoatDong("XOA_TAXI", "Taxi ID: " + id, 
                        "Bien so: " + txXoa.bienSo + " | Tai xe anh huong: " + to_string(txXoa.dsTaiXe.size()), 
                        "THANH_CONG");
    
    Utils::setColor(10);
    cout << "Xoa taxi thanh cong!\n";
    Utils::setColor(7);
    Utils::pause();
}

void QuanLyTaXi::hienThiTaxi() {
    system("cls");
    Utils::printHeader("DANH SACH TAXI");
    if (dsTaxi.empty()) { 
        Utils::setColor(12); 
        cout << "Danh sach taxi trong!\n"; 
        Utils::setColor(7); 
        Utils::pause(); 
        return; 
    }
    cout << left 
        << setw(8) << "ID" 
        << setw(12) << "Bien so" 
        << setw(10) << "Mau" 
        << setw(12) << "Hang" 
        << setw(8) << "Nam SX" 
        << setw(10) << "Suc chua" 
        << setw(12) << "Bao duong" 
        << setw(12) << "Trang thai" 
        << setw(20) << "Danh sach tai xe" << endl;
    cout << string(110, '-') << endl;
    for (const auto& tx : dsTaxi) {
        cout << left 
            << setw(8) << tx.IDXe 
            << setw(12) << tx.bienSo 
            << setw(10) << tx.mauXe 
            << setw(12) << tx.hangXe 
            << setw(8) << tx.namSX 
            << setw(10) << tx.sucChua 
            << setw(12) << tx.ngayBaoDuongGanNhat 
            << setw(12) << (tx.trangThaiXe ? "Hoat dong" : "Bao tri");
        if (tx.dsTaiXe.empty()) {
            cout << setw(20) << "Chua co";
        }
        else {
            string dsTenTaiXe;
            if (pTaiXeByID) {
                for (const auto& idTX : tx.dsTaiXe) {
                    auto it = pTaiXeByID->find(idTX);
                    if (it != pTaiXeByID->end()) {
                        dsTenTaiXe += it->second->tenTX + ", ";
                    }
                }
                if (!dsTenTaiXe.empty()) {
                    dsTenTaiXe = dsTenTaiXe.substr(0, dsTenTaiXe.length() - 2);
                }
            }
            cout << setw(20) << dsTenTaiXe;
        }
        cout << endl;
    }
    cout << "\nTong so xe: " << dsTaxi.size() << endl; 
    Utils::pause();
}

void QuanLyTaXi::timTaxi() {
    system("cls");
    Utils::printHeader("TIM KIEM TAXI");
    cout << "Chon tieu chi tim kiem:\n";
    cout << "1. Tim theo ID\n";
    cout << "2. Tim theo bien so\n";
    cout << "3. Tim theo hang xe\n";
    cout << "4. Tim theo mau xe\n";
    cout << "5. Tim theo nam san xuat\n";
    cout << "6. Tim theo trang thai\n";
    cout << "7. Tim theo suc chua\n";
    cout << "8. Quay lai\n";
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
    
    MyVector<TaXi*> ketQua;
    
    switch(choice) {
        case 1: { 
            string id; 
            cout << "Nhap ID can tim (VD: XE001, XE012,...): "; 
            getline(cin, id); 
            for (auto& tx : dsTaxi) 
                if (tx.IDXe.find(id) != string::npos) 
                    ketQua.push_back(&tx); 
            break; 
        }
        case 2: { 
            string bienSo; 
            cout << "Nhap bien so can tim: "; 
            getline(cin, bienSo); 
            for (auto& tx : dsTaxi) 
                if (tx.bienSo.find(bienSo) != string::npos) 
                    ketQua.push_back(&tx); 
            break; 
        }
        case 3: { 
            string hang; 
            cout << "Nhap hang xe can tim: "; 
            getline(cin, hang); 
            for (auto& tx : dsTaxi) 
                if (tx.hangXe.find(hang) != string::npos) 
                    ketQua.push_back(&tx); 
            break; 
        }
        case 4: { 
            string mau; 
            cout << "Nhap mau xe can tim: "; 
            getline(cin, mau); 
            for (auto& tx : dsTaxi) 
                if (tx.mauXe.find(mau) != string::npos) 
                    ketQua.push_back(&tx); 
            break; 
        }
        case 5: { 
            string nam; 
            cout << "Nhap nam san xuat can tim: "; 
            getline(cin, nam); 
            for (auto& tx : dsTaxi) 
                if (tx.namSX.find(nam) != string::npos) 
                    ketQua.push_back(&tx); 
            break; 
        }
        case 6: { 
            cout << "Tim xe hoat dong (1) hay bao tri (0)? "; 
            int tt; 
            cin >> tt; 
            bool trangThai = (tt == 1); 
            for (auto& tx : dsTaxi) 
                if (tx.trangThaiXe == trangThai) 
                    ketQua.push_back(&tx); 
            break; 
        }
        case 7: { 
            int sucChua; 
            cout << "Nhap suc chua can tim: "; 
            cin >> sucChua; 
            for (auto& tx : dsTaxi) 
                if (tx.sucChua == sucChua) 
                    ketQua.push_back(&tx); 
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
    Utils::printHeader("KET QUA TIM KIEM");
    if (ketQua.empty()) { 
        Utils::setColor(12); 
        cout << "Khong tim thay xe phu hop!\n"; 
        Utils::setColor(7); 
        Utils::pause(); 
        return; 
    }
    
    cout << left 
        << setw(8) << "ID" 
        << setw(12) << "Bien so" 
        << setw(10) << "Mau" 
        << setw(12) << "Hang" 
        << setw(8) << "Nam SX" 
        << setw(10) << "Suc chua" 
        << setw(12) << "Bao duong" 
        << setw(12) << "Trang thai" 
        << setw(20) << "Danh sach tai xe" << endl;
    cout << string(110, '-') << endl;
    
    for (const auto& tx : ketQua) {
        cout << left 
            << setw(8) << tx->IDXe 
            << setw(12) << tx->bienSo 
            << setw(10) << tx->mauXe 
            << setw(12) << tx->hangXe 
            << setw(8) << tx->namSX 
            << setw(10) << tx->sucChua 
            << setw(12) << tx->ngayBaoDuongGanNhat 
            << setw(12) << (tx->trangThaiXe ? "Hoat dong" : "Bao tri");
        if (tx->dsTaiXe.empty()) {
            cout << setw(20) << "Chua co";
        }
        else {
            string dsTenTaiXe;
            if (pTaiXeByID) {
                for (const auto& idTX : tx->dsTaiXe) {
                    auto it = pTaiXeByID->find(idTX);
                    if (it != pTaiXeByID->end()) {
                        dsTenTaiXe += it->second->tenTX + ", ";
                    }
                }
                if (!dsTenTaiXe.empty()) {
                    dsTenTaiXe = dsTenTaiXe.substr(0, dsTenTaiXe.length() - 2);
                }
            }
            cout << setw(20) << dsTenTaiXe;
        }
        cout << endl;
    }
    
    cout << "\nTim thay " << ketQua.size() << " xe.\n";
    Utils::pause();
}

void QuanLyTaXi::xemChiTietTaxi() {
    system("cls");
    Utils::printHeader("XEM CHI TIET TAXI");
    cout<< "(ESC de quay lai)" << endl;
    string id; 
    if(! Utils::getInputWithESC(id, "Nhap ID xe can xem chi tiet (VD: XE001, XE012,...): ")) { 
        return; 
    }
    auto itMap = taxiByID.find(id);
    if (itMap == taxiByID.end()) { 
        Utils::setColor(12); 
        cout << "Khong tim thay xe voi ID: " << id << "\n"; 
        Utils::setColor(7); 
        Utils::pause(); 
        return; 
    }
    TaXi* tx = itMap->second;
    system("cls");
    Utils::printHeader("THONG TIN CHI TIET TAXI");
    cout << "ID Xe: " << tx->IDXe << endl;
    cout << "Bien so: " << tx->bienSo << endl;
    cout << "Mau xe: " << tx->mauXe << endl;
    cout << "Hang xe: " << tx->hangXe << endl;
    cout << "Nam san xuat: " << tx->namSX << endl;
    cout << "Suc chua: " << tx->sucChua << " cho" << endl;
    cout << "Dung tich khoang hanh ly: " << tx->dungTichKhoangHanhLy << " lit" << endl;
    cout << "Ngay bao duong gan nhat: " << tx->ngayBaoDuongGanNhat << endl;
    cout << "Trang thai: " << (tx->trangThaiXe ? "Hoat dong" : "Bao tri") << endl;
    cout << "\nDanh sach tai xe duoc gan:\n";
    if (tx->dsTaiXe.empty()) {
        cout << "  (Chua co tai xe nao)\n";
    }
    else {
        int stt = 1;
        for (const auto& idTX : tx->dsTaiXe) {
            if (pTaiXeByID) {
                auto it = pTaiXeByID->find(idTX);
                if (it != pTaiXeByID->end()) {
                    cout << "  " << stt++ << ". " << it->second->tenTX << " (ID: " << idTX << ")\n";
                } else {
                    cout << "  " << stt++ << ". " << idTX << "\n";
                }
            } else {
                cout << "  " << stt++ << ". " << idTX << "\n";
            }
        }
    }
    Utils::pause();
}

TaXi* QuanLyTaXi::timTaxiByID(const string& id) {
    auto it = taxiByID.find(id);
    if (it != taxiByID.end()) {
        return it->second;
    }
    return nullptr;
}

MyVector<TaXi>& QuanLyTaXi::getDSTaxi() {
    return dsTaxi;
}

unordered_map<string, TaXi*>& QuanLyTaXi::getTaxiByID() {
    return taxiByID;
}

void QuanLyTaXi::sapXepTaxi() {
    if (dsTaxi. empty()) {
        Utils::setColor(12);
        cout << "Danh sach taxi trong!\n";
        Utils::setColor(7);
        Utils::pause();
        return;
    }
    
    system("cls");
    Utils::printHeader("SAP XEP TAXI");
    
    cout << "Chon tieu chi sap xep:\n";
    cout << "1. Sap xep theo ID (tang dan)\n";
    cout << "2. Sap xep theo ID (giam dan)\n";
    cout << "3. Sap xep theo bien so (A-Z)\n";
    cout << "4. Sap xep theo bien so (Z-A)\n";
    cout << "5. Sap xep theo hang xe (A-Z)\n";
    cout << "6. Sap xep theo hang xe (Z-A)\n";
    cout << "7. Sap xep theo nam san xuat (cu -> moi)\n";
    cout << "8. Sap xep theo nam san xuat (moi -> cu)\n";
    cout << "9. Sap xep theo suc chua (tang dan)\n";
    cout << "10. Sap xep theo suc chua (giam dan)\n";
    cout << "11. Sap xep theo trang thai (Hoat dong truoc)\n";
    cout << "12. Sap xep theo trang thai (Bao tri truoc)\n";
    cout << "13. Quay lai\n";
    cout << "Lua chon: ";
    
    int choice;
    cin >> choice;
    cin.ignore();
    
    switch(choice) {
        case 1:
            Utils_Sort::sapXepTaxiTheoID(dsTaxi, true);
            cout << "\n✓ Da sap xep theo ID tang dan!\n";
            break;
            
        case 2:
            Utils_Sort::sapXepTaxiTheoID(dsTaxi, false);
            cout << "\n✓ Da sap xep theo ID giam dan!\n";
            break;
            
        case 3:
            Utils_Sort::sapXepTaxiTheoBienSo(dsTaxi, true);
            cout << "\n✓ Da sap xep theo bien so A-Z!\n";
            break;
            
        case 4:
            Utils_Sort::sapXepTaxiTheoBienSo(dsTaxi, false);
            cout << "\n✓ Da sap xep theo bien so Z-A!\n";
            break;
            
        case 5:
            Utils_Sort::sapXepTaxiTheoHangXe(dsTaxi, true);
            cout << "\n✓ Da sap xep theo hang xe A-Z!\n";
            break;
            
        case 6:
            Utils_Sort::sapXepTaxiTheoHangXe(dsTaxi, false);
            cout << "\n✓ Da sap xep theo hang xe Z-A!\n";
            break;
            
        case 7:
            Utils_Sort::sapXepTaxiTheoNamSX(dsTaxi, true);
            cout << "\n✓ Da sap xep theo nam san xuat (cu -> moi)!\n";
            break;
            
        case 8:
            Utils_Sort::sapXepTaxiTheoNamSX(dsTaxi, false);
            cout << "\n✓ Da sap xep theo nam san xuat (moi -> cu)!\n";
            break;
            
        case 9:
            Utils_Sort::sapXepTaxiTheoSucChua(dsTaxi, true);
            cout << "\n✓ Da sap xep theo suc chua tang dan!\n";
            break;
            
        case 10:
            Utils_Sort::sapXepTaxiTheoSucChua(dsTaxi, false);
            cout << "\n✓ Da sap xep theo suc chua giam dan!\n";
            break;
            
        case 11:
            Utils_Sort::sapXepTaxiTheoTrangThai(dsTaxi, true);
            cout << "\n✓ Da sap xep theo trang thai (Hoat dong truoc)!\n";
            break;
            
        case 12:
            Utils_Sort::sapXepTaxiTheoTrangThai(dsTaxi, false);
            cout << "\n✓ Da sap xep theo trang thai (Bao tri truoc)!\n";
            break;
            
        case 13:
            return;
            
        default:
            Utils::setColor(12);
            cout << "Lua chon khong hop le!\n";
            Utils::setColor(7);
            Utils::pause();
            return;
    }
    
    rebuildTaxiMap();
    hienThiDanhSachTaxiDaSapXep();
    ghiTaxi();
    
    ghiLichSuHoatDong("SAP_XEP_TAXI", 
                      "Tieu chi: " + to_string(choice), 
                      "So luong: " + to_string(dsTaxi.size()), 
                      "THANH_CONG");
}

void QuanLyTaXi::hienThiDanhSachTaxiDaSapXep() {
    system("cls");
    Utils::printHeader("DANH SACH TAXI DA SAP XEP");
    
    cout << left 
        << setw(8) << "ID" 
        << setw(12) << "Bien so" 
        << setw(10) << "Mau" 
        << setw(12) << "Hang" 
        << setw(8) << "Nam SX" 
        << setw(10) << "Suc chua" 
        << setw(12) << "Bao duong" 
        << setw(12) << "Trang thai" << endl;
    cout << string(84, '-') << endl;
    
    for (const auto& tx : dsTaxi) {
        cout << left 
            << setw(8) << tx. IDXe 
            << setw(12) << tx.bienSo 
            << setw(10) << tx.mauXe 
            << setw(12) << tx.hangXe 
            << setw(8) << tx.namSX 
            << setw(10) << tx.sucChua 
            << setw(12) << tx.ngayBaoDuongGanNhat 
            << setw(12) << (tx.trangThaiXe ? "Hoat dong" : "Bao tri") << endl;
    }
    
    cout << "\nTong so xe: " << dsTaxi. size() << endl;
    Utils::pause();
}