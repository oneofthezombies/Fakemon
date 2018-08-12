#pragma once

#define LIST_ERROR_LOG_FILE "list_error_log.txt"

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
