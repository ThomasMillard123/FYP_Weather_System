#include "WeatherMap.h"
#include< cmath >
#include"C++HelperFunctions.h"
#include"ParticleEffects.h"
#include"ParticleEffectManager.h"
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
	WeatherMapSize = DirectX::XMFLOAT3(SquareMax.x, SquareMax.y,0);
	DirectX::XMFLOAT2 SquareSize=DirectX::XMFLOAT2(SizeX, SizeZ);
	DirectX::XMFLOAT3 Position= DirectX::XMFLOAT3(0- Size.x/2,0,0- Size.z/2);
	
	for (size_t i = 0; i < SquareMax.y; i++)
	{
		for (size_t j = 0; j < SquareMax.x; j++)
		{
			Position.x += SizeX;
			worldSqare = new WorldSquare(Position, SquareSize);

			m_WorldSquareData.push_back(worldSqare);

		}
		Position.x = 0 - Size.x/2;
		Position.z += SizeZ;
	}

	SetWindData();
	
}

void WeatherMap::CreatPressuerSystem(PressuerSystemType type, DirectX::XMFLOAT3 Pos, double Power)
{
	PressureSystem* pressureSystem = new PressureSystem(type, Pos, Power);
	m_PressureSystems.push_back(pressureSystem);
}

void WeatherMap::CreatAirMass(AirMassType Type, DirectX::XMFLOAT3 Pos, float Power,float Size)
{
	DirectX::XMFLOAT3 GenWindDirection = DirectX::XMFLOAT3(0, 0, 0);
	AirMass* airMass = new AirMass(Type, Pos, Power, Size, GenWindDirection);
	m_AirMassData.push_back(airMass);
	SetAirMassData();
}

void WeatherMap::Update(float deltaT)
{
	//time componets
	std::vector<FrontData> front;
	for (auto airMass : m_AirMassData)
	{
		for (auto airMass2 : m_AirMassData)
		{
			if (airMass == airMass2) {
				continue;
			}
			front.push_back(airMass->IsHit(airMass2));
		}
	}

	//move airmass
	
	for (auto airMass : m_AirMassData)
	{
		airMass->Move( XMFLOAT3(0,0,1), deltaT);
		SetAirMassData();
		SetWindData();
	}
	//fog is fromed when diff between air temp and dewpoint is less than 2.5 degeres c (https://glossary.ametsoc.org/wiki/Fog)
	vector< WorldSquare*> WeatherActive;
	//get/set weather effects
	for (auto FrontData : front)
	{
		switch (FrontData._FrontType)
		{
		case WarmFront:
		{
			//GetSquareInArea(size of over lap ,pos of hit)
			//humidity check for air mouster
			
			

			//state the square percipitation conditions
			std::vector<WorldSquare*> apple = GetSquareInArea(FrontData);

			for (auto world : apple)
			{
				WeatherActive.push_back(world);
			}
			
				

			//summer 
			//leading edge can produce rain

			//winter
			//no rain before
			//persistant light to hevey rain in center
			//super light rain to not rain after
		}
		break;
		case ColdFront:
		{
			std::vector<WorldSquare*> apple = GetSquareInArea(FrontData);

			for (auto world : apple)
			{
				WeatherActive.push_back(world);
			}
			//hevey rain
			//leading edge haze(fog)

			//ledaing edge genrly light rain

			//summer 
			//leading edge can produce hevey rain (flowwing squal line)

			//winter
			//leading edge can produce hevey rain/snow (flowwing squal line)


			//during prolong rain

			//flowowed by rain to clear

		}
		break;
		case StationaryFront:
			//humidy high rain happens 
			break;
		case NoFront:
			break;
		default:
			break;
		}
	}



	for (auto data : m_WorldSquareData)
	{
		bool remove = true;
		for (auto world : WeatherActive)
		{
			if (world == data) {
				world->SetActiveWeather();
				remove = false;
				break;
			}
		}
		if (remove) {
			data->DeatvateWeather();
		}
	}
	//if not in front obay air mass rules
}




std::vector<WorldSquare*> WeatherMap::GetWorldData()
{
	return m_WorldSquareData;
}

WorldSquare* WeatherMap::GetWorldData(int Num)
{
	return m_WorldSquareData[Num];
}

WorldSquare* WeatherMap::GetWorldSquare(int x, int z)
{
	return m_WorldSquareData[x * (int)WeatherMapSize.x + z];
}

std::vector<WorldSquare*> WeatherMap::GetSquareInArea(int size, DirectX::XMFLOAT3 Pos)
{
	std::vector<WorldSquare*> SquareInSpace;
	for (auto worldSquar : m_WorldSquareData)
	{
		if (std::pow((worldSquar->GetPos().x - Pos.x),2) + std::pow((worldSquar->GetPos().z - Pos.z),2) < std::pow(size,2))
		{
			SquareInSpace.push_back(worldSquar);
		}
	}

	return SquareInSpace;
}

std::vector<WorldSquare*> WeatherMap::GetSquareInArea(int width, int hight, DirectX::XMFLOAT3 Pos)
{
	std::vector<WorldSquare*> SquareInSpace;
	for (auto worldSquar : m_WorldSquareData)
	{

		if (worldSquar->GetPos().x >= Pos.x &&
			worldSquar->GetPos().x <= (Pos.x + width) &&
			worldSquar->GetPos().z >= Pos.z &&
			worldSquar->GetPos().z <= (Pos.z + hight))
		{
			SquareInSpace.push_back(worldSquar);
		}
	}

	return SquareInSpace;
}

std::vector<WorldSquare*> WeatherMap::GetSquareInArea(FrontData FrontData)
{
	//d = (x−x1)(y2−y1)−(y−y1)(x2−x1)

	DirectX::XMFLOAT2 k1 = DirectX::XMFLOAT2(0, (FrontData.Slope * 0) + FrontData.yInter2);
	DirectX::XMFLOAT2 k2 = DirectX::XMFLOAT2(1000, (FrontData.Slope * 1000) + FrontData.yInter2);
	
	DirectX::XMFLOAT2 J1 = DirectX::XMFLOAT2(0, (FrontData.Slope * 0) + FrontData.yInter3);
	DirectX::XMFLOAT2 J2 = DirectX::XMFLOAT2(1000, (FrontData.Slope * 1000) + FrontData.yInter3);

	std::vector<WorldSquare*> SquareInSpace;
	for (auto worldSquar : m_WorldSquareData)
	{
		if (((worldSquar->GetPos().x- k1.x)*(k2.y - k1.y)-(worldSquar->GetPos().z- k1.y)*(k2.x- k1.x)) <= 0) {
			if (((worldSquar->GetPos().x - J1.x) * (J2.y - J1.y) - (worldSquar->GetPos().z - J1.y) * (J2.x - J1.x)) > 0) {
				SquareInSpace.push_back(worldSquar);
			}
		}	
	}
	return SquareInSpace;
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

void WeatherMap::SetWindData()
{
	//find 
	for (size_t x = 0; x < WeatherMapSize.x; x++)
	{
		for (size_t y = 0; y < WeatherMapSize.x; y++)
		{
			//could become wind zonzes to creat diffrent movments across map but small maps will not needs this and will all move in same diarection
			m_WorldSquareData[x * (int)WeatherMapSize.x + y]->GetWindData()->SetDir(DirectX::XMFLOAT3(1, 0, 0));
		}
	}
}

void WeatherMap::SetAirMassData()
{
	for (auto airMass: m_AirMassData)
	{
		std::vector<WorldSquare*> squareintAirmass = GetSquareInArea(airMass->GetSize(), airMass->GetPos());
		
	
		for (auto squaer : squareintAirmass)
		{
			//base temp warm
			squaer->SetSerfaceTemp(airMass->GetTemp());
		}
	}

}


