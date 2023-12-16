CC=g++
CSTD=-std=c++11
CFLAGS=-ldl -lSDL2

SRC=main.cpp
DST=build/main.o

CPP_DEP_EFFECT =	effect.hpp
CPP_DEP_PLOT =		plot.hpp
CPP_DEP_LIST =		list.hpp
CPP_DEPS =	$(CPP_DEP_EFFECT) $(CPP_DEP_PLOT) $(CPP_DEP_LIST)

all:
	make build
	make run
	make clean

build: $(DST)

run: 
	./$(DST)

$(DST): main.cpp $(CPP_DEPS)
	mkdir -p build
	$(CC) $(CSTD) $(SRC) -o $(DST) $(CFLAGS)

debug:	main.cpp $(CPP_DEPS)
	mkdir -p build
	$(CC) $(CSTD) -g $(SRC) -o $(DST) $(CFLAGS)
	gdb $(DST)
	make clean

clean:
	rm -rf build
