#include "AbstractEnvironment.hh"

#include "../WorldGenerators/SimpleWorldGenerator.hh"

#include <iostream>
#include <math.h>
#include <functional>
#include <algorithm>

using ReLeMesh::tensor;
using ReLeMesh::integer;
using ReLeMesh::AbstractObject;

ReLeMesh::AbstractEnvironment::
AbstractEnvironment(const array1dInt environmentSize) :
_size(environmentSize), _overlappingPixelPenalty(8), // TODO remove hardcoded values
_cornerMatchBonus(10) ,_render(environmentSize)
{
    _worldGenerator = std::make_unique<SimpleWorldGenerator>();
    static_assert(environmentSize.size() > 1);
}

void ReLeMesh::AbstractEnvironment::reset()
{
    _nHeros = 0;
    if(_worldGenerator){
        _objects = _worldGenerator->generate(_size);
        _startObjects = _worldGenerator->takeStartObjects();
    }
    _actions.clear();
    _done = false;
    _totalReward = 0.0;
    _bonusNormalisationValue = _cornerMatchBonus; // TODO: get the ideal area from world generator getIdealObjectArea(_centerOfFocus);

    std::random_shuffle(_startObjects.begin(),_startObjects.end());  // TODO: Add shuffle
    _objects.push_back(createNewHero());
    ++_nHeros;

    for(auto& obj : _objects){
        resizeObjToFitEnv(obj); // Do we need to check all objects ?
    }
    renderEnv(); 
    _currentBonusValue = calculateBonusForHero();

}

std::tuple<double,bool,tensor&> ReLeMesh::AbstractEnvironment::step(const unsigned action)
{
    auto [northWest,northEast,newHero] = convertStepInput(action);
    if(_objects.empty()){
        std::cout << "empty"<< std::endl;
        throw "No objects created in environment";
    }
    _actions.push_back(action);
    if(_done){    
        return {0.0,_done,_state};
    }

    if(newHero){        
        saveHeroAsWall(); 
        if(_useCenterOfFocus){
            pushToFrontStarterObjectNearestToPoint(_centerOfFocus); // TODO: function does nothing
        }
        if(!_startObjects.empty() && _nHeros < getMaxNumberOfHeros() ){
            _objects.push_back(createNewHero());
            ++_nHeros;
        } else {
            _done = true;
        }
    } else {
        getHero()->changeNorthEast(northEast);
        getHero()->changeNorthWest(northWest);
    }
    resizeObjToFitEnv(getHero());
    
    if(newHero) {
        _currentBonusValue = 0;
    }
    renderEnv(); // TODO: Only do a light render if it is not a new hero.
    // TODO create reward class ?

    double reward = -0.5;
    double newBonusValue = calculateBonusForHero();
    reward += newBonusValue - _currentBonusValue;
    _currentBonusValue = newBonusValue;
    reward =  reward / _bonusNormalisationValue;
    _totalReward += reward;
    
    return {reward,_done,_state};
}

double ReLeMesh::AbstractEnvironment::calculateBonusForHero() const
{
    auto idealArea = getIdealObjectArea(getHero()->getCenterPoint());// atm ideal area is not a function of the coordinates
    auto actualArea = getHero()->calculateArea();
    auto newBonusValue = actualArea;
    newBonusValue -= pow(abs(actualArea-idealArea),1.5);

    newBonusValue -= countOverlappingPixels()*_overlappingPixelPenalty;
    newBonusValue += calculateFinishedObjectBonus();
    return 0.0;
}

void ReLeMesh::AbstractEnvironment::setWorldGenerator(
    std::unique_ptr<AbstractWorldGenerator> generator){
    _worldGenerator = std::move(generator);
}
void ReLeMesh::AbstractEnvironment::setCenterOfFocus(const array1dInt envSize) 
{
    // def setCenterOfFocus(self,newCenterOfFocus):
    //     self._useCenterOfFocus = True
    //     self._centerOfFocus = newCenterOfFocus
} // TODO

const tensor& ReLeMesh::AbstractEnvironment::getState() const 
{
    return _state;
}

void ReLeMesh::AbstractEnvironment::printState() const 
{
    for(auto& matrix : _state){
        for(int j = int(matrix.front().size()-1); j >= 0; --j){
            for(size_t i = 0; i < matrix.size(); ++i){
                std::cout << matrix[i][j] << " ";
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }
}

integer ReLeMesh::AbstractEnvironment::getSizeX() const 
{
    return _size[0];
}

integer ReLeMesh::AbstractEnvironment::getSizeY() const 
{ 
    return _size[1];
}

integer ReLeMesh::AbstractEnvironment::getActionCount() const 
{ 
    return _actions.size();
}

integer ReLeMesh::AbstractEnvironment::getChannelCount() const 
{
    return 2;
}

std::unique_ptr<AbstractObject>& ReLeMesh::AbstractEnvironment::getHero() 
{
    return _objects.back();
} 

const std::unique_ptr<AbstractObject>& ReLeMesh::AbstractEnvironment::getHero() const 
{
    return _objects.back();
} 

integer ReLeMesh::AbstractEnvironment::countOverlappingPixels() const
{ 
    integer count = 0;
    for(auto& matrix: _state){
        for(auto& vector: matrix){
            for(auto& value: vector){
                if(value > 0.0 && value < 0.6){
                    count++;
                }
            }
        }
    }
    return count;
} // Move to analyser class ?

double ReLeMesh::AbstractEnvironment::calculateFinishedObjectBonus() const 
{ 
    auto northWest = getHero()->getNorthWest();
    auto northEast = getHero()->getNorthEast();
    double reward = 0.0;
    auto northWestValue = _state[1][northWest[0]][northWest[1]];
    auto northEastValue = _state[1][northEast[0]][northEast[1]];
    if(northWestValue == 1.0){
        reward += _cornerMatchBonus;
    } else if(northWestValue > 0.0){
        reward -= _cornerMatchBonus;
    }
    if(northEastValue == 1.0){
        reward += _cornerMatchBonus;
    } else if(northEastValue > 0.0){
        reward -= _cornerMatchBonus;
    }
    return reward;

}// Move to analyser class ?

void ReLeMesh::AbstractEnvironment::renderEnv()
{ 
    _render.renderEnv(_objects,_state);
} 

void ReLeMesh::AbstractEnvironment::resizeObjToFitEnv(std::unique_ptr<AbstractObject>& object)
{
    auto northWest = object->getNorthWest();
    auto northEast = object->getNorthEast();

    std::vector<std::tuple<integer&,integer>> valueSet; // value, maximum value
    valueSet.push_back(std::make_tuple(std::ref(northWest[0]),_size[0]));
    valueSet.push_back(std::make_tuple(std::ref(northWest[1]),_size[1]));
    valueSet.push_back(std::make_tuple(std::ref(northEast[0]),_size[0]));
    valueSet.push_back(std::make_tuple(std::ref(northEast[1]),_size[1]));
    
    for (auto& [value, max] : valueSet) {
        if (value >= max){
            value = max-1;
        } else if (value < 0){
            value = 0;
        }
    }
    object->setNorthEast(northEast);
    object->setNorthWest(northWest);
}// Move to environment handler class ?

void ReLeMesh::AbstractEnvironment::saveHeroAsWall()
{
    getHero()->setRole(AbstractObject::Role::Active);
    if(_nHeros > 0){
        convertHeroToStartObjects();
    }    
}// Move to environment handler class ?

void ReLeMesh::AbstractEnvironment::pushToFrontStarterObjectNearestToPoint(const array1dInt point1) 
{ 
    //TODO

    // def pushToFrontStarterObjectNearestToPoint(self, coord):
    //     x, y = coord
    //     nObjs = len(self.startObjects)
    //     if nObjs < 2:
    //         return
    //     nearestObj = 0
    //     smallestDistance =  math.inf
    //     for i in range(nObjs):
    //         (xObj,yObj) = self.startObjects[i].getCenterPoint()
    //         distance = math.sqrt((xObj-x)**2+(yObj-y)**2 )
    //         if distance < smallestDistance:
    //             nearestObj = i
    //             smallestDistance = distance
    //     self.startObjects.insert(0, self.startObjects.pop(nearestObj))

} // Move to environment handler class ?
