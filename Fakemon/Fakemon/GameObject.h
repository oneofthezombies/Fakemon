#pragma once

typedef struct _GameObject
{
    void(*Destroy)(struct _GameObject* self);
    void(*Update)(struct _GameObject* self, int deltaTime);
    void(*Render)(struct _GameObject* self);
    void(*RegisterChild)(struct _GameObject* self, struct _GameObject* child);
    void*(*GetComponent)(struct _GameObject* self, ComponentType componentType);

    int _id;
    TagType _tag;
    struct _GameObject* _parent;
    List* _children;
    Dictionary* _components;

} GameObject;

GameObject* CreateGameObject();
