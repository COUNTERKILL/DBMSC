#pragma once

#include <vector>
#include "CNode.h"

class CSwitch: public CNode
{
public:
                    CSwitch             (std::size_t id, std::size_t weight);
                    ~CSwitch            ()                                  = default;
public:
                    CSwitch             (CSwitch&)                          = default;
                    CSwitch             (CSwitch&&)                         = default;
public:
                    CSwitch& operator=	(CSwitch&)                          = default;
                    CSwitch& operator=	(CSwitch&&)                         = default;
public:
    TIME            Process			    ();
public:
    TIME            SendPacket		    (CPacket&&, CNode*);
public:
    virtual void            StartStep           ();
private:
    std::size_t     m_weight;
};
