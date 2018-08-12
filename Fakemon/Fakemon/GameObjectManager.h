#pragma once
typedef struct _GameObjectManager
{
    void(*Destroy)(struct _GameObjectManager* self);
    void(*Update)(struct _GameObjectManager* self, int deltaTime);
    void(*RegisterGameObject)(struct _GameObjectManager* self, GameObject* gameObject);
    GameObject*(*FindWithTag)(struct _GameObjectManager* self, TagType tag);

    int _gameObjectId;
    List* _gameObjects;

} GameObjectManager;

GameObjectManager* CreateGameObjectManager();