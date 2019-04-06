#ifndef ReLeMesh_ABSTRACT_WORLD_GENERATOR_H
#define ReLeMesh_ABSTRACT_WORLD_GENERATOR_H

#include<array>
#include<vector>
#include<memory>

#include "../gameObjects/AbstractObject.hh"
#include "../gameObjects/LineObject.hh"

namespace ReLeMesh
{
    class AbstractWorldGenerator 
    {
    public:
        integer generateRandomDeviation(const integer minDeviation, const integer maxDeviation ) const;
        virtual std::vector<std::unique_ptr<AbstractObject>> generate(const std::array<integer,2> envSize) = 0;
        std::vector<LineObject> takeStartObjects() { return std::move(_startObjects); };
        double getIdealAverageSquareArea();
    protected:

        std::vector<LineObject> _startObjects; 

      };
}

#endif