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
            Role role) : _role(role)
{
}

ReLeMesh::AbstractObject::AbstractObject() : _role(Role::Active)
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
        //   ---------- 0 deg
        //  
        //        /
        //       / 
        //     /   45 ish deg
        //    /______
        //    \
        //     \
        //      \  - 55 ish deg

    //  def calculateSouthWestCornerAngle(self):
    //      angle1 = self.calculateAngle(self._southWest,self._southEast)
    //      angle2 = self.calculateAngle(self._southWest,self._northWest) 
    //      angle = angle2 - angle1
    //      if (angle2 < angle1):
    //          angle += 360.0
    //      return angle
  
    //  def calculateSouthEastCornerAngle(self):
    //      angle1 = self.calculateAngle(self._southEast,self._southWest)
    //      angle2 = self.calculateAngle(self._southEast,self._northEast) 
    //      angle = angle1-angle2
    //      if (angle1 < angle2):
    //          angle += 360.0
    //      return angle

//     def calculateNorthWestCornerAngle(self):
//         angle1 = self.calculateAngle(self._northWest,self._northEast)
//         angle2 = self.calculateAngle(self._northWest,self._southWest) 
//         angle = angle1 - angle2
//         if (angle1 < angle2):
//             angle += 360.0
//         return angle
    
//     def calculateNorthEastCornerAngle(self):
//         angle1 = self.calculateAngle(self._northEast,self._northWest)
//         angle2 = self.calculateAngle(self._northEast,self._southEast) 
//         angle = angle2-angle1
//         if (angle2 < angle1):
//             angle += 360.0
//         return angle
//     def getArea(self):
//         x1 = self._southWest[0]
//         y1 = self._southWest[1]
//         x2 = self._northWest[0]
//         y2 = self._northWest[1]

//         x3 = self._northEast[0]
//         y3 = self._northEast[1]
//         x4 = self._southEast[0]
//         y4 = self._southEast[1]

//         a123 = abs(0.5*((x2-x1)*(y3-y1)-(x3-x1)*(y2-y1)))
//         a341 = abs(0.5*((x4-x1)*(y3-y1)-(x3-x1)*(y4-y1)))
//         return a123+a341

//     def getBonusValue(self):
//         bonusValue = 0
//         bonusValue += self.getArea()
//         return bonusValue
    
//     def isNewShapeValid(self):
//         return True
    
//     def calculateAngle(self, originPoint, secondPoint):
//         difX = secondPoint[0] - originPoint[0]
//         difY = secondPoint[1] - originPoint[1]
// #    
// #        angle = atan(abs(difY)/abs(difX))
// #        if(difX < 0.0 and difY > 0.0):
// #            print("1")
// #            angle += 0.5*pi
// #        if(difX < 0.0 and difY < 0.0):
// #            print("2")
// #            angle += pi
// #        if(difX > 0.0 and difY < 0.0):
// #            print("3")
// #            angle += 1.5*pi
//         angle = atan2(difY,difX)
//         if (angle<0.0):
//             angle = 2*pi + angle
//         return degrees(angle)
//         # ---------- 0 deg
//         #
//         #      /
//         #     / 
//         #   /   45 ish deg
//         #  /______
//         #  \
//         #   \
//         #    \  - 55 ish deg
        
//     def getName(self):
//         return self.name
    
//     def printAngles(self):
//         pass
// #        print("SouthWest: ", self.calculateSouthWestCornerAngle())
// #        print("SouthEast: ", self.calculateSouthEastCornerAngle())
// #        print("NorthWest: ", self.calculateNorthWestCornerAngle())
// #        print("NorthEast: ", self.calculateNorthEastCornerAngle())
// #        print("")
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
    for(int i = 0; i < changeVector.size(); ++i){
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
//     def getNorthWest(self):
//         return self._northWest
    
//     def getNorthEast(self):
//         return self._northEast
    
//     def getSouthWest(self):
//         return self._southWest
    
//     def getSouthEast(self):
//         return self._southEast
    