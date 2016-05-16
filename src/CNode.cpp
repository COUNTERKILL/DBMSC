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

void CNode::AddChild(CNodePtr pNode)
{
	m_children.push_back(pNode);
	pNode->SetParent(this);
}


void CNode::SetParent(CNode* pNode)
{
	m_parent = pNode;
}