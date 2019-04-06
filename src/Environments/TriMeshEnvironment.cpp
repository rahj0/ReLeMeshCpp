#include "TriMeshEnvironment.hh"
#include "../gameObjects/TriangleObject.hh"
#include <iostream>

using ReLeMesh::coordinate;

ReLeMesh::TriMeshEnvironment::
TriMeshEnvironment(const std::array<int,ReLeMesh_N_DIM> environmentSize) :
ReLeMesh::AbstractEnvironment(environmentSize)
{
    reset();
}

long ReLeMesh::TriMeshEnvironment::getMaxNumberOfHeros() const
{
    return long(1000); //TODO
}

double ReLeMesh::TriMeshEnvironment::getIdealObjectArea(const array1dInt point1) const
{
    return 0.0; //TODO
}
std::unique_ptr<ReLeMesh::AbstractObject> ReLeMesh::TriMeshEnvironment::createNewHero()
{
    coordinate p1 {0,0};
    coordinate p2 {1,1};
    if(! _startObjects.empty()){
        p1 =_startObjects.back().getNorthWest();
        p2 = _startObjects.back().getNorthEast();
    }
    _startObjects.pop_back();
    return std::make_unique<TriangleObject>(p1,p2, AbstractObject::Role::Active);
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

void ReLeMesh::TriMeshEnvironment::convertHeroToStartObjects()
{ 
    auto northWest = getHero()->getNorthWest();
    auto northEast = getHero()->getNorthEast();
    int channel = 1;
    auto valueWest = _state[northWest[0],northWest[1],channel];
    auto valueEast = _state[northEast[0],northEast[1],channel];
    // 
    // if((valueWest == 0.0) or (valueEast == 0.0)):
    //     self.startObjects.append(self.objects[-1])
    //     return
    // else:
    //     for pixel in BasicEnvironmentRender.computePixelsFromLine(northWest[0],northWest[1],northEast[0],northEast[1]):
    //         if(self._state[pixel[0],pixel[1],1] == 0.0 ):
    //             self.startObjects.append(self.objects[-1])
    //             return

}// Move to environment handler class ?
