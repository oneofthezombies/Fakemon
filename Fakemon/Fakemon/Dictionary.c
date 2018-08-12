#include "stdafx.h"
#include "Dictionary.h"

void _Dictionary_Destroy(Dictionary* self)
{
    for (int i = 0; i < self->_data->_end; ++i)
    {
        Pair* pair = (Pair*)(self->_data->At(self->_data, i));
        pair->Destroy(pair);
    }

    if (self->_data)
        free(self->_data);

    if (self)
        free(self);
}

Dictionary* CreateDictionary()
{
    Dictionary* dictionary = (Dictionary*)malloc(sizeof(Dictionary));

    dictionary->Destroy = _Dictionary_Destroy;

    dictionary->_data = CreateList(sizeof(Pair));

    return dictionary;
}
