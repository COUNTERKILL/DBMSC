#include "CDBMSC.h"

using namespace std;

TIME CDBMSC::Query()
{
  TIME queryTime = 0;

  for(int step = 0; step < m_stepsCount; step++)
  {
    TIME allStepTime = 0;
    m_tree.StartStep();
    do
    {
      allStepTime = m_tree.Process();
      queryTime += allStepTime;
    } while(allStepTime != 0);
  }
  return queryTime;
}


void CDBMSC::Initialize(std::string fileNameDchTree)
{
    m_tree.LoadFromFile(fileNameDchTree);
    m_stepsCount = 2;
}