#compiler Flags
cxx_flags = -Wall -std=c++17 

#includes
inc_enet = third_party/enet/include
includes = -I$(inc_enet)

#libraries
enet_path = third_party/enet/lib

lib_paths = -L$(enet_path)

lib_objs = -lenet

libs = $(lib_paths) $(lib_objs)

#control
src = $(wildcard src/*.cpp) #will need to += additional paths
src += $(wildcard src/network/*.cpp)
src += $(wildcard src/network-server/*.cpp)
src += $(wildcard src/network-client/*.cpp)
obj = $(src:.cpp=.o)





.PHONY = run all clean launch
run: all
all: clean build launch



build: $(obj) 
	clang++ -o ./game build/*.o $(libs)

%.o: %.cpp
	clang++ -o build/$(notdir $@) -c $< $(cxx_flags) $(includes)

clean: 
	mkdir -p build && rm -f build/*.o && rm -f ./game

launch:
	./game