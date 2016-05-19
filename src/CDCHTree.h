#pragma once

#include <vector>
#include "CNode.h"
#include "CWorker.h"
#include "CCoordinator.h"
#include "CSwitch.h"
#include "CLine.h"

class CDCHTree
{
	
public:
                    CDCHTree            ()                      = default;
                    ~CDCHTree           ()                      = default;
public:
                    CDCHTree            (CDCHTree&)             = delete;
                    CDCHTree            (CDCHTree&&)            = delete;
public:
    CDCHTree&       operator=           (CDCHTree&)             = delete;
    CDCHTree&       operator=           (CDCHTree&&)            = delete;
public:
    TIME            Process             ();
public:
    void            LoadFromFile        (std::string fileName);
public:
    CNode&          FindNode            (size_t id);
    void            AddNode             (CNode::CNodePtr pNode, 
                                         std::size_t parentId);
public:
    void            StartStep           ()                      { m_rootNode->StartStep(); };
private:
    CNode::CNodePtr 	m_rootNode      = nullptr;
};
