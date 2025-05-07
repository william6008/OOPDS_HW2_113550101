CXX = g++
CXXFLAGS = -std=c++17 -Wall
TARGET = main

SRCS = main.cpp \
       BookSystem.cpp \
       Library.cpp \
       InputSystem.cpp \
       UserSystem.cpp \
       Admin.cpp \
       Reader.cpp

OBJS = $(SRCS:.cpp=.o)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $<

clean:
	rm -f $(OBJS) $(TARGET)
