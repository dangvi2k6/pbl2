#include "QuanLyGanXe.h"

QuanLyGanXe::QuanLyGanXe(const string& admin,
            unordered_map<string, TaiXe*>* taiXeByID,
            unordered_map<string, TaXi*>* taxiByID,
            MyVector<TaXi>* dsTaxi)
    : currentAdmin(admin), pTaiXeByID(taiXeByID), pTaxiByID(taxiByID), pDsTaxi(dsTaxi) {}

QuanLyGanXe::~QuanLyGanXe() {}

string QuanLyGanXe::taoMaGhiNhan() {
    static int counter = 0;
    counter++;
    time_t now = time(0);
    tm* ltm = localtime(&now);
    char buffer[50];
    sprintf(buffer, "GAN%04d%02d%02d_%04d",
            1900 + ltm->tm_year,
            1 + ltm->tm_mon,
            ltm->tm_mday,
            counter);
    return string(buffer);
}

void QuanLyGanXe::ghiLog(const string& thaoTac, const string& noiDung) {
    ofstream file("data/gan_taixe_xe.log", ios::app);
    if (!file.is_open()) return;
    file << "[" << Utils::layThoiGianHienTai() << "] "
            << "[" << currentAdmin << "] "
            << thaoTac << ": " << noiDung << endl;
    file.close();
}

void QuanLyGanXe::ghiLichSuChiTiet(const string& maGhiNhan, const string& loaiThaoTac,
                        const string& idTaiXe, const string& hoDemTX, const string& tenTX, const string& gplxTaiXe,
                        const string& idXe, const string& bienSo, const string& loaiXe, int sucChua,
                        const string& trangThai, const string& ghiChu) {
    ofstream file("data/gan_taixe_xe_history.txt", ios::app);
    if (!file.is_open()) return;
    file << "=== Lich su gan tai xe cho xe ===\n";
    file << "Ma ghi nhan: " << maGhiNhan << "\n";
    file << "Thoi gian: " << Utils::layThoiGianHienTai() << "\n";
    file << "Nguoi thuc hien: " << currentAdmin << "\n";
    file << "Loai thao tac: " << loaiThaoTac << "\n";
    file << "Tai xe: " << idTaiXe << " - " << hoDemTX << tenTX << " (GPLX: " << gplxTaiXe << ")\n";
    file << "Xe: " << idXe << " - " << bienSo << " (" << loaiXe << ", " << sucChua << " cho)\n";
    file << "Trang thai: " << trangThai << "\n";
    if (!ghiChu.empty()) {
        file << "Ghi chu: " << ghiChu << "\n";
    }
    file << string(60, '-') << "\n\n";
    
    file.close();
}

void QuanLyGanXe::setCurrentAdmin(const string& admin) {
    currentAdmin = admin;
}

void QuanLyGanXe::setTaiXeByID(unordered_map<string, TaiXe*>* taiXeByID) {
    pTaiXeByID = taiXeByID;
}

void QuanLyGanXe::setTaxiByID(unordered_map<string, TaXi*>* taxiByID) {
    pTaxiByID = taxiByID;
}

void QuanLyGanXe::setDsTaxi(MyVector<TaXi>* dsTaxi) {
    pDsTaxi = dsTaxi;
}

void QuanLyGanXe::ganTaiXeChoXe() {
    system("cls");
    Utils::printHeader("GAN TAI XE CHO XE (THIET LAP QUYEN)");
    cout<<"(ESC de quay lai)"<<endl;
    string idXe, idTX;
    if(! Utils::getInputWithESC(idXe, "Nhap ID xe can gan tai xe (VD: XE001, XE012,...): ")) {
        return;
    }

    if (!pTaxiByID) {
        Utils::setColor(12);
        cout << "Loi: He thong chua khoi tao!\n";
        Utils::setColor(7);
        Utils::pause();
        return;
    }

    auto itXe = pTaxiByID->find(idXe);
    if (itXe == pTaxiByID->end()) {
        Utils::setColor(12);
        cout << "Xe khong ton tai!\n";
        Utils::setColor(7);
        Utils::pause();
        return;
    }

    TaXi* xe = itXe->second;
    cout << "\n=== THONG TIN XE ===\n";
    cout << "Bien so: " << xe->bienSo << endl;
    cout << "Hang xe: " << xe->hangXe << " " << xe->mauXe << endl;
    cout << "Suc chua: " << xe->sucChua << " cho\n";
    cout << "Nam SX: " << xe->namSX << endl;

    cout << "\nDanh sach tai xe da duoc gan:\n";
    if (xe->dsTaiXe.empty()) {
        cout << "  (Chua co tai xe nao)\n";
    } else {
        int stt = 1;
        for (const auto& id : xe->dsTaiXe) {
            if (pTaiXeByID) {
                auto it = pTaiXeByID->find(id);
                if (it != pTaiXeByID->end()) {
                    cout << "  " << stt++ << ". " << it->second->hoDemTX << it->second->tenTX 
                            << " (" << id << ") - GPLX: " << it->second->hangGPLX << endl;
                }
            }
        }
    }

    if(! Utils::getInputWithESC(idTX, "\nNhap ID tai xe can gan cho xe (VD: TX001, TX012): ")) {
        return;
    }

    if (!pTaiXeByID) {
        Utils::setColor(12);
        cout << "Loi: He thong chua khoi tao!\n";
        Utils::setColor(7);
        Utils::pause();
        return;
    }

    auto itTX = pTaiXeByID->find(idTX);
    if (itTX == pTaiXeByID->end()) {
        Utils::setColor(12);
        cout << "Tai xe khong ton tai!\n";
        Utils::setColor(7);
        ghiLog("GAN_THAT_BAI", "Tai xe " + idTX + " khong ton tai -> Xe " + idXe);
        Utils::pause();
        return;
    }
    TaiXe* tx = itTX->second;

    auto& ds = xe->dsTaiXe;
    if (find(ds.begin(), ds.end(), idTX) != ds.end()) {
        Utils::setColor(12);
        cout << "Tai xe da duoc gan cho xe nay!\n";
        Utils::setColor(7);
        ghiLog("GAN_THAT_BAI", "Tai xe " + idTX + " (" + tx->hoDemTX + tx->tenTX + ") da duoc gan cho xe " + idXe);
        Utils::pause();
        return;
    }

    // Kiểm tra GPLX phù hợp
    bool gplxPhuHop = false;
    if (xe->sucChua <= 4) {
        gplxPhuHop = (tx->hangGPLX == "B2" || tx->hangGPLX == "C" || tx->hangGPLX == "D" || tx->hangGPLX == "E");
    } else if (xe->sucChua <= 9) {
        gplxPhuHop = (tx->hangGPLX == "C" || tx->hangGPLX == "D" || tx->hangGPLX == "E");
    } else {
        gplxPhuHop = (tx->hangGPLX == "D" || tx->hangGPLX == "E");
    }

    if (!gplxPhuHop) {
        Utils::setColor(12);
        cout << "CANH BAO: GPLX cua tai xe (" << tx->hangGPLX 
                << ") khong phu hop voi loai xe nay!\n";
        Utils::setColor(7);
        cout << "Ban co muon tiep tuc gan khong? (Y/N): ";
        char c = _getch();
        cout << c << "\n";
        if (c != 'Y' && c != 'y') {
            ghiLog("GAN_HUY", "Huy gan: GPLX khong phu hop -> Tai xe " + idTX + " | Xe " + idXe);
            Utils::pause();
            return;
        }
    }

    // Thực hiện gắn
    xe->dsTaiXe.push_back(idTX);

    // Ghi lịch sử chi tiết và log
    string ma = taoMaGhiNhan();
    ghiLichSuChiTiet(ma, "GAN", idTX, tx->hoDemTX, tx->tenTX, tx->hangGPLX, xe->IDXe, xe->bienSo, xe->hangXe, xe->sucChua, "Da gan tai xe cho xe");
    ghiLog("GAN_THANH_CONG", "Da gan tai xe " + idTX + " (" + tx->hoDemTX + tx->tenTX + ") cho xe " + idXe);

    Utils::setColor(10);
    cout << "Gan tai xe thanh cong!\n";
    Utils::setColor(7);
    Utils::pause();
}

void QuanLyGanXe::huyGanTaiXeChoXe() {
    system("cls");
    Utils::printHeader("HUY GAN TAI XE CHO XE");
    cout<<"(ESC de quay lai)"<<endl;
    
    string idXe;
    if(! Utils::getInputWithESC(idXe, "Nhap ID xe can huy gan tai xe (VD: XE001, XE012,...): ")) {
        return;
    }

    if (!pTaxiByID) {
        Utils::setColor(12);
        cout << "Loi: He thong chua khoi tao!\n";
        Utils::setColor(7);
        Utils::pause();
        return;
    }

    auto itXe = pTaxiByID->find(idXe);
    if (itXe == pTaxiByID->end()) {
        Utils::setColor(12); 
        cout << "Xe khong ton tai!\n"; 
        Utils::setColor(7); 
        Utils::pause(); 
        return;
    }
    
    TaXi* xe = itXe->second;
    if (xe->dsTaiXe.empty()) {
        cout << "Xe chua co tai xe nao duoc gan.\n"; 
        Utils::pause(); 
        return;
    }

    cout << "Danh sach tai xe dang gan cho xe " << idXe << ":\n";
    for (size_t i = 0; i < xe->dsTaiXe.size(); ++i) {
        if (pTaiXeByID) {
            auto it = pTaiXeByID->find(xe->dsTaiXe[i]);
            if (it != pTaiXeByID->end()) {
                cout << i+1 << ". " << it->second->hoDemTX << it->second->tenTX<< " (" << xe->dsTaiXe[i] << ")\n";
            } else {
                cout << i+1 << ". " << xe->dsTaiXe[i] << "\n";
            }
        } else {
            cout << i+1 << ". " << xe->dsTaiXe[i] << "\n";
        }
    }
    
    int stt;
    string sttStr; 
    if(! Utils::getInputWithESC(sttStr, "Nhap STT tai xe muon huy gan: ")) {
        return;
    }
    stt= stoi(sttStr);
    
    if (stt < 1 || stt > (int)xe->dsTaiXe.size()) {
        Utils::setColor(12); 
        cout << "STT khong hop le!\n"; 
        Utils::setColor(7); 
        Utils::pause(); 
        return;
    }
    
    string idTX = xe->dsTaiXe[stt-1];
    string hd = "";
    string ten = "Unknown";
    string gplx = "";
    
    if (pTaiXeByID) {
        auto itTX = pTaiXeByID->find(idTX);
        if (itTX != pTaiXeByID->end()) {
            hd = itTX->second->hoDemTX;
            ten = itTX->second->tenTX;
            gplx = itTX->second->hangGPLX;
        }
    }

    xe->dsTaiXe.erase(xe->dsTaiXe.begin() + (stt-1));

    string ma = taoMaGhiNhan();
    ghiLichSuChiTiet(ma, "HUY_GAN", idTX, hd, ten, gplx, xe->IDXe, xe->bienSo, xe->hangXe, xe->sucChua, "Da huy gan tai xe");
    ghiLog("HUY_GAN", "Da huy gan tai xe " + idTX + " (" + hd + ten + ") khoi xe " + idXe);

    Utils::setColor(10); 
    cout << "Huy gan thanh cong!\n"; 
    Utils::setColor(7); 
    Utils::pause();
}

void QuanLyGanXe::xemLog() {
    system("cls");
    Utils::printHeader("XEM LOG GAN TAI XE - XE");
    ifstream file("data/gan_taixe_xe.log");
    if (!file.is_open()) {
        cout << "Khong tim thay file log.\n"; 
        Utils::pause(); 
        return;
    }
    string line;
    while (getline(file, line)) {
        cout << line << "\n";
    }
    file.close();
    Utils::pause();
}

void QuanLyGanXe::xemLichSuChiTiet() {
    system("cls");
    Utils::printHeader("LICH SU CHI TIET GAN TAI XE - XE");
    ifstream file("data/gan_taixe_xe_history.txt");
    if (!file.is_open()) {
        cout << "Khong tim thay file lich su.\n";
        Utils::pause();
        return;
    }
    string line;
    while (getline(file, line)) {
        cout << line << "\n";
    }
    file.close();
    Utils::pause();
}