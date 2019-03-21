#include "TriMeshEnvironment.hh"

using ReLeMesh::coordinate;

ReLeMesh::TriMeshEnvironment::
TriMeshEnvironment(const std::array<int,ReLeMesh_N_DIM> environmentSize) :
ReLeMesh::AbstractEnvironment(environmentSize)
{

}

long ReLeMesh::TriMeshEnvironment::getMaxNumberOfHeros() const
{
    return long(1000); //TODO
}

double ReLeMesh::TriMeshEnvironment::getIdealObjectArea(const array1dInt point1)
{
    return 0.0; //TODO
}
void ReLeMesh::TriMeshEnvironment::createNewHero()
{

}
std::tuple<coordinate,coordinate,bool>
ReLeMesh::TriMeshEnvironment::convertStepInput(const unsigned int input) const
{
    //TODO Get rid of tuple. maybe split in to functions
    // for better readability
        integer changeNorthWestX = 0;
        integer changeNorthWestY = 0;
        integer changeNorthEastX = 0;
        integer changeNorthEastY = 0;
        bool newHero = false;
        if(input == 0){
            changeNorthWestX = 1;
        } else if( input == 1){
            changeNorthWestX = -1;
        }
        else if( input == 2){
            changeNorthWestY = 1;
        }
        else if( input == 3){
            changeNorthWestY = -1;
        }
        else if( input == 4){         
            changeNorthWestX = 1;
            changeNorthWestY = 1;
        }
        else if( input == 5){
            changeNorthWestX = -1;
            changeNorthWestY = 1;
        }
        else if( input == 6){
            changeNorthWestX = 1;
            changeNorthWestY = -1;
        }
        else if( input == 7){
            changeNorthWestX = -1;
            changeNorthWestY = -1;
        }
        else if( input == 8){ // # 8 is used by the viewer
            newHero = true;
        }
        return {{changeNorthWestX, changeNorthWestY},{ changeNorthEastX, changeNorthEastY}, newHero};
}