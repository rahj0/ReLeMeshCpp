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
        long getMaxNumberOfHeros() const override;

    protected:
        double calculateFinishedObjectBonus() const override;
        void convertHeroToStartObjects() override;
        double getIdealObjectArea(const array1dInt point1) const override;
        std::unique_ptr<AbstractObject> createNewHero() override;
        std::tuple<coordinate,coordinate,bool> convertStepInput(
            const unsigned int input) const override;
    };
}

#endif