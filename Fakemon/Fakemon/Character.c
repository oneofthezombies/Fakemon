#include "stdafx.h"
#include "Character.h"

void _Character_Destroy(Character* self)
{
    if (self)
        free(self);
}

void _Character_DoNothing(Character* self)
{
    // Do Nothing
}

void _Character_MoveToLeft(Character* self)
{
    self->_position.X--;
}

void _Character_MoveUp(Character* self)
{
    self->_position.Y--;
}

void _Character_MoveToRight(Character* self)
{
    self->_position.X++;
}

void _Character_MoveDown(Character* self)
{
    self->_position.Y++;
}

TextBox* _Character_ApplyExp(Character* self, int exp)
{
    self->_currentExp += exp;
    if (self->_currentExp >= self->_maxExp)
    {
        self->_level++;
        self->_currentExp -= self->_maxExp;
        self->_maxExp = self->_level * 100;
        self->_maxHp = self->_level * 100;
        self->_currentHp = self->_maxHp;

        TextBox* tb = CreateTextBox(6, 0, 40, 1, BG_WHITE, "");
        sprintf_s(tb->_text, MAX_SIZE_OF_TEXT_IN_TEXTBOX, "레벨이 %d가 되었다!! 체력이 가득 찼다.", self->_level);
        return tb;
    }

    return NULL;
}

Character* CreateCharacter(CharacterType characterType)
{
    Character* character = (Character*)malloc(sizeof(Character));

    character->Destroy = _Character_Destroy;
    character->DoNothing = _Character_DoNothing;
    character->MoveToLeft = _Character_MoveToLeft;
    character->MoveUp = _Character_MoveUp;
    character->MoveToRight = _Character_MoveToRight;
    character->MoveDown = _Character_MoveDown;
    character->ApplyExp = _Character_ApplyExp;

    character->Act = character->DoNothing;

    character->_characterType = characterType;
    character->_maxExp = 0;
    character->_currentExp = 0;
    COORD position = { 0, 0 };
    character->_position = position;

    switch (characterType)
    {
    case CharacterType_Ash:
    {
        character->_level = 1;
        character->_maxExp = character->_level * 100;
        character->_maxHp = 100;
        COORD ashPosition = { 7, 7 };
        character->_position = ashPosition;
        character->_skills[0] = SkillType_Ember;
        character->_skills[1] = SkillType_WaterGun;
        character->_skills[2] = SkillType_VineWhip;
    }
    break;
    case CharacterType_Oddish:
    {
        character->_level = 1;
        character->_maxHp = 10;
        character->_skills[0] = SkillType_Tackle;
        character->_skills[1] = SkillType_Growth;
        character->_skills[2] = SkillType_Crouching;
    }
    break;
    case CharacterType_Mew:
    {
        character->_level = 100;
        character->_maxHp = 10000;
        for (int i = 0; i < SIZE_OF_SKILLS; ++i)
        {
            character->_skills[i] = SkillType_HyperBeam;
        }
    }
    break;
    default:
    {
        character->_level = 0;
        character->_maxHp = 0;
        for (int i = 0; i < SIZE_OF_SKILLS; ++i)
        {
            character->_skills[i] = SkillType_Splash;
        }
    }
    break;
    }

    character->_currentHp = character->_maxHp;

    return character;
}
