#pragma once

#include <vector>
#include <list>
#include <memory>
#include "DBMSC_defs.h"
#include "CPacket.h"


class CNode
{
public:
typedef std::shared_ptr<CNode> CNodePtr;
public:
                                        CNode           (std::size_t id):
                                                            m_id(id) {};
    virtual                             ~CNode          ()          = default;
public:
                                        CNode           (CNode&)    = default;
                                        CNode           (CNode&&)   = default;
public:
            CNode&                      operator=       (CNode&)    = default;
            CNode&                      operator=       (CNode&&)   = default;
public:
            std::size_t                 GetId           ()          { return m_id; };
public:
    virtual	TIME                        Process         ()          = 0;
public:
            void                        AddChild        (CNodePtr);
public:
    virtual TIME                        SendPacket      (CPacket&&, CNode*) = 0;
    virtual void                        ReceivePacket   (CPacket&&);
public:
    virtual void                        StartStep       ();    
public:
            CNode*                      FindNode        (std::size_t searcherId, std::size_t id);
            CNode*                      FindNode        (std::size_t id);
public:
            void                        SetParent       (CNode*);
protected:
            TIME                        ProcessChildren	();
protected:
            std::size_t                                 m_step      = 0;
            std::size_t                                 m_id;
            CNode*                                      m_parent    = nullptr;
            std::vector<CNodePtr>                       m_children;
            std::list<CPacket>                          m_packets;          
};
