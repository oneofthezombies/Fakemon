#include "stdafx.h"
#include "TextBox.h"

void _TextBox_Destroy(TextBox* self)
{
    free(self);
}

TextBox* _TextBox_Duplicate(TextBox* self)
{
    TextBox* textBox = (TextBox*)malloc(sizeof(TextBox));
    
    textBox->Destroy = _TextBox_Destroy;
    textBox->Duplicate = _TextBox_Duplicate;

    textBox->_offset = self->_offset;
    textBox->_size = self->_size;
    textBox->_color = self->_color;
    strcpy_s(textBox->_text, MAX_SIZE_OF_TEXT_IN_TEXTBOX, self->_text);

    return textBox;
}

TextBox* CreateTextBox(int offsetX, int offsetY, int sizeX, int sizeY, WORD color, char* text)
{
    TextBox* tb = (TextBox*)malloc(sizeof(TextBox));

    tb->Destroy = _TextBox_Destroy;
    tb->Duplicate = _TextBox_Duplicate;

    COORD offset = { offsetX, offsetY };
    tb->_offset = offset;
    COORD size = { sizeX, sizeY };
    tb->_size = size;
    tb->_color = color;
    sprintf_s(tb->_text, MAX_SIZE_OF_TEXT_IN_TEXTBOX, text);

    return tb;
}

void _TextBoxes_Destroy(TextBoxes* self)
{
    for (int i = 0; i < self->_end; ++i)
    {
        if (self->_textBoxes[i])
            free(self->_textBoxes[i]);
    }
    if (self->_textBoxes)
        free(self->_textBoxes);
    free(self);
}

int _TextBoxes_PushBack(TextBoxes* self, TextBox* textBox)
{
    if (self->_end < self->_size)
    {
        self->_textBoxes[self->_end++] = textBox;
        return TRUE;
    }
    return FALSE;
}

void _TextBoxes_Clear(TextBoxes* self)
{
    for (int i = 0; i < self->_end; ++i)
    {
        if (self->_textBoxes[i])
            free(self->_textBoxes[i]);
    }
    self->_end = 0;
}

int _TextBoxes_PopFront(TextBoxes* self)
{
    if (self->_end > 0)
    {
        free(self->_textBoxes[0]);
        for (int i = 1; i < self->_end; ++i)
        {
            self->_textBoxes[i - 1] = self->_textBoxes[i];
        }
        self->_end--;
        return TRUE;
    }
    return FALSE;
}

void _TextBoxes_PushBackForce(TextBoxes* self, TextBox* textBox)
{
    if (self->_end == self->_size)
    {
        self->PopFront(self);
        self->PushBack(self, textBox);
    }
    else
    {
        self->PushBack(self, textBox);
    }
}

TextBoxes* CreateTextBoxes(int size)
{
    TextBoxes* tbs = (TextBoxes*)malloc(sizeof(TextBoxes));

    tbs->Destroy = _TextBoxes_Destroy;
    tbs->Clear = _TextBoxes_Clear;
    tbs->PushBack = _TextBoxes_PushBack;
    tbs->PopFront = _TextBoxes_PopFront;
    tbs->PushBackForce = _TextBoxes_PushBackForce;

    tbs->_textBoxes = (TextBox**)malloc(sizeof(TextBox*) * size);
    tbs->_size = size;
    tbs->_end = 0;

    return tbs;
}

