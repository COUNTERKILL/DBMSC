#pragma once

#include <vector>
#include "CNode.h"

class CDBMSC
{
  typedef int TIME;
public:
  CDBMSC() = default;
	~CDBMSC() = default;
public:
	CDBMSC(CDBMSC&) = delete;
	CDBMSC(CDBMSC&&) = delete;
public:
  CDBMSC& operator=(CDBMSC&) = delete;
  CDBMSC& operator=(CDBMSC&&) = delete;
public:
  TIME Query();
private:
	std::vector<Node> m_nodes;
	std::size_t m_steps_count;
};
