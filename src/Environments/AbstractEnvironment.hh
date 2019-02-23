#ifndef ReLeMesh_ABSTRACTENVIRONMENT_H
#define ReLeMesh_ABSTRACTENVIRONMENT_H

#include <array>

#include "../gameObjects/AbstractObject.hh"

namespace ReLeMesh
{
    class AbstractEnvironment
    {
    public:
        AbstractEnvironment(const std::array<int,ReLeMesh_N_DIM> envSize);
    private:
        const std::array<int,ReLeMesh_N_DIM> _size;
    };
}

#endif