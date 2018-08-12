#pragma once

typedef struct _Game
{
    void(*Destroy)(struct _Game* self);
    void(*HandleInputOnField)(struct _Game* self, WORD key);
    void(*HandleInputOnBattle)(struct _Game* self, WORD key);
    void(*UpdateOnField)(struct _Game* self);
    void(*UpdateOnBattle)(struct _Game* self);
    void(*RenderOnField)(struct _Game* self);
    void(*RenderOnBattle)(struct _Game* self);
    void(*SetScene)(struct _Game* self, SceneType sceneType);
    int(*WriteToFile)(struct _Game* self, char* fileName);
    int(*ReadFromFile)(struct _Game* self, char* fileName);
    int(*Backup)(struct _Game* self, char* src, char* dst);

    void(*HandleInput)(struct _Game* self, WORD key);
    void(*Update)(struct _Game* self);
    void(*Render)(struct _Game* self);

    Random* _random;
    Time* _time;
    TextBoxes* _textBoxes;
    TextBoxes* _fieldLog;
    TextBoxes* _battleLog;
    Map* _map;
    Character* _ash;
    Character* _pokemon;

    int _isFinished;
    int _turn;
    int _isMoved;
    COORD _cursorPosition;

    SceneType _sceneType;
    BattleSceneType _battleSceneType;
    int _isMenu;

    int _backupCoolTime;
    int _backupCoolDown;
    unsigned long _previousTime;
} Game;

Game* CreateGame();