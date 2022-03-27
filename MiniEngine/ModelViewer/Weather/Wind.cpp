#include "Wind.h"

Wind::Wind()
{
    CaluatePower();
}

Wind::~Wind()
{
}

void Wind::CaluatePower()
{
    Power = RandomGen::random<int>(0, 12);
}
