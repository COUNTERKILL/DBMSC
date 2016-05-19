#include "CSwitch.h"
#include <cmath>

CSwitch::CSwitch(std::size_t id, std::size_t weight):
                    CNode(id),
                    m_weight(weight)
{
   
}


TIME CSwitch::Process()
{
    TIME maxTime = 0;
    for(auto& childNode : m_children)
    {
        for(auto pPacket = m_packets.begin(); pPacket != m_packets.end(); pPacket++)
        {
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
        if(m_parent->FindNode(m_id, pPacket->GetDst()))
        {
            auto rpacket = *pPacket;
            m_packets.erase(pPacket);
            maxTime = std::max(SendPacket(std::move(rpacket), m_parent), maxTime);
            break;
        }
    }
    maxTime = std::max(ProcessChildren(), maxTime);
    return maxTime;
}

TIME CSwitch::SendPacket(CPacket&& packet, CNode* pNode)
{
    pNode->ReceivePacket(std::move(packet));
    TIME time = packet.GetWidth() * packet.GetLength() * m_weight;
    return time;
}

void CSwitch::StartStep()
{
    CNode::StartStep();
    return;
}

