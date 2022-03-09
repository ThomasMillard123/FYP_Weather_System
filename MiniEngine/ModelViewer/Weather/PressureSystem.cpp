#include "PressureSystem.h"

PressureSystem::PressureSystem()
{
}

PressureSystem::PressureSystem(PressuerSystemType type, DirectX::XMFLOAT3 Pos, double Power):
	m_PressuerSystemType(type),
	Pos(Pos),
	Power(Power)
{
}

PressureSystem::~PressureSystem()
{
}
