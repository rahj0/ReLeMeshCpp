#include "TriangleObject.hh"

#include <iostream>

ReLeMesh::TriangleObject::TriangleObject(
            coordinate southWest,
            coordinate southEast,
            coordinate north,   
            Role role) : 
            AbstractObject(southWest,southEast,north,north,role)
{
}

ReLeMesh::TriangleObject::TriangleObject(
            coordinate southWest,
            coordinate southEast,  
            Role role) : 
            AbstractObject(southWest,southEast,
            generateNorthCoordinate(southWest,southEast),
            generateNorthCoordinate(southWest,southEast),
            role)
{
}
ReLeMesh::coordinate ReLeMesh::TriangleObject::generateNorthCoordinate(
            coordinate southWest,
            coordinate southEast)
{

    auto xDif = (southEast[0] - southWest[0] ) / 2.0;
    auto yDif = (southEast[1] - southWest[1] ) / 2.0;

    integer northX = integer(((southWest[0]-yDif)+(southEast[0]-yDif))/2);
    integer northY = integer(((southWest[1]+xDif)+(southEast[1]+xDif))/2);
        
    return {northX,northY};
}
     
double ReLeMesh::TriangleObject::calculateArea() const
{
    auto x1 = _southWest[0];
    auto y1 = _southWest[1];
    auto x2 = _northEast[0];
    auto y2 = _northEast[1];
    auto x3 = _southEast[0];
    auto y3 = _southEast[1];
    return abs(0.5*((x2-x1)*(y3-y1)-(x3-x1)*(y2-y1)));
}

bool ReLeMesh::TriangleObject::changeNorthWest(const coordinate changeVector)
{
    bool success = true;
    success &= AbstractObject::changeNorthEast(changeVector);
    if(success){
        success &= AbstractObject::changeNorthWest(changeVector);
    }
    return success;
}
bool ReLeMesh::TriangleObject::changeNorthEast(const coordinate changeVector)
{
    return changeNorthWest(changeVector);
}

void ReLeMesh::TriangleObject::setNorthWest(const coordinate newCoords)
{
    AbstractObject::setNorthWest(newCoords);
    AbstractObject::setNorthEast(newCoords);
}
void ReLeMesh::TriangleObject::setNorthEast(const coordinate newCoords)
{
    AbstractObject::setNorthWest(newCoords);
    AbstractObject::setNorthEast(newCoords);
}