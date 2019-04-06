CFLAGS = -Wall -pedantic -std=c++17 -fPIC
CC = g++ $(CFLAGS)
SRCDIR := src
BUILDDIR := build
INC := -I include -I ../boost_1_69_0
LIBFOLDER := lib/debug
LIB := $(LIBFOLDER)/*

all: test

libOnly: ./bin/unitTester
	./bin/unitTester
	python3 ./src/test.py

test: bin/unitTest bin/unitTester
	./bin/unitTester
	python3 ./src/test.py
	# --- Boost Unit Tests --- #
	./bin/unitTest

bin/unitTester: src/unitTester.cpp bin/ReLeMeshInterface.so
	$(CC) src/unitTester.cpp $(LIBFOLDER)/* -o bin/unitTester

bin/ReLeMeshInterface.so: src/ReLeMeshInterface.cpp $(LIBFOLDER)/AbstractEnvironment.o $(LIBFOLDER)/AbstractObject.o $(LIBFOLDER)/TriangleObject.o $(LIBFOLDER)/LineObject.o $(LIBFOLDER)/AbstractEnvironment.o $(LIBFOLDER)/Basic2dEnvironmentRender.o $(LIBFOLDER)/AbstractWorldGenerator.o
	$(CC) src/ReLeMeshInterface.cpp -shared $(LIB) -o bin/ReLeMeshInterface.so

$(LIBFOLDER)/AbstractObject.o: src/gameObjects/AbstractObject.cpp
	$(CC) src/gameObjects/AbstractObject.cpp $(INC) -c -o $(LIBFOLDER)/AbstractObject.o
	
$(LIBFOLDER)/TriangleObject.o: src/gameObjects/TriangleObject.cpp 
	$(CC) src/gameObjects/TriangleObject.cpp $(INC) -c -o $(LIBFOLDER)/TriangleObject.o

$(LIBFOLDER)/LineObject.o: src/gameObjects/LineObject.cpp
	$(CC) src/gameObjects/LineObject.cpp $(INC) -c -o $(LIBFOLDER)/LineObject.o

$(LIBFOLDER)/AbstractEnvironment.o: src/Environments/AbstractEnvironment.cpp src/Environments/TriMeshEnvironment.cpp $(LIBFOLDER)/AbstractWorldGenerator.o
	$(CC) src/Environments/AbstractEnvironment.cpp $(INC) -c -o $(LIBFOLDER)/AbstractEnvironment.o
	$(CC) src/Environments/TriMeshEnvironment.cpp $(INC) -c -o $(LIBFOLDER)/TriMeshEnvironment.o

$(LIBFOLDER)/Basic2dEnvironmentRender.o: src/Environments/Rendering/Basic2dEnvironmentRender.cpp 
	$(CC) src/Environments/Rendering/Basic2dEnvironmentRender.cpp -c -o $(LIBFOLDER)/Basic2dEnvironmentRender.o $(INC)

$(LIBFOLDER)/AbstractWorldGenerator.o: src/WorldGenerators/AbstractWorldGenerator.cpp src/WorldGenerators/SimpleWorldGenerator.cpp 
	$(CC) src/WorldGenerators/AbstractWorldGenerator.cpp $(INC) -c -o $(LIBFOLDER)/AbstractWorldGenerator.o
	$(CC) src/WorldGenerators/SimpleWorldGenerator.cpp $(INC) -c -o $(LIBFOLDER)/SimpleWorldGenerator.o

bin/unitTest: src/unitTests/Basic2dEnvironmentRender_unitTest.cpp src/unitTests/Dummy_unitTest.cpp src/unitTests/TriMeshEnvironment_unitTest.cpp src/unitTests/unitTestMain.cpp bin/ReLeMeshInterface.so
	$(CC) src/unitTests/unitTestMain.cpp $(INC) -c -o lib/tests/unitTestMain.o
	$(CC) src/unitTests/Basic2dEnvironmentRender_unitTest.cpp $(INC) -c -o lib/tests/Basic2dEnvironmentRender_unitTest.o
	$(CC) src/unitTests/TriMeshEnvironment_unitTest.cpp $(INC) -c -o lib/tests/TriMeshEnvironment_unitTest.o
	$(CC) src/unitTests/Dummy_unitTest.cpp $(INC) -c -o lib/tests/Dummy_unitTest.o
	$(CC) lib/tests/* $(INC) $(LIBFOLDER)/* -o bin/unitTest

clean:
	rm -f bin/** $(LIBFOLDER)/** lib/tests/**
pyTest: bin/unitTester
	python3 src/test.py
