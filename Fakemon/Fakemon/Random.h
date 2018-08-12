#pragma once

typedef struct _Random
{
    void(*Destroy)(struct _Random* self);
    int(*GetIntFromTo)(int from , int to);
    int(*GetInt)(int num);
} Random;

Random* CreateRandom();