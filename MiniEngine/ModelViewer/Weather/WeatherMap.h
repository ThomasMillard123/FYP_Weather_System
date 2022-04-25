#pragma once
#include<vector>
#include<string>
#include<DirectXMath.h>
#include <chrono>

#include"WorldSquare.h"
#include"AirMass.h"
#include"PressureSystem.h"

#define PI 3.14159265
/// <summary>
/// Overview of all the weathere in the world
/// </summary>
class WeatherMap
{
public:
	WeatherMap();
	~WeatherMap();

	void LoadFromJson(std::string JSON_WEATHER_DATA);


	void CreatWeatherMap(DirectX::XMFLOAT3 Size,unsigned int HightLayerMax, DirectX::XMFLOAT2 SquareMax);
	void CreatPressuerSystem(PressuerSystemType type, DirectX::XMFLOAT3 Pos, double Power);
	void CreatAirMass(AirMassType Type, DirectX::XMFLOAT3 Pos, float Power, float Size);
	

	void Update(float deltaT);

	std::vector<WorldSquare*> GetWorldData();
	WorldSquare* GetWorldData(int Num);

	WorldSquare* GetWorldSquare(int x, int z);
	
	std::vector<WorldSquare*> GetSquareInArea(int size, DirectX::XMFLOAT3 Pos);
	std::vector<WorldSquare*> GetSquareInArea(int width, int hight, DirectX::XMFLOAT3 Pos);
	std::vector<WorldSquare*> GetSquareInArea(FrontData FrontData);

	std::vector<AirMass*> GetAirMassData();
	AirMass* GetAirMass(int Num);


	std::vector<PressureSystem*> GetPressureSystemData();
	PressureSystem* GetPressureSystem(int Num);

	void GenrateAirMass();

	void SetWindData();
	void SetAirMassData();
	bool GetFogOn() { return FogOn; }
private:
	
	void SmoothData();
public:
private:
	//Location of weather and Data to be used
	std::vector<WorldSquare*> m_WorldSquareData;

	//Global Data
	std::vector<AirMass*> m_AirMassData;
	std::vector<PressureSystem*> m_PressureSystems;

	DirectX::XMFLOAT3 WeatherMapSize;

	bool FogOn=false;
	//season data
	enum class Season
	{
		winter = 0,
		Summer,
	};
	Season season;

	std::chrono::steady_clock::time_point m_start;
	std::chrono::steady_clock::time_point m_end;
	double TimeStep = 100;
};




//A clouds job
//creation
//Move
//Rain
//Remove
