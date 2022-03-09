#pragma once
#include<DirectXMath.h>
#include<vector>

#include"Wind.h"
#include"WorldHight.h"
class WorldSquare
{
public:
	WorldSquare();
	WorldSquare(DirectX::XMFLOAT3 Pos, DirectX::XMFLOAT2 size);
	WorldSquare(DirectX::XMFLOAT3 Pos, DirectX::XMFLOAT3 size);
	WorldSquare(DirectX::XMFLOAT3 Pos, DirectX::XMFLOAT2 size, unsigned int MaxHight);
	WorldSquare(DirectX::XMFLOAT3 Pos, DirectX::XMFLOAT2 size, unsigned int MaxHight, int NumberOfLayers);

	~WorldSquare();


	WorldHight* GetHightData(int level) { return HightAreas[level]; }
	Wind* GetWindData() { return WindData; }

	DirectX::XMFLOAT3 GetPos() { return PositionCenter; }
	DirectX::XMFLOAT2 GetSize() { return Size; }
	int  GetHightLimitLayers() { return HightLimit; }
	int GetHightLinitY() { return HightLimitY; }


	void SetSerfaceTemp(int temp);

	void Update();
private:
	void CreatHightData();
	void CreatWindData();
	void CreatPresuerData();
	void CreatDewPoint();

	void CaluateCloudHight();


	void CaluateHumidity();

	void CleanUp();
private:
	//squaer data
	DirectX::XMFLOAT3 PositionCenter;
	DirectX::XMFLOAT2 Size;

	//hight Data
	int HightLimit;
	int HightLimitY;
	std::vector<WorldHight*> HightAreas;

	//wind data of square
	Wind* WindData;

	//weather data
	int pressuer;
	int sufaceTemp;
	float dewPointTemp;
	float humidity;

	//cloud data
	float CloudHight;
	float elevation=0;
};

