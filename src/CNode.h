#pragma once

#include <vector>
#include "DBMSC_defs.h"

class CNode
{
typedef std::shared_ptr<CNode> CNodePtr;
public:
                                        CNode           (std::size_t id)
                                                            m_id(id) {};
    virtual                             ~CNode          ()          = default;
public:
                                        CNode           (CNode&)    = default;
                                        CNode           (CNode&&)   = default;
public:
            CNode&                      operator=       (CNode&)    = default;
            CNode&                      operator=       (CNode&&)   = default;
public:
    virtual	TIME                        Process         ()          = 0;
public:
            void                        AddChild        (CNodePtr);
public:
    virtual TIME                        SendPacket      (CPacket&&) = 0;
public:
    virtual void                        StartStep       ()          { m_step++; };     
protected:
            void                        ReceivePacket   (CPacket&&);
protected:
            void                        SetParent       (CNode*);
            TIME                        ProcessChildren	();
protected:
            CNode*                      FindNode        (std::size_t searcherId, std::size_t id);
protected:
            std::size_t                 m_step      = 0;
            std::size_t                 m_id;
            CNode*                      m_parent    = nullptr;
private:
         
            std::vector<CNodePtr>       m_children;
            std::vector<CPacket>        m_packets;

            
};
