#include "CWorker.h"
#include "Config.h"
#include <cmath>


std::size_t CWorker::coordinatorId  = 0;
std::vector<std::size_t> CWorker::workers      = std::vector<std::size_t>();


CWorker::CWorker(std::size_t id, float perfomance):
                    CNode(id),
                    m_perfomance(perfomance)
{
    CWorker::workers.push_back(id);
}


TIME CWorker::Process()
{
    if(!m_queryExecuted)
    {
        m_queryExecuted = true;
        if(m_step == 1)
        {
            m_currentIndicesCount = 1;
            std::size_t firstRelationSize = Config::GetRelationSize(0) / CWorker::workers.size();
            m_currentIndexSize = firstRelationSize;
        }
        // Calculate join time
        std::size_t nextRelationSize = Config::GetRelationSize(m_step) / CWorker::workers.size();
        TIME joinTime = m_currentIndexSize + nextRelationSize;
        joinTime /= m_perfomance;
        // sending packets
        if(m_step == Config::GetStepsCount()) // need send to coordinator
        {
            std::size_t packetWidth = m_currentIndicesCount + Config::GetIndicesAddition(m_step);
            std::size_t resSize = Config::GetResultSize(m_step) / CWorker::workers.size();
            std::size_t packetLength = resSize;
            SendPacket(std::move(CPacket(m_id, CWorker::coordinatorId, packetWidth, packetLength)), m_parent);
        }
        else
        {
            std::size_t packetWidth = m_currentIndicesCount + Config::GetIndicesAddition(m_step);
            std::size_t resSize = Config::GetResultSize(m_step) / CWorker::workers.size();
            for(auto& id : CWorker::workers)
            {
                for(std::size_t i = 0; i < resSize/CWorker::workers.size(); i++)
                {
                    std::size_t packetLength = 1;
                    SendPacket(std::move(CPacket(m_id, id, packetWidth, packetLength)), m_parent);
                }
            }
            m_currentIndicesCount = packetWidth;
            m_currentIndexSize = resSize;
        }
        //std::cout << "Hoin time: " << joinTime << std::endl;
        return joinTime;
    }
    if(m_packetsReceivedCount == (CWorker::workers.size()-1) * m_currentIndexSize) // packets from all nodes received
    {
        if(m_sortExecuted)
            return 0;
        else
        {
            std::size_t PCTSize = m_currentIndexSize;
            m_sortExecuted = true;
            return std::size_t(m_currentIndicesCount*PCTSize*std::log2(float(PCTSize))/m_perfomance);
        };
            
    }
    else
        return 0;
    
}

TIME CWorker::SendPacket(CPacket&& packet, CNode* pNode)
{
    pNode->ReceivePacket(std::move(packet));
    return 0;
}

void CWorker::ReceivePacket(CPacket&& packet)
{
    m_packetsReceivedCount++;
    return;
}

void CWorker::StartStep()
{
    CNode::StartStep();
    m_queryExecuted         = false;
    m_sortExecuted          = false;
    m_packetsReceivedCount  = 0;
    return;
}