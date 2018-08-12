#include "stdafx.h"
#include "Pair.h"

void _Pair_Destroy(Pair* self)
{
    if (self->_value)
        free(self->_value);

    if (self)
        free(self);
}

Pair* CreatePair()
{
    Pair* pair = (Pair*)malloc(sizeof(Pair));

    pair->Destroy = _Pair_Destroy;

    pair->_key = -1;
    pair->_value = (void*)-1;

    return pair;
}
