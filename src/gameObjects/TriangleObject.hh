#ifndef ReLeMesh_TRIANGLEBJECT_H
#define ReLeMesh_TRIANGLEBJECT_H

#include "AbstractObject.hh"

namespace ReLeMesh
{
    class TriangleObject : public AbstractObject
    {
    public:
        TriangleObject(
            coordinate southWest,
            coordinate southEast,
            coordinate north,
            Role role);        
        TriangleObject(
            coordinate southWest,
            coordinate southEast,
            Role role);

        double calculateArea() const;
        virtual bool changeNorthWest(const coordinate changeVector) override;
        virtual bool changeNorthEast(const coordinate changeVector) override;
        virtual void setNorthWest(const coordinate newCoords) override;
        virtual void setNorthEast(const coordinate newCoords) override;
    private:
        static coordinate generateNorthCoordinate(
            coordinate southWest,
            coordinate southEast);
    };
}

#endif