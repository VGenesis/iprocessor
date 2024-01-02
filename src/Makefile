CXX=g++
CXXSTD=-std=c++17 -fpic
CXXFLAGS=-ldl -lSDL2

SRC=main.cpp
DST=build/main.o

CPP_CMDS=		$(wildcard ./cmds/src/*.cpp)
CPP_IMAGE=		$(wildcard ./image/src/*.cpp)
CPP_GLAD=		./glad/src/glad.c

HPP_INC_DS=		./ds/include
HPP_INC_CMDS=	./cmds/include
HPP_INC_IMAGE=	./image/include
HPP_INC_MISC=	./misc/include
HPP_INC_GLAD=	./glad/include

HPP_DS=			$(wildcard $(HPP_INC_DS)/*.hpp)
HPP_CMDS=		$(wildcard $(HPP_INC_CMDS)/*.hpp)
HPP_IMAGE=		$(wildcard $(HPP_INC_IMAGE)/*.hpp)
HPP_MISC=		$(wildcard $(HPP_INC_MISC)/*.hpp)
HPP_GLAD=		$(wildcard $(HPP_INC_GLAD)/*.hpp)

CPP_DEPS= 		$(CPP_CMDS) $(CPP_IMAGE) $(CPP_GLAD)
HPP_DEPS= 		$(HPP_DS) $(HPP_CMDS) $(HPP_IMAGE) $(HPP_MISC) $(HPP_GLAD)
HPP_INCS= 		-I$(HPP_INC_DS) -I$(HPP_INC_CMDS) -I$(HPP_INC_IMAGE) -I$(HPP_INC_MISC) -I$(HPP_INC_GLAD)

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
	$(CXX) $(CXXSTD) $(SRC) $(CPP_DEPS) -o $(DST) $(HPP_INCS) $(CXXFLAGS)

debug:	main.cpp $(CPP_DEPS)
	mkdir -p build
	$(CXX) $(CXXSTD) -g $(SRC) $(CPP_DEPS) -o $(DST) $(CXXFLAGS)
	gdb $(DST)
	make clean

clean:
	rm -rf build

imagetest.o: imagetest.cpp
	$(CXX) $(CXXSTD) imagetest.cpp glad/src/glad.c -o $(TEST) -I./glad/include $(CXXFLAGS) 
