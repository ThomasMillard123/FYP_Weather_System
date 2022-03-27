#pragma once
#include<DirectXMath.h>

#include<cmath>
#include<vector>
#include"C++HelperFunctions.h"
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
	OccludedFront,
	NoFront
};

struct FrontData
{
	FrontType _FrontType;
	DirectX::XMFLOAT2 CenterPos;
	float Slope;
	float yInter1;
	float yInter2;
	float yInter3;
	
};
//set weather fronts
//set temp of area
class AirMass
{
public:
	AirMass();
	AirMass(AirMassType AirMassType, DirectX::XMFLOAT3 Pos, float size,float power);
	AirMass(AirMassType AirMassType, DirectX::XMFLOAT3 Pos, float size, float power, DirectX::XMFLOAT3 DirGen);
	~AirMass();
	
	FrontData IsHit(AirMass* airMass);
	void Move(DirectX::XMFLOAT3 DirWind, float dt);


	float GetSize() { return Size; }
	DirectX::XMFLOAT3 GetPos(){ return Pos; }
	AirMassType GetAirmassType() { return m_AirMassType; }
	float GetPower() { return Power; }



	DirectX::XMFLOAT3 GetDir() { return Dir; }


	int GetTemp();
	int GetMaxTemp() { return maxTemp; }
	int GetMinTemp() { return minTemp; }
private:
	AirMassType m_AirMassType;
	DirectX::XMFLOAT3 Pos;

	//move ment
	float Power;
	float Size;


	int maxTemp;
	int minTemp;

	DirectX::XMFLOAT3 Dir= DirectX::XMFLOAT3();
	DirectX::XMFLOAT3 DirGen;
};

