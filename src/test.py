from ctypes import *

print("Start of python with c++ interface test")

reLeMeshLib = CDLL('./bin/ReLeMeshInterface.so')

reLeMeshLib.createTriMeshEnvironment.restype = c_void_p
reLeMeshLib.deleteEnvironment.restype = None
reLeMeshLib.step.restype = None
reLeMeshLib.getSizeX.restype = c_int
reLeMeshLib.getSizeY.restype = c_int
reLeMeshLib.getChannelCount.restype = c_int

print("Try to create tri mesh environment")
testTriEnv = reLeMeshLib.createTriMeshEnvironment(10,10)

print("Created tri mesh environment")

xSize = reLeMeshLib.getSizeX(testTriEnv)
print("Got Horisontal Size: ", xSize )
ySize = reLeMeshLib.getSizeY(testTriEnv)
print("Got verticaltal Size: ", ySize )
nChannels = reLeMeshLib.getChannelCount(testTriEnv)
data = (c_float*(ySize*xSize*nChannels))()
dataFromGetState = (c_float*(ySize*xSize*nChannels))()
reward = c_float()
done = c_bool()

reLeMeshLib.step(testTriEnv,0,byref(reward),byref(done),data)


print("Reward: ", reward.value)
if done:
    status = "Running"
else:
    status = "Finished"
print("Status: ", status)


reLeMeshLib.getState(testTriEnv,dataFromGetState)
print("Maximum number of heroes: ", reLeMeshLib.getMaxNumberOfHeros(testTriEnv))
print("action count: ", reLeMeshLib.getActionCount(testTriEnv))

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

print("Python with c++ interface test finished succesfully")