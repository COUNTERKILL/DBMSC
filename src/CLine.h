#pragma once

#include <vector>
#include "CNode.h"

class CLine: public CNode
{
public:
                    CLine               (std::size_t id, float weight);
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
    bool            WorkIsEmpty         ();
public:
    virtual void            StartStep           ();
private:
    float     m_weight;
};
