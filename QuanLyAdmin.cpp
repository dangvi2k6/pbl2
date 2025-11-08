#include "QuanLyAdmin.h"

QuanLyAdmin::QuanLyAdmin() {
    docAdmins();
}
QuanLyAdmin::~QuanLyAdmin() {}

void QuanLyAdmin::docAdmins() {
    ifstream file("admins.txt");
    if(!file.is_open()) {
        admins["admin"] = "admin123";
        ghiAdmins();
        return;
    }
    admins.clear();
    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string username, password;
        getline(ss, username, '|');
        getline(ss, password);
        if(!username.empty()) admins[username] = password;
    }
    file.close();
}

void QuanLyAdmin::ghiAdmins() {
    ofstream file("admins.txt");
    for (const auto& [user, pass] : admins) {
        file << user << "|" << pass << endl;
    }
    file.close();
}

void QuanLyAdmin::dangKyAdmin() {
    system("cls");
    Utils::printHeader("DANG KY TAI KHOAN ADMIN MOI");
    string username;
    cout << "Nhap ten dang nhap: ";
    cin >> username;
        
    if (admins.find(username) != admins.end()) {
        Utils::setColor(12);
        cout << "Ten dang nhap da ton tai!\n";
        Utils::setColor(7);
        Utils::pause();
        return;
    }
        
    cout << "Nhap mat khau: ";
    string password = Utils::nhapMatKhauAn();
        
    cout << "Xac nhan mat khau: ";
    string confirmPass = Utils::nhapMatKhauAn();
        
    if (password != confirmPass) {
        Utils::setColor(12);
        cout << "Mat khau xac nhan khong khop!\n";
        Utils::setColor(7);
        Utils::pause();
        return;
    }
        
    admins[username] = password;
    ghiAdmins();
    Utils::setColor(10);
    cout << "Dang ky tai khoan admin thanh cong!\n";
    Utils::setColor(7);
    Utils::pause();
}

bool QuanLyAdmin::dangNhap() {
    string username, password;
    int attempts = 3;
    
    while (attempts > 0) {
        system("cls");
        Utils::printHeader("DANG NHAP ADMIN");
        cout << "Nhap ten dang nhap: ";
        cin >> username;
        cout << "Nhap mat khau: ";
        password = Utils::nhapMatKhauAn();
        
        auto it = admins.find(username);
        if (it != admins.end() && it->second == password) {
            currentAdmin = username;
            Utils::setColor(10);
            cout << "Dang nhap thanh cong! Chao mung " << username << "!\n";
            Utils::setColor(7);
            Utils::pause();
            return true;
        } else {
            attempts--;
            Utils::setColor(12);
            cout << "Ten dang nhap hoac mat khau sai! Con " << attempts << " lan thu.\n";
            Utils::setColor(7);
            Utils::pause();
        }
    }
    
    Utils::setColor(12);
    cout << "Het luot dang nhap. Quay lai menu chinh.\n";
    Utils::setColor(7);
    Utils::pause();
    return false;
}

string QuanLyAdmin::getCurrentAdmin() const {
    return currentAdmin;
}

void QuanLyAdmin::resetCurrentAdmin() {
    currentAdmin = "";
}

void QuanLyAdmin::hienThiAdmin() {
    system("cls");
    Utils::printHeader("DANH SACH ADMIN");
    if (admins.empty()) {
        cout << "Chua co admin nao.\n";
    } else {
        int stt = 1;
        for (const auto& [username, password] : admins) {
            cout << stt++ << ". " << username << endl;
        }
    }
    Utils::pause();
}

void QuanLyAdmin::xoaAdmin() {
    system("cls");
    Utils::printHeader("XOA ADMIN");
    string username;
    cout << "Nhap ten admin can xoa: ";
    cin >> username;
    
    if (username == "admin") {
        Utils::setColor(12);
        cout << "Khong the xoa admin mac dinh!\n";
        Utils::setColor(7);
        Utils::pause();
        return;
    }
    
    if (admins.erase(username)) {
        ghiAdmins();
        Utils::setColor(10);
        cout << "Da xoa admin: " << username << endl;
        Utils::setColor(7);
    } else {
        Utils::setColor(12);
        cout << "Khong tim thay admin nay!\n";
        Utils::setColor(7);
    }
    Utils::pause();
}



