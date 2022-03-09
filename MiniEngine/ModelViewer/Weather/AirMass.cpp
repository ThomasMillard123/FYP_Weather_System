#include "AirMass.h"

AirMass::AirMass():
    m_AirMassType(AirMassType::Null),
    Pos(DirectX::XMFLOAT3()),
    Power(0.0f),
    Size(0.0f)
{
}

AirMass::AirMass(AirMassType AirMassType, DirectX::XMFLOAT3 Pos, float size, float power):
    m_AirMassType(AirMassType),
    Pos(Pos),
    Power(size),
    Size(power)
{
}

AirMass::~AirMass()
{
}

FrontType AirMass::IsHit(AirMass* airMass)
{
    FrontType frontType = FrontType::ColdFront;
    float dx = (this->Pos.x + this->Size) - (airMass->Pos.x + airMass->Size);
    float dy = (this->Pos.y + this->Size) - (airMass->Pos.y + airMass->Size);
    float distance = std::sqrt(dx * dx + dy * dy);

    if (distance < this->Size + airMass->Size) {
        // collision detected!

    }
    //Warm into cold= warm
    //cold into Hot= Cold
    //dir of tavle same
    if (1==1)
    {
        if (this->Power < airMass->Power && this->GetAirmassType() == AirMassType::Hot && airMass->GetAirmassType() == AirMassType::Cold) {
            frontType = FrontType::ColdFront;
        }
        if (this->Power < airMass->Power && this->GetAirmassType() == AirMassType::Cold && airMass->GetAirmassType() == AirMassType::Hot) {
            frontType = FrontType::WarmFront;
        }
    }
    // power = power = StationaryFront
    if (this->Power == airMass->Power && this->GetAirmassType() !=  airMass->GetAirmassType()) {
        frontType = FrontType::StationaryFront;
    }
   

    return frontType;
}

int AirMass::GetTemp()
{
    return RandomGen::random<int>(minTemp, maxTemp);
}
