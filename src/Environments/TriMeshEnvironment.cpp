#include "TriMeshEnvironment.hh"

ReLeMesh::TriMeshEnvironment::
TriMeshEnvironment(const std::array<int,ReLeMesh_N_DIM> environmentSize) :
ReLeMesh::AbstractEnvironment(environmentSize)
{

}

long ReLeMesh::TriMeshEnvironment::getMaxNumberOfHeros() const
{
    return 1000; //TODO
}

double ReLeMesh::TriMeshEnvironment::getIdealObjectArea(const array1dInt point1)
{
    return 0.0; //TODO
}
void ReLeMesh::TriMeshEnvironment::createNewHero()
{

}
void ReLeMesh::TriMeshEnvironment::convertStepInput()
{

}