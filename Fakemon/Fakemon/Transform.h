#pragma once

typedef struct _Vector2
{
    float x;
    float y;
} Vector2;

typedef struct _Transform
{
    void(*Destroy)(struct _Transform* self);

    Vector2 _position;
    Vector2 _size;
    Vector2 _velocity;
} Transform;

Transform* CreateTransform();
