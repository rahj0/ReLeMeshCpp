#include <iostream>
#include "gameObjects/AbstractObject.hh"
#include "gameObjects/LineObject.hh"
#include "gameObjects/TriangleObject.hh"
#include "Environments/AbstractEnvironment.hh"
#include "Environments/TriMeshEnvironment.hh"
#include "Environments/Rendering/Basic2dEnvironmentRender.hh"
#include "WorldGenerators/SimpleWorldGenerator.hh"

#include <memory>
#include <assert.h>

using ReLeMesh::TriangleObject;
using ReLeMesh::coordinate;
using ReLeMesh::integer;
using std::unique_ptr;
using std::cout; using std::endl; using std::vector;

void unitTest_Basic2dEnvironmentRender()
{
    int size = 10;
    std::vector<std::unique_ptr<ReLeMesh::AbstractObject>> objects; 
    coordinate p11 {0,0}; 
    coordinate p12 {8,0}; 
    coordinate p13 {5,1};
    coordinate p14 {8,1};

    coordinate p21 {7,7};
    coordinate p23 {9,3};

    objects.push_back(std::unique_ptr<TriangleObject>(
        new TriangleObject(p11,p12,p21, TriangleObject::Role::Active)));
    objects.push_back(std::unique_ptr<TriangleObject>(
        new TriangleObject(p13,p14,p23, TriangleObject::Role::PreDefined)));

    ReLeMesh::Basic2dEnvironmentRender envRender({size,size});

    vector<vector<vector<float>>> state;

    envRender.renderEnv(objects,state);

    for(auto& matrix : state){
        for(int j = int(matrix.front().size()-1); j >= 0; --j){
            for(size_t i = 0; i < matrix.size(); ++i){
                cout << matrix[i][j] << " ";
            }
            cout << endl;
        }
        cout << endl;
    }
}

void unitTest_AbstractEnvironment()
{
    std::cout << "--------- unitTest_AbstractEnvironment --------" << std::endl;
    int size = 10;
    ReLeMesh::TriMeshEnvironment testEnv({size,size});
    std::cout << testEnv.getMaxNumberOfHeros() << std::endl;
    testEnv.step(0);
    testEnv.step(1);
    testEnv.step(2);
    testEnv.step(3);
    testEnv.step(4);
    testEnv.step(5);
    testEnv.step(6);
    testEnv.step(7);
    testEnv.step(8);
    testEnv.printState();
    std::cout << "--------- end of: unitTest_AbstractEnvironment --------" << std::endl;
    
}

void unitTest_WorldGenerator()
{
    std::cout << "------ unitTest_WorldGenerator -----" << std::endl;
    int size = 10;
    ReLeMesh::SimpleWorldGenerator generator;
    auto objects = generator.generate({size,size});
    auto startObjects = generator.takeStartObjects();
    std::cout <<"Size1" << startObjects.size() << std::endl;
    assert(!startObjects.empty() );
    auto startObjects2 = generator.takeStartObjects();
    std::cout <<"Size2" << startObjects2.size() << std::endl;
    assert(startObjects2.empty() );
    std::cout << "Basic2dEnvironmentRender" << std::endl;
    ReLeMesh::Basic2dEnvironmentRender envRender({size,size});

    vector<vector<vector<float>>> state;
    envRender.renderEnv(objects,state);
    for(auto& matrix : state){
        for(int j = int(matrix.front().size()-1); j >= 0; --j){
            for(size_t i = 0; i < matrix.size(); ++i){
                cout << matrix[i][j] << " ";
            }
            cout << endl;
        }
        cout << endl;
    }
}

void unitTest_Objects()
{
    ReLeMesh::coordinate southWest {0,0}; 
    ReLeMesh::coordinate southEast {3,0}; 
    ReLeMesh::coordinate north {1,3};
    ReLeMesh::TriangleObject triObject1(
      southWest,southEast,north,ReLeMesh::TriangleObject::Role::Active); 
    ReLeMesh::TriangleObject triObject2(
      southWest,southEast,north,ReLeMesh::TriangleObject::Role::PreDefined); 
    ReLeMesh::LineObject lineObject1(
      southWest,southEast,ReLeMesh::TriangleObject::Role::Active); 
    ReLeMesh::LineObject lineObject2(
      southEast,southWest,ReLeMesh::TriangleObject::Role::Active);
}
int main()
{
    std::cout << "Hello World!" << std::endl;

    unitTest_Objects();
    unitTest_Basic2dEnvironmentRender();
    unitTest_AbstractEnvironment();
    unitTest_WorldGenerator();

    return 0;
}