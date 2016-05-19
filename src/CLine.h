#pragma once

#include <vector>
#include "CNode.h"

class CLine: public CNode
{
public:
                    CLine               (std::size_t id, std::size_t weight);
                    ~CLine              ()                                  = default;
public:
                    CLine               (CLine&)                          = default;
                    CLine               (CLine&&)                         = default;
public:
                    CLine& operator=    (CLine&)                          = default;
                    CLine& operator=    (CLine&&)                         = default;
public:
    TIME            Process             ();
public:
    TIME            SendPacket          (CPacket&&, CNode*);
public:
    virtual void            StartStep           ();
private:
    std::size_t     m_weight;
};
