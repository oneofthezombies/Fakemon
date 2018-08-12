#pragma once

typedef struct _Time
{
    void(*Destroy)(struct _Time* self);
    int(*DeltaTime)(struct _Time* self);

    DWORD _previousTime;
} Time;

Time* CreateTime();