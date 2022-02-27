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
	~WorldSquare();

private:
	DirectX::XMFLOAT3 PositionCenter;
	DirectX::XMFLOAT2 Size;

	std::vector<WorldHight*> HightAreas;
	Wind* WindData;
};

