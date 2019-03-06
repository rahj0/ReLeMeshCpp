#include "TriangleObject.hh"

#include <iostream>

ReLeMesh::TriangleObject::TriangleObject(
            coordinate southWest,
            coordinate southEast,
            coordinate north,   
            Role role) : AbstractObject(southWest,southEast,north,north,role)
{
    std::cout << "TriangleObject Created" << std::endl;
}

ReLeMesh::TriangleObject::TriangleObject()
{
    std::cout << "TriangleObject Created" << std::endl;
}

double ReLeMesh::TriangleObject::calculateArea() const
{
    return 0.0;
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