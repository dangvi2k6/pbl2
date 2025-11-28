#include "Utils_Sort.h"

//Partition cho tai xe
int Utils_Sort::partitionTaiXe(MyVector<TaiXe>& arr, int low, int high,
                                bool (*compare)(const TaiXe&, const TaiXe&)){
    TaiXe pivot=arr[high];
    int i=low-1;
    
    for(int j=low; j<high; j++){
        if(compare(arr[j], pivot)){
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i+1], arr[high]);
    return i+1;
}

void Utils_Sort::quickSortTaiXe(MyVector<TaiXe>& arr, int low, int high, 
                                bool (*compare)(const TaiXe&, const TaiXe&)){
    if(low<high){
        int pi=partitionTaiXe(arr, low, high, compare);
        quickSortTaiXe(arr, low, pi-1, compare);
        quickSortTaiXe(arr, pi+1, high, compare);
    } 
}
//Cac ham sap xep tai xe
void Utils_Sort::sapXepTaiXeTheoID(MyVector<TaiXe>& arr, bool tangDan){
    if(arr.empty()) return;

    if (tangDan){
        quickSortTaiXe(arr, 0, arr.size()-1,
                        [](const TaiXe& a, const TaiXe& b) -> bool {
                            return a.IDTX<b.IDTX;
                        });
    }
    else{
        quickSortTaiXe(arr, 0, arr.size()-1,
                        [](const TaiXe& a, const TaiXe& b) -> bool {
                            return a.IDTX>b.IDTX;
                        });
    }
}

void Utils_Sort::sapXepTaiXeTheoTen(MyVector<TaiXe>& arr, bool tangDan) {
    if (arr.empty()) return;
    
    if (tangDan) {
        quickSortTaiXe(arr, 0, arr.size() - 1,
            [](const TaiXe& a, const TaiXe& b) -> bool {
                return a.tenTaiXe < b.tenTaiXe;
            });
    } else {
        quickSortTaiXe(arr, 0, arr.size() - 1,
            [](const TaiXe& a, const TaiXe& b) -> bool {
                return a.tenTaiXe > b.tenTaiXe;
            });
    }
}

void Utils_Sort::sapXepTaiXeTheoHangGPLX(MyVector<TaiXe>& arr, bool tangDan) {
    if (arr.empty()) return;
    
    if (tangDan) {
        quickSortTaiXe(arr, 0, arr.size() - 1,
            [](const TaiXe& a, const TaiXe& b) -> bool {
                return a.hangGPLX < b.hangGPLX;
            });
    } else {
        quickSortTaiXe(arr, 0, arr.size() - 1,
            [](const TaiXe& a, const TaiXe& b) -> bool {
                return a.hangGPLX > b.hangGPLX;
            });
    }
}

void Utils_Sort::sapXepTaiXeTheoTrangThai(MyVector<TaiXe>& arr, bool ranhTruoc) {
    if (arr.empty()) return;
    
    if (ranhTruoc) {
        quickSortTaiXe(arr, 0, arr.size() - 1,
            [](const TaiXe& a, const TaiXe& b) -> bool {
                return a.trangThaiTX > b.trangThaiTX; // true (Rảnh) trước false (Bận)
            });
    } else {
        quickSortTaiXe(arr, 0, arr.size() - 1,
            [](const TaiXe& a, const TaiXe& b) -> bool {
                return a. trangThaiTX < b.trangThaiTX;
            });
    }
}

//Partition cho taxi
int Utils_Sort::partitionTaxi(MyVector<TaXi>& arr, int low, int high,
                               bool (*compare)(const TaXi&, const TaXi&)) {
    TaXi pivot = arr[high];
    int i = low - 1;
    
    for (int j = low; j < high; j++) {
        if (compare(arr[j], pivot)) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return i + 1;
}

void Utils_Sort::quickSortTaxi(MyVector<TaXi>& arr, int low, int high,
                                bool (*compare)(const TaXi&, const TaXi&)) {
    if (low < high) {
        int pi = partitionTaxi(arr, low, high, compare);
        quickSortTaxi(arr, low, pi - 1, compare);
        quickSortTaxi(arr, pi + 1, high, compare);
    }
}
//Cac ham sap xep taxi
void Utils_Sort::sapXepTaxiTheoID(MyVector<TaXi>& arr, bool tangDan) {
    if (arr.empty()) return;
    
    if (tangDan) {
        quickSortTaxi(arr, 0, arr.size() - 1,
            [](const TaXi& a, const TaXi& b) -> bool {
                return a.IDXe < b.IDXe;
            });
    } else {
        quickSortTaxi(arr, 0, arr.size() - 1,
            [](const TaXi& a, const TaXi& b) -> bool {
                return a.IDXe > b.IDXe;
            });
    }
}

void Utils_Sort::sapXepTaxiTheoBienSo(MyVector<TaXi>& arr, bool tangDan) {
    if (arr.empty()) return;
    
    if (tangDan) {
        quickSortTaxi(arr, 0, arr.size() - 1,
            [](const TaXi& a, const TaXi& b) -> bool {
                return a.bienSo < b.bienSo;
            });
    } else {
        quickSortTaxi(arr, 0, arr.size() - 1,
            [](const TaXi& a, const TaXi& b) -> bool {
                return a.bienSo > b.bienSo;
            });
    }
}

void Utils_Sort::sapXepTaxiTheoHangXe(MyVector<TaXi>& arr, bool tangDan) {
    if (arr.empty()) return;
    
    if (tangDan) {
        quickSortTaxi(arr, 0, arr.size() - 1,
            [](const TaXi& a, const TaXi& b) -> bool {
                return a.hangXe < b.hangXe;
            });
    } else {
        quickSortTaxi(arr, 0, arr.size() - 1,
            [](const TaXi& a, const TaXi& b) -> bool {
                return a. hangXe > b.hangXe;
            });
    }
}

void Utils_Sort::sapXepTaxiTheoNamSX(MyVector<TaXi>& arr, bool tangDan) {
    if (arr.empty()) return;
    
    if (tangDan) {
        quickSortTaxi(arr, 0, arr.size() - 1,
            [](const TaXi& a, const TaXi& b) -> bool {
                return a.namSX < b.namSX;
            });
    } else {
        quickSortTaxi(arr, 0, arr.size() - 1,
            [](const TaXi& a, const TaXi& b) -> bool {
                return a.namSX > b.namSX;
            });
    }
}

void Utils_Sort::sapXepTaxiTheoSucChua(MyVector<TaXi>& arr, bool tangDan) {
    if (arr.empty()) return;
    
    if (tangDan) {
        quickSortTaxi(arr, 0, arr.size() - 1,
            [](const TaXi& a, const TaXi& b) -> bool {
                return a.sucChua < b.sucChua;
            });
    } else {
        quickSortTaxi(arr, 0, arr. size() - 1,
            [](const TaXi& a, const TaXi& b) -> bool {
                return a.sucChua > b. sucChua;
            });
    }
}

void Utils_Sort::sapXepTaxiTheoTrangThai(MyVector<TaXi>& arr, bool hoatDongTruoc) {
    if (arr.empty()) return;
    
    if (hoatDongTruoc) {
        quickSortTaxi(arr, 0, arr.size() - 1,
            [](const TaXi& a, const TaXi& b) -> bool {
                return a.trangThaiXe > b.trangThaiXe; // true (Hoạt động) trước false (Bảo trì)
            });
    } else {
        quickSortTaxi(arr, 0, arr.size() - 1,
            [](const TaXi& a, const TaXi& b) -> bool {
                return a.trangThaiXe < b.trangThaiXe;
            });
    }
}


//Partition cho chuyen xe

int Utils_Sort::partitionChuyenXe(MyVector<ChuyenXe>& arr, int low, int high,
                                   bool (*compare)(const ChuyenXe&, const ChuyenXe&)) {
    ChuyenXe pivot = arr[high];
    int i = low - 1;
    
    for (int j = low; j < high; j++) {
        if (compare(arr[j], pivot)) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return i + 1;
}

void Utils_Sort::quickSortChuyenXe(MyVector<ChuyenXe>& arr, int low, int high,
                                    bool (*compare)(const ChuyenXe&, const ChuyenXe&)) {
    if (low < high) {
        int pi = partitionChuyenXe(arr, low, high, compare);
        quickSortChuyenXe(arr, low, pi - 1, compare);
        quickSortChuyenXe(arr, pi + 1, high, compare);
    }
}

//Cac ham sap xep chuyen xe

void Utils_Sort::sapXepChuyenXeTheoID(MyVector<ChuyenXe>& arr, bool tangDan) {
    if (arr.empty()) return;
    
    if (tangDan) {
        quickSortChuyenXe(arr, 0, arr.size() - 1,
            [](const ChuyenXe& a, const ChuyenXe& b) -> bool {
                return a.IDChuyen < b.IDChuyen;
            });
    } else {
        quickSortChuyenXe(arr, 0, arr.size() - 1,
            [](const ChuyenXe& a, const ChuyenXe& b) -> bool {
                return a.IDChuyen > b.IDChuyen;
            });
    }
}

void Utils_Sort::sapXepChuyenXeTheoThoiDiem(MyVector<ChuyenXe>& arr, bool tangDan) {
    if (arr.empty()) return;
    
    if (tangDan) {
        quickSortChuyenXe(arr, 0, arr.size() - 1,
            [](const ChuyenXe& a, const ChuyenXe& b) -> bool {
                return a.thoiDiem < b.thoiDiem;
            });
    } else {
        quickSortChuyenXe(arr, 0, arr.size() - 1,
            [](const ChuyenXe& a, const ChuyenXe& b) -> bool {
                return a.thoiDiem > b.thoiDiem;
            });
    }
}

void Utils_Sort::sapXepChuyenXeTheoKhoangCach(MyVector<ChuyenXe>& arr, bool tangDan) {
    if (arr.empty()) return;
    
    if (tangDan) {
        quickSortChuyenXe(arr, 0, arr.size() - 1,
            [](const ChuyenXe& a, const ChuyenXe& b) -> bool {
                return a.khoangCach < b.khoangCach;
            });
    } else {
        quickSortChuyenXe(arr, 0, arr.size() - 1,
            [](const ChuyenXe& a, const ChuyenXe& b) -> bool {
                return a.khoangCach > b.khoangCach;
            });
    }
}

void Utils_Sort::sapXepChuyenXeTheoCuocPhi(MyVector<ChuyenXe>& arr, bool tangDan) {
    if (arr.empty()) return;
    
    if (tangDan) {
        quickSortChuyenXe(arr, 0, arr.size() - 1,
            [](const ChuyenXe& a, const ChuyenXe& b) -> bool {
                return a.cuocPhi < b.cuocPhi;
            });
    } else {
        quickSortChuyenXe(arr, 0, arr.size() - 1,
            [](const ChuyenXe& a, const ChuyenXe& b) -> bool {
                return a. cuocPhi > b.cuocPhi;
            });
    }
}

void Utils_Sort::sapXepChuyenXeTheoThoiGian(MyVector<ChuyenXe>& arr, bool tangDan) {
    if (arr.empty()) return;
    
    if (tangDan) {
        quickSortChuyenXe(arr, 0, arr.size() - 1,
            [](const ChuyenXe& a, const ChuyenXe& b) -> bool {
                return a.thoiGian < b.thoiGian;
            });
    } else {
        quickSortChuyenXe(arr, 0, arr.size() - 1,
            [](const ChuyenXe& a, const ChuyenXe& b) -> bool {
                return a.thoiGian > b.thoiGian;
            });
    }
}

void Utils_Sort::sapXepChuyenXeTheoTenKhach(MyVector<ChuyenXe>& arr, bool tangDan) {
    if (arr.empty()) return;
    
    if (tangDan) {
        quickSortChuyenXe(arr, 0, arr.size() - 1,
            [](const ChuyenXe& a, const ChuyenXe& b) -> bool {
                return a.tenKhach < b.tenKhach;
            });
    } else {
        quickSortChuyenXe(arr, 0, arr.size() - 1,
            [](const ChuyenXe& a, const ChuyenXe& b) -> bool {
                return a. tenKhach > b.tenKhach;
            });
    }
}


//Partition cho phan cong

int Utils_Sort::partitionPhanCong(MyVector<PhanCong>& arr, int low, int high,
                                   bool (*compare)(const PhanCong&, const PhanCong&)) {
    PhanCong pivot = arr[high];
    int i = low - 1;
    
    for (int j = low; j < high; j++) {
        if (compare(arr[j], pivot)) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return i + 1;
}

void Utils_Sort::quickSortPhanCong(MyVector<PhanCong>& arr, int low, int high,
                                    bool (*compare)(const PhanCong&, const PhanCong&)) {
    if (low < high) {
        int pi = partitionPhanCong(arr, low, high, compare);
        quickSortPhanCong(arr, low, pi - 1, compare);
        quickSortPhanCong(arr, pi + 1, high, compare);
    }
}

//Cac ham sap xep phan cong
void Utils_Sort::sapXepPhanCongTheoID(MyVector<PhanCong>& arr, bool tangDan) {
    if (arr.empty()) return;
    
    if (tangDan) {
        quickSortPhanCong(arr, 0, arr.size() - 1,
            [](const PhanCong& a, const PhanCong& b) -> bool {
                return a. IDPC < b.IDPC;
            });
    } else {
        quickSortPhanCong(arr, 0, arr. size() - 1,
            [](const PhanCong& a, const PhanCong& b) -> bool {
                return a.IDPC > b. IDPC;
            });
    }
}

void Utils_Sort::sapXepPhanCongTheoNgay(MyVector<PhanCong>& arr, bool tangDan) {
    if (arr.empty()) return;
    
    if (tangDan) {
        quickSortPhanCong(arr, 0, arr.size() - 1,
            [](const PhanCong& a, const PhanCong& b) -> bool {
                return a.ngayLamViec < b.ngayLamViec;
            });
    } else {
        quickSortPhanCong(arr, 0, arr.size() - 1,
            [](const PhanCong& a, const PhanCong& b) -> bool {
                return a.ngayLamViec > b.ngayLamViec;
            });
    }
}

void Utils_Sort::sapXepPhanCongTheoCa(MyVector<PhanCong>& arr, bool tangDan) {
    if (arr. empty()) return;
    
    if (tangDan) {
        quickSortPhanCong(arr, 0, arr. size() - 1,
            [](const PhanCong& a, const PhanCong& b) -> bool {
                return a.caLamViec < b.caLamViec;
            });
    } else {
        quickSortPhanCong(arr, 0, arr.size() - 1,
            [](const PhanCong& a, const PhanCong& b) -> bool {
                return a.caLamViec > b.caLamViec;
            });
    }
}