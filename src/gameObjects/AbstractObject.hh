#ifndef ReLeMesh_ABSTRACTOBJECT_H
#define ReLeMesh_ABSTRACTOBJECT_H

#define ReLeMesh_COORD_TYPE int
#define ReLeMesh_N_DIM 2
#include<array>



namespace ReLeMesh
{
    const ReLeMesh_COORD_TYPE nDim = ReLeMesh_N_DIM;
    typedef std::array<ReLeMesh_COORD_TYPE,ReLeMesh_N_DIM> coordinate;
    typedef std::array<ReLeMesh_COORD_TYPE,ReLeMesh_N_DIM> array1dInt;
    typedef ReLeMesh_COORD_TYPE integer;

    class AbstractObject 
    {
    public:
        enum Role{
            Active,
            Locked,
            PreDefined,
        };

        AbstractObject(
            coordinate southWest,
            coordinate southEast,
            coordinate northWest,
            coordinate northEast,
            Role role);
        AbstractObject() = delete;

        virtual coordinate getCenterPoint() const;
        virtual coordinate getMovingCenterPoint() const;
        double calculateNorthEastCornerAngle() const;
        double calculateNorthWestCornerAngle() const;
        double calculateSouthEastCornerAngle() const;
        double calculateSouthWestCornerAngle() const;
        virtual bool changeNorthWest(const coordinate changeVector);
        virtual bool changeNorthEast(const coordinate changeVector);
        virtual bool changeSouthWest(const coordinate changeVector);
        virtual bool changeSouthEast(const coordinate changeVector);
        virtual void setNorthWest(const coordinate newCoords);
        virtual void setNorthEast(const coordinate newCoords);
        virtual void setSouthWest(const coordinate newCoords);
        virtual void setSouthEast(const coordinate newCoords);
        coordinate getNorthWest() const {return _northWest;}
        coordinate getNorthEast() const {return _northEast;}
        coordinate getSouthWest() const {return _southWest;}
        coordinate getSouthEast() const {return _southEast;}
        Role getRole() const {return _role;}
        virtual double calculateArea() const = 0;

    protected:
        const Role _role;
    private:
        bool changeCorner(const coordinate changeVector, coordinate corner);
        virtual bool isNewShapeValid() const;
        double calculateAngle(
            const coordinate originPoint,
            const coordinate secondPoint) const;

        coordinate _southWest;
        coordinate _southEast;
        coordinate _northWest;
        coordinate _northEast;
        
      };
}

#endif