#ifndef ReLeMesh_ABSTRACTENVIRONMENT_H
#define ReLeMesh_ABSTRACTENVIRONMENT_H

#include <array>
#include <vector>
#include <memory>
#include <tuple>

#include "../gameObjects/AbstractObject.hh"
#include "../gameObjects/LineObject.hh"
#include "Rendering/Basic2dEnvironmentRender.hh"
#include "../WorldGenerators/AbstractWorldGenerator.hh"

namespace ReLeMesh
{
    class AbstractEnvironment
    {
    public:
        AbstractEnvironment(const array1dInt envSize); //  add world Generator to argument list; // TODO

        std::tuple<double,bool,tensor&> step(const unsigned action); // This might need to return tuple
        void reset();
        void setCenterOfFocus(const array1dInt envSize); // TODO
        void setWorldGenerator(std::unique_ptr<AbstractWorldGenerator> generator);
        const tensor& getState() const;
        integer getSizeX() const;
        integer getSizeY() const;
        virtual long getMaxNumberOfHeros() const = 0;
        integer getActionCount() const;
        integer getChannelCount() const;
        void printState() const;
        integer getObjectCount() const {return _objects.size();}

    protected:
        std::unique_ptr<AbstractObject>& getHero(); // is this needed ?
        const std::unique_ptr<AbstractObject>& getHero() const; // is this needed ?
        // void moveChar(); // This might need to return tuple
        integer countOverlappingPixels() const; // Move to analyser class ?
        virtual double calculateFinishedObjectBonus() const;  // Move to analyser class ?
        void renderEnv(); 

        void resizeObjToFitEnv(std::unique_ptr<AbstractObject>& object);  // Move to environment handler class ?
        virtual void convertHeroToStartObjects() = 0;  // Move to environment handler class ?
        void saveHeroAsWall();  // Move to environment handler class ?
        void pushToFrontStarterObjectNearestToPoint(const array1dInt point1); // Move to environment handler class ?

        virtual double getIdealObjectArea(const array1dInt point1) const = 0;
        virtual std::unique_ptr<AbstractObject> createNewHero() = 0;
        virtual std::tuple<coordinate,coordinate,bool> 
            convertStepInput(const unsigned int action) const = 0;
            
        std::vector<LineObject> _startObjects;
        tensor _state;
        const double _cornerMatchBonus;
        std::unique_ptr<AbstractWorldGenerator> _worldGenerator;
        
    private:
        double calculateBonusForHero() const;
        const array1dInt _size;
        std::vector<std::unique_ptr<AbstractObject>> _objects;        
        std::vector<integer> _actions;
        bool _done;
        bool _useCenterOfFocus;
        array1dInt _centerOfFocus;
        integer _nHeros;
        double _currentBonusValue;
        const double _overlappingPixelPenalty;
        double _bonusNormalisationValue;
        double _totalReward;
        Basic2dEnvironmentRender _render;
    };
}

#endif