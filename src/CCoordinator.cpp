#include "CCoordinator.h"
#include <cmath>

CCoordinator::CCoordinator(std::size_t id, float perfomance):
                    CNode(id),
                    m_perfomance(perfomance)
{
}


TIME CCoordinator::Process()
{
    return 0;
}

TIME CCoordinator::SendPacket(CPacket&& packet, CNode* pNode)
{
    return 0;
}

void CCoordinator::ReceivePacket(CPacket&& packet)
{
    return;
}

