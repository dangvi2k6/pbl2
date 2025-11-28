```makefile
# Compiler
CXX = g++
CXXFLAGS = -std=c++11 -Wall

# Target executable
TARGET = main. exe

# Object files
OBJS = main. o \
       QuanLyAdmin.o \
       QuanLyTaiXe.o \
       QuanLyTaXi.o \
       QuanLyChuyenXe.o \
       QuanLyPhanCong.o \
       QuanLyGanXe.o \
       Utils_Sort.o

# Default target
all: $(TARGET)

# Link object files to create executable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

# Compile main.cpp
main.o: main.cpp QuanLyAdmin.h QuanLyTaiXe.h QuanLyTaXi.h QuanLyChuyenXe.h QuanLyPhanCong.h QuanLyGanXe. h Utils. h
	$(CXX) $(CXXFLAGS) -c main.cpp

# Compile QuanLyAdmin.cpp
QuanLyAdmin.o: QuanLyAdmin.cpp QuanLyAdmin.h Utils.h
	$(CXX) $(CXXFLAGS) -c QuanLyAdmin. cpp

# Compile QuanLyTaiXe.cpp
QuanLyTaiXe.o: QuanLyTaiXe.cpp QuanLyTaiXe.h TaiXe.h TaXi.h MyVector.h Utils.h Utils_Sort.h
	$(CXX) $(CXXFLAGS) -c QuanLyTaiXe.cpp

# Compile QuanLyTaXi.cpp
QuanLyTaXi.o: QuanLyTaXi.cpp QuanLyTaXi.h TaXi.h TaiXe.h MyVector. h Utils.h Utils_Sort. h
	$(CXX) $(CXXFLAGS) -c QuanLyTaXi.cpp

# Compile QuanLyChuyenXe.cpp
QuanLyChuyenXe.o: QuanLyChuyenXe.cpp QuanLyChuyenXe.h ChuyenXe.h TaiXe.h TaXi.h MyVector.h Utils. h Utils_Sort.h
	$(CXX) $(CXXFLAGS) -c QuanLyChuyenXe. cpp

# Compile QuanLyPhanCong.cpp
QuanLyPhanCong.o: QuanLyPhanCong.cpp QuanLyPhanCong.h PhanCong.h TaiXe.h TaXi. h MyVector.h Utils.h Utils_Sort.h
	$(CXX) $(CXXFLAGS) -c QuanLyPhanCong.cpp

# Compile QuanLyGanXe.cpp
QuanLyGanXe.o: QuanLyGanXe.cpp QuanLyGanXe.h TaiXe.h TaXi.h MyVector.h Utils.h
	$(CXX) $(CXXFLAGS) -c QuanLyGanXe. cpp

# Compile Utils_Sort.cpp
Utils_Sort. o: Utils_Sort.cpp Utils_Sort.h TaiXe.h TaXi.h ChuyenXe.h PhanCong.h MyVector.h
	$(CXX) $(CXXFLAGS) -c Utils_Sort.cpp

# Clean build files
clean:
	del /Q *.o $(TARGET)

# Rebuild
rebuild: clean all

. PHONY: all clean rebuild
```