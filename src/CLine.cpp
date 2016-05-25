#include "CLine.h"
#include <cmath>

CLine::CLine(std::size_t id, float weight):
                    CNode(id),
                    m_weight(weight)
{
   
}


TIME CLine::Process()
{
    TIME maxTime = 1;
    if(m_packets.size() > 0)
    {
        std::size_t packetsNeedToSend = m_weight / m_packets.begin()->GetWidth();
       // std::cout << "Packets count in " << m_id << ": " << m_packets.size() << "need to send: " << packetsNeedToSend <<  std::endl;
        for(auto& childNode : m_children)
        {
            auto pPacket = m_packets.begin();
            while(pPacket != m_packets.end())
            {
                if(childNode->FindNode(m_id, pPacket->GetDst()))
                {
                    if(packetsNeedToSend)
                    {
                        auto rpacket = *pPacket;
                        pPacket = m_packets.erase(pPacket);
                        SendPacket(std::move(rpacket), childNode.get());
                        packetsNeedToSend--;
                    }
                }
                pPacket++;
            }
        }
    }
    if(m_packets.size() > 0)
    {
        std::size_t packetsNeedToSend = m_weight / m_packets.begin()->GetWidth();
       // std::cout << "Packets count in " << m_id << ": " << m_packets.size() << "need to send: " << packetsNeedToSend <<  std::endl;
        auto pPacket = m_packets.begin();
        while(pPacket != m_packets.end())
        {
            //std::cout << pPacket->GetDst() << std::endl;
            if(m_parent->FindNode(m_id, pPacket->GetDst()))
            {
                if(packetsNeedToSend)
                {
                    //std::cout << packetsNeedToSend << std::endl;
                    auto rpacket = *pPacket;
                    pPacket = m_packets.erase(pPacket);
                    //std::cout << "Packets count in " << pPacket << ": " << m_packets.size() << "need to send: " << packetsNeedToSend <<  std::endl;
                    SendPacket(std::move(rpacket), m_parent);
                    packetsNeedToSend--;
                }
            }
            pPacket++;
        }
    }
    maxTime = std::max(ProcessChildren(), maxTime);
    return maxTime;
}

TIME CLine::SendPacket(CPacket&& packet, CNode* pNode)
{
   //std::cout << pNode->GetId() << std::endl;
    pNode->ReceivePacket(std::move(packet));
    TIME time = packet.GetWidth() * packet.GetLength() / m_weight;
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