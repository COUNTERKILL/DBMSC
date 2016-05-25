#include "CSwitch.h"
#include <cmath>

CSwitch::CSwitch(std::size_t id, float weight):
                    CNode(id),
                    m_weight(weight)
{
   
}


TIME CSwitch::Process()
{
    //std::cout << "Packets count in " << m_id << ": " << m_packets.size() << std::endl;
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
        if(m_parent && m_parent->FindNode(m_id, pPacket->GetDst()))
        {
            auto rpacket = *pPacket;
            m_packets.erase(pPacket);
            maxTime = std::max(SendPacket(std::move(rpacket), m_parent), maxTime);
            break;
        }
    }
    //std::cout << "Max switch time: " << maxTime << std::endl;
    //maxTime = 0;
    maxTime = std::max(ProcessChildren(), maxTime);
    return maxTime;
}

TIME CSwitch::SendPacket(CPacket&& packet, CNode* pNode)
{
    //std::cout << pNode->GetId() << std::endl;
    pNode->ReceivePacket(std::move(packet));
    TIME time = packet.GetWidth() * packet.GetLength() * m_weight;
    std::cout << "Switch sending " << packet.GetLength() << std::endl;
    return time;
}

void CSwitch::StartStep()
{
    CNode::StartStep();
    return;
}
bool CSwitch::WorkIsEmpty()
{
    if(!WorkIsEmptyChildren())
        return false;
    return (m_packets.size() == 0);
}
