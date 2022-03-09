#pragma once
#include<DirectXMath.h>

#include<cmath>
#include<vector>
enum class AirMassType
{
	Hot = 0,
	Cold,
	Null
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
	AirMass(AirMassType AirMassType, DirectX::XMFLOAT3 Pos, float size,float power);
	~AirMass();
	
	FrontType IsHit(AirMass* airMass);
	void Move();


	float GetSize() { return Size; }
	DirectX::XMFLOAT3 GetPos(){ return Pos; }
	AirMassType GetAirmassType() { return m_AirMassType; }
	float GetPower() { return Power; }

private:
	AirMassType m_AirMassType;
	DirectX::XMFLOAT3 Pos;

	//move ment
	float Power;
	float Size;


	int maxTemp;
	int minTemp;

};

