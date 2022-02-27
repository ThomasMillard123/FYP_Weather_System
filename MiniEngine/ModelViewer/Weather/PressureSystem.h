#pragma once
#include<DirectXMath.h>
#include<vector>
enum class PressuerSystemType
{
	High,
	Low
};
/// <summary>
/// 
/// </summary>
class PressureSystem
{
public:
	PressureSystem();
	PressureSystem(PressuerSystemType type, DirectX::XMFLOAT3 Pos, double Power);
	~PressureSystem();

	void Update();

private:
	PressuerSystemType m_PressuerSystemType;

	double Power;
	DirectX::XMFLOAT3 Pos;
};

