#pragma once
#include<DirectXMath.h>
class Fog
{
public:
    Fog();
    ~Fog();

    void EnableFog() { isEnabled = true; }
private:

    bool isEnabled = false;
    DirectX::XMFLOAT4 fogColour;
    float Dist;
    float Start;

};

