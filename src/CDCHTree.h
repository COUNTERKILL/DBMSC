#pragma once

#include <vector>
#include "CNode.h"

class CDCHTree
{
public:
			CDCHTree				() 			= default;
			~CDCHTree				() 			= default;
public:
			CDCHTree				(CDCHTree&) 	= delete;
			CDCHTree				(CDCHTree&&) 	= delete;
public:
			CDCHTree& operator=		(CDCHTree&) 	= delete;
			CDCHTree& operator=		(CDCHTree&&) 	= delete;
public:
	TIME 		Process();
public:
	void 		LoadFromFile(std::string fileName);
public:
	CNode& 	FindNode(size_t id);
	void 		AddNode(CNode node);
private:
	CNode* 	m_rootNode;
};
