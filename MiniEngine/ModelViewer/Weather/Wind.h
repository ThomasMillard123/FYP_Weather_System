#pragma once
#include<DirectXMath.h>
#include"C++HelperFunctions.h"
class Wind
{
public:
    Wind();
    ~Wind();

    void SetDir(DirectX::XMFLOAT3 dir) { Dir = dir; }
    DirectX::XMFLOAT3 GetDir() { return Dir; }
    void CaluatePower();
    int GetPower() { return Power; }
private:
    DirectX::XMFLOAT3 Dir;
    int Power;
};

