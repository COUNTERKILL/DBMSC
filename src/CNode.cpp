#include "CNode.h"
#include <algorithm>


TIME 	CNode::ProcessChildren()
{
	TIME maxTime = 0;
	for(auto& pChildNode : m_children)
	{
		TIME currentTime = pChildNode->Process();
		maxTime = std::max(maxTime, currentTime);
	}
	return maxTime;
}

void CNode::AddChild(CNode* node)
{
	m_children.push_back(node);
}


void CNode::SetParent(CNode* node)
{
	m_parent = node;
}