#include "CDBMSC.h"

using namespace std;

TIME CDBMSC::Query()
{
  TIME queryTime = 0;

  for(int step = 0; step < m_stepsCount; step++)
  {
    TIME allStepTime = 0;
    do
    {
			TIME maxTime = 0;
      allStepTime = 0;
      for(size_t nodeIdx = 0; nodeIdx < m_nodes.size(); nodeIdx++)
      {
        TIME currentTime = m_nodes[nodeIdx].Process();
        allStepTime += currentTime;
        if(maxTime < currentTime)
          maxTime = currentTime;
      }
      queryTime += maxTime;
    } while(allStepTime != 0);
  }
  return queryTime;	
}


