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
    if(m_packets.size() > 0)
    {
        for(auto& childNode : m_children)
        {
            if(m_packets.size() > 0)
            {
                std::size_t packetsNeedToSend = m_width / m_packets.begin()->GetWidth();
                for(auto pPacket = m_packets.begin(); pPacket != m_packets.end(); pPacket++)
                {
                    if(childNode->FindNode(m_id, pPacket->GetDst()))
                    {
                        if(packetsNeedToSend)
                        {
                            auto rpacket = *pPacket;
                            m_packets.erase(pPacket);
                            maxTime = std::max(SendPacket(std::move(rpacket), childNode.get()), maxTime);
                            packetsNeedToSend--;
                        }
                    }
                }
            }
            else
                break;
        }
    }
    if(m_packets.size() > 0)
    {
        std::size_t packetsNeedToSend = m_width / m_packets.begin()->GetWidth();
        for(auto pPacket = m_packets.begin(); pPacket != m_packets.end(); pPacket++)
        {
            //std::cout << pPacket->GetDst() << std::endl;
            if(m_parent->FindNode(m_id, pPacket->GetDst()))
            {
                if(packetsNeedToSend)
                {
                    auto rpacket = *pPacket;
                    m_packets.erase(pPacket);
                    maxTime = std::max(SendPacket(std::move(rpacket), m_parent), maxTime);
                    packetsNeedToSend--;
                }
            }
        }
    }
    
    return 1;
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

