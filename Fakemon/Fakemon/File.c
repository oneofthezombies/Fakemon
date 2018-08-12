#include "stdafx.h"
#include "File.h"

int WriteLogToFile(char* fileName, char* text)
{
    FILE* file = NULL;
    fopen_s(&file, fileName, "a");

    if (!file)
    {
        printf("%s file open failed.\n", fileName);
        return FALSE;
    }

    fputs(text, file);
    fclose(file);

    return TRUE;
}
