#include "stdafx.h"
#include "GameObject.h"

void _GameObject_Destroy(GameObject* self)
{
    if (self->_children)
        self->_children->Destroy(self->_children);

    if (self->_components)
        self->_components->Destroy(self->_components);

    if (self)
        free(self);
}

void _GameObject_Update(GameObject* self, int deltaTime)
{
    for (int i = 0; i < self->_children->_end; ++i)
    {
        GameObject* child = self->_children->At(self->_children, i);
        child->Update(child, deltaTime);
    }
}

void _GameObject_Render(GameObject* self)
{
    for (int i = 0; i < self->_children->_end; ++i)
    {
        GameObject* child = self->_children->At(self->_children, i);
        child->Render(child);
    }
}

void _GameObject_RegisterChild(GameObject* self, GameObject* child)
{
    child->_parent = self;
    self->_children->PushBack(self->_children, child);
}

void* _GameObject_GetComponent(GameObject* self, ComponentType componentType)
{
    for (int i = 0; i < self->_components->_data->_end; ++i)
    {
        Pair* pair = (Pair*)self->_components->_data->_data[i];
        if (pair->_key == (unsigned int)componentType)
        {
            return pair->_value;
        }
    }

    Component* component = CreateComponent(componentType);
    if (component == NULL)
        return NULL;

    Pair* newPair = CreatePair();
    newPair->_key = (unsigned int)componentType;
    newPair->_value = component;

    self->_components->_data->PushBack(self->_components->_data, newPair);

    return newPair->_value;
}

GameObject* CreateGameObject()
{
    GameObject* gameObject = (GameObject*)malloc(sizeof(GameObject));

    gameObject->Destroy       = _GameObject_Destroy;
    gameObject->Update        = _GameObject_Update;
    gameObject->Render        = _GameObject_Render;
    gameObject->RegisterChild = _GameObject_RegisterChild;
    gameObject->GetComponent  = _GameObject_GetComponent;

    gameObject->_id = -1;
    gameObject->_tag = TagType_Idle;
    gameObject->_parent = NULL;
    gameObject->_children = CreateList(sizeof(GameObject));
    gameObject->_components = CreateDictionary();

    return gameObject;
}
