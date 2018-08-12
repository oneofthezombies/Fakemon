#pragma once

typedef struct _Dictionary
{
    void(*Destroy)(struct _Dictionary* self);

    List* _data;
} Dictionary;

Dictionary* CreateDictionary();