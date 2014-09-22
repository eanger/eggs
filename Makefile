
SRCS= \
	  engine.cpp \
	  main.cpp

INC=-I/home/Eric/.local/include
LDFLAGS=-L/home/Eric/.local/lib
LIBS=-lSDL2

TARGET=game

###########################################################
CXX=g++
CXXFLAGS=-g -O0
CPPFLAGS=-Wall -Wextra -std=c++14 -Isrc $(INC)
LDLIBS=$(LIBS)

SRC=$(addprefix src/,$(SRCS))
OBJ=$(subst .cpp,.o,$(SRC))

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(LDFLAGS) -o $(TARGET) $(OBJ) $(LDLIBS)

.PHONY: clean
clean:
	rm -f $(OBJ) $(TARGET)
