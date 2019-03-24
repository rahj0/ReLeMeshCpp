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

extern "C" void step(void* ptr, int action, float* data)
{
    auto env = static_cast<TriMeshEnvironment*>(ptr);
    auto [reward,done,state] = env->step(action);
    std::cout << "Reward: " << reward << std::endl;
    std::cout << "Done: " << (done ? "True" : "False") << std::endl;
    std::cout << "Size of state: " << state.size() << std::endl;
    env->printState();
    long i = 0;
    for(auto& matrix : state){
        for(auto& vector : matrix){
            for(auto& value : vector){
                data[i] = value;
                ++i;
                std::cout << i << std::endl;
            }
        }
    }
}

extern "C" void deleteEnvironment(void* ptr)
{
    auto env = static_cast<TriMeshEnvironment*>(ptr);
    delete env;
}

extern "C" int getChannelCount(void* ptr)
{
    auto env = static_cast<TriMeshEnvironment*>(ptr);
    return int(env->getChannelCount());
}

extern "C" int getSizeX(void* ptr)
{
    auto env = static_cast<TriMeshEnvironment*>(ptr);
    std::cout << env->getSizeX() << std::endl;
    return int(env->getSizeX());
}

extern "C" int getSizeY(void* ptr)
{
    auto env = static_cast<TriMeshEnvironment*>(ptr);
    std::cout << env->getSizeY() << std::endl;
    return int(env->getSizeY());
}