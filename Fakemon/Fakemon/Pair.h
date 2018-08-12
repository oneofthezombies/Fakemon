#pragma once

typedef struct _Pair
{
    void(*Destroy)(struct _Pair* self);

    unsigned int _key;
    void* _value;
} Pair;

Pair* CreatePair();
