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
        virtual ~TriMeshEnvironment() {}
        long getMaxNumberOfHeros() const;


    protected:
        double getIdealObjectArea(const array1dInt point1);
        std::unique_ptr<AbstractObject> createNewHero();
        std::tuple<coordinate,coordinate,bool> convertStepInput(const unsigned int input) const;
    };
}

#endif