#include "AirMass.h"

AirMass::AirMass():
    m_AirMassType(AirMassType::Null),
    Pos(DirectX::XMFLOAT3()),
    Power(0.0f),
    Size(0.0f),
    maxTemp(30),
    minTemp(0),
    DirGen(DirectX::XMFLOAT3())
{
}

AirMass::AirMass(AirMassType AirMassType, DirectX::XMFLOAT3 Pos, float size, float power):
    m_AirMassType(AirMassType),
    Pos(Pos),
    Power(size),
    Size(power),
    maxTemp(30),
    minTemp(0),
    DirGen(DirectX::XMFLOAT3())
{
}

AirMass::AirMass(AirMassType AirMassType, DirectX::XMFLOAT3 Pos, float size, float power, DirectX::XMFLOAT3 DirGen):
    m_AirMassType(AirMassType),
    Pos(Pos),
    Power(size),
    Size(power),
    maxTemp(30),
    minTemp(0),
    DirGen(DirGen)
{
}

AirMass::~AirMass()
{
}

FrontData AirMass::IsHit(AirMass* airMass)
{
    FrontType frontType = FrontType::NoFront;
    float dx = (this->Pos.x + this->Size) - (airMass->GetPos().x + airMass->GetSize());
    float dy = (this->Pos.z + this->Size) - (airMass->GetPos().z + airMass->GetSize());
    float distance = std::sqrt(dx * dx + dy * dy);
 
   
    bool hit = true;
    if (distance < this->Size + airMass->GetSize()) {
        // collision detected!
      
        //dir of tavle same
        if (DirectX::XMVector3Equal(DirectX::XMVector3Normalize(DirectX::XMLoadFloat3(&this->Dir)), DirectX::XMVector3Normalize(DirectX::XMLoadFloat3(&airMass->GetDir()))))
        {    //Warm into cold= warm
            //cold into Hot= Cold
            
            //airMass->GetPos()-->this->Pos
            
            DirectX::XMFLOAT3 normDir;
           DirectX::XMStoreFloat3(&normDir, DirectX::XMVector3Normalize(DirectX::XMLoadFloat3(&airMass->GetDir())));
            double product = (this->Pos.x - airMass->GetPos().x) * normDir.x
                            +(this->Pos.y - airMass->GetPos().y) * normDir.y
                            + (this->Pos.z - airMass->GetPos().z) * normDir.z;
          
            if (product>0) {
                if (this->GetAirmassType() == AirMassType::Hot && airMass->GetAirmassType() == AirMassType::Cold) {
                    frontType = FrontType::ColdFront;
                }
                else if (this->GetAirmassType() == AirMassType::Cold && airMass->GetAirmassType() == AirMassType::Hot) {
                    frontType = FrontType::WarmFront;
                }
                // power = power = StationaryFront
                else if (this->Power == airMass->GetPower() && this->GetAirmassType() != airMass->GetAirmassType()) {
                    frontType = FrontType::StationaryFront;
                }
            }
            else {
                FrontData frontData;
                return frontData;
            }
        }
    }


    DirectX::XMFLOAT3 PointTOPoint = DirectX::XMFLOAT3(this->Pos.x - airMass->GetPos().x, this->Pos.y - airMass->GetPos().y, this->Pos.z - airMass->GetPos().z);
    float m = sqrt(PointTOPoint.x * PointTOPoint.x + PointTOPoint.y * PointTOPoint.y + PointTOPoint.z * PointTOPoint.z);
    PointTOPoint.x /= m;
    PointTOPoint.y /= m;
    PointTOPoint.z /= m;

    FrontData frontData;
    frontData._FrontType = frontType;
    frontData.CenterPos= DirectX::XMFLOAT2(airMass->GetPos().x + (PointTOPoint.x * (distance / 2)), airMass->GetPos().z + (PointTOPoint.z * (distance/2)));

    DirectX::XMFLOAT2 g = DirectX::XMFLOAT2(PointTOPoint.x, PointTOPoint.z);
    DirectX::XMFLOAT2 a;
    DirectX::XMStoreFloat2(&a, DirectX::XMVector2Normalize(DirectX::XMVector2Orthogonal(DirectX::XMLoadFloat2(&g))));
  
 
    float slope = a.y / a.x;
    ////slope *= 10;
    frontData.Slope = slope;

    int b = (slope * -frontData.CenterPos.x) + frontData.CenterPos.y;
    frontData.yInter1 = b;

    DirectX::XMFLOAT2 point1= DirectX::XMFLOAT2(airMass->GetPos().x + (PointTOPoint.x * (distance )), airMass->GetPos().z + (PointTOPoint.z * (distance )));
   int  interA = (slope * -point1.x) + point1.y;
   
   
    
    DirectX::XMFLOAT2 point1Vector = DirectX::XMFLOAT2(point1.x - airMass->GetPos().x, point1.y - airMass->GetPos().z);
    float point1Mag = sqrt(point1Vector.x * point1Vector.x + point1Vector.y * point1Vector.y);

    DirectX::XMFLOAT2 point2 = DirectX::XMFLOAT2(frontData.CenterPos.x - (PointTOPoint.x * 0.5f), frontData.CenterPos.y- (PointTOPoint.z * 0.5f));
    DirectX::XMFLOAT2 point2Vector = DirectX::XMFLOAT2(point2.x - airMass->GetPos().x, point2.y - airMass->GetPos().z);
    float point2Mag = sqrt(point2Vector.x * point2Vector.x + point2Vector.y * point2Vector.y);
    int  interb = (slope * -point2.x) + point2.y;
    

    if (interA > interb) {

        //far
        frontData.yInter2 = interb;
        //cloase
        frontData.yInter3 = interA;

    }
    else
    {
       
        frontData.yInter2 = interA;
        //cloase
        
        frontData.yInter3 = interb;
    }
  


    int y = (slope * 0) + b;
    return frontData;
}

DirectX::XMFLOAT3 operator + (DirectX::XMFLOAT3 left, DirectX::XMFLOAT3 right) {
    DirectX::XMFLOAT3 Out;
    Out.x = left.x + right.x;
    Out.y = left.y + right.y;
    Out.z = left.z + right.z;
    return Out;
}
DirectX::XMFLOAT3 operator * (DirectX::XMFLOAT3 left, float right) {
    DirectX::XMFLOAT3 Out;
    Out.x = left.x * right;
    Out.y = left.y * right;
    Out.z = left.z * right;
    return Out;
}
void AirMass::Move(DirectX::XMFLOAT3 DirWind,float dt)
{
    Dir = DirWind * Power;
    Pos = Pos+Dir*dt* dt;

    //Power = sqrt((Dir.x * Dir.x) + (Dir.y * Dir.y) + (Dir.z * Dir.z));
   
}

int AirMass::GetTemp()
{
    return RandomGen::random<int>(minTemp, maxTemp);
}
