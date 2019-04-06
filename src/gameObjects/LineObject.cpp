#include "LineObject.hh"

#include <iostream>

ReLeMesh::LineObject::LineObject(
            coordinate west,
            coordinate east,
            Role role) : AbstractObject(west,east,west,east,role)
{
}

double ReLeMesh::LineObject::calculateArea() const
{
    return 0.0;
}

bool ReLeMesh::LineObject::changeEast(const coordinate changeVector)
{
    bool success = true;
    success &= changeNorthWest(changeVector);
    if(success){
        success &= changeSouthWest(changeVector);
    }
    return success;
}
         
bool ReLeMesh::LineObject::changeWest(const coordinate changeVector)
{
    bool success = true;
    success &= changeNorthEast(changeVector);
    if(success){
        success &= changeSouthEast(changeVector);
    }
    return success;
}