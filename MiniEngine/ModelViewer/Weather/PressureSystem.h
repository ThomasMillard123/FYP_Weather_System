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

	PressuerSystemType GetPressuerSystemType() { return m_PressuerSystemType; }
	double GetPower() { return Power; }
	DirectX::XMFLOAT3 GetPos() { return Pos; }
private:
	PressuerSystemType m_PressuerSystemType;

	double Power;
	DirectX::XMFLOAT3 Pos;
};

