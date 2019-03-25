from ctypes import *

reLeMeshLib = CDLL('./bin/ReLeMeshInterface.so')

reLeMeshLib.createTriMeshEnvironment.restype = c_void_p
reLeMeshLib.deleteEnvironment.restype = None
reLeMeshLib.step.restype = None
reLeMeshLib.getSizeX.restype = c_int
reLeMeshLib.getSizeY.restype = c_int
reLeMeshLib.getChannelCount.restype = c_int

reLeMeshLib.step.argtypes = [c_void_p,c_int,POINTER(c_float)]

testTriEnv = reLeMeshLib.createTriMeshEnvironment(10,10)
xSize = reLeMeshLib.getSizeX(testTriEnv)
ySize = reLeMeshLib.getSizeY(testTriEnv)
nChannels = reLeMeshLib.getChannelCount(testTriEnv)
data = (c_float*(ySize*xSize*nChannels))()
reLeMeshLib.step(testTriEnv,0,data)
reLeMeshLib.deleteEnvironment(testTriEnv)
index = 0
for i in range(nChannels):
    for j in range(xSize):
        myString = "E  "
        for k in range(ySize):
            myString += str(int(data[index])) + " "
            index += 1
        print(myString)
    print("\n\n")