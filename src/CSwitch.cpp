#include "CSwitch.h"
#include <cmath>

CSwitch::CSwitch(std::size_t id, float weight):
                    CNode(id),
                    m_weight(weight)
{
   
}


TIME CSwitch::Process()
{
   TIME maxTime = 1;
    if(m_packets.size() > 0)
    {
        std::cout << "Packets count in " << m_id << ": " << m_packets.size() << std::endl;
        for(auto& childNode : m_children)
        {
            if(m_packets.size() > 0)
            {
                std::size_t packetsNeedToSend = m_weight / m_packets.begin()->GetWidth();
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
            else
                break;
        }
    }
    if(m_packets.size() > 0)
    {
        std::size_t packetsNeedToSend = m_weight / m_packets.begin()->GetWidth();
         auto pPacket = m_packets.begin();
         while(pPacket != m_packets.end())
         {
            //std::cout << pPacket->GetDst() << std::endl;
            if(m_parent && m_parent->FindNode(m_id, pPacket->GetDst()))
            {
                if(packetsNeedToSend)
                {
                    auto rpacket = *pPacket;
                    pPacket = m_packets.erase(pPacket);
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

TIME CSwitch::SendPacket(CPacket&& packet, CNode* pNode)
{
    //std::cout << pNode->GetId() << std::endl;
    pNode->ReceivePacket(std::move(packet));
    TIME time = packet.GetWidth() * packet.GetLength() * m_weight;
    //std::cout << "Switch sending " << packet.GetLength() << std::endl;
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
