# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -O2

# Target executable
TARGET = main. exe

# Source files
SRCS = main.cpp \
       QuanLyAdmin.cpp \
       QuanLyChuyenXe.cpp \
       QuanLyGanXe.cpp \
       QuanLyPhanCong.cpp \
       QuanLyTaXi.cpp \
       QuanLyTaiXe.cpp

# Header files (for dependencies)
HEADERS = ChuyenXe.h \
          MyVector.h \
          PhanCong.h \
          QuanLyAdmin.h \
          QuanLyChuyenXe.h \
          QuanLyGanXe. h \
          QuanLyPhanCong.h \
          QuanLyTaXi.h \
          QuanLyTaiXe.h \
          TaXi.h \
          TaiXe.h \
          Utils.h

# Object files
OBJS = $(SRCS:.cpp=.o)

# Default target
all: $(TARGET)

# Link object files to create executable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Compile source files to object files
%.o: %.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean build artifacts
clean:
	rm -f $(OBJS) $(TARGET)

# Rebuild everything
rebuild: clean all

# Run the program
run: $(TARGET)
	./$(TARGET)

. PHONY: all clean rebuild run
