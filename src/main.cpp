#include <thread>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <thread>
#include "CDBMSC.h"

using namespace std;


int main(int argc, char** argv)
{
    try
    {
        size_t vecSize = 0;
        CDBMSC dbmsc;
        dbmsc.Initialize("media/tree.xml");
        std::cout << "Query time: " << dbmsc.Query() << std::endl;
    }
    catch(const char* errStr)
    {
        cout << errStr << endl;
    }
    return 0;
}
