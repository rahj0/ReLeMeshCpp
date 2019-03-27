
#ifndef ReLeMesh_BASIC2DENVIRONMENTRENDER1_H
#define ReLeMesh_BASIC2DENVIRONMENTRENDER1_H

#include <array>
#include <vector> 
#include <map>
#include <memory>

#include "../../gameObjects/AbstractObject.hh"
 
namespace ReLeMesh
{
    typedef std::vector<std::vector<std::vector<float>>> tensor;
    class Basic2dEnvironmentRender
    {
    public:
        Basic2dEnvironmentRender(const std::array<integer,2> envSize);

        static std::vector<coordinate> computePixelsFromLine(const coordinate point1, const coordinate point2);
        bool renderObject(const std::unique_ptr<AbstractObject>& object, std::vector<std::vector<float>>& channelState);
        bool renderEnv(const std::vector<std::unique_ptr<AbstractObject>>& objects, 
        tensor& channelState);
        int getRoleChannel(const AbstractObject::Role role) const {return _roleChannels.at(role);}

    private:
        const integer _sizeX;
        const integer _sizeY;
        std::map<AbstractObject::Role,int> _roleChannels;

        array1dInt calculateXYmoveUnitVector(
            const coordinate point1,const coordinate point2);   
        static std::vector<integer> valueLeft(const integer index,const integer minValue,
        const integer maxValue,const integer maxIndex);
    };
}
#endif