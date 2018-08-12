#pragma once

typedef struct _Map
{
    void(*Destroy)(struct _Map* self);

    MapType** _map;
    int _sizeOfSide;
} Map;

Map* CreateMap();