#include "Basic2dEnvironmentRender.hh"
#include <iostream>
#include <math.h>
#include <algorithm>

using ReLeMesh::integer;
using ReLeMesh::array1dInt;

ReLeMesh::Basic2dEnvironmentRender::Basic2dEnvironmentRender(const std::array<integer,2> envSize) :
_sizeX(envSize[0]), _sizeY(envSize[1])
{
    _roleChannels[AbstractObject::Role::Active] = 0;
    _roleChannels[AbstractObject::Role::Locked] = 1;
    _roleChannels[AbstractObject::Role::PreDefined] = 1;
}

ReLeMesh::Basic2dEnvironmentRender::Basic2dEnvironmentRender(const int test) :
_sizeX(1), _sizeY(1)
{
    _roleChannels[AbstractObject::Role::Active] = 0;
    _roleChannels[AbstractObject::Role::Locked] = 1;
    _roleChannels[AbstractObject::Role::PreDefined] = 1;
}

ReLeMesh::Basic2dEnvironmentRender::Basic2dEnvironmentRender() :
_sizeX(1), _sizeY(1)
{
    _roleChannels[AbstractObject::Role::Active] = 0;
    _roleChannels[AbstractObject::Role::Locked] = 1;
    _roleChannels[AbstractObject::Role::PreDefined] = 1;
}

std::vector<array1dInt> ReLeMesh::Basic2dEnvironmentRender::computePixelsFromLine(
    const array1dInt point1, const array1dInt point2)
{
    integer lengthX = point2[0]-point1[0];
    integer lengthY = point2[1]-point1[1];

    integer lengthMax = std::max(abs(lengthX),abs(lengthY));

    integer xOdd = (lengthX % 2 != 0 );
    integer yOdd = (lengthY % 2 != 0 );
    integer maxOdd = (lengthMax % 2 != 0 );
    integer firstSection = int( maxOdd ? lengthMax/2 : (lengthMax-1)/2);

    std::vector<array1dInt> pixels = {{point1[0],point1[1]}};
        
    for(integer i = 0; i < lengthMax; ++i){
        std::vector<integer> x = valueLeft(i,point1[0],point2[0],lengthMax);
        std::vector<integer> y = valueLeft(i,point1[1],point2[1],lengthMax);

        pixels.push_back({x[0],y[0]});
        integer xLen = x.size();
        integer yLen = y.size();
        if(xLen == 2 ){
            if(yLen == 1){
                pixels.push_back({x[1],y[0]});
            } else if (yLen == 2) {
                pixels.push_back({x[1],y[1]});
            } 
        } else if(xLen == 1 && yLen == 2){
            pixels.push_back({x[0],y[1]});
        }
  
        pixels.push_back({point2[0],point2[1]});
    }
    for(auto& pixel : pixels){
        std::cout << "Pixel: " << pixel[0] << "," << pixel[1] << std::endl;
    }   
    return pixels;
}

bool ReLeMesh::Basic2dEnvironmentRender::renderObject(
    const std::unique_ptr<AbstractObject>& object, std::vector<std::vector<float>>& channelState)
{
    // assert(channelState.size() == _sizeX);
    // for(auto& vec : channelState){
    //     assert(channelState.size() == _sizeX);
    // }
    float intensity = 1;
    // object.intensity = 0.75
    auto southWestCorner = object->getSouthWest();
    auto southEastCorner = object->getSouthEast();
    auto northWestCorner = object->getNorthWest();
    auto northEastCorner = object->getNorthEast();
    
    std::cout << southWestCorner[0] << std::endl;
    std::cout << southWestCorner[1] << std::endl;
    std::cout << southEastCorner[0] << std::endl;
    std::cout << southEastCorner[1] << std::endl;
    std::cout << northWestCorner[0] << std::endl;
    std::cout << northWestCorner[1] << std::endl;
    std::cout << northEastCorner[0] << std::endl;
    std::cout << northEastCorner[1] << std::endl;
        // auto northEastCornerX
        // auto northEastCornerY) = object.getNorthEast()
    
    auto pixelsSouth = computePixelsFromLine(southEastCorner,southWestCorner);
    auto pixelsWest = computePixelsFromLine(southWestCorner,northWestCorner);
    auto pixelsNorth = computePixelsFromLine(northEastCorner,northWestCorner);
    auto pixelsEast = computePixelsFromLine(southEastCorner,northEastCorner);
        
    // if(object->getRole() == AbstractObject::Role::Active){
    //         bool  wrongMove = false;
            // TODO Find way to replace this
            // if [northWestCornerX,northWestCornerY] in pixelsWest[:-1]:
            //     wrongMove = True
            // elif [northWestCornerX,northWestCornerY] in pixelsEast[:-1]:
            //     wrongMove = True
            // elif [northEastCornerX,northEastCornerY] in pixelsWest[:-1]:
            //     wrongMove = True
            // elif [northEastCornerX,northEastCornerY] in pixelsEast[:-1]:
            //     wrongMove = True
            // if wrongMove:
            //     return [False, 0]
// }
            
    for(auto& pixel : pixelsWest){
        std::cout << "Pixel W: " << pixel[0] << "," << pixel[1] << std::endl;
        channelState[pixel[0]][pixel[1]] = intensity;
    }
    for(auto& pixel : pixelsNorth){
        std::cout << "Pixel N: " << pixel[0] << "," << pixel[1] << std::endl;
        channelState[pixel[0]][pixel[1]] = intensity;
    }  
    for(auto& pixel : pixelsEast){
        // std::cout << "Pixel E: " << pixel[0] << "," << pixel[1] << std::endl;
        channelState[pixel[0]][pixel[1]] = intensity;
        }               
    for(auto& pixel : pixelsSouth){
        std::cout << "Pixel S: " << pixel[0] << "," << pixel[1] << std::endl;
        channelState[pixel[0]][pixel[1]] = intensity;
    }
    if(object->getRole() == AbstractObject::Role::Active){
        channelState[pixelsWest[0][0]][pixelsWest[0][1]] = 1.0;
        channelState[pixelsEast[0][0]][pixelsEast[0][1]] = 1.0;
    }

    channelState[pixelsWest.back()[0]][pixelsWest.back()[1]] = 1;
    channelState[pixelsEast.back()[0]][pixelsEast.back()[1]] = 1;
    
    return true;
}
bool ReLeMesh::Basic2dEnvironmentRender::renderEnv(
    const std::vector<std::unique_ptr<AbstractObject>>& objects, 
    std::vector<std::vector<std::vector<float>>>& state)
{
    int channels = 2;
    state = std::vector<std::vector<std::vector<float>>>(channels,
    std::vector<std::vector<float>>(_sizeX,std::vector<float>(_sizeY)));
    // TODO Optimize
    // TODO idea. do vec vec of usigned int 

    for(auto& object : objects){
        bool ok = renderObject(
            object,state[_roleChannels[object->getRole()]]);
        if(!ok){
            state.clear();
            std::cout << "Failed to render" << std::endl;
            return false;
        }
    }
    return true;
}

array1dInt ReLeMesh::
Basic2dEnvironmentRender::calculateXYmoveUnitVector(const array1dInt point1,const array1dInt point2)
{
    integer xDiff = point2[0]-point1[0];
    integer yDiff = point2[1]-point1[1]; 
    integer xMove, yMove;
    if (abs(xDiff) > abs(yDiff)){
        xMove = 0;
        if(xDiff != 0){
            yMove = -int(xDiff/abs(xDiff));
        } else {
            yMove = 0;
        }
    }
    else {
        yMove = 0;
        if(yDiff != 0){
            xMove = int(yDiff/abs(yDiff));
        } else {
            xMove = 0;
        }
    }
    return {xMove,yMove};
}

std::vector<integer> ReLeMesh::Basic2dEnvironmentRender::valueLeft(
    const integer index,const integer minValue,
    const integer maxValue,const integer maxIndex)
{
    integer direction, difference = maxValue - minValue;
    if(difference < 0){
        direction = -1;
    }
    else{
        direction = 1;
    }
    
    bool maxIndexOdd = ((maxIndex+1) % 2 != 0 );
    bool differenceOdd = ((difference+1) % 2 != 0 );     
    integer midSectionIndex = integer(maxIndex/2);
    integer valueSectionSize = integer(abs(difference)/2);
    integer value = -1;
    if (index == midSectionIndex){ //#Middsection
        if(maxIndexOdd && differenceOdd){
            value = minValue+valueSectionSize*direction;
            }
        else if(maxIndexOdd){
            value = minValue+valueSectionSize*direction;
            return {value,value+direction};
            }
        else{
            value = minValue+valueSectionSize*direction; 
            }
    } else if (index < midSectionIndex){
        if(index < valueSectionSize ){
            value = minValue + index*direction;
            }
        else{
            value = minValue + valueSectionSize*direction;
            }
    } else if (index >= midSectionIndex){
        if(index > maxIndex - valueSectionSize ){
            value = maxValue - (maxIndex - index)*direction;
        }
        else{
            value = maxValue - valueSectionSize*direction;
            }
    }
    return {value}; 
}