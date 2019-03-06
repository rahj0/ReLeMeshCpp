#include<iostream>
#include<vector>

extern "C" int square(int x)
{
  return x*x;
}

class Test
{
    public:
        Test(int testNumber){_t.push_back(testNumber);}
        void hello(){std::cout << "Hello" << std::endl; }
        int test1(){return _t.front();}
        void push_back(const int t){_t.push_back(t);}
        int at(const int i){return _t.at(i);}
    private:
        std::vector<int> _t;

};

extern "C" void* getNew(int testNumber)
{
   return new Test(testNumber);
}

extern "C" int useTest(void* ptr)
{
   auto test = static_cast<Test*>(ptr);
   return test->test1();
}

extern "C" void deleteTest(void* ptr)
{
    auto test = static_cast<Test*>(ptr);
    delete test;
    std::cout << "Completed the deletion" << std::endl; 
}

extern "C" void push_back(void* ptr, int t)
{
    auto test = static_cast<Test*>(ptr);
    test->push_back(t);
}

extern "C" int atTest(void* ptr, int i)
{
    auto test = static_cast<Test*>(ptr);
    return test->at(i);
}


