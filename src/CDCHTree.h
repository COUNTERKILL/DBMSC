#pragma once

#include <vector>
#include "CNode.h"

class CDCHTree
{
	
public:
                    CDCHTree            ()                      = default;
                    ~CDCHTree           ()                      = default;
public:
                    CDCHTree            (CDCHTree&)             = delete;
                    CDCHTree            (CDCHTree&&)            = delete;
public:
                    CDCHTree& operator= (CDCHTree&)             = delete;
                    & operator=         (CDCHTree&&)            = delete;
public:
    TIME            Process             ();
public:
    void            LoadFromFile        (std::string fileName);
public:
    CNode&          FindNode            (size_t id);
    void            AddNode             (CNode::CNodePtr pNode, 
                                         size_t parentId);
private:
    CNode::CNodePtr 	m_rootNode  = nullptr;
};
