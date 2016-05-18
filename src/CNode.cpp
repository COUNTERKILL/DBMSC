#include "CNode.h"
#include <algorithm>


TIME CNode::ProcessChildren()
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

void CNode::ReceivePacket(CPacket&& packet)
{
	m_packets.push_back(std::move(packet));
	return;
}

CNode* CNode::FindNode(std::size_t searcherId, std::size_t id)
{
    if(m_id == id) return this;
    CNode *res = nullptr;
    for(auto& pNode : m_children)
    {
        if(pNode->m_id != searcherId)
            res = FindNode(this->m_id, id);
        if(res)
            return res;
    }
    if((m_parent != nullptr) && (m_parent->m_id != searcherId))
    {
        res = FindNode(this->m_id, id);
        if(res)
            return res;
    }
    return nullptr;
}