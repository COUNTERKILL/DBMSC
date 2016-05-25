#include "CLine.h"
#include <cmath>

CLine::CLine(std::size_t id, float weight):
                    CNode(id),
                    m_weight(weight)
{
   
}


TIME CLine::Process()
{
    //std::cout << "Packets count in " << m_id << ": " << m_packets.size() << std::endl;
    TIME maxTime = 0;
    for(auto& childNode : m_children)
    {
        for(auto pPacket = m_packets.begin(); pPacket != m_packets.end(); pPacket++)
        {
            //std::cout << "Line_id: " << m_id << std::endl;
            if(childNode->FindNode(m_id, pPacket->GetDst()))
            {
                auto rpacket = *pPacket;
                m_packets.erase(pPacket);
                maxTime = std::max(SendPacket(std::move(rpacket), childNode.get()), maxTime);
                break;
            }
        }
    }
    for(auto pPacket = m_packets.begin(); pPacket != m_packets.end(); pPacket++)
    {
        //std::cout << pPacket->GetDst() << std::endl;
        if(m_parent->FindNode(m_id, pPacket->GetDst()))
        {
            auto rpacket = *pPacket;
            m_packets.erase(pPacket);
            maxTime = std::max(SendPacket(std::move(rpacket), m_parent), maxTime);
            break;
        }
    }
    //std::cout << "Max time: " << maxTime << std::endl;
    maxTime = std::max(ProcessChildren(), maxTime);
    return maxTime;
}

TIME CLine::SendPacket(CPacket&& packet, CNode* pNode)
{
     //std::cout << pNode->GetId() << std::endl;
    pNode->ReceivePacket(std::move(packet));
    TIME time = packet.GetWidth() * packet.GetLength() * m_weight;
    return time;
}

void CLine::StartStep()
{
    CNode::StartStep();
    return;
}

bool CLine::WorkIsEmpty()
{
    if(!WorkIsEmptyChildren())
        return false;
    return (m_packets.size() == 0);
}