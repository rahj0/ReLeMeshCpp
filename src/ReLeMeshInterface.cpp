#include<iostream>
#include<vector>
#include<array>

#include "Environments/TriMeshEnvironment.hh"
using ReLeMesh::TriMeshEnvironment;

extern "C" void* createTriMeshEnvironment(int sizeX, int sizeY)
{
    std::array<int,2> environmentSize{sizeX,sizeY};

    return new TriMeshEnvironment(environmentSize);
}

extern "C" void step(void* ptr, int action)
{
   auto env = static_cast<TriMeshEnvironment*>(ptr);
   env->step(action);
    std::cout << "Action" << std::endl;
    env->printState();

    std::cout << env->getMaxNumberOfHeros() << std::endl;
    std::cout << "Action" << std::endl;
}