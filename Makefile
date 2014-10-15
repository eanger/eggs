
SRCS= \
	  engine.cpp \
	  screen.cpp \
	  input.cpp \
	  entity.cpp \
	  world.cpp \
	  main.cpp

INC=
LDFLAGS=
LIBS=-lpanelw -lncursesw

TARGET=eggs

###########################################################
CXXFLAGS=-g -O0
CPPFLAGS=-Wall -Wextra -std=c++1y -Isrc $(INC)
LDLIBS=$(LIBS)

SRC=$(addprefix src/,$(SRCS))
OBJ=$(patsubst src/%.cpp,obj/%.o,$(SRC))

TAGS=src/tags

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(LDFLAGS) -o $@ $^ $(LDLIBS)

tags: $(TAGS)

$(TAGS): $(SRC)
	( cd src && ctags * && cd - )
	

.PHONY: clean
clean:
	rm -f $(OBJ) $(TARGET)
