CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -g -IClasses -IUserSystem
LDFLAGS =

SRC = \
    Classes/Book.cpp \
    Classes/BookCopy.cpp \
    Classes/InputSystem.cpp \
    Classes/Library.cpp \
    UserSystem/Admin.cpp \
    UserSystem/Reader.cpp \
    UserSystem/User.cpp \
    main.cpp

OBJ = $(SRC:.cpp=.o)

TARGET = library_app.exe

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) $(OBJ) -o $@ $(LDFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)
