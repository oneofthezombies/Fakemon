#include "stdafx.h"
#include "Random.h"

void _Random_Destroy(Random* self)
{
    if (self)
        free(self);
}

int _Random_GetIntFromTo(int from, int to)
{
    return rand() % (to - from + 1) + from;
}

int _Random_GetInt(int num)
{
    return rand() % num;
}

Random* CreateRandom()
{
    srand((unsigned int)time(NULL));

    Random* random = (Random*)malloc(sizeof(Random));
    
    random->Destroy = _Random_Destroy;
    random->GetIntFromTo = _Random_GetIntFromTo;
    random->GetInt = _Random_GetInt;
    
    return random;
}
