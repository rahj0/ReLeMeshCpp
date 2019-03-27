CFLAGS = -Wall -pedantic -std=c++17 -fPIC
CC = g++ $(CFLAGS)
SRCDIR := src
BUILDDIR := build
INC := -I include -I ../boost_1_69_0
LIBFOLDER := lib/debug
LIB := -L $(LIBFOLDER)/*

all: test

bin/unitTester: src/unitTester.cpp bin/ReLeMeshInterface.so
	$(CC) $(LDFLAGS) src/unitTester.cpp $(LIBFOLDER)/* -o bin/unitTester

bin/ReLeMeshInterface.so: $(LIBFOLDER)/AbstractObject.o $(LIBFOLDER)/TriangleObject.o $(LIBFOLDER)/LineObject.o $(LIBFOLDER)/Basic2dEnvironmentRender.o $(LIBFOLDER)/AbstractEnvironment.o $(LIBFOLDER)/Basic2dEnvironmentRender.o
	$(CC) $(LDFLAGS) src/ReLeMeshInterface.cpp -shared $(LIB) -o bin/ReLeMeshInterface.so

$(LIBFOLDER)/AbstractObject.o: src/gameObjects/AbstractObject.cpp
	$(CC) $(LDFLAGS) src/gameObjects/AbstractObject.cpp $(INC) -c -o $(LIBFOLDER)/AbstractObject.o
	
$(LIBFOLDER)/TriangleObject.o: src/gameObjects/TriangleObject.cpp 
	$(CC) $(LDFLAGS) src/gameObjects/TriangleObject.cpp $(INC) -c -o $(LIBFOLDER)/TriangleObject.o

$(LIBFOLDER)/LineObject.o: src/gameObjects/LineObject.cpp
	$(CC) $(LDFLAGS) src/gameObjects/LineObject.cpp $(INC) -c -o $(LIBFOLDER)/LineObject.o

$(LIBFOLDER)/AbstractEnvironment.o: src/Environments/AbstractEnvironment.cpp src/Environments/TriMeshEnvironment.cpp $(LIBFOLDER)/AbstractWorldGenerator.o
	$(CC) $(LDFLAGS) src/Environments/AbstractEnvironment.cpp  $(INC) -c -o $(LIBFOLDER)/AbstractEnvironment.o
	$(CC) $(LDFLAGS) src/Environments/TriMeshEnvironment.cpp $(INC) -c -o $(LIBFOLDER)/TriMeshEnvironment.o

$(LIBFOLDER)/Basic2dEnvironmentRender.o: src/Environments/Rendering/Basic2dEnvironmentRender.cpp 
	$(CC) $(LDFLAGS) src/Environments/Rendering/Basic2dEnvironmentRender.cpp -c -o $(LIBFOLDER)/Basic2dEnvironmentRender.o $(INC)

$(LIBFOLDER)/AbstractWorldGenerator.o: src/WorldGenerators/AbstractWorldGenerator.cpp src/WorldGenerators/SimpleWorldGenerator.cpp 
	$(CC) $(LDFLAGS) src/WorldGenerators/AbstractWorldGenerator.cpp $(INC) -c -o $(LIBFOLDER)/AbstractWorldGenerator.o
	$(CC) $(LDFLAGS) src/WorldGenerators/SimpleWorldGenerator.cpp $(INC) -c -o $(LIBFOLDER)/SimpleWorldGenerator.o

test: bin/unitTest bin/unitTester
	./bin/unitTester
	# --- Boost Unit Tests --- #
	./bin/unitTest

bin/unitTest: src/unitTests/Basic2dEnvironmentRender_unitTest.cpp src/unitTests/Dummy_unitTest.cpp src/unitTests/unitTestMain.cpp bin/ReLeMeshInterface.so
	$(CC) $(LDFLAGS) src/unitTests/unitTestMain.cpp $(INC) -c -o lib/tests/unitTestMain.o
	$(CC) $(LDFLAGS) src/unitTests/Basic2dEnvironmentRender_unitTest.cpp $(INC) -c -o lib/tests/Basic2dEnvironmentRender_unitTest.o
	$(CC) $(LDFLAGS) src/unitTests/Dummy_unitTest.cpp $(INC) -c -o lib/tests/Dummy_unitTest.o
	$(CC) $(LDFLAGS) lib/tests/* $(INC) $(LIBFOLDER)/* -o bin/unitTest

clean:
	rm -f bin/** $(LIBFOLDER)/**  lib/tests/**

pyTest:
	python3 src/test.py
