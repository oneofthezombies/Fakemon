#include "stdafx.h"
#include "Console.h"

void _Console_Destroy(Console* self)
{
	if (!self) return;

    for (int i = 0; i < NUMBER_OF_SCREEN_BUFFER; ++i)
    {
		if (self->_screenBuffer && 
			self->_screenBuffer[i])
		{
			free(self->_screenBuffer[i]->charInfos);
			free(self->_screenBuffer[i]);
		}
    }
    free(self->_screenBuffer);

    free(self->_errorInfo->message);
    free(self->_errorInfo);

    free(self->_inputBuffer);

    free(self->_title);
    free(self);
}

void _Console_ReadKeyEvent(Console* self, void(*HandleInput)(Game* game, WORD key), Game* game)
{
    if (!ReadConsoleInput(self->_hStdin, self->_inputBuffer, SIZE_OF_INPUT_BUFFER, &self->_readNum))
    {
        strcat_s(self->_errorInfo->message, sizeof(self->_errorInfo->message), "Failed to read console input\n");
        self->WriteLog(self);
        self->Close(self);
    }

    for (DWORD i = 0; i < self->_readNum; ++i)
    {
        switch (self->_inputBuffer[i].EventType)
        {
        case KEY_EVENT:
        {
            KEY_EVENT_RECORD ker = self->_inputBuffer[i].Event.KeyEvent;
            if (ker.bKeyDown)
            {
                HandleInput(game, ker.wVirtualKeyCode);
            }
        }
        break;
        }
    }
}

void _Console_WriteLog(Console* self)
{
    FILE* textFile = NULL;

    fopen_s(&textFile, "errorlog.txt", "a+");
    if (textFile == NULL)
    {
        puts("Failed to open errorlog.txt");
        return;
    }

    fputs(self->_errorInfo->message, textFile);
    fclose(textFile);
}

void _Console_Close(Console* self)
{
    SetConsoleMode(self->_hStdin, self->_saveOldMode);

    for (int i = 0; i < NUMBER_OF_SCREEN_BUFFER; ++i)
    {
        CloseHandle(self->_screenBuffer[i]->handle);
    }

    self->Destroy(self);
}

void _Console_WriteConsoleFromTextBoxes(Console* self, TextBoxes* textBoxes)
{
    // used buffer
    ScreenBuffer* sb1 = self->_screenBuffer[self->_screenBufferFlag];

    // swap buffer
    self->_screenBufferFlag = !self->_screenBufferFlag;

    // to be used buffer
    ScreenBuffer* sb2 = self->_screenBuffer[self->_screenBufferFlag];

    // clear console screen buffer
    for (int i = 0; i < self->_windowSize.X * self->_windowSize.Y; ++i)
    {
        sb2->charInfos[i].Attributes = 255;
        sb2->charInfos[i].Char.AsciiChar = ' ';
    }

    for (int i = 0; i < textBoxes->_end; ++i)
    {
        // fucking error
        self->Draw(self, sb2->charInfos, textBoxes->_textBoxes[i]);
    }

    COORD coord = { 0, 0 };
    WriteConsoleOutput(sb2->handle, sb2->charInfos, self->_windowSize, coord, &self->_windowRect);

    // fps 60
    Sleep(17);
    // fps 30
    //Sleep(33);

    SetConsoleActiveScreenBuffer(sb2->handle);
}

void _Console_Draw(Console* self, CHAR_INFO charInfos[], TextBox* textBox)
{
    SHORT width = textBox->_size.X;
    SHORT height = textBox->_size.Y;
    SHORT offsetX = textBox->_offset.X;
    SHORT offsetY = textBox->_offset.Y;
    WORD color = textBox->_color;

    int textIndex = 0;
    for (int i = offsetY; i < offsetY + height; ++i)
    {
        for (int j = offsetX; j < offsetX + width; ++j)
        {
            if (textBox->_text[textIndex] == 0)
            {
                charInfos[i * self->_windowSize.X + j].Char.AsciiChar = ' ';
            }
            else
            {
                charInfos[i * self->_windowSize.X + j].Char.AsciiChar = textBox->_text[textIndex++];
            }
            charInfos[i * self->_windowSize.X + j].Attributes = color;
        }
    }
}

Console* CreateConsole(char* title, int width, int height)
{
    Console* console = (Console*)malloc(sizeof(Console));

    console->Destroy = _Console_Destroy;
    console->ReadKeyEvent = _Console_ReadKeyEvent;
    console->WriteLog = _Console_WriteLog;
    console->Close = _Console_Close;
    console->WriteConsoleFromTextBoxes = _Console_WriteConsoleFromTextBoxes;
    console->Draw = _Console_Draw;

    console->_title = (char*)malloc(sizeof(char) * MAX_SIZE_OF_TITLE);

    strcpy_s(console->_title, MAX_SIZE_OF_TITLE, title);
    COORD coord = { width, height };
    console->_windowSize = coord;
    SMALL_RECT sr = { 0, 0, console->_windowSize.X - 1, console->_windowSize.Y - 1 };
    console->_windowRect = sr;
    console->_hStdin = NULL;
    console->_hStdout = NULL;
    console->_screenBufferFlag = 0;
    console->_readNum = 0;
    console->_mode = 0;
    console->_saveOldMode = 0;

    console->_inputBuffer = (INPUT_RECORD*)malloc(sizeof(INPUT_RECORD) * SIZE_OF_INPUT_BUFFER);

    console->_errorInfo = (ErrorInfo*)malloc(sizeof(ErrorInfo));

	const int messageSize = sizeof(char) * MAX_SIZE_OF_ERROR_MESSAGE;
    console->_errorInfo->message = (char*)malloc(messageSize);
	memset(console->_errorInfo->message, 0, messageSize);

    console->_hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
    if (console->_hStdout == INVALID_HANDLE_VALUE)
    {
        strcat_s(console->_errorInfo->message, MAX_SIZE_OF_ERROR_MESSAGE, "Failed to get stdout handle.\n");
        console->WriteLog(console);
        console->Destroy(console);
        exit(EXIT_FAILURE);
    }

    console->_hStdin = GetStdHandle(STD_INPUT_HANDLE);
    if (console->_hStdin == INVALID_HANDLE_VALUE)
    {
        strcat_s(console->_errorInfo->message, MAX_SIZE_OF_ERROR_MESSAGE, "Failed to get stdin handle.\n");
        console->WriteLog(console);
        console->Destroy(console);
        exit(EXIT_FAILURE);
    }

    if (!GetConsoleMode(console->_hStdin, &console->_saveOldMode))
    {
        strcat_s(console->_errorInfo->message, MAX_SIZE_OF_ERROR_MESSAGE, "Failed to get console mode.\n");
        SetConsoleMode(console->_hStdin, console->_saveOldMode);
        console->WriteLog(console);
        console->Destroy(console);
        exit(EXIT_FAILURE);
    }

    if (!SetConsoleScreenBufferSize(console->_hStdout, console->_windowSize))
    {
        strcat_s(console->_errorInfo->message, MAX_SIZE_OF_ERROR_MESSAGE, "Failed to set console screen buffer size.\n");
        console->WriteLog(console);
        console->Destroy(console);
        exit(EXIT_FAILURE);
    }

    if (!SetConsoleWindowInfo(console->_hStdout, TRUE, &console->_windowRect))
    {
        strcat_s(console->_errorInfo->message, MAX_SIZE_OF_ERROR_MESSAGE, "Failed to set console window info.\n");
        console->WriteLog(console);
        console->Destroy(console);
        exit(EXIT_FAILURE);
    }

    if (!SetConsoleTitle(console->_title))
    {
        strcat_s(console->_errorInfo->message, MAX_SIZE_OF_ERROR_MESSAGE, "Failed to set console title.\n");
        console->WriteLog(console);
        console->Destroy(console);
        exit(EXIT_FAILURE);
    }

    CONSOLE_CURSOR_INFO info;
    info.dwSize = 80;
    info.bVisible = FALSE;

	const int screenBufferPtrSize = sizeof(ScreenBuffer*) * NUMBER_OF_SCREEN_BUFFER;
    console->_screenBuffer = (ScreenBuffer**)malloc(screenBufferPtrSize);
	memset(console->_screenBuffer, 0, screenBufferPtrSize);

    for (int i = 0; i < NUMBER_OF_SCREEN_BUFFER; ++i)
    {
        console->_screenBuffer[i] = (ScreenBuffer*)malloc(sizeof(ScreenBuffer));
        console->_screenBuffer[i]->charInfos = (CHAR_INFO*)malloc(sizeof(CHAR_INFO) * console->_windowSize.X * console->_windowSize.Y);
        console->_screenBuffer[i]->handle = CreateConsoleScreenBuffer(GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);

        if (!SetConsoleScreenBufferSize(console->_screenBuffer[i]->handle, console->_windowSize))
        {
            strcat_s(console->_errorInfo->message, MAX_SIZE_OF_ERROR_MESSAGE, "Failed to set console screen buffer size.\n");
            console->WriteLog(console);
            console->Destroy(console);
            exit(EXIT_FAILURE);
        }

        if (!SetConsoleWindowInfo(console->_screenBuffer[i]->handle, TRUE, &console->_windowRect))
        {
            strcat_s(console->_errorInfo->message, MAX_SIZE_OF_ERROR_MESSAGE, "Failed to set console window info.\n");
            console->WriteLog(console);
            console->Destroy(console);
            exit(EXIT_FAILURE);
        }

        SetConsoleCursorInfo(console->_screenBuffer[i]->handle, &info);
    }

    return console;
}
