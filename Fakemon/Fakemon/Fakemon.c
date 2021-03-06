// Fakemon.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

typedef struct _Foo
{
    int bar;
    int bar2;
    int bar3;
} Foo;

Foo* func(Foo* e)
{
    return e;
}

int func2(int acc, Foo* lhs)
{
    return acc + lhs->bar + lhs->bar2 + lhs->bar3;
}

int main()
{
    Console* console = CreateConsole("Fakemon", WINDOW_WIDTH, WINDOW_HEIGHT);
    Game* game = CreateGame();

    while (!game->_isFinished)
    {
        console->ReadKeyEvent(console, game->HandleInput, game);
        game->Update(game);
        game->Render(game);
        console->WriteConsoleFromTextBoxes(console, game->_textBoxes);
        game->_textBoxes->Clear(game->_textBoxes);
    }

    if (game)
        game->Destroy(game);
    
    if (console)
        console->Close(console);

    //GameObject* gameObject = CreateGameObject();
    //Transform* tr = gameObject->GetComponent(gameObject, ComponentType_Transform);
    //tr->_position.x = 1;
    //printf("%f ", tr->_position.x);

    //tr = gameObject->GetComponent(gameObject, ComponentType_Transform);
    //printf("%f ", tr->_position.x);

    //system("pause");

    return 0;
}

