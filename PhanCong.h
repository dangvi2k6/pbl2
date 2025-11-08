#ifndef PHANCONG_H
#define PHANCONG_H

#include <string>
#include <fstream>
#include <stdexcept>
#include "TaiXe.h"
#include "TaXi.h"

using namespace std;

class PhanCong {
public:
    string IDPC;
    string IDTX;
    string IDXe;
    string StartTime;
    string EndTime;
    string Note;

public:
    PhanCong(const string&, const string&, const string&, 
             const string&, const string&, const string&);

    ~PhanCong();

    void saveToFile(const string&) const;
};

#endif