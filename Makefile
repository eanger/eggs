
SRCS= \
	  engine.cpp \
	  main.cpp

INC=-I/home/Eric/.local/include
LDFLAGS=
LIBS=-L/home/Eric/.local/lib -lSDL2

TARGET=eggs

###########################################################
CXX=clang++
CXXFLAGS=-g -O0
CPPFLAGS=-Wall -Wextra -std=c++1y -Isrc $(INC)
LDLIBS=$(LIBS)

SRC=$(addprefix src/,$(SRCS))
OBJ=$(subst .cpp,.o,$(SRC))

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(LDFLAGS) -o $(TARGET) $(OBJ) $(LDLIBS)

.PHONY: clean
clean:
	rm -f $(OBJ) $(TARGET)
