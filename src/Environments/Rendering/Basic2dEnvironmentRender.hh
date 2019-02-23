
#ifndef ReLeMesh_BASIC2DENVIRONMENTRENDER_H
#define ReLeMesh_BASIC2DENVIRONMENTRENDER_H

#include <array>
#include <vector> 
#include "../../gameObjects/AbstractObject.hh"
 
namespace ReLeMesh
{
    class Basic2dEnvironmentRender
    {
    public:
        Basic2dEnvironmentRender(const std::array<integer,2> envSize);

        static std::vector<array1dInt> computePixelsFromLine(const array1dInt point1, const array1dInt point2);
        bool renderObject(const AbstractObject& object, std::vector<std::vector<float>>& channelState);
        bool renderEnv(const std::vector<AbstractObject> objects, std::vector<std::vector<integer>>& channelState);

    private:
        const integer _sizeX;
        const integer _sizeY;

        array1dInt calculateXYmoveUnitVector(
            const array1dInt point1,const array1dInt point2);   
        static std::vector<integer> valueLeft(const integer index,const integer minValue,
        const integer maxValue,const integer maxIndex);
    };
}
#endif