#ifndef ReLeMesh_ABSTRACT_WORLD_GENERATOR_H
#define ReLeMesh_ABSTRACT_WORLD_GENERATOR_H

#include<array>
#include<vector>
#include<memory>

#include "../gameObjects/AbstractObject.hh"

namespace ReLeMesh
{
    class AbstractWorldGenerator 
    {
    public:

        AbstractWorldGenerator();
        integer generateRandomDeviation(const integer minDeviation, const integer maxDeviation ) const;
        virtual std::vector<std::unique_ptr<AbstractObject>> generate(const std::array<integer,2> envSize) = 0;
        // def getObjects(); // 
        // def getStartObjects():
        double getIdealAverageSquareArea();
        //def generateBorder(self,minX, minY, maxX, maxY, cornerMovement = [[0,0],[0,0],[0,0],[0,0]]):


      };
}

#endif

// class AbstractMeshWorldGenerator(ABC):
//     def __init__(self, deviationProbability):
//         if deviationProbability < 1:
//             deviationProbability *= 100.0
//         self._deviationProbability = deviationProbability
//         self._objects = []
//         self._startObjects = []
//         self._idealAverageSquareArea = 0.0
        
//     def generateRandomDeviation(self,minDeviation, maxDeviation ):
//         if int(random.randint(0, 100)) < int(self._deviationProbability):
//             return random.randint(minDeviation, maxDeviation)
//         return 0
    
//     def getObjects(self):
//         return self._objects
    
//     def getStartObjects(self):
//         return self._startObjects
        
//     @abstractmethod
//     def generate(self, worldSizeX, worldSizeY):
//         raise

//     def getIdealAverageSquareArea(self):
//         if self._idealAverageObjectArea <= 0.0:
//             raise
//         return self._idealAverageSquareArea

//     def generateBorder(self,minX, minY, maxX, maxY, cornerMovement = [[0,0],[0,0],[0,0],[0,0]]):
                
//         southWestX = minX + cornerMovement[0][0]
//         southWestY = minY + cornerMovement[0][1]
//         southWest = (southWestX,southWestY)
// #        print(southWest)
//         southEastX = maxX - cornerMovement[1][0]
//         southEastY = minY + cornerMovement[1][1]
//         southEast = (southEastX,southEastY)
// #        print(southEast)
//         northWestX = minX + cornerMovement[2][0]
//         northWestY = maxY - cornerMovement[2][1]   
//         northWest = (northWestX,northWestY)
// #        print(northWest)
//         northEastX = maxX - cornerMovement[3][0]
//         northEastY = maxY - cornerMovement[3][1]  
//         northEast = (northEastX,northEastY)
// #        print(northEast)
        
//         self._objects.append(lineOb((southWestX,southWestY),(southEastX,southEastY))) # south
//         self._objects.append(lineOb((northWestX,northWestY),(southWestX,southWestY))) # West
//         self._objects.append(lineOb((northEastX,northEastY),(northWestX,northWestY))) # North
//         self._objects.append(lineOb((southEastX,southEastY),(northEastX,northEastY))) # East
        
            
