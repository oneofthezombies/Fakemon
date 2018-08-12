#include "stdafx.h"
#include "List.h"

void _List_Destroy(List* self)
{
    for (int i = 0; i < self->_end; ++i)
        if (self->_data[i])
            free(self->_data[i]);

    if (self)
        free(self);
}

void _List_PushBack(List* self, void* element)
{
    if (self->_end == self->_capacity)
    {
        if (self->_capacity == 0)
        {
            self->_capacity = 2;
            self->_data = malloc(sizeof(void*) * self->_capacity);
            if (self->_data == NULL)
            {
                WriteLogToFile(LIST_ERROR_LOG_FILE, "malloc() failed.");
                exit(EXIT_FAILURE);
            }
        }
        else
        {
            self->_capacity *= 2;
            self->_data = realloc(self->_data, sizeof(void*) * self->_capacity);
            if (self->_data == NULL)
            {
                WriteLogToFile(LIST_ERROR_LOG_FILE, "realloc() failed.");
                exit(EXIT_FAILURE);
            }
        }
    }

    self->_data[self->_end] = malloc(self->_elementSize);
    if (memcpy_s(self->_data[self->_end], self->_elementSize, element, self->_elementSize))
    {
        WriteLogToFile(LIST_ERROR_LOG_FILE, "memcpy_s() failed.");
        exit(EXIT_FAILURE);
    }
    self->_end++;
}

void _List_Clear(List* self)
{
    self->_end = 0;
}

void* _List_At(List* self, int index)
{
    if (index >= self->_end)
        return NULL;
    
    return self->_data[index];
}

int _List_Size(List* self)
{
    return self->_end;
}

List* _List_Map(List* self, void*(*unaryOp)(void* element))
{
    for (int i = 0; i < self->_end; ++i)
        self->_data[i] = unaryOp(self->_data[i]);

    return self;
}

void* _List_Foldl(List* self, void*(*binaryOp)(void* lhs, void* rhs), void* accumulator)
{
    for (int i = 0; i < self->_end; ++i)
    {
        accumulator = binaryOp(accumulator, self->_data[i]);
    }

    return accumulator;
}

List* CreateList(int elementSize)
{
    List* list = (List*)malloc(sizeof(List));

    list->Destroy  = _List_Destroy;
    list->PushBack = _List_PushBack;
    list->Clear    = _List_Clear;
    list->At       = _List_At;
    list->Size     = _List_Size;
    list->Map      = _List_Map;
    list->Foldl    = _List_Foldl;
   
    list->_capacity    = 0;
    list->_end         = 0;
    list->_elementSize = elementSize;
    list->_data        = NULL;

    return list;
}
