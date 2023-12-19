CC=g++
CSTD=-std=c++11
CFLAGS=-ldl -lSDL2

SRC=main.cpp
DST=build/main.o

HPP_DEPS = $(wildcard "./**/*.hpp")
CPP_DEPS = $(wildcard "./**/*.cpp")

all:
	make build
	make run
	make clean

build: $(DST)

run: 
	./$(DST)

$(DST): main.cpp $(CPP_DEPS) $(HPP_DEPS)
	mkdir -p build
	$(CC) $(CSTD) $(SRC) $(CPP_DEPS) -o $(DST) $(CFLAGS)

debug:	main.cpp $(CPP_DEPS) $(HPP_DEPS)
	mkdir -p buildj
	$(CC) $(CSTD) -g $(SRC) $(CPP_DEPS) -o $(DST) $(CFLAGS)
	gdb $(DST)
	make clean

clean:
	rm -rf build
