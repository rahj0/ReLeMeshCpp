CFLAGS = -Wall -pedantic -std=c++17
CC = g++
SRCDIR := src
BUILDDIR := build
INC := -I include
SRCEXT := cc
LIB := -L lib/*

SOURCES := $(shell find $(SRCDIR) -type f -name *.$(SRCEXT))

all: unitTester



unitTester: src/unitTester.cpp
	# Commands start with TAB not spaces
	$(CC) $(LDFLAGS) src/gameObjects/AbstractObject.cpp -c -o lib/AbstractObject.o $(INC)
	$(CC) $(LDFLAGS) src/gameObjects/LineObject.cpp -c -o lib/LineObject.o $(INC)
	$(CC) $(LDFLAGS) src/gameObjects/TriangleObject.cpp -c -o lib/TriangleObject.o $(INC)
	$(CC) $(LDFLAGS) src/Environments/Rendering/Basic2dEnvironmentRender.cpp -c -o lib/Basic2dEnvironmentRender.o $(INC)
	$(CC) $(LDFLAGS) src/Environments/AbstractEnvironment.cpp src/Environments/TriMeshEnvironment.cpp $(INC) -c

	$(CC) $(LDFLAGS) src/unitTester.cpp  $(INC) $(LIB) -o bin/unitTester
	#$(CC) $(LDFLAGS) src/ccTester.cpp  $(INC) $(LIB) -c -o bin/ccTester
	$(CC) $(LDFLAGS) src/testInterFace.cpp -shared -fPIC -o bin/testInterface.so

clean:
	rm -f bin/** lib/**