#include "Config.h"

std::size_t Config::GetRelationSize(std::size_t step)
{
    switch(step)
    {
        case 0:
            return 630000;
            break;
        case 1:
            return 63000000;
            break;
        case 2:
            return 20000;
            break;
    }
    return 0;
}

std::size_t Config::GetResultSize(std::size_t step)
{
    switch(step)
    {
        case 1:
            return 31500;
            break;
        case 2:
            return 1000000;
            break;
    }
    return 0;
}

std::size_t Config::GetIndicesAddition(std::size_t step)
{
    switch(step)
    {
        case 1:
            return 2;
            break;
        case 2:
            return -1;
            break;
    }
    return 0;
}

std::size_t Config::GetStepsCount()
{
    return 1;
}