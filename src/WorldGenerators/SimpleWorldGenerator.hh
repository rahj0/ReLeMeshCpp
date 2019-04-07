#ifndef ReLeMesh_SIMPLE_WORLD_GENERATOR_H
#define ReLeMesh_SIMPLE_WORLD_GENERATOR_H

#include<array>

#include "../gameObjects/AbstractObject.hh"
#include "../gameObjects/LineObject.hh"
#include "../WorldGenerators/AbstractWorldGenerator.hh"

namespace ReLeMesh
{
    class SimpleWorldGenerator : public AbstractWorldGenerator
    {
    public:
        SimpleWorldGenerator();
        std::vector<std::unique_ptr<AbstractObject>> generate(const std::array<integer,2> envSize);
        double getIdealAverageSquareArea() const;
    private: 
        integer _nHorisontalLines;
        integer _nVerticalLines;
        integer _totalArea;
    };
}

#endif