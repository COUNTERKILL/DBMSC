#pragma once

#include <vector>
#include "DBMSC_defs.h"

class CNode
{
typedef std::shared_ptr<CNode> CNodePtr;
public:
					CNode			() 			= default;
					~CNode			() 			= default;
public:
					CNode			(CNode&) 		= default;
					CNode			(CNode&&) 		= default;
public:
					CNode& operator=	(CNode&) 		= default;
					CNode& operator=	(CNode&&) 		= default;
public:
	TIME 				Process			()			= 0;
public:
	void				AddChild		(CNodePtr);
protected:
	void				SetParent		(CNode*);
	TIME				ProcessChildren		();
private:
	size_t 				m_id;
	std::vector<CNodePtr> 		m_children;
	CNode* 				m_parent;
};
