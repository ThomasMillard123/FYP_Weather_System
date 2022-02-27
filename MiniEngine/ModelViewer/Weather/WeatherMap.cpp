#include "WeatherMap.h"

WeatherMap::WeatherMap()
{
}

WeatherMap::~WeatherMap()
{
}

void WeatherMap::CreatWeatherMap(DirectX::XMFLOAT3 Size, unsigned int HightLayerMax, DirectX::XMFLOAT2 SquareMax)
{
	WorldSquare* worldSqare;
	int SizeX = Size.x / SquareMax.x;
	int SizeZ = Size.z / SquareMax.y;

	DirectX::XMFLOAT2 SquareSize=DirectX::XMFLOAT2(SizeX, SizeZ);
	DirectX::XMFLOAT3 Position= DirectX::XMFLOAT3(0,0,0);
	for (size_t i = 0; i < SquareMax.y; i++)
	{
		for (size_t i = 0; i < SquareMax.x; i++)
		{
			Position.x += SizeX;
			worldSqare = new WorldSquare(Position, SquareSize);

			m_WorldSquareData.push_back(worldSqare);
		}
		Position.z += SizeZ;
	}
}

void WeatherMap::CreatPressuerSystem(PressuerSystemType type, DirectX::XMFLOAT3 Pos, double Power)
{
	PressureSystem* pressureSystem = new PressureSystem(type, Pos, Power);
	m_PressureSystems.push_back(pressureSystem);
}

void WeatherMap::CreatAirMass(AirMassType Type, DirectX::XMFLOAT3 Pos, float Power,float Size)
{
	AirMass* airMass = new AirMass();
	m_AirMassData.push_back(airMass);
}

void WeatherMap::Update(float deltaT)
{
}




std::vector<WorldSquare*> WeatherMap::GetWorldData()
{
	return m_WorldSquareData;
}

WorldSquare* WeatherMap::GetWorldData(int Num)
{
	return m_WorldSquareData[Num];
}

std::vector<AirMass*> WeatherMap::GetAirMassData()
{
	return m_AirMassData;
}

AirMass* WeatherMap::GetAirMass(int Num)
{
	return m_AirMassData[Num];
}

std::vector<PressureSystem*> WeatherMap::GetPressureSystemData()
{
	return m_PressureSystems;
}

PressureSystem* WeatherMap::GetPressureSystem(int Num)
{
	return m_PressureSystems[Num];
}


