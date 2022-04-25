#include "WorldHight.h"
#include "C++HelperFunctions.h"
WorldHight::WorldHight()
{
}



WorldHight::WorldHight(int level, int size):
    Level(level),
    LevelStart(level* size),
    size(size)
{
    CaluateTemp();
    CaluatePresser();
}

WorldHight::WorldHight(int level, int size, int yHight):
    Level(level),
    LevelStart(yHight),
    size(size)
{
    CaluateTemp();
    CaluatePresser();
}

WorldHight::~WorldHight()
{
}

void WorldHight::SetTemp(int Temp)
{
    temp = Temp;
    CaluateTemp();
    CaluatePresser();
}



void WorldHight::CaluateTemp()
{
    float tempAdd=0;
    
       float h = ((LevelStart) / 100) * 1000;
       tempAdd = temp - (0.0065f * h);
    
    //avrag temp
    temp = tempAdd ;
}

void WorldHight::CaluatePresser()
{
    double g = 9.80665;
    double M = 0.0289644;
    double h = 0;
    double R = 8.31432;
    double T = temp + 273.15;
    double P = 1;
    

    float presser = 0;
    //h = ((LevelStart + 0) / 100) * 1000;
    //presser = P * std::exp(-(g * M) * (h - 0) / (R * T));

    h= ((LevelStart) / 100)*1000;
    presser = P * std::exp(-(g * M) * (h - 0) / (R * T));
  
    //avrag temp
    pressuer = presser;
}



