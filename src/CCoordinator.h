#pragma once

#include <vector>
#include "CNode.h"

class CCoordinator: public CNode
{
public:
                    CCoordinator        (std::size_t id, float perfomance);
                    ~CCoordinator       ()                                  = default;
public:
                    CCoordinator        (CCoordinator&)                          = default;
                    CCoordinator        (CCoordinator&&)                         = default;
public:
    CCoordinator&   operator=	        (CCoordinator&)                          = default;
    CCoordinator&   operator=	        (CCoordinator&&)                         = default;
public:
    TIME            Process			    ();
public:
    TIME            SendPacket		    (CPacket&&,CNode*);
    bool            WorkIsEmpty         ();
protected:
    virtual void                        ReceivePacket   (CPacket&&);
private:
            float                       m_perfomance            = 1.0f;
};
