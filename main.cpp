#include <iostream>
#include "../include/utils/Utils.h"
#include "../include/managers/QuanLyAdmin.h"
#include "../include/managers/QuanLyTaiXe.h"
// Include các manager khác tương tự

using namespace std;

int main() {
    QuanLyAdmin qlAdmin;
    QuanLyTaiXe qlTaiXe(&qlAdmin);
    // Khởi tạo các manager khác
    
    // Menu chính
    while (true) {
        int choice = Utils::showMenu("HE THONG QUAN LY TAXI", {
            "1. Dang nhap",
            "2. Dang ky admin moi",
            "3. Thoat"
        });
        
        if (choice == -1 || choice == 2) {
            Utils::setColor(10);
            cout << "Cam on ban da su dung he thong!\n";
            Utils::setColor(7);
            return 0;
        }
        
        if (choice == 1) {
            qlAdmin.dangKyAdmin();
            continue;
        }
        
        if (qlAdmin.dangNhap()) {
            // Menu chính sau khi đăng nhập
            while (true) {
                int mainChoice = Utils::showMenu("MENU CHINH", {
                    "1. Quan ly Tai Xe",
                    "2. Quan ly Taxi",
                    "3. Quan ly Chuyen Xe",
                    "4. Dang xuat",
                    "5. Thoat"
                });
                
                if (mainChoice == 0) {
                    qlTaiXe.themTaiXe();
                }
                // Xử lý các lựa chọn khác...
                
                if (mainChoice == 3) {
                    qlAdmin.resetCurrentAdmin();
                    break;
                }
                
                if (mainChoice == 4) {
                    return 0;
                }
            }
        }
    }
    
    return 0;
}