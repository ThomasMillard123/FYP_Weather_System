#pragma once
#include<DirectXMath.h>
#include<vector>
enum class AirMassType
{
	Hot = 0,
	Cold
};

enum FrontType
{
	WarmFront,
	ColdFront,
	StationaryFront,
	OccludedFront
};
class AirMass
{
public:
	AirMass();
	~AirMass();
	
	FrontType IsHit(AirMass* airMass);
	void Move();

private:
	AirMassType m_AirMassType;
	DirectX::XMFLOAT3 Pos;
	float Power;
	float Size;
};

