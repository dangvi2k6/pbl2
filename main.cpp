#include <iostream>
#include "Utils.h"
#include "QuanLyAdmin.h"
#include "QuanLyTaiXe.h"
#include "QuanLyTaXi.h"
#include "QuanLyChuyenXe.h"
#include "QuanLyPhanCong.h"
#include "QuanLyGanXe.h"
//g++ main.cpp QuanLyAdmin.cpp QuanLyTaiXe.cpp QuanLyTaXi.cpp QuanLyChuyenXe.cpp QuanLyPhanCong.cpp QuanLyGanXe.cpp Utils_Sort.cpp -o main.exe
using namespace std;

void drawBox(int left, int top, int width, int height) {
	int right = left + width + 1;
	int bottom = top + height + 1;

	Utils::setColor(4);

	Utils::gotoxy(left, top);
	cout<<"╔";

	Utils::gotoxy(right, top);
	cout<<"╗"; 

	Utils::gotoxy(left, bottom);
	cout<<"╚";

	Utils::gotoxy(right, bottom);
	cout<<"╝";

	for (int x = left + 1; x < right; x++) {
		Utils::gotoxy(x, top);
		cout<<"═";
		Utils::gotoxy(x, bottom);
		cout<<"═";
	}
	for (int y = top + 1; y < bottom; y++) {
		Utils::gotoxy(left, y);
		cout<<"║";
		Utils::gotoxy(right, y);
		cout<<"║";
	}
}

void info() {
    system("cls");
    drawBox(8,2,100,13);

	Utils::setColor(14);
	Utils::gotoxy(40, 4);
	cout<<"***PBL2: Dự án cơ sở lập trình***";

	Utils::gotoxy(28, 6);
	cout<<"Đề tài: Xây dựng xây dựng ứng dụng quản lý hệ thống taxi";

	Utils::gotoxy(17, 9);
	cout<<"-Sinh viên thực hiện:";

	Utils::gotoxy(77, 9);
	cout<<"-Giảng viên hướng dẫn:";

	Utils::gotoxy(19, 10);
	cout<<"Nguyễn Hoa Việt Xô";

	Utils::gotoxy(19, 11);
	cout<<"Đặng Lâm Chí Vĩ";

	Utils::gotoxy(17, 12);
	cout<<"-Lớp SH: 24T_KHDL";

	Utils::gotoxy(79, 10);
	cout<<"ThS. Trần Hồ Thủy Tiên";

}

// Forward declaration
void menuChinhSauDangNhap(QuanLyAdmin& qlAdmin, QuanLyTaiXe& qlTaiXe, QuanLyTaXi& qlTaxi,
                          QuanLyChuyenXe& qlChuyenXe, QuanLyPhanCong& qlPhanCong, QuanLyGanXe& qlGanXe);

void menuQuanLyAdmin(QuanLyAdmin& qlAdmin) {
    while (true) {
        int c = Utils::showMenu("QUAN LY ADMIN", {
            "1. Hien thi danh sach admin",
            "2. Dang ky admin moi",
            "3. Xoa admin",
            "4. Quay lai"
        });

        if (c == -1 || c == 3) break;

        if (c == 0) {
            qlAdmin.hienThiAdmin();
        }
        else if (c == 1) {
            qlAdmin.dangKyAdmin();
        }
        else if (c == 2) {
            qlAdmin.xoaAdmin();
        }
    }
}

void menuQuanLyTaiXe(QuanLyTaiXe& qlTaiXe) {
    while (true) {
        int c = Utils::showMenu("QUAN LY TAI XE", {
            "1. Them Tai Xe",
            "2. Sua Tai Xe",
            "3. Xoa Tai Xe",
            "4. Hien thi danh sach Tai Xe",
            "5. Tim Tai Xe",
            "6. Sap xep tai xe",
            "7. Quay lai"
        });

        if (c == -1 || c == 6) break;

        if (c == 0) qlTaiXe.themTaiXe();
        else if (c == 1) qlTaiXe.suaTaiXe();
        else if (c == 2) qlTaiXe.xoaTaiXe();
        else if (c == 3) qlTaiXe.hienThiTaiXe();
        else if (c == 4) qlTaiXe.timTaiXe();
        else if (c == 5) qlTaiXe.sapXepTaiXe(); 
    }
}

void menuQuanLyTaxi(QuanLyTaXi& qlTaxi) {
    while (true) {
        int c = Utils::showMenu("QUAN LY TAXI", {
            "1. Them Taxi",
            "2. Sua Taxi",
            "3. Xoa Taxi",
            "4. Hien thi danh sach Taxi",
            "5. Tim Taxi",
            "6. Xem chi tiet Taxi",
            "7. Sap xep Taxi",
            "8. Quay lai"
        });

        if (c == -1 || c == 7) break;

        if (c == 0) qlTaxi.themTaxi();
        else if (c == 1) qlTaxi.suaTaxi();
        else if (c == 2) qlTaxi.xoaTaxi();
        else if (c == 3) qlTaxi.hienThiTaxi();
        else if (c == 4) qlTaxi.timTaxi();
        else if (c == 5) qlTaxi.xemChiTietTaxi();
        else if (c == 6) qlTaxi.sapXepTaxi();
    }
}

void menuQuanLyChuyenXe(QuanLyChuyenXe& qlChuyenXe) {
    while (true) {
        int c = Utils::showMenu("QUAN LY CHUYEN XE", {
            "1. Them chuyen xe",
            "2. Sua chuyen xe",
            "3. Xoa chuyen xe",
            "4. Tim chuyen xe",
            "5. Hien thi danh sach chuyen xe",
            "6. Sap xep chuyen xe",
            "7. Quay lai"
        });

        if (c == -1 || c == 6) break;

        if (c == 0) qlChuyenXe.themChuyenXe();
        else if (c == 1) qlChuyenXe.suaChuyenXe();
        else if (c == 2) qlChuyenXe.xoaChuyenXe();
        else if (c == 3) qlChuyenXe.timChuyenXe();
        else if (c == 4) qlChuyenXe.hienThiChuyenXe();
        else if (c == 5) qlChuyenXe.sapXepChuyenXe();
    }

}

void menuQuanLyPhanCong(QuanLyPhanCong& qlPhanCong) {
    while (true) {
        int c = Utils::showMenu("QUAN LY PHAN CONG", {
            "1. Them phan cong",
            "2. Sua phan cong",
            "3. Xoa phan cong",
            "4. Hien thi danh sach phan cong",
            "5. Tim kiem phan cong",
            "6. Sap xep phan cong",
            "7. Quay lai"
        });

        if (c == -1 || c == 6) break;

        if (c == 0) qlPhanCong.themPhanCong();
        else if (c == 1) qlPhanCong.suaPhanCong();
        else if (c == 2) qlPhanCong.xoaPhanCong();
        else if (c == 3) qlPhanCong.hienThiPhanCong();
        else if (c == 4) qlPhanCong.timPhanCong();
        else if (c == 5) qlPhanCong.sapXepPhanCong();
    }
}

void menuGanHuyGan(QuanLyGanXe& qlGanXe, QuanLyTaXi& qlTaxi) {
    while (true) {
        int c = Utils::showMenu("GAN / HUY GAN TAI XE - XE", {
            "1. Gan tai xe cho xe",
            "2. Huy gan tai xe khoi xe",
            "3. Quay lai"
        });

        if (c == -1 || c == 2) break;

        if (c == 0) {
            qlGanXe.ganTaiXeChoXe();
            qlTaxi.ghiTaxi(); // Lưu thay đổi
        }
        else if (c == 1) {
            qlGanXe.huyGanTaiXeChoXe();
            qlTaxi.ghiTaxi(); // Lưu thay đổi
        }
    }
}

void menuTimKiem(QuanLyTaiXe& qlTaiXe, QuanLyTaXi& qlTaxi, QuanLyChuyenXe& qlChuyenXe, QuanLyPhanCong& qlPhanCong) {
    while (true) {
        int c = Utils::showMenu("TIM KIEM", {
            "1. Tim tai xe",
            "2. Tim taxi",
            "3. Tim chuyen xe",
            "4. Tim phan cong",
            "5. Quay lai"
        });

        if (c == -1 || c == 4) break;

        if (c == 0) qlTaiXe.timTaiXe();
        else if (c == 1) qlTaxi.timTaxi();
        else if (c == 2) qlChuyenXe.timChuyenXe();
        else if (c == 3) qlPhanCong.timPhanCong();
    }
}

void menuLogLichSu(QuanLyGanXe& qlGanXe) {
    while (true) {
        int c = Utils::showMenu("LOG & LICH SU", {
            "1. Xem log gan tai xe - xe",
            "2. Xem lich su chi tiet gan tai xe - xe",
            "3. Xem lich su tai xe",
            "4. Xem lich su taxi",
            "5. Xem lich su chuyen xe",
            "6. Xem lich su hoat dong tong quat",
            "7. Quay lai"
        });

        if (c == -1 || c == 6) break;

        if (c == 0) {
            qlGanXe.xemLog();
        }
        else if (c == 1) {
            qlGanXe.xemLichSuChiTiet();
        }
        else if (c == 2) {
            system("cls");
            Utils::printHeader("LICH SU TAI XE");
            ifstream f("taixe_history.log");
            if (!f.is_open()) {
                cout << "Khong tim thay file lich su.\n";
            } else {
                string line;
                while (getline(f, line)) cout << line << "\n";
                f.close();
            }
            Utils::pause();
        }
        else if (c == 3) {
            system("cls");
            Utils::printHeader("LICH SU TAXI");
            ifstream f("taxi_history.log");
            if (!f.is_open()) {
                cout << "Khong tim thay file lich su.\n";
            } else {
                string line;
                while (getline(f, line)) cout << line << "\n";
                f.close();
            }
            Utils::pause();
        }
        else if (c == 4) {
            system("cls");
            Utils::printHeader("LICH SU CHUYEN XE");
            ifstream f("chuyenxe_history.log");
            if (!f.is_open()) {
                cout << "Khong tim thay file lich su.\n";
            } else {
                string line;
                while (getline(f, line)) cout << line << "\n";
                f.close();
            }
            Utils::pause();
        }
        else if (c == 5) {
            system("cls");
            Utils::printHeader("LICH SU HOAT DONG TONG QUAT");
            ifstream f("activity_history.log");
            if (!f.is_open()) {
                cout << "Khong tim thay file lich su.\n";
            } else {
                string line;
                while (getline(f, line)) cout << line << "\n";
                f.close();
            }
            Utils::pause();
        }
    }
}

void menuChinhSauDangNhap(QuanLyAdmin& qlAdmin, QuanLyTaiXe& qlTaiXe, QuanLyTaXi& qlTaxi,
                          QuanLyChuyenXe& qlChuyenXe, QuanLyPhanCong& qlPhanCong, QuanLyGanXe& qlGanXe) {
    while (true) {
        int mainChoice = Utils::showMenu("MENU CHINH - QUAN LY TAXI", {
            "1. Quan ly Admin",
            "2. Quan ly Tai Xe",
            "3. Quan ly Taxi",
            "4. Quan ly Chuyen Xe",
            "5. Quan ly Phan Cong",
            "6. Gan/Huy gan Tai xe <-> Xe",
            "7. Tim kiem",
            "8. Xem log / lich su",
            "9. Dang xuat",
            "10. Thoat"
        });

        if (mainChoice == -1) continue;

        switch (mainChoice) {
            case 0:
                menuQuanLyAdmin(qlAdmin);
                break;
            case 1:
                menuQuanLyTaiXe(qlTaiXe);
                break;
            case 2:
                menuQuanLyTaxi(qlTaxi);
                break;
            case 3:
                menuQuanLyChuyenXe(qlChuyenXe);
                break;
            case 4:
                menuQuanLyPhanCong(qlPhanCong);
                break;

            case 5:
                menuGanHuyGan(qlGanXe, qlTaxi);
                break;
            case 6:
                menuTimKiem(qlTaiXe, qlTaxi, qlChuyenXe, qlPhanCong);
                break;
            case 7:
                menuLogLichSu(qlGanXe);
                break;
            case 8:
                Utils::setColor(11);
                cout << "Dang xuat tai admin: " << qlAdmin.getCurrentAdmin() << "\n";
                Utils::setColor(7);
                qlAdmin.resetCurrentAdmin();
                Utils::pause();
                return; 

            case 9:
                Utils::setColor(10);
                cout << "Cam on ban da su dung he thong! Hen gap lai.\n";
                Utils::setColor(7);
                Utils::pause();
                exit(0);
            default:
                break;
        }
    }
}

int main() {
    SetConsoleOutputCP(CP_UTF8);
	SetConsoleCP(CP_UTF8);
    // Khởi tạo QuanLyAdmin
    QuanLyAdmin qlAdmin;

    info();
    Utils::gotoxy(22, 17);
    Utils::pause();

    // Menu đăng nhập/đăng ký
    while (true) {      
        int choice = Utils::showMenu("HE THONG QUAN LY TAXI - ADMIN", {
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

        // choice == 0 -> Đăng nhập
        if (qlAdmin.dangNhap()) {
            // Đăng nhập thành công
            string currentAdmin = qlAdmin.getCurrentAdmin();

            // Khởi tạo các manager với admin hiện tại
            QuanLyTaiXe qlTaiXe(currentAdmin);
            QuanLyTaXi qlTaxi(currentAdmin);
            QuanLyChuyenXe qlChuyenXe(currentAdmin);
            QuanLyPhanCong qlPhanCong(currentAdmin);
            QuanLyGanXe qlGanXe(currentAdmin);

            // Liên kết các manager với nhau
            qlTaiXe.setDSTaxi(&qlTaxi.getDSTaxi());
            qlTaxi.setTaiXeByID(&qlTaiXe.getTaiXeByID());
            qlChuyenXe.setTaiXeByID(&qlTaiXe.getTaiXeByID());
            qlChuyenXe.setTaxiByID(&qlTaxi.getTaxiByID());
            qlPhanCong.setTaiXeByID(&qlTaiXe.getTaiXeByID());
            qlPhanCong.setTaxiByID(&qlTaxi.getTaxiByID());
            qlGanXe.setTaiXeByID(&qlTaiXe.getTaiXeByID());
            qlGanXe.setTaxiByID(&qlTaxi.getTaxiByID());
            qlGanXe.setDsTaxi(&qlTaxi.getDSTaxi());

            // Vào menu chính
            menuChinhSauDangNhap(qlAdmin, qlTaiXe, qlTaxi, qlChuyenXe, qlPhanCong, qlGanXe);
        }
    }

    return 0;
}

