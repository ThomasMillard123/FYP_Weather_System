#pragma once
class WorldHight
{
public:
    WorldHight();
    WorldHight(int level, int size);
    WorldHight(int level, int size, int yHight);
    ~WorldHight();

    void SetTemp(int Temp);
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
    float pressuer;
};

