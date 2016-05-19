#pragma once
#include <cstddef>

class Config
{
public:
    static std::size_t GetRelationSize(std::size_t step);
    static std::size_t GetResultSize(std::size_t step);
    static std::size_t GetIndicesAddition(std::size_t step);
    static std::size_t GetStepsCount();
};