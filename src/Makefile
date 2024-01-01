CC=g++
CSTD=-std=c++11
CFLAGS=-ldl -lSDL2

SRC=main.cpp
DST=build/main.o

CPP_CMDS=$(wildcard ./cmds/src/*.cpp)
CPP_IMAGE=$(wildcard ./image/src/*.cpp)
CPP_DEPS = $(CPP_CMDS) $(CPP_IMAGE)

HPP_DS=		$(wildcard ./ds/include/*.hpp)
HPP_CMDS=	$(wildcard ./cmds/include/*.hpp)
HPP_IMAGE=	$(wildcard ./image/include/*.hpp)
HPP_MISC=	$(wildcard ./misc/include/*.hpp)
HPP_DEPS= 	$(HPP_DS) $(HPP_CMDS) $(HPP_IMAGE) $(HPP_MISC)

HPP_DEPS_INC= 	-I$(HPP_DS) -I$(HPP_CMDS) -I$(HPP_IMAGE) -I$(HPP_MISC)

TEST = imagetest.o

all:
	make build
	make run
	make clean

show:
	@echo $(CPP_DEPS)
	@echo $(HPP_DEPS)

build: $(DST)

run: 
	./$(DST)

test: $(TEST)

$(DST): main.cpp $(CPP_DEPS) $(HPP_DEPS)
	mkdir -p build
	$(CC) $(CSTD) $(SRC) $(CPP_DEPS) -o $(DST) $(CFLAGS)

debug:	main.cpp $(CPP_DEPS)
	mkdir -p build
	$(CC) $(CSTD) -g $(SRC) $(CPP_DEPS) -o $(DST) $(CFLAGS)
	gdb $(DST)
	make clean

clean:
	rm -rf build

imagetest.o: imagetest.cpp
	$(CC) $(CSTD) imagetest.cpp -o $(TEST) $(CFLAGS)
