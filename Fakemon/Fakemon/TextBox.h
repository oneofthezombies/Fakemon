#pragma once

#define MAX_SIZE_OF_TEXT_IN_TEXTBOX 128

typedef struct _TextBox
{
    void(*Destroy)(struct _TextBox* self);
    struct _TextBox*(*Duplicate)(struct _TextBox* self);

    COORD _offset;
    COORD _size;
    WORD _color;
    char _text[MAX_SIZE_OF_TEXT_IN_TEXTBOX];
} TextBox;

TextBox* CreateTextBox(int offsetX, int offsetY, int sizeX, int sizeY, WORD color, char* text);

typedef struct _TextBoxes
{
    void(*Destroy)(struct _TextBoxes* self);
    int(*PushBack)(struct _TextBoxes* self, TextBox* textBox);
    int(*PopFront)(struct _TextBoxes* self);
    void(*PushBackForce)(struct _TextBoxes* self, TextBox* textBox);
    void(*Clear)(struct _TextBoxes* self);

    TextBox** _textBoxes;
    int _size;
    int _end;
} TextBoxes;

TextBoxes* CreateTextBoxes(int size);