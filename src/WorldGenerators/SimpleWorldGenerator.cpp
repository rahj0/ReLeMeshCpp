#include "SimpleWorldGenerator.hh"
#include <memory>
#include <vector>
#include <iostream>


ReLeMesh::SimpleWorldGenerator::SimpleWorldGenerator()
{
    _nHorisontalLines = 2;
    _nVerticalLines = 2;
}
std::vector<std::unique_ptr<ReLeMesh::AbstractObject>> 
ReLeMesh::SimpleWorldGenerator::generate(const std::array<integer,2> envSize)
{
        integer minX = 0;
        integer minY = 0;
        integer worldSizeX = envSize[0];
        integer worldSizeY = envSize[1];
        integer maxX = worldSizeX - 1;
        integer maxY = worldSizeY - 1;
        std::vector<std::unique_ptr<AbstractObject>> objects;
        // TODO: Add checks that worldSizeX is bigger than _maxDeviations for x and y
        
        integer baseXLineLength = int(worldSizeX/_nHorisontalLines);
        integer baseYLineLength = int(worldSizeY/_nVerticalLines);

        integer lastX = minX;
        integer lastY = minY;
        
        integer southWestX = lastX;
        integer southWestY = lastY;
        
        // TODO: This code has been taken from the python project and converted directly.
        //       Next step is to split it up in to functions to get rid of the code duplication.

        for(integer i = 0; i <_nHorisontalLines; ++i){
            std::cout << "Test1" << i << std::endl;
            integer newX = lastX + baseXLineLength;
            if(i == _nHorisontalLines-1){
                newX = maxX;
            }
            else{
                //TODO // newX += generateRandomDeviation(-self._maxDeviationX,self._maxDeviationX)
            }
            integer newY = minY; //TODO + self.generateRandomDeviation(0,self._maxDeviationX)
            
            _startObjects.push_back(LineObject({lastX,lastY},{newX,newY},AbstractObject::PreDefined));
            objects.push_back(std::make_unique<LineObject>(_startObjects.back()));
            lastY = newY;
            lastX = newX;
        }

        integer southEastX = lastX;
        integer southEastY = lastY;
        lastX = southWestX;
        lastY = southWestY;
        
        //# print("southWest to northWest")
        //#### Y 
        integer northWestX, northWestY;
        if(true){ //TODO 
            for(integer i = 0; i <_nVerticalLines; ++i){
                std::cout << "Test2" << i << std::endl;
                integer newY = lastY + baseYLineLength;
                if(i == _nVerticalLines-1){
                    newY = maxY;
                }
                else{
                    // newY += self.generateRandomDeviation(-self._maxDeviationY,self._maxDeviationY);
                }
                integer newX = minX;// TODO + self.generateRandomDeviation(0,self._maxDeviationX)
                _startObjects.push_back(LineObject({lastX,lastY},{newX,newY},AbstractObject::PreDefined)); // TODO: Add 
                objects.push_back(std::make_unique<LineObject>(_startObjects.back()));
                lastY = newY;
                lastX = newX; 
    
            northWestX = lastX;
            northWestY = lastY;
            }
        }
        else{
            northWestX = minX;
            northWestY = maxY;
            lastX = northWestX;
            lastY = northWestY;
        }
        integer northEastX, northEastY;
        if(true){
            //# print("northWest to northEast")
            for(integer i = 0; i <_nHorisontalLines; ++i){

                std::cout << "Test3" << i << std::endl;
                integer newX = lastX + baseXLineLength;
                if(i == _nHorisontalLines-1){
                    newX = maxX;
                }
                else{
                    //newX += self.generateRandomDeviation(-self._maxDeviationX,self._maxDeviationX)
                }
                integer newY = maxY; //TODO - self.generateRandomDeviation(0,self._maxDeviationX)
                

                _startObjects.push_back(LineObject({lastX,lastY},{newX,newY},AbstractObject::PreDefined));
                objects.push_back(std::make_unique<LineObject>(_startObjects.back()));
                lastY = newY;
                lastX = newX;   
            }
            northEastX = lastX;
            northEastY = lastY;


        lastX = southEastX;
        lastY = southEastY;
        }
        if(true){
        //# print("southEast to northEast")    
            for(integer i = 0; i <_nHorisontalLines; ++i){

                std::cout << "Test4" << i << std::endl;
                integer newY = lastY + baseYLineLength;
                integer newX = maxX; // TODO - self.generateRandomDeviation(0,self._maxDeviationX)
                if(i == _nVerticalLines-1){
                    newY = northEastY;
                    newX = northEastX;
                }
                else{
                    // newY += self.generateRandomDeviation(-self._maxDeviationY,self._maxDeviationY)
                }
                
                _startObjects.push_back(LineObject({lastX,lastY},{newX,newY},AbstractObject::PreDefined));
                objects.push_back(std::make_unique<LineObject>(_startObjects.back()));
                lastY = newY;
                lastX = newX;   
        }
    }
    return objects;
}