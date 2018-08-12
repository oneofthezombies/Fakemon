#include "stdafx.h"
#include "Time.h"

void _Time_Destroy(Time* self)
{
    if (self)
        free(self);
}

int _Time_DeltaTime(Time* self)
{
    DWORD currentTime = GetTickCount();
    DWORD deltaTime = currentTime - self->_previousTime;
    self->_previousTime = currentTime;
    return (int)deltaTime;
}

Time* CreateTime()
{
    Time* time = (Time*)malloc(sizeof(Time));
    
    time->Destroy      = _Time_Destroy;
    time->DeltaTime    = _Time_DeltaTime;

    time->_previousTime = GetTickCount();

    return time;
}