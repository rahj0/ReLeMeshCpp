#include <boost/test/unit_test.hpp>
#include <memory>
#include<iostream>
#include <tuple>
#include <vector>
#include <map>

#include "../gameObjects/AbstractObject.hh"
#include "../gameObjects/LineObject.hh"
#include "../gameObjects/TriangleObject.hh"
#include "../Environments/Rendering/Basic2dEnvironmentRender.hh"

using ReLeMesh::TriangleObject;
using ReLeMesh::coordinate;
using ReLeMesh::integer;
using std::unique_ptr;
using std::cout; using std::endl; using std::vector;

BOOST_AUTO_TEST_CASE( Basic2dEnvironmentRender_test )
{
    std::cout << "Basic2dEnvironmentRender Unit Test" << std::endl;
    int size = 10;
    std::vector<std::unique_ptr<ReLeMesh::AbstractObject>> objects; 
    coordinate p11 {0,1}; 
    coordinate p12 {8,0}; 
    coordinate p13 {5,1};
    coordinate p14 {8,1};

    coordinate p21 {7,7};
    coordinate p23 {9,3};

    objects.push_back(std::unique_ptr<TriangleObject>(
        new TriangleObject(p11,p12,p21, TriangleObject::Role::Active)));
    objects.push_back(std::unique_ptr<TriangleObject>(
        new TriangleObject(p13,p14,p23, TriangleObject::Role::PreDefined)));

    ReLeMesh::Basic2dEnvironmentRender envRender({size,size});
    vector<vector<vector<float>>> state;

    envRender.renderEnv(objects,state);

    vector<std::tuple<coordinate,TriangleObject::Role>> tests;

    // Check that pixels, matching these points, are not zero anymore
    tests.push_back({ p11, TriangleObject::Role::Active });
    tests.push_back({ p12, TriangleObject::Role::Active });
    tests.push_back({ p21, TriangleObject::Role::Active });
    tests.push_back({ p13, TriangleObject::Role::PreDefined });
    tests.push_back({ p14, TriangleObject::Role::PreDefined });
    tests.push_back({ p23, TriangleObject::Role::PreDefined });
    
    for(auto& [point, role] : tests){
        auto channel = envRender.getRoleChannel(role);
        BOOST_CHECK(state[channel][point[0]][point[1]] != 0.0);
    }
}