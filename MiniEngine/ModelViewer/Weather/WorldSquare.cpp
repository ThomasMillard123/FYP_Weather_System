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
	LoadEffects();
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
	LoadEffects();
	
	
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
	LoadEffects();
	
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
	LoadEffects();
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

void WorldSquare::SetActiveWeather()
{
	isActive = true;
	float tempdiff = sufaceTemp-dewPointTemp;
	if (tempdiff > 2.5f) {
		//fog

	}
	
	int chnace = RandomGen::random<int>(humidity, 100);
	if (chnace > 25)
	{
		if (sufaceTemp <= 0 && sufaceTemp > -2) {
			//snow
			ParticleEffect* EffectPorop;
			//EffectPorop = ParticleEffectManager::GetEffect(EffectsData[1]);
			//EffectPorop->enabled = true;
			/*ParticleEffectProperties a = EffectPorop->GetOriginalEffectProperties();
			a.Velocity=XMFLOAT4(0, 0, 1, 0);
			a.EmitProperties.MaxParticles = 100 * chnace;
			a.Spread = XMFLOAT3(Size.x, 0, Size.y);
			EffectPorop->SetParticalProperties(a);*/

		}
		else if (sufaceTemp <= -2) {
			//hail
			//ParticleEffectManager::GetEffect(EffectsData[2])->enabled = true;
		}
		else
		{
			//rain
			ParticleEffect* EffectPorop;
			EffectPorop = ParticleEffectManager::GetEffect(EffectsData[0]);
			ParticleEffectManager::GetEffect(EffectsData[0])->enabled = true;
			ParticleEffectProperties a = EffectPorop->GetOriginalEffectProperties();
			//a.Velocity = XMFLOAT4(0, 0, 1, 0);
			a.EmitProperties.MaxParticles = 5000;
			a.EmitProperties.EmitPosW = PositionCenter;
			a.EmitProperties.EmitPosW.y = CloudHight;
			a.EmitProperties.LastEmitPosW = PositionCenter;
			a.EmitProperties.LastEmitPosW.y = CloudHight;
			EffectPorop->SetParticalProperties(a);
		}
	}
}

void WorldSquare::DeatvateWeather()
{
	isActive = false;
	for (auto Effect: EffectsData)
	{
		ParticleEffectManager::GetEffect(Effect)->enabled = false;
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

void WorldSquare::LoadEffects()
{
	EffectsData = ParticleEffects::InitFromJSON(L"Weather/particles.json");

	for (auto data : EffectsData)
	{
		ParticleEffectManager::GetEffect(data)->enabled = false;
		ParticleEffectProperties a = ParticleEffectManager::GetEffect(data)->GetOriginalEffectProperties();
		a.EmitProperties.EmitPosW = PositionCenter;
		a.EmitProperties.EmitPosW.y = CloudHight;
		a.Spread = XMFLOAT3(Size.x/2,0, Size.y/2);
		ParticleEffectManager::GetEffect(data)->SetParticalProperties(a);
	}
}

void WorldSquare::CaluateCloudHight()
{
	CloudHight = ((sufaceTemp - 8) / 2.5f)*1000+(elevation* 3.281f);
	CloudHight = CloudHight / 3.281f;
	CloudHight *= 10;
}

void WorldSquare::CaluateHumidity()
{
	humidity = RandomGen::random<int>(0, 100);
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
