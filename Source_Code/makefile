# 編譯器與預設選項
CXX = g++

# 一般與 Debug 模式的 flags
CXXFLAGS = -std=c++17 -Wall -IClasses -IUserSystem
DEBUGFLAGS = -g

# 檔案列表
SRCS = main.cpp \
       Classes/Book.cpp \
       Classes/BookCopy.cpp \
       Classes/Library.cpp \
       UserSystem/User.cpp

OBJS = $(SRCS:.cpp=.o)

# 預設目標
TARGET = library_app

all: $(TARGET)

# Release 模式（無 -g）
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Debug 模式（使用 -g）
debug: CXXFLAGS += $(DEBUGFLAGS)
debug: clean $(TARGET)

# 清除所有中間檔
clean:
	rm -f $(OBJS) $(TARGET)
