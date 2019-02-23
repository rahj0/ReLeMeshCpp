#ifndef ReLeMesh_LINEOBJECT_H
#define ReLeMesh_LINEOBJECT_H

#include "AbstractObject.hh"

namespace ReLeMesh
{
    class LineObject : public AbstractObject
    {
    public:
        LineObject(
            coordinate,
            coordinate,
            coordinate,
            coordinate,
            Role role);
        LineObject();

        double calculateArea() const;

        bool changeEast(const coordinate changeVector);
        bool changeWest(const coordinate changeVector);
      };
}

#endif