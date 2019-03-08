#ifndef ReLeMesh_ABSTRACTENVIRONMENT_H
#define ReLeMesh_ABSTRACTENVIRONMENT_H

#include <array>
#include <vector>
#include <memory>

#include "../gameObjects/AbstractObject.hh"
#include "Rendering/Basic2dEnvironmentRender.hh"

namespace ReLeMesh
{
    class AbstractEnvironment
    {
    public:
        AbstractEnvironment(const array1dInt envSize); //  add world Generator to argument list; // TODO

        void step(const unsigned action); // This might need to return tuple
        void reset();
        
        void setSeed(const int newSeed); // TODO
        void setCenterOfFocus(const array1dInt envSize); // TODO

        const tensor& getState() const; // TODO
        integer getSizeX() const;
        integer getSizeY() const;
        virtual long getMaxNumberOfHeros() const = 0;
        integer getActionCount() const;
        integer getChannelCount() const;

    protected:
        void resetVariables(); // private ?
        std::unique_ptr<AbstractObject>& getHero(); // is this needed ?
        void moveChar(); // This might need to return tuple
        integer countOverlappingPixels(); // Move to analyser class ?
        double calculateFinishedObjectBonusReward() const;  // Move to analyser class ?
        void renderEnv(); 

        void resizeObjToFitEnv(AbstractObject& object);  // Move to environment handler class ?
        void convertHeroToStartObjects();  // Move to environment handler class ?
        void saveHeroAsWall();  // Move to environment handler class ?
        void pushToFrontStarterObjectNearestToPoint(const array1dInt point1); // Move to environment handler class ?

        virtual double getIdealObjectArea(const array1dInt point1) = 0;
        virtual void createNewHero() = 0;
        virtual void convertStepInput() = 0; // This might need to return tuple

    private:
        const std::array<int,ReLeMesh_N_DIM> _size;
        std::vector<std::unique_ptr<AbstractObject>> _objects;
        tensor _stateTensor;
        integer _actionCount;
    };
}

#endif