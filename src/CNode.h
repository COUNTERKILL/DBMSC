#pragma once

#include <vector>
#include "DBMSC_defs.h"

class CNode
{
public:
		CNode() 					= default;
		~CNode() 					= default;
public:
		CNode(CNode&) 				= delete;
		CNode(CNode&&) 				= delete;
public:
		CNode& operator=(CNode&) 		= delete;
		CNode& operator=(CNode&&) 	= delete;
public:
	TIME 	Process()					= 0;
public:
	void	AddChild(CNode*);
protected:
	void	SetParent(CNode*);
	TIME	ProcessChildren();
private:
	size_t 			m_id;
	std::vector<CNode*> 	m_children;
	CNode* 			m_parent;
};
