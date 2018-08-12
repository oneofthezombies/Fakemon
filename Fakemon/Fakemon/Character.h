#pragma once

#define SIZE_OF_SKILLS 3

typedef struct _Character
{
    void(*Destroy)(struct _Character* self);
    void(*DoNothing)(struct _Character* self);
    void(*MoveToLeft)(struct _Character* self);
    void(*MoveUp)(struct _Character* self);
    void(*MoveToRight)(struct _Character* self);
    void(*MoveDown)(struct _Character* self);
    TextBox*(*ApplyExp)(struct _Character* self, int exp);

    void(*Act)(struct _Character* self);

    CharacterType _characterType;
    int _level;
    int _currentExp;
    int _maxExp;
    int _currentHp;
    int _maxHp;
    COORD _position;
    SkillType _skills[SIZE_OF_SKILLS];
    SkillType _currentSkill;
} Character;

Character* CreateCharacter(CharacterType characterType);
