#include "stdafx.h"
#include "Map.h"

void _Map_Destroy(Map* self)
{
    for (int i = 0; i < self->_sizeOfSide; ++i)
    {
        free(self->_map[i]);
    }
    free(self->_map);
    free(self);
}

Map* CreateMap()
{
    Map* map = (Map*)malloc(sizeof(Map));

    map->Destroy = _Map_Destroy;

    map->_sizeOfSide = 9;
    map->_map = (MapType**)malloc(sizeof(MapType*) * map->_sizeOfSide);
    for (int i = 0; i < map->_sizeOfSide; ++i)
    {
        map->_map[i] = (MapType*)malloc(sizeof(MapType) * map->_sizeOfSide);
    }

    for (int i = 0; i < map->_sizeOfSide; ++i)
    {
        for (int j = 0; j < map->_sizeOfSide; ++j)
        {
            if (i == 0 ||
                i == map->_sizeOfSide - 1 ||
                j == 0 ||
                j == map->_sizeOfSide - 1 ||
                (i == 4 && j < map->_sizeOfSide - 2))
            {
                map->_map[i][j] = MapType_Wall;
            }
            else if (i > 0 &&
                     i < 4 &&
                     j > 0 &&
                     j < 7)
            {
                map->_map[i][j] = MapType_Grass;
            }
            else if (i > 4 &&
                     i < map->_sizeOfSide - 1 &&
                     j > 0 &&
                     j < 4)
            {
                map->_map[i][j] = MapType_TallGrass;
            }
            else
            {
                map->_map[i][j] = MapType_Road;
            }
        }
    }

    map->_map[1][1] = MapType_Switch;
    for (int i = 0; i < 3; ++i)
    {
        map->_map[5 + i][6] = MapType_Door;
    }

    return map;
}
