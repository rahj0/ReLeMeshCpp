#include <iostream>
#include "gameObjects/AbstractObject.hh"
#include "gameObjects/LineObject.hh"
#include "gameObjects/TriangleObject.hh"

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
  return 0;
}