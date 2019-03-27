#include "AbstractObject.hh"
#include <iostream>
#include <math.h>
#define _USE_MATH_DEFINES

using namespace ReLeMesh;

ReLeMesh::AbstractObject::AbstractObject(
            coordinate southWest,
            coordinate southEast,
            coordinate northWest,
            coordinate northEast,
            Role role) : _role(role),
            _southWest(southWest),_southEast(southEast),
            _northWest(northWest),_northEast(northEast)
{
}

coordinate 
ReLeMesh::AbstractObject::getCenterPoint() const
{
    coordinate temp;
    for(int i = 0; i < ReLeMesh_N_DIM; ++i){
        temp[i] = _southWest[i] + _southEast[i] + _northWest[i] +_northEast[i];
        temp[i] /= 4.0;
    }
    return temp;
}

coordinate
ReLeMesh::AbstractObject::getMovingCenterPoint() const
{
  coordinate temp;
  for(int i = 0; i < ReLeMesh_N_DIM; ++i){
      temp[i] = _northWest[i] +_northEast[i];
      temp[i] /= 2.0;
  }
  return temp;
}

double ReLeMesh::AbstractObject::calculateAngle(
    const coordinate originPoint, 
    const coordinate secondPoint) const
{
    auto difX = secondPoint[0] - originPoint[0];
    auto difY = secondPoint[1] - originPoint[1];

    double angle = atan2(difY,difX);
    if (angle<0.0){
        angle = 2*M_PI+ angle;
    }
    return angle*180/M_PI;

}

bool ReLeMesh::AbstractObject::changeNorthWest(const coordinate changeVector)
{
    return changeCorner(changeVector,_northWest);
}
bool ReLeMesh::AbstractObject::changeNorthEast(const coordinate changeVector)
{
    return changeCorner(changeVector,_northEast);
}
bool ReLeMesh::AbstractObject::changeSouthWest(const coordinate changeVector)
{
    return changeCorner(changeVector,_southWest);
}
bool ReLeMesh::AbstractObject::changeSouthEast(const coordinate changeVector)
{
    return changeCorner(changeVector,_southEast);
}

void ReLeMesh::AbstractObject::setNorthWest(const coordinate newCoords)
{
    _northWest = newCoords;
}
void ReLeMesh::AbstractObject::setNorthEast(const coordinate newCoords)
{
    _northEast = newCoords;
}
void ReLeMesh::AbstractObject::setSouthWest(const coordinate newCoords)
{
    _southWest = newCoords;
}
void ReLeMesh::AbstractObject::setSouthEast(const coordinate newCoords)
{
    _southEast = newCoords;
}
bool ReLeMesh::AbstractObject::changeCorner(
    const coordinate changeVector, 
    coordinate corner)
{
    auto oldCoordinate = corner;
    for(int i = 0; i < int(changeVector.size()); ++i){
        corner[i] += changeVector[i]; 
    }
    if (! isNewShapeValid()){
        corner = oldCoordinate;
        return false;
    }   
    return true;
}
bool ReLeMesh::AbstractObject::isNewShapeValid() const
{
    return true;
}