#ifndef UTILS_SORT_H
#define UTILS_SORT_H

#include "TaiXe.h"
#include "TaXi.h"
#include "ChuyenXe.h"
#include "PhanCong.h"
#include "MyVector.h"

class Utils_Sort {
public:
    //quicksort cho tài xế
    static void sapXepTaiXeTheoID(MyVector<TaiXe>& arr, bool tangDan = true);
    static void sapXepTaiXeTheoTen(MyVector<TaiXe>& arr, bool tangDan = true);
    static void sapXepTaiXeTheoNgayGiaNhap(MyVector<TaiXe>& arr, bool tangDan = true);
    static void sapXepTaiXeTheoHangGPLX(MyVector<TaiXe>& arr, bool tangDan = true);
    static void sapXepTaiXeTheoTrangThai(MyVector<TaiXe>& arr, bool ranhTruoc = true); 
    //quicksort cho taxi
    static void sapXepTaxiTheoID(MyVector<TaXi>& arr, bool tangDan = true);
    static void sapXepTaxiTheoBienSo(MyVector<TaXi>& arr, bool tangDan = true);
    static void sapXepTaxiTheoHangXe(MyVector<TaXi>& arr, bool tangDan = true);
    static void sapXepTaxiTheoNamSX(MyVector<TaXi>& arr, bool tangDan = true);
    static void sapXepTaxiTheoSucChua(MyVector<TaXi>& arr, bool tangDan = true);
    static void sapXepTaxiTheoTrangThai(MyVector<TaXi>& arr, bool hoatDongTruoc = true);
    //quicksort cho chuyến xe
    static void sapXepChuyenXeTheoID(MyVector<ChuyenXe>& arr, bool tangDan = true);
    static void sapXepChuyenXeTheoThoiDiem(MyVector<ChuyenXe>& arr, bool tangDan = true);
    static void sapXepChuyenXeTheoKhoangCach(MyVector<ChuyenXe>& arr, bool tangDan = true);
    static void sapXepChuyenXeTheoCuocPhi(MyVector<ChuyenXe>& arr, bool tangDan = true);
    static void sapXepChuyenXeTheoThoiGian(MyVector<ChuyenXe>& arr, bool tangDan = true);
    static void sapXepChuyenXeTheoTenKhach(MyVector<ChuyenXe>& arr, bool tangDan = true);
    //quicksort cho phân công
    static void sapXepPhanCongTheoID(MyVector<PhanCong>& arr, bool tangDan = true);
    static void sapXepPhanCongTheoNgay(MyVector<PhanCong>& arr, bool tangDan = true);
    static void sapXepPhanCongTheoCa(MyVector<PhanCong>& arr, bool tangDan = true);
private:
    //ham partition 
    static int partitionTaiXe(MyVector<TaiXe>& arr, int low, int high, 
                              bool (*compare)(const TaiXe&, const TaiXe&));

    static int partitionTaxi(MyVector<TaXi>& arr, int low, int high,
                             bool (*compare)(const TaXi&, const TaXi&));
    
    static int partitionChuyenXe(MyVector<ChuyenXe>& arr, int low, int high,
                                 bool (*compare)(const ChuyenXe&, const ChuyenXe&));
    
    static int partitionPhanCong(MyVector<PhanCong>& arr, int low, int high,
                                 bool (*compare)(const PhanCong&, const PhanCong&));
    
    
    //ham quicksort
    static void quickSortTaiXe(MyVector<TaiXe>& arr, int low, int high,
                               bool (*compare)(const TaiXe&, const TaiXe&));
    
    static void quickSortTaxi(MyVector<TaXi>& arr, int low, int high,
                              bool (*compare)(const TaXi&, const TaXi&));
    
    static void quickSortChuyenXe(MyVector<ChuyenXe>& arr, int low, int high,
                                  bool (*compare)(const ChuyenXe&, const ChuyenXe&));
    
    static void quickSortPhanCong(MyVector<PhanCong>& arr, int low, int high,
                                  bool (*compare)(const PhanCong&, const PhanCong&));
    
    //ham swap
    template<typename T>
    static void swap(T& a, T& b);
};

// Template implementation phải ở header
template<typename T>
void Utils_Sort::swap(T& a, T& b) {
    T temp = a;
    a = b;
    b = temp;
}

#endif