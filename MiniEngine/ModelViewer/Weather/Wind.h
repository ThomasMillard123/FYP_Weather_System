#pragma once
#include<DirectXMath.h>
#include"C++HelperFunctions.h"
class Wind
{
public:
    Wind();
    ~Wind();

    void CaluatePower();
private:
    DirectX::XMFLOAT3 Dir;
    int Power;
};

