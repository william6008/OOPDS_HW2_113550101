# 編譯器與參數
CXX = g++
CXXFLAGS = -std=c++17 -Wall -IClasses -IDataStructure -IUserSystem -IHelper

# 專案檔案清單
SRC_DIRS = Classes DataStructure UserSystem Helper
SRCS = $(wildcard main.cpp $(foreach dir, $(SRC_DIRS), $(dir)/*.cpp))
OBJS = $(SRCS:.cpp=.o)

# 最終執行檔
TARGET = library_app.exe

# 預設目標
all: $(TARGET)

# 連結所有 .o 檔成最終執行檔
$(TARGET): $(OBJS)
	$(CXX) $(OBJS) -o $@

# 編譯 .cpp 成 .o
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# 清除編譯產物
clean:
	rm -f $(OBJS) $(TARGET)
