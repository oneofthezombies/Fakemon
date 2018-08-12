#include "stdafx.h"
#include "GameObjectManager.h"

void _GameObjectManager_Destroy(GameObjectManager* self)
{
    if (self->_gameObjects)
        self->_gameObjects->Destroy(self->_gameObjects);

    if (self)
        free(self);
}

void _GameObjectManager_Update(GameObjectManager* self, int deltaTime)
{
    for (int i = 0; i < self->_gameObjects->_end; ++i)
    {
        GameObject* go = self->_gameObjects->At(self->_gameObjects, i);
        go->Update(go, deltaTime);
    }
}

void _GameObjectManager_RegisterGameObject(GameObjectManager* self, GameObject* go)
{
    go->_id = self->_gameObjectId++;
    self->_gameObjects->PushBack(self->_gameObjects, go);
}

GameObject* _GameObjectManager_FindWithTag(GameObjectManager* self, TagType tag)
{
    for (int i = 0; self->_gameObjects->_end; ++i)
    {
        GameObject* go = self->_gameObjects->At(self->_gameObjects, i);
        if (go->_tag == tag)
            return go;
    }

    return NULL;
}

GameObjectManager* CreateGameObjectManager()
{
    GameObjectManager* gameObjectManager = (GameObjectManager*)malloc(sizeof(GameObjectManager));

    gameObjectManager->Destroy            = _GameObjectManager_Destroy;
    gameObjectManager->Update             = _GameObjectManager_Update;
    gameObjectManager->RegisterGameObject = _GameObjectManager_RegisterGameObject;
    gameObjectManager->FindWithTag        = _GameObjectManager_FindWithTag;

    gameObjectManager->_gameObjectId = 0;
    gameObjectManager->_gameObjects = CreateList(sizeof(GameObject));

    return gameObjectManager;
}
