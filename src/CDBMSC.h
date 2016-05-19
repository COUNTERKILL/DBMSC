#pragma once

#include "CDCHTree.h"


class CDBMSC
{
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
  void Initialize(std::string fileNameDchTree);
  TIME Query();
private:
    CDCHTree    m_tree;
    std::size_t m_stepsCount;
};
