#ifndef ReLeMesh_TRI_MESH_ENVIRONMENT_H
#define ReLeMesh_TRI_MESH_ENVIRONMENT_H

#include <array>

#include "AbstractEnvironment.hh"

namespace ReLeMesh
{
    class TriMeshEnvironment : public AbstractEnvironment
    {
    public:
        TriMeshEnvironment(const std::array<int,ReLeMesh_N_DIM> envSize);
        long getMaxNumberOfHeros() const;

    protected:
        double getIdealObjectArea(const array1dInt point1);
        void createNewHero();
        void convertStepInput(); // This might need to return tuple
    };
}

#endif