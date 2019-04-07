#include <boost/test/unit_test.hpp>
#include <memory>
#include<iostream>
#include <tuple>
#include <vector>
#include <list>
#include <map>
#include "../Environments/TriMeshEnvironment.hh"

using ReLeMesh::TriMeshEnvironment;
using std::cout;
using std::endl;

namespace ReLeMesh 
{
    bool isEqual(const tensor& tensor1,const tensor& tensor2)
    {
        if(tensor1.size() != tensor2.size() ){
            return false;
        }
        bool result = true;
        for(int i = 0; i < tensor1.size(); ++i){
            if(tensor1[i].size() != tensor2[i].size() ){
                return false;
            }
            // std::cout << "i: " << i << std::endl;
            for(int j = 0; j < tensor1.at(i).size(); ++j){
                result &= std::equal(tensor1.at(i).at(j).begin(), 
                tensor1.at(i).at(j).end(), tensor2.at(i).at(j).begin());
            }
        }
        return result;
    }
}

BOOST_AUTO_TEST_CASE( TriMeshEnvironment_test )
{
    int size = 10;
    ReLeMesh::TriMeshEnvironment testEnv({size,size});
    BOOST_CHECK(testEnv.getMaxNumberOfHeros() != 0);
    BOOST_CHECK(testEnv.getActionCount() == 0);
    BOOST_CHECK(testEnv.getActionCount() == 0);

    ReLeMesh::tensor state0 = testEnv.getState();
    testEnv.step(0);

    BOOST_CHECK(testEnv.getActionCount() == 1);
    ReLeMesh::tensor state1 = testEnv.getState();
    BOOST_CHECK(!ReLeMesh::isEqual(state0,state1));
    std::list<int> actions{0,1,2,3,4,5,6,7};
    for(auto action :actions){
        for(int i = 0; i < size*3 ; ++i){  // Step enough time to reach boundary 
            testEnv.step(action);
        }
        ReLeMesh::tensor state2 = testEnv.getState();
        testEnv.step(action);
        ReLeMesh::tensor state3 = testEnv.getState();
        ReLeMesh::isEqual(state2,state3);
        BOOST_CHECK(ReLeMesh::isEqual(state2,state3));
    }
}

BOOST_AUTO_TEST_CASE( TriMeshEnvironment_newHero_test )
{
    int size = 10;
    ReLeMesh::TriMeshEnvironment testEnv({size,size});
    BOOST_CHECK(testEnv.getMaxNumberOfHeros() != 0);
    BOOST_CHECK(testEnv.getActionCount() == 0);
    ReLeMesh::tensor state0 = testEnv.getState();
    auto objCount0 = testEnv.getObjectCount();

    testEnv.step(0);
    auto objCount1 = testEnv.getObjectCount();
    BOOST_CHECK(testEnv.getActionCount() == 1);
    BOOST_CHECK(objCount0 == objCount1);
    ReLeMesh::tensor state1 = testEnv.getState();

    testEnv.step(8);
    auto objCount2 = testEnv.getObjectCount();
    BOOST_CHECK(testEnv.getActionCount() == 2);
    BOOST_CHECK(objCount2 == objCount1+1);
    ReLeMesh::tensor state2 = testEnv.getState();
    BOOST_CHECK(!ReLeMesh::isEqual(state1,state2));
}

BOOST_AUTO_TEST_CASE( TriMeshEnvironment_reset_test )
{
    int size = 10;
    ReLeMesh::TriMeshEnvironment testEnv({size,size});
    BOOST_CHECK(testEnv.getMaxNumberOfHeros() != 0);
    BOOST_CHECK(testEnv.getActionCount() == 0);

    std::list<int> actions{0,1,2,3,8,8};
    for(auto action :actions){
            testEnv.step(action);
    }
    BOOST_CHECK(testEnv.getActionCount() != 0);
    BOOST_CHECK(testEnv.getObjectCount() > 2);
    ReLeMesh::tensor state0 = testEnv.getState();
    testEnv.reset();

    BOOST_CHECK(testEnv.getActionCount() == 0);
    BOOST_CHECK(testEnv.getObjectCount() > 2);
    ReLeMesh::tensor state1 = testEnv.getState();
    BOOST_CHECK(!ReLeMesh::isEqual(state0,state1));
}

BOOST_AUTO_TEST_CASE( TriMeshEnvironment_reward_test )
{
    int size = 10;
    ReLeMesh::TriMeshEnvironment testEnv({size,size});
    BOOST_CHECK(testEnv.getMaxNumberOfHeros() != 0);
    BOOST_CHECK(testEnv.getActionCount() == 0);
    // auto [reward,done,state] = testEnv.step(action);
    double stepPenalty = 0.0, totalReward = 0.0;
    std::list<int> actions{0,1,2,3,4,5,6,7};
    for(auto action :actions){
        auto [reward,done,state] = testEnv.step(action);
        totalReward += reward;
        stepPenalty += 0.05; // this is the normalised step penalty. TODO: get rid of hard coded value
    }
    BOOST_CHECK((totalReward + stepPenalty) < 1e-8);
}