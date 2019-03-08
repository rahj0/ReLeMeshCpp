#include <iostream>
#include "gameObjects/AbstractObject.hh"
#include "gameObjects/LineObject.hh"
#include "gameObjects/TriangleObject.hh"
#include "Environments/AbstractEnvironment.hh"
#include "Environments/TriMeshEnvironment.hh"
#include "Environments/Rendering/Basic2dEnvironmentRender.hh"

#include <memory>

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
    coordinate p22 {4,3};
    coordinate p23 {9,3};

    objects.push_back(std::unique_ptr<TriangleObject>(
        new TriangleObject(p11,p12,p21, TriangleObject::Role::Active)));
    objects.push_back(std::unique_ptr<TriangleObject>(
        new TriangleObject(p13,p14,p23, TriangleObject::Role::PreDefined)));

    ReLeMesh::Basic2dEnvironmentRender envRender({size,size});

    vector<vector<vector<float>>> state;

    envRender.renderEnv(objects,state);

    for(auto& matrix : state){
        for(int j = matrix.front().size()-1; j >= 0; --j){
            for(int i = 0; i < matrix.size(); ++i){
                cout << matrix[i][j];
            }
            cout << endl;
        }
        cout << endl;
    }
}

void unitTest_AbstractEnvironment()
{
    int size = 10;
    ReLeMesh::TriMeshEnvironment testEnv({size,size});
}

int main()
{
    ReLeMesh::LineObject lineObject; 
    ReLeMesh::TriangleObject triObject; 
    ReLeMesh::coordinate southWest {0,0}; 
    ReLeMesh::coordinate southEast {3,0}; 
    ReLeMesh::coordinate north {1,3};
    ReLeMesh::TriangleObject triObject2(
      southWest,southEast,north,ReLeMesh::TriangleObject::Role::Active); 
    std::cout << "Hello World!" << std::endl;

    unitTest_Basic2dEnvironmentRender();

    return 0;
}