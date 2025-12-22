# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++11 -Wall -Iinclude

# Directories
SRC_DIR = src
INC_DIR = include
BUILD_DIR = build

# Target executable
TARGET = $(BUILD_DIR)/main.exe

# Object files (đặt trong thư mục build)
OBJS = $(BUILD_DIR)/main.o \
       $(BUILD_DIR)/QuanLyAdmin.o \
       $(BUILD_DIR)/QuanLyTaiXe.o \
       $(BUILD_DIR)/QuanLyTaXi.o \
       $(BUILD_DIR)/QuanLyChuyenXe.o \
       $(BUILD_DIR)/QuanLyPhanCong.o \
       $(BUILD_DIR)/QuanLyGanXe.o \
       $(BUILD_DIR)/Utils_Sort.o

# Default target
all: $(BUILD_DIR) $(TARGET)

# Tạo thư mục build nếu chưa có
$(BUILD_DIR):
	@if not exist "$(BUILD_DIR)" mkdir $(BUILD_DIR)

# Link object files to create executable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)
	@echo Build successful!  Executable: $(TARGET)

# Compile main.cpp
$(BUILD_DIR)/main.o: $(SRC_DIR)/main.cpp $(INC_DIR)/QuanLyAdmin.h $(INC_DIR)/QuanLyTaiXe.h $(INC_DIR)/QuanLyTaXi.h $(INC_DIR)/QuanLyChuyenXe.h $(INC_DIR)/QuanLyPhanCong.h $(INC_DIR)/QuanLyGanXe.h $(INC_DIR)/Utils.h
	$(CXX) $(CXXFLAGS) -c $(SRC_DIR)/main.cpp -o $(BUILD_DIR)/main.o

# Compile QuanLyAdmin.cpp
$(BUILD_DIR)/QuanLyAdmin.o: $(SRC_DIR)/QuanLyAdmin.cpp $(INC_DIR)/QuanLyAdmin.h $(INC_DIR)/Utils.h
	$(CXX) $(CXXFLAGS) -c $(SRC_DIR)/QuanLyAdmin.cpp -o $(BUILD_DIR)/QuanLyAdmin.o

# Compile QuanLyTaiXe.cpp
$(BUILD_DIR)/QuanLyTaiXe.o: $(SRC_DIR)/QuanLyTaiXe.cpp $(INC_DIR)/QuanLyTaiXe.h $(INC_DIR)/TaiXe.h $(INC_DIR)/TaXi.h $(INC_DIR)/MyVector.h $(INC_DIR)/Utils.h $(INC_DIR)/Utils_Sort.h
	$(CXX) $(CXXFLAGS) -c $(SRC_DIR)/QuanLyTaiXe.cpp -o $(BUILD_DIR)/QuanLyTaiXe.o

# Compile QuanLyTaXi.cpp
$(BUILD_DIR)/QuanLyTaXi.o: $(SRC_DIR)/QuanLyTaXi.cpp $(INC_DIR)/QuanLyTaXi.h $(INC_DIR)/TaXi.h $(INC_DIR)/TaiXe.h $(INC_DIR)/MyVector.h $(INC_DIR)/Utils.h $(INC_DIR)/Utils_Sort.h
	$(CXX) $(CXXFLAGS) -c $(SRC_DIR)/QuanLyTaXi.cpp -o $(BUILD_DIR)/QuanLyTaXi.o

# Compile QuanLyChuyenXe.cpp
$(BUILD_DIR)/QuanLyChuyenXe.o: $(SRC_DIR)/QuanLyChuyenXe.cpp $(INC_DIR)/QuanLyChuyenXe.h $(INC_DIR)/ChuyenXe.h $(INC_DIR)/TaiXe.h $(INC_DIR)/TaXi.h $(INC_DIR)/MyVector.h $(INC_DIR)/Utils.h $(INC_DIR)/Utils_Sort.h
	$(CXX) $(CXXFLAGS) -c $(SRC_DIR)/QuanLyChuyenXe.cpp -o $(BUILD_DIR)/QuanLyChuyenXe.o

# Compile QuanLyPhanCong.cpp
$(BUILD_DIR)/QuanLyPhanCong.o: $(SRC_DIR)/QuanLyPhanCong.cpp $(INC_DIR)/QuanLyPhanCong.h $(INC_DIR)/PhanCong.h $(INC_DIR)/TaiXe.h $(INC_DIR)/TaXi.h $(INC_DIR)/MyVector.h $(INC_DIR)/Utils.h $(INC_DIR)/Utils_Sort.h
	$(CXX) $(CXXFLAGS) -c $(SRC_DIR)/QuanLyPhanCong.cpp -o $(BUILD_DIR)/QuanLyPhanCong.o

# Compile QuanLyGanXe.cpp
$(BUILD_DIR)/QuanLyGanXe.o: $(SRC_DIR)/QuanLyGanXe.cpp $(INC_DIR)/QuanLyGanXe.h $(INC_DIR)/TaiXe.h $(INC_DIR)/TaXi.h $(INC_DIR)/MyVector.h $(INC_DIR)/Utils.h
	$(CXX) $(CXXFLAGS) -c $(SRC_DIR)/QuanLyGanXe.cpp -o $(BUILD_DIR)/QuanLyGanXe.o

# Compile Utils_Sort.cpp
$(BUILD_DIR)/Utils_Sort.o: $(SRC_DIR)/Utils_Sort.cpp $(INC_DIR)/Utils_Sort.h $(INC_DIR)/TaiXe.h $(INC_DIR)/TaXi.h $(INC_DIR)/ChuyenXe.h $(INC_DIR)/PhanCong.h $(INC_DIR)/MyVector.h
	$(CXX) $(CXXFLAGS) -c $(SRC_DIR)/Utils_Sort.cpp -o $(BUILD_DIR)/Utils_Sort.o

# Run the program
run: $(TARGET)
	cd $(BUILD_DIR) && main.exe

# Clean build files
clean:
	@if exist "$(BUILD_DIR)\*.o" del /Q $(BUILD_DIR)\*.o
	@if exist "$(TARGET)" del /Q $(TARGET)
	@echo Cleaned build files

# Clean all (including build directory)
cleanall: clean
	@if exist "$(BUILD_DIR)" rmdir /S /Q $(BUILD_DIR)
	@echo Removed build directory

# Rebuild
rebuild: clean all

. PHONY: all clean cleanall rebuild run