#pragma once

#include <vector>
#include "DBMSC_defs.h"

class CWorker: public CNode
{
public:
                    CWorker             (std::size_t id, float perfomance);
                    ~CWorker            ()                                  = default;
public:
                    CWorker             (CWorker&)                          = default;
                    CWorker             (CWorker&&)                         = default;
public:
                    CWorker& operator=	(CWorker&)                          = default;
                    CWorker& operator=	(CWorker&&)                         = default;
public:
    TIME            Process			    ();
public:
    TIME            SendPacket		    (CPacket&&);
public:
    void            StartStep           ();
private:
            std::size_t                 m_currentIndicesCount   = 0;
            std::size_t                 m_currentIndexSize      = 0; // for one index
            bool                        m_queryExecuted         = false;
            bool                        m_sortExecuted          = false;
            std::size_t                 m_packetsReceivedCount  = 0;
            //std::size_t               m_packetsReceivedSize = 0; // for all packets in sum
            float                       m_perfomance            = 1.0f;
    static  std::size_t                 m_count                 = 0;
    static  std::vector<std::size_t>    m_workers               = std::vector<std::size_t>();

};
