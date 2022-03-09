#include "WorldSquare.h"

WorldSquare::WorldSquare()
{
}

WorldSquare::WorldSquare(DirectX::XMFLOAT3 Pos, DirectX::XMFLOAT2 size) :
	PositionCenter(Pos),
	Size(size),
	HightLimit(10),
	HightLimitY(1000)
{
	CreatHightData();
	CaluateHumidity();
	SetSerfaceTemp(15);
	CreatWindData();
	
}

WorldSquare::WorldSquare(DirectX::XMFLOAT3 Pos, DirectX::XMFLOAT3 size):
	PositionCenter(Pos),
	Size(DirectX::XMFLOAT2(size.x, size.y)),
	HightLimit(10),
	HightLimitY(size.y)
{
	CreatHightData();
	CaluateHumidity();
	SetSerfaceTemp(15);
	CreatWindData();
	
}

WorldSquare::WorldSquare(DirectX::XMFLOAT3 Pos, DirectX::XMFLOAT2 size, unsigned int MaxHight):
	PositionCenter(Pos),
	Size(size),
	HightLimit(10),
	HightLimitY(MaxHight)
{
	CreatHightData();
	CaluateHumidity();
	SetSerfaceTemp(15);
	CreatWindData();
}

WorldSquare::WorldSquare(DirectX::XMFLOAT3 Pos, DirectX::XMFLOAT2 size, unsigned int MaxHight, int NumberOfLayers):
	PositionCenter(Pos),
	Size(size),
	HightLimit(NumberOfLayers),
	HightLimitY(MaxHight)
{
	CreatHightData();
	CaluateHumidity();
	SetSerfaceTemp(15);
	CreatWindData();
}

WorldSquare::~WorldSquare()
{
}

void WorldSquare::SetSerfaceTemp(int temp)
{
	
	if (temp != sufaceTemp) {
		sufaceTemp = temp;
		for (auto layer: HightAreas)
		{
			layer->SetTemp(temp);
		}
		CreatDewPoint();
		CaluateCloudHight();
	}
	
}

void WorldSquare::CreatHightData()
{
	WorldHight* Higth;
	int size = HightLimitY / HightLimit;
	for (size_t i = 0; i < HightLimit; i++)
	{
		Higth = new WorldHight(i, size);
		HightAreas.push_back(Higth);
	}

}

void WorldSquare::CreatWindData()
{
	WindData = new Wind();
}

void WorldSquare::CreatPresuerData()
{
	
}

void WorldSquare::CreatDewPoint()
{
	dewPointTemp = sufaceTemp-((100-humidity)/5);
}

void WorldSquare::CaluateCloudHight()
{
	CloudHight = ((15 - 8) / 2.5f)*1000+(elevation* 3.281f);
	CloudHight = CloudHight / 3.281f;
}

void WorldSquare::CaluateHumidity()
{
	humidity = RandomGen::randomFloat<double>(0, 100);
}

void WorldSquare::CleanUp()
{
	for (auto Hight: HightAreas)
	{
		delete Hight;
		Hight = nullptr;
	}
	HightAreas.clear();

	if (WindData) delete WindData;
	WindData = nullptr;

}
