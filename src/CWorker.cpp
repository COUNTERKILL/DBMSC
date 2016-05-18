#include "CWorker.h"
#include <cmath>

CWorker::CWorker(std::size_t id, float perfomance):
                    CNode(id),
                    m_perfomance(perfomance)
{
    CWorker::m_count++;
    CWorker::m_workers.push_back(id);
}


TIME CWorker::Process()
{
    if(!m_queryExecuted)
    {
        m_queryExecuted = true;
        // Calculate join time
        std::size_t nextRelationSize = Config::GetRelationSize(m_step) / m_count;
        TIME joinTime = m_currentIndexSize + nextRelationSize;
        // sending packets
        for(auto& id : CWorker::m_workers)
        {
            std::size_t packetWidth = m_currentIndicesCount + Config::GetIndicesAddition(m_step);
            std::size_t resSize = Config::GetResultSize(m_step) / CWorker::m_count;
            std::size_t packetLength = resSize / CWorker::m_count;
            SendPacket(std::move(CPacket(m_id, id, packetWidth, packetLength)));
        }
        m_currentIndicesCount = packetWidth;
        m_currentIndexSize = packetLength * m_count;
        return joinTime;
    }
    if(m_packetsReceivedCount == CWorker::count) // packets from all nodes received
    {
        if(m_sortExecuted)
            return 0;
        else
        {
            std::size_t PCTSize = m_currentIndexSize;
            m_sortExecuted = true;
            return std::size_t(std::log2(float(PCTSize)));
        };
            
    }
    else
        return 0;
    
}

TIME CWorker::SendPacket(CPacket&& packet)
{
    m_parent->ReceivePacket(std::move(CPacket(m_id, id, packetWidth, packetLength)));
    return 0;
}

void CWorker::StartStep()
{
    CNode::StartStep();
    m_queryExecuted         = false;
    m_sortExecuted          = false;
    m_packetsReceivedCount  = 1;
    return;
}