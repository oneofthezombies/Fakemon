# Fakemon
simple pokemon like console game.

# Description
this is written in C. but i implement this using OOP.  
structure has some function pointer and variables.  
and i implement list container likely std::list.  
my list has push_back and size method.

i'll rewrite soon. because this is not running on current environment. :(

# Sample Code

```
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
```
```
typedef struct _List
{
    void(*Destroy)(struct _List* self);
    void(*PushBack)(struct _List* self, void* element);
    void(*Clear)(struct _List* self);
    void*(*At)(struct _List* self, int index);
    int(*Size)(struct _List* self);
    struct _List*(*Map)(struct _List* self, void*(*unaryOp)(void* element));
    void*(*Foldl)(struct _List* self, void*(*binaryOp)(void* lhs, void* rhs), void* accumulator);

    int _capacity;
    int _end;
    int _elementSize;
    void** _data;
} List;

List* CreateList(int elementSize);
```
