#include "CDBMSC.h"
#include <thread>
#include <chrono>

using namespace std;

TIME CDBMSC::Query()
{
  TIME queryTime = 0;
    std::cout << CWorker::coordinatorId << std::endl;
  for(int step = 0; step < m_stepsCount; step++)
  {
    //std::cout << "\tstep: " << step << std::endl;
    TIME sum = 0;
    int iter = 0;
    m_tree.StartStep();
    do
    {
     // std::this_thread::sleep_for(std::chrono::milliseconds(100));
     // std::cout << "\tetap: " << step << std::endl;
      TIME allStepTime = 0;
      allStepTime = m_tree.Process();
      if(iter!=0)
          sum += allStepTime;
      iter++;
      //std::cout << "step time: " << allStepTime << std::endl;
      queryTime += allStepTime;
      //std::cout << "Sum: " << sum << std::endl;
    } while(!m_tree.WorkIsEmpty());
    std::cout << "Sum: " << sum << std::endl;
  }
  return queryTime;
}


void CDBMSC::Initialize(std::string fileNameDchTree)
{
    m_tree.LoadFromFile(fileNameDchTree);
    m_stepsCount = 1;
}