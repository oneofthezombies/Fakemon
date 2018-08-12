#pragma once

#define MAX_SIZE_OF_TITLE 128
#define MAX_SIZE_OF_ERROR_MESSAGE 256
#define SIZE_OF_INPUT_BUFFER 128
#define NUMBER_OF_SCREEN_BUFFER 2

typedef enum _VirtualKey
{
    Space = 32,
    Left = 37,
    Up = 38,
    Right = 39,
    Down = 40
} VirtualKey;

typedef struct _ErrorInfo
{
    char* message;
} ErrorInfo;

typedef struct _ScreenBuffer
{
    HANDLE handle;
    CHAR_INFO* charInfos;
} ScreenBuffer;

typedef struct _Console
{
    void(*Destroy)(struct _Console* self);
    void(*ReadKeyEvent)(struct _Console* self, void(*HandleInput)(Game* game, WORD key), Game* game);
    void(*WriteLog)(struct _Console* self);
    void(*Close)(struct _Console* self);
    void(*WriteConsoleFromTextBoxes)(struct _Console* self, TextBoxes* textBoxes);
    void(*Draw)(struct _Console* self, CHAR_INFO charInfos[], TextBox* textBox);

    HANDLE _hStdout;
    HANDLE _hStdin;

    // to set window
    char* _title;
    COORD _windowSize;
    SMALL_RECT _windowRect;

    // for write to screen
    ScreenBuffer** _screenBuffer;
    int _screenBufferFlag;

    // to read key input
    DWORD _readNum;
    DWORD _mode;
    DWORD _saveOldMode;
    INPUT_RECORD* _inputBuffer;

    ErrorInfo* _errorInfo;

} Console;

Console* CreateConsole(char* title, int width, int height);