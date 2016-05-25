#include "CLine.h"
#include <cmath>

CLine::CLine(std::size_t id, std::size_t weight):
                    CNode(id),
                    m_weight(weight)
{
   
}


TIME CLine::Process()
{
    TIME maxTime = 0;
    if(m_packets.size() > 0)
    {
        std::size_t packetsNeedToSend = m_width / m_packets.begin()->GetWidth();
        for(auto& childNode : m_children)
        {
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

TIME CLine::SendPacket(CPacket&& packet, CNode* pNode)
{
    pNode->ReceivePacket(std::move(packet));
    TIME time = packet.GetWidth() * packet.GetLength() * m_weight;
    return time;
}

void CLine::StartStep()
{
    CNode::StartStep();
    return;
}