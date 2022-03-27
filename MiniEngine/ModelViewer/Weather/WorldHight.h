#pragma once
#include"ParticleEffects.h"
#include"ParticleEffectManager.h"
class WorldHight
{
public:
    WorldHight();
    WorldHight(int level, int size);
    WorldHight(int level, int size, int yHight);
    ~WorldHight();

    void SetTemp(int Temp);

    //gets
    int GetLevel() { return Level; }
    int GetLevelStart() { return LevelStart; }
    int GetSize() { return size; }
    int GetTemp() { return temp; }
    double Getpressuer() { return pressuer; }
private:
    void CaluateTemp();
    void CaluatePresser();
    
private:
    //is 1,2,3...
    int Level;
    //y hight value
    int LevelStart;

    //size of hight layer
    int size;
    //temp at hight
    //celciuse
    int temp;
    //atm
    double pressuer;
};

