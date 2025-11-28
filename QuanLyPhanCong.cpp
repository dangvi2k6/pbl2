#include "QuanLyPhanCong.h"
#include "Utils_Sort.h"

QuanLyPhanCong::QuanLyPhanCong(const string& admin,
                unordered_map<string, TaiXe*>* taiXeByID,
                unordered_map<string, TaXi*>* taxiByID)
    : currentAdmin(admin), pTaiXeByID(taiXeByID), pTaxiByID(taxiByID) {
    docPhanCong();
}

QuanLyPhanCong::~QuanLyPhanCong() {
}

string QuanLyPhanCong::sinhIDPhanCong() {
    int maxID = 0;
    for (const auto& pc : dsPhanCong) {
        if (pc.IDPC.substr(0, 2) == "PC") {
            try {
                int num = stoi(pc.IDPC.substr(2));
                if (num > maxID) maxID = num;
            } catch(...) {}
        }
    }
    char buffer[10];
    sprintf(buffer, "PC%04d", maxID + 1);
    return string(buffer);
}

void QuanLyPhanCong::rebuildPhanCongMap() {
    phanCongByID.clear();
    for (auto& pc : dsPhanCong) {
        phanCongByID[pc.IDPC] = &pc;
    }
}

void QuanLyPhanCong::setCurrentAdmin(const string& admin) {
    currentAdmin = admin;
}

void QuanLyPhanCong::setTaiXeByID(unordered_map<string, TaiXe*>* taiXeByID) {
    pTaiXeByID = taiXeByID;
}

void QuanLyPhanCong::setTaxiByID(unordered_map<string, TaXi*>* taxiByID) {
    pTaxiByID = taxiByID;
}

void QuanLyPhanCong::docPhanCong() {
    ifstream file("phancong.txt");
    if (!file.is_open()) {
        ofstream newFile("phancong.txt");
        newFile.close();
        return;
    }
    dsPhanCong.clear();
    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string idpc, idtx, idxe, st, et, note;
        if (!getline(ss, idpc, '|')) continue;
        if (!getline(ss, idtx, '|')) continue;
        if (!getline(ss, idxe, '|')) continue;
        if (!getline(ss, st, '|')) continue;
        if (!getline(ss, et, '|')) continue;
        if (!getline(ss, note)) note = "";
        dsPhanCong.emplace_back(idpc, idtx, idxe, st, et, note);
    }
    file.close();
    rebuildPhanCongMap();
}

void QuanLyPhanCong::ghiPhanCong() {
    ofstream file("phancong.txt");
    for (const auto& pc : dsPhanCong) {
        file << pc.IDPC << "|" << pc.IDTX << "|" << pc.IDXe << "|" 
                << pc.StartTime << "|" << pc.EndTime << "|" << pc.Note << endl;
    }
    file.close();
}

void QuanLyPhanCong::themPhanCong() {
    system("cls");
    Utils::printHeader("THEM PHAN CONG");
    cout<<"(ESC de quay lai)"<<endl;

    string idpc = sinhIDPhanCong();
    cout << "ID phan cong (tu dong): " << idpc << endl;
    
    string idtx, idxe, st, et, note;
    
    if (!Utils::getInputWithESC(idtx, "Nhap ID tai xe (VD: TX001, TX012,...): ")) {
        return;
    }
    
    if (pTaiXeByID && pTaiXeByID->find(idtx) == pTaiXeByID->end()) {
        Utils::setColor(12); 
        cout << "Tai xe khong ton tai!\n"; 
        Utils::setColor(7); 
        Utils::pause(); 
        return;
    }
    
    if (!Utils::getInputWithESC(idxe, "Nhap ID xe (VD: XE001, XE012,...): ")) {
        return;
    }
    
    if (pTaxiByID && pTaxiByID->find(idxe) == pTaxiByID->end()) {
        Utils::setColor(12); 
        cout << "Xe khong ton tai!\n"; 
        Utils::setColor(7); 
        Utils::pause(); 
        return;
    }
    
    if (! Utils::getInputWithESC(st, "Nhap thoi gian bat dau (dd/mm/yyyy HH:MM): ")) {
        return;
    }
    
    if (!Utils::getInputWithESC(et, "Nhap thoi gian ket thuc (dd/mm/yyyy HH:MM): ")) {
        return;
    }
    
    if (!Utils::getInputWithESC(note, "Nhap ghi chu: ")) {
        return;
    }
    
    dsPhanCong.emplace_back(idpc, idtx, idxe, st, et, note);
    phanCongByID[idpc] = &dsPhanCong.back();
    ghiPhanCong();
    
    Utils::setColor(10); 
    cout << "\nThem phan cong thanh cong!\n"; 
    Utils::setColor(7); 
    Utils::pause();
}

void QuanLyPhanCong::suaPhanCong() {
    system("cls");
    Utils::printHeader("SUA THONG TIN PHAN CONG");
    cout<<"(ESC de quay lai)"<<endl;

    string id;
    cout << "Nhap ID phan cong can sua (VD: PC0001, PC0002,...): "; 
    if (!Utils::getInputWithESC(id, "Nhap ID phan cong can sua (VD: PC0001, PC0002,...): ")) {
        return;
    }
    
    auto it = phanCongByID.find(id);
    if (it == phanCongByID.end()) {
        Utils::setColor(12); 
        cout << "Khong tim thay phan cong voi ID: " << id << "\n"; 
        Utils::setColor(7); 
        Utils::pause(); 
        return;
    }
    
    PhanCong* pc = it->second;
    
    cout << "ID hien tai: " << pc->IDPC << "\n";
    string newID; 
    if (! Utils::getInputWithESC(newID, "Nhap ID moi (Enter de giu nguyen): ")) {
        return;
    }
    if (!newID.empty() && newID != pc->IDPC) {
        if (phanCongByID.count(newID)) { 
            Utils::setColor(12); 
            cout << "ID moi da ton tai!\n"; 
            Utils::setColor(7); 
            Utils::pause(); 
            return; 
        }
        phanCongByID.erase(it);
        pc->IDPC = newID;
        phanCongByID[newID] = pc;
    }
    
    cout << "ID tai xe hien tai: " << pc->IDTX << "\n";
    string idtx; 
    if (!Utils::getInputWithESC(idtx, "Nhap ID tai xe moi (Enter de giu nguyen): ")) {
        return;
    }
    if (!idtx.empty()) {
        if (pTaiXeByID && pTaiXeByID->find(idtx) == pTaiXeByID->end()) { 
            Utils::setColor(12); 
            cout << "Tai xe khong ton tai!\n"; 
            Utils::setColor(7); 
            Utils::pause(); 
            return; 
        }
        pc->IDTX = idtx;
    }
    
    cout << "ID xe hien tai: " << pc->IDXe << "\n";
    string idxe; 
    if (!Utils::getInputWithESC(idxe, "Nhap ID xe moi (Enter de giu nguyen): ")) {
        return;
    }
    if (!idxe.empty()) {
        if (pTaxiByID && pTaxiByID->find(idxe) == pTaxiByID->end()) { 
            Utils::setColor(12); 
            cout << "Xe khong ton tai!\n"; 
            Utils::setColor(7); 
            Utils::pause(); 
            return; 
        }
        pc->IDXe = idxe;
    }
    
    cout << "Thoi gian bat dau hien tai: " << pc->StartTime << "\n";
    string st; 
    if (!Utils::getInputWithESC(st, "Nhap thoi gian bat dau moi (Enter de giu nguyen): ")) {
        return;
    }
    if (!st.empty()) pc->StartTime = st;
    
    cout << "Thoi gian ket thuc hien tai: " << pc->EndTime << "\n";
    string et; 
    if (!Utils::getInputWithESC(et, "Nhap thoi gian ket thuc moi (Enter de giu nguyen): ")) {
        return;
    }
    if (!et.empty()) pc->EndTime = et;
    
    cout << "Ghi chu hien tai: " << pc->Note << "\n";
    string note; 
    if (! Utils::getInputWithESC(note, "Nhap ghi chu moi (Enter de giu nguyen): ")) {
        return;
    }
    if (!note.empty()) pc->Note = note;
    
    ghiPhanCong();
    
    Utils::setColor(10); 
    cout << "\nCap nhat phan cong thanh cong!\n"; 
    Utils::setColor(7); 
    Utils::pause();
}

void QuanLyPhanCong::xoaPhanCong() {
    system("cls");
    Utils::printHeader("XOA PHAN CONG");
    cout<<"(ESC de quay lai)"<<endl;

    string id; 
    if (! Utils::getInputWithESC(id, "Nhap ID phan cong can xoa (VD: PC0001, PC0002,...): ")) 
        return;
    cout<<endl;
    
    auto it = phanCongByID.find(id);
    if (it == phanCongByID.end()) { 
        Utils::setColor(12); 
        cout << "Khong tim thay phan cong voi ID: " << id << "\n"; 
        Utils::setColor(7); 
        Utils::pause(); 
        return; 
    }
    
    cout << "Ban co chac chan muon xoa phan cong " << id << "? (Y/N): ";
    char confirm; 
    cin >> confirm;
    
    if (confirm != 'Y' && confirm != 'y') { 
        cout << "Huy xoa!\n"; 
        Utils::pause(); 
        return; 
    }
    
    dsPhanCong.erase(remove_if(dsPhanCong.begin(), dsPhanCong.end(), 
                                [&](const PhanCong& p){ return p.IDPC == id; }), 
                        dsPhanCong.end());
    phanCongByID.erase(it);
    ghiPhanCong();
    
    Utils::setColor(10); 
    cout << "Xoa phan cong thanh cong!\n"; 
    Utils::setColor(7); 
    Utils::pause();
}

void QuanLyPhanCong::hienThiPhanCong() {
    system("cls");
    Utils::printHeader("DANH SACH PHAN CONG");
    
    if (dsPhanCong.empty()) { 
        Utils::setColor(12); 
        cout << "Danh sach phan cong trong!\n"; 
        Utils::setColor(7); 
        Utils::pause(); 
        return; 
    }
    
    cout << left 
        << setw(10) << "ID PC" 
        << setw(10) << "ID TX" 
        << setw(10) << "ID Xe" 
        << setw(20) << "Start Time" 
        << setw(20) << "End Time" 
        << setw(30) << "Note" << endl;
    cout << string(100, '-') << endl;
    
    for (const auto& pc : dsPhanCong) {
        cout << left 
            << setw(10) << pc.IDPC 
            << setw(10) << pc.IDTX 
            << setw(10) << pc.IDXe 
            << setw(20) << pc.StartTime 
            << setw(20) << pc.EndTime 
            << setw(30) << pc.Note << endl;
    }
    
    cout << "\nTong so phan cong: " << dsPhanCong.size() << endl;
    Utils::pause();
}

void QuanLyPhanCong::timPhanCong() {
    system("cls");
    Utils::printHeader("TIM KIEM PHAN CONG");
    
    cout << "Chon tieu chi tim kiem:\n";
    cout << "1. Tim theo ID phan cong\n";
    cout << "2. Tim theo ID tai xe\n";
    cout << "3. Tim theo ID xe\n";
    cout << "4. Quay lai\n";
    cout << "Lua chon: ";
    
    int choice; 
    cin >> choice; 
    cin.ignore();
    
    MyVector<PhanCong*> ketQua;
    
    switch(choice) {
        case 1: { 
            string id; 
            cout << "Nhap ID phan cong can tim (VD: PC0001, PC0002,...): "; 
            getline(cin, id); 
            for (auto& pc : dsPhanCong) 
                if (pc.IDPC.find(id) != string::npos) 
                    ketQua.push_back(&pc); 
            break; 
        }
        case 2: { 
            string idtx; 
            cout << "Nhap ID tai xe can tim (VD: TX001, TX012,...): "; 
            getline(cin, idtx); 
            for (auto& pc : dsPhanCong) 
                if (pc.IDTX.find(idtx) != string::npos) 
                    ketQua.push_back(&pc); 
            break; 
        }
        case 3: { 
            string idxe; 
            cout << "Nhap ID xe can tim (VD: XE001, XE012,...): "; 
            getline(cin, idxe); 
            for (auto& pc : dsPhanCong) 
                if (pc.IDXe.find(idxe) != string::npos) 
                    ketQua.push_back(&pc); 
            break; 
        }
        case 4: 
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
        cout << "Khong tim thay phan cong phu hop!\n"; 
        Utils::setColor(7); 
        Utils::pause(); 
        return; 
    }
    
    cout << left 
        << setw(10) << "ID PC" 
        << setw(10) << "ID TX" 
        << setw(10) << "ID Xe" 
        << setw(20) << "Start Time" 
        << setw(20) << "End Time" 
        << setw(30) << "Note" << endl;
    cout << string(100, '-') << endl;
    
    for (const auto& pc : ketQua) {
        cout << left 
            << setw(10) << pc->IDPC 
            << setw(10) << pc->IDTX 
            << setw(10) << pc->IDXe 
            << setw(20) << pc->StartTime 
            << setw(20) << pc->EndTime 
            << setw(30) << pc->Note << endl;
    }
    
    cout << "\nTim thay " << ketQua.size() << " phan cong.\n";
    Utils::pause();
}

MyVector<PhanCong>& QuanLyPhanCong::getDSPhanCong() {
    return dsPhanCong;
}

void QuanLyPhanCong::sapXepPhanCong() {
    if (dsPhanCong.empty()) {
        Utils::setColor(12);
        cout << "Danh sach phan cong trong!\n";
        Utils::setColor(7);
        Utils::pause();
        return;
    }
    
    system("cls");
    Utils::printHeader("SAP XEP PHAN CONG");
    
    cout << "Chon tieu chi sap xep:\n";
    cout << "1. Sap xep theo ID phan cong (tang dan)\n";
    cout << "2. Sap xep theo ID phan cong (giam dan)\n";
    cout << "3. Sap xep theo ngay phan cong (cu -> moi)\n";
    cout << "4. Sap xep theo ngay phan cong (moi -> cu)\n";
    cout << "5.  Sap xep theo ca lam viec (A-Z)\n";
    cout << "6. Sap xep theo ca lam viec (Z-A)\n";
    cout << "7. Quay lai\n";
    cout << "Lua chon: ";
    
    int choice;
    cin >> choice;
    cin.ignore();
    
    switch(choice) {
        case 1:
            Utils_Sort::sapXepPhanCongTheoID(dsPhanCong, true);
            cout << "\n✓ Da sap xep theo ID phan cong tang dan!\n";
            break;
            
        case 2:
            Utils_Sort::sapXepPhanCongTheoID(dsPhanCong, false);
            cout << "\n✓ Da sap xep theo ID phan cong giam dan!\n";
            break;
            
        case 3:
            Utils_Sort::sapXepPhanCongTheoNgay(dsPhanCong, true);
            cout << "\n✓ Da sap xep theo ngay phan cong (cu -> moi)!\n";
            break;
            
        case 4:
            Utils_Sort::sapXepPhanCongTheoNgay(dsPhanCong, false);
            cout << "\n✓ Da sap xep theo ngay phan cong (moi -> cu)!\n";
            break;
            
        case 5:
            Utils_Sort::sapXepPhanCongTheoCa(dsPhanCong, true);
            cout << "\n✓ Da sap xep theo ca lam viec (A-Z)!\n";
            break;
            
        case 6:
            Utils_Sort::sapXepPhanCongTheoCa(dsPhanCong, false);
            cout << "\n✓ Da sap xep theo ca lam viec (Z-A)!\n";
            break;
            
        case 7:
            return;
            
        default:
            Utils::setColor(12);
            cout << "Lua chon khong hop le!\n";
            Utils::setColor(7);
            Utils::pause();
            return;
    }
    
    rebuildPhanCongMap();
    hienThiDanhSachPhanCongDaSapXep();
    ghiPhanCong();
    
    ghiLichSuHoatDong("SAP_XEP_PHAN_CONG", 
                      "Tieu chi: " + to_string(choice), 
                      "So luong: " + to_string(dsPhanCong.size()), 
                      "THANH_CONG");
}

void QuanLyPhanCong::hienThiDanhSachPhanCongDaSapXep() {
    system("cls");
    Utils::printHeader("DANH SACH PHAN CONG DA SAP XEP");
    
    cout << left 
        << setw(12) << "ID PC"
        << setw(10) << "ID TX"
        << setw(10) << "ID Xe"
        << setw(20) << "Ngay phan cong"
        << setw(15) << "Ca lam viec" << endl;
    cout << string(67, '-') << endl;
    
    for (const auto& pc : dsPhanCong) {
        cout << left 
            << setw(12) << pc. IDPC
            << setw(10) << pc.IDTX
            << setw(10) << pc.IDXe
            << setw(20) << pc.ngayPhanCong
            << setw(15) << pc.caLamViec << endl;
    }
    
    cout << "\nTong so phan cong: " << dsPhanCong. size() << endl;
    Utils::pause();
}