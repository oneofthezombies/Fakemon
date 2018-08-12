#include "stdafx.h"
#include "Game.h"

void _Game_Destroy(Game* self)
{
    if (self->_random)
        self->_random->Destroy(self->_random);

    if (self->_time)
        self->_time->Destroy(self->_time);
    
    if (self->_textBoxes)
        self->_textBoxes->Destroy(self->_textBoxes);

    if (self->_fieldLog)
        self->_fieldLog->Destroy(self->_fieldLog);

    if (self->_battleLog)
        self->_battleLog->Destroy(self->_battleLog);

    if (self->_map)
        self->_map->Destroy(self->_map);

    if (self->_ash)
        self->_ash->Destroy(self->_ash);
    
    if (self->_pokemon)
        self->_pokemon->Destroy(self->_pokemon);

    if (self)
        free(self);
}

void _Game_HandleInputOnField(Game* self, WORD key)
{
    COORD pos = self->_ash->_position;
    MapType** map = self->_map->_map;

    switch (key)
    {
    case 'Z':
    {
        if (self->_isMenu)
        {
            switch (self->_cursorPosition.Y)
            {
            case 0:
            {
                if (self->WriteToFile(self, "fakemon.txt"))
                {
                    self->_fieldLog->PushBackForce(self->_fieldLog,
                                                   CreateTextBox(6, 0, 40, 1, BG_D_BLUE | FG_WHITE, "���̺� �Ϸ�."));
                    //SYSTEMTIME st;
                    //GetSystemTime(&st);
                    //TextBox* tb = CreateTextBox(6, 0, 40, 1, BG_D_BLUE | FG_WHITE, "���̺� �Ϸ�.");
                    //sprintf_s(tb->_text, MAX_SIZE_OF_TEXT_IN_TEXTBOX, "%d %d %d %d", st.wHour + 9, st.wMinute, st.wSecond, st.wMilliseconds);
                    //self->_fieldLog->PushBackForce(self->_fieldLog, tb);
                }
                else
                {
                    self->_fieldLog->PushBackForce(self->_fieldLog,
                                                   CreateTextBox(6, 0, 40, 1, BG_D_BLUE | FG_WHITE, "���̺� ����."));
                }
            }
            break;
            case 1:
            {
                if (self->ReadFromFile(self, "fakemon.txt"))
                {
                    self->_fieldLog->PushBackForce(self->_fieldLog,
                                                   CreateTextBox(6, 0, 40, 1, BG_D_BLUE | FG_WHITE, "�ε� �Ϸ�."));
                }
                else
                {
                    self->_fieldLog->PushBackForce(self->_fieldLog,
                                                   CreateTextBox(6, 0, 40, 1, BG_D_BLUE | FG_WHITE, "�ε� ����."));
                }
            }
            break;
            case 2:
            {
                self->_isFinished = TRUE;
            }
            break;
            }
        }
    }
    break;
    case 'C':
    {
        self->_isMenu = !self->_isMenu;
    }
    break;
    case Left:
    {
        if (!self->_isMenu)
        {
            self->_turn++;

            MapType leftMap = map[pos.Y][pos.X - 1];
            if (leftMap != MapType_Wall && leftMap != MapType_Door)
            {
                self->_isMoved = TRUE;
                self->_ash->Act = self->_ash->MoveToLeft;
                //self->_fieldLog->PushBackForce(self->_fieldLog, 
                //                               CreateTextBox(6, 0, 40, 1, BG_WHITE, "�������� �̵��ߴ�."));
            }
            else if (leftMap == MapType_Wall)
            {
                self->_fieldLog->PushBackForce(self->_fieldLog,
                                               CreateTextBox(6, 0, 40, 1, BG_WHITE | FG_D_RED, "���� ���� ���� �̵��� �� ����."));
            }
            else if (leftMap == MapType_Door)
            {
                self->_fieldLog->PushBackForce(self->_fieldLog,
                                               CreateTextBox(6, 0, 40, 1, BG_WHITE | FG_D_BLUE, "���� ��� �ִ�."));
            }
        }
    }
    break;
    case Up:
    {
        if (!self->_isMenu)
        {
            self->_turn++;

            MapType upMap = map[pos.Y - 1][pos.X];
            if (upMap != MapType_Wall && upMap != MapType_Door)
            {
                self->_isMoved = TRUE;
                self->_ash->Act = self->_ash->MoveUp;
                //self->_fieldLog->PushBackForce(self->_fieldLog,
                //                               CreateTextBox(6, 0, 40, 1, BG_WHITE, "�������� �̵��ߴ�."));
            }
            else if (upMap == MapType_Wall)
            {
                self->_fieldLog->PushBackForce(self->_fieldLog,
                                               CreateTextBox(6, 0, 40, 1, BG_WHITE | FG_D_RED, "���� ���� ���� �̵��� �� ����."));
            }
            else if (upMap == MapType_Door)
            {
                self->_fieldLog->PushBackForce(self->_fieldLog,
                                               CreateTextBox(6, 0, 40, 1, BG_WHITE | FG_D_BLUE, "���� ��� �ִ�."));
            }
        }
        else
        {
            if (self->_cursorPosition.Y > 0)
            {
                self->_cursorPosition.Y--;
            }
        }
    }
    break;
    case Right:
    {
        if (!self->_isMenu)
        {
            self->_turn++;

            MapType rightMap = map[pos.Y][pos.X + 1];
            if (rightMap != MapType_Wall && rightMap != MapType_Door)
            {
                self->_isMoved = TRUE;
                self->_ash->Act = self->_ash->MoveToRight;
                //self->_fieldLog->PushBackForce(self->_fieldLog,
                //                               CreateTextBox(6, 0, 40, 1, BG_WHITE, "���������� �̵��ߴ�."));
            }
            else if (rightMap == MapType_Wall)
            {
                self->_fieldLog->PushBackForce(self->_fieldLog,
                                               CreateTextBox(6, 0, 40, 1, BG_WHITE | FG_D_RED, "���� ���� ���� �̵��� �� ����."));
            }
            else if (rightMap == MapType_Door)
            {
                self->_fieldLog->PushBackForce(self->_fieldLog,
                                               CreateTextBox(6, 0, 40, 1, BG_WHITE | FG_D_BLUE, "���� ��� �ִ�."));
            }
        }
    }
    break;
    case Down:
    {
        if (!self->_isMenu)
        {
            self->_turn++;

            MapType downMap = map[pos.Y + 1][pos.X];
            if (downMap != MapType_Wall && downMap != MapType_Door)
            {
                self->_isMoved = TRUE;
                self->_ash->Act = self->_ash->MoveDown;
                //self->_fieldLog->PushBackForce(self->_fieldLog,
                //                               CreateTextBox(6, 0, 40, 1, BG_WHITE, "�Ʒ������� �̵��ߴ�."));
            }
            else if (downMap == MapType_Wall)
            {
                self->_fieldLog->PushBackForce(self->_fieldLog,
                                               CreateTextBox(6, 0, 40, 1, BG_WHITE | FG_D_RED, "���� ���� ���� �̵��� �� ����."));
            }
            else if (downMap == MapType_Door)
            {
                self->_fieldLog->PushBackForce(self->_fieldLog,
                                               CreateTextBox(6, 0, 40, 1, BG_WHITE | FG_D_BLUE, "���� ��� �ִ�."));
            }
        }
        else
        {
            if (self->_cursorPosition.Y < 2)
            {
                self->_cursorPosition.Y++;
            }
        }
    }
    break;
    default:
    {
        self->_ash->Act = self->_ash->DoNothing;
    }
    break;
    }
}

void _Game_HandleInputOnBattle(Game* self, WORD key)
{
    switch (key)
    {
    case 'Z':
    {
        switch (self->_battleSceneType)
        {
        case BattleSceneType_Idle:
        {
            switch (self->_cursorPosition.Y)
            {
            case 0:
            {
                self->_battleSceneType = BattleSceneType_Skills;
            }
            break;
            case 1:
            {
                self->_battleSceneType = BattleSceneType_BeFriend;
            }
            break;
            case 2:
            {
                self->SetScene(self, SceneType_Field);
                self->_pokemon->Destroy(self->_pokemon);
                self->_fieldLog->PushBackForce(self->_fieldLog,
                                               CreateTextBox(6, 0, 40, 1, BG_WHITE, "���������� �����ƴ�!"));
            }
            break;
            }
        }
        break;
        case BattleSceneType_Skills:
        {
            self->_battleSceneType = BattleSceneType_Battle;
            self->_ash->_currentSkill = self->_ash->_skills[self->_cursorPosition.Y];
        }
        break;
        }
    }
    break;
    case 'X':
    {
        switch (self->_battleSceneType)
        {
        case BattleSceneType_Skills:
        {
            self->_battleSceneType = BattleSceneType_Idle;
        }
        break;
        }
    }
    break;
    case Up:
    {
        if (self->_cursorPosition.Y > 0)
        {
            self->_cursorPosition.Y--;
        }
    }
    break;
    case Down:
    {
        if (self->_cursorPosition.Y < 2)
        {
            self->_cursorPosition.Y++;
        }
    }
    break;
    }
}

void _Game_UpdateOnField(Game* self)
{
    self->_ash->Act(self->_ash);
    self->_ash->Act = self->_ash->DoNothing;

    if (self->_isMoved)
    {
        self->_isMoved = FALSE;

        COORD pos = self->_ash->_position;
        MapType** map = self->_map->_map;
        
        switch (map[pos.Y][pos.X])
        {
        case MapType_Grass:
        {
            if (!self->_random->GetInt(10))
            {
                self->_pokemon = CreateCharacter(CharacterType_Oddish);
                self->SetScene(self, SceneType_Battle);
                self->_battleLog->PushBackForce(self->_battleLog,
                                                CreateTextBox(6, 0, 40, 1, BG_WHITE | FG_D_GREEN, "�߻��� �ѹ��ʰ� ��Ÿ����!"));
            }
        }
        break;
        case MapType_TallGrass:
        {
            if (!self->_random->GetInt(10))
            {
                self->_pokemon = CreateCharacter(self->_random->GetIntFromTo(1, 2));
                self->SetScene(self, SceneType_Battle);
                if (self->_pokemon->_characterType == CharacterType_Oddish)
                {
                    self->_battleLog->PushBackForce(self->_battleLog,
                                                    CreateTextBox(6, 0, 40, 1, BG_WHITE | FG_D_GREEN, "�߻��� �ѹ��ʰ� ��Ÿ����!"));
                }
                else
                {
                    self->_battleLog->PushBackForce(self->_battleLog,
                                                    CreateTextBox(6, 0, 40, 1, BG_WHITE | FG_D_MAGENTA, "�߻��� �°� ��Ÿ����!"));
                }
            }
        }
        break;
        case MapType_Switch:
        {
            for (int i = 0; i < 3; ++i)
            {
                map[5 + i][6] = MapType_Road;
            }
            self->_fieldLog->PushBackForce(self->_fieldLog,
                                           CreateTextBox(6, 0, 40, 1, BG_WHITE, "����ġ�� ������."));
            self->_fieldLog->PushBackForce(self->_fieldLog,
                                           CreateTextBox(6, 0, 40, 1, BG_WHITE, "�°� ������ �� ���� ���� �������!!"));
        }
        break;
        }
    }

    unsigned long currentTime = GetTickCount();
    unsigned long deltaTime = currentTime - self->_previousTime;
    self->_previousTime = currentTime;
    self->_backupCoolDown -= (int)deltaTime;
    if (self->_backupCoolDown < 0)
    {
        self->_backupCoolDown = self->_backupCoolTime;

        if (self->Backup(self, "fakemon.txt", "fakemon_backup.txt"))
        {
            self->_fieldLog->PushBackForce(self->_fieldLog,
                                           CreateTextBox(6, 0, 40, 1, BG_D_BLUE | FG_WHITE, "��� �Ϸ�."));
        }
        else
        {
            self->_fieldLog->PushBackForce(self->_fieldLog,
                                           CreateTextBox(6, 0, 40, 1, BG_D_BLUE | FG_WHITE, "��� ����."));
        }
    }
}

void _Game_UpdateOnBattle(Game* self)
{
    switch (self->_battleSceneType)
    {
    case BattleSceneType_Battle:
    {
        switch (self->_pokemon->_characterType)
        {
        case CharacterType_Oddish:
        {
            switch (self->_ash->_currentSkill)
            {
            case SkillType_Ember:
            {
                self->_battleLog->PushBackForce(self->_battleLog,
                                                CreateTextBox(6, 0, 40, 1, BG_WHITE | FG_RED, "�����(��) �Ҳɼ��ʸ�(��) ����ߴ�!!"));

                switch (self->_pokemon->_skills[self->_random->GetInt(3)])
                {
                case SkillType_Crouching:
                {
                    self->_pokemon->_currentHp -= 0;

                    self->_battleLog->PushBackForce(self->_battleLog,
                                                    CreateTextBox(6, 0, 40, 1, BG_WHITE, "�ѹ��ʴ�(��) ��ũ���⸦(��) ����ߴ�!!"));
                    self->_battleLog->PushBackForce(self->_battleLog,
                                                    CreateTextBox(6, 0, 40, 1, BG_WHITE, "�Ҳɼ�����(��) ������ �ʾҴ�..."));
                }
                break;
                case SkillType_Growth:
                {
                    self->_pokemon->_currentHp -= 5;

                    self->_battleLog->PushBackForce(self->_battleLog,
                                                    CreateTextBox(6, 0, 40, 1, BG_WHITE, "�ѹ��ʴ�(��) ���带(��) ����ߴ�!!"));
                    self->_battleLog->PushBackForce(self->_battleLog,
                                                    CreateTextBox(6, 0, 40, 1, BG_WHITE, "�ѹ��ʴ�(��) 5�� �������� �Ծ���."));
                }
                break;
                case SkillType_Tackle:
                {
                    self->_pokemon->_currentHp -= 10;
                    self->_ash->_currentHp -= 1;

                    self->_battleLog->PushBackForce(self->_battleLog,
                                                    CreateTextBox(6, 0, 40, 1, BG_WHITE, "�ѹ��ʴ�(��) �����ġ�⸦(��) ����ߴ�!!"));
                    self->_battleLog->PushBackForce(self->_battleLog,
                                                    CreateTextBox(6, 0, 40, 1, BG_WHITE, "�ѹ��ʴ�(��) 10�� �������� �Ծ���."));
                    self->_battleLog->PushBackForce(self->_battleLog,
                                                    CreateTextBox(6, 0, 40, 1, BG_WHITE, "�����(��) 1�� �������� �Ծ���."));
                }
                break;
                }
            }
            break;
            case SkillType_WaterGun:
            {
                self->_battleLog->PushBackForce(self->_battleLog,
                                                CreateTextBox(6, 0, 40, 1, BG_WHITE | FG_BLUE, "�����(��) ��ǰ������(��) ����ߴ�!!"));

                switch (self->_pokemon->_skills[self->_random->GetInt(3)])
                {
                case SkillType_Crouching:
                {
                    self->_pokemon->_currentHp -= 1;

                    self->_battleLog->PushBackForce(self->_battleLog,
                                                    CreateTextBox(6, 0, 40, 1, BG_WHITE, "�ѹ��ʴ�(��) ��ũ���⸦(��) ����ߴ�!!"));
                    self->_battleLog->PushBackForce(self->_battleLog,
                                                    CreateTextBox(6, 0, 40, 1, BG_WHITE, "�ѹ��ʴ�(��) 1�� �������� �Ծ���."));
                }
                break;
                case SkillType_Growth:
                {
                    self->_pokemon->_currentHp -= 0;

                    self->_battleLog->PushBackForce(self->_battleLog,
                                                    CreateTextBox(6, 0, 40, 1, BG_WHITE, "�ѹ��ʴ�(��) ���带(��) ����ߴ�!!"));
                    self->_battleLog->PushBackForce(self->_battleLog,
                                                    CreateTextBox(6, 0, 40, 1, BG_WHITE, "��ǰ������(��) ������ �ʾҴ�..."));
                }
                break;
                case SkillType_Tackle:
                {
                    self->_pokemon->_currentHp -= 2;
                    self->_ash->_currentHp -= 1;

                    self->_battleLog->PushBackForce(self->_battleLog,
                                                    CreateTextBox(6, 0, 40, 1, BG_WHITE, "�ѹ��ʴ�(��) �����ġ�⸦(��) ����ߴ�!!"));
                    self->_battleLog->PushBackForce(self->_battleLog,
                                                    CreateTextBox(6, 0, 40, 1, BG_WHITE, "�ѹ��ʴ�(��) 2�� �������� �Ծ���."));
                    self->_battleLog->PushBackForce(self->_battleLog,
                                                    CreateTextBox(6, 0, 40, 1, BG_WHITE, "�����(��) 1�� �������� �Ծ���."));
                }
                break;
                }
            }
            break;
            case SkillType_VineWhip:
            {
                self->_battleLog->PushBackForce(self->_battleLog,
                                                CreateTextBox(6, 0, 40, 1, BG_WHITE | FG_D_GREEN, "�����(��) ����ä�︦(��) ����ߴ�!!"));

                switch (self->_pokemon->_skills[self->_random->GetInt(3)])
                {
                case SkillType_Crouching:
                {
                    self->_pokemon->_currentHp -= 0;

                    self->_battleLog->PushBackForce(self->_battleLog,
                                                    CreateTextBox(6, 0, 40, 1, BG_WHITE, "�ѹ��ʴ�(��) ��ũ���⸦(��) ����ߴ�!!"));
                    self->_battleLog->PushBackForce(self->_battleLog,
                                                    CreateTextBox(6, 0, 40, 1, BG_WHITE, "����ä����(��) ������ �ʾҴ�..."));
                }
                break;
                case SkillType_Growth:
                {
                    self->_pokemon->_currentHp -= 2;

                    self->_battleLog->PushBackForce(self->_battleLog,
                                                    CreateTextBox(6, 0, 40, 1, BG_WHITE, "�ѹ��ʴ�(��) ���带(��) ����ߴ�!!"));
                    self->_battleLog->PushBackForce(self->_battleLog,
                                                    CreateTextBox(6, 0, 40, 1, BG_WHITE, "�ѹ��ʴ�(��) 2�� �������� �Ծ���."));
                }
                break;
                case SkillType_Tackle:
                {
                    self->_pokemon->_currentHp -= 5;
                    self->_ash->_currentHp -= 1;

                    self->_battleLog->PushBackForce(self->_battleLog,
                                                    CreateTextBox(6, 0, 40, 1, BG_WHITE, "�ѹ��ʴ�(��) �����ġ�⸦(��) ����ߴ�!!"));
                    self->_battleLog->PushBackForce(self->_battleLog,
                                                    CreateTextBox(6, 0, 40, 1, BG_WHITE, "�ѹ��ʴ�(��) 5�� �������� �Ծ���."));
                    self->_battleLog->PushBackForce(self->_battleLog,
                                                    CreateTextBox(6, 0, 40, 1, BG_WHITE, "�����(��) 1�� �������� �Ծ���."));
                }
                break;
                }
            }
            break;
            }
        }
        break;
        case CharacterType_Mew:
        {
            self->_ash->_currentHp -= 100;

            self->_battleLog->PushBackForce(self->_battleLog,
                                            CreateTextBox(6, 0, 40, 1, BG_WHITE, "�´�(��) �ı�������(��) ����ߴ�!!"));
            self->_battleLog->PushBackForce(self->_battleLog,
                                            CreateTextBox(6, 0, 40, 1, BG_WHITE, "�����(��) 100�� �������� �Ծ���."));
        }
        break;
        }

        if (self->_ash->_currentHp <= 0)
        {
            self->_battleLog->PushBackForce(self->_battleLog,
                                            CreateTextBox(6, 0, 40, 1, BG_BLACK | FG_WHITE, "������ ����������."));
        }

        if (self->_pokemon->_currentHp <= 0)
        {
            self->SetScene(self, SceneType_Field);

            if (self->_pokemon->_characterType == CharacterType_Oddish)
            {
                self->_fieldLog->PushBackForce(self->_fieldLog,
                                               CreateTextBox(6, 0, 40, 1, BG_WHITE, "����ġ 100��(��) ȹ���ߴ�."));

                TextBox* tb = self->_ash->ApplyExp(self->_ash, 100);
                if (tb != NULL)
                {
                    self->_fieldLog->PushBackForce(self->_fieldLog, tb);
                }
            }
            else
            {

            }

            self->_pokemon->Destroy(self->_pokemon);
        }
        else
        {
            self->_battleSceneType = BattleSceneType_Idle;
        }
    }
    break;
    case BattleSceneType_BeFriend:
    {
        int isFriend = FALSE;

        switch (self->_pokemon->_characterType)
        {
        case CharacterType_Oddish:
        {
            if (!self->_random->GetInt(2))
            {
                isFriend = TRUE;
            }
        }
        break;
        case CharacterType_Mew:
        {
            if (!self->_random->GetInt(10))
            {
                isFriend = TRUE;
            }
        }
        break;
        }

        if (isFriend)
        {
            self->SetScene(self, SceneType_Field);

            if (self->_pokemon->_characterType == CharacterType_Oddish)
            {
                self->_fieldLog->PushBackForce(self->_fieldLog,
                                               CreateTextBox(6, 0, 40, 1, BG_WHITE, "�ѹ��ʿ�(��) ģ���� �Ǿ���!!!!"));
                self->_fieldLog->PushBackForce(self->_fieldLog,
                                               CreateTextBox(6, 0, 40, 1, BG_WHITE, "����ġ 100��(��) ȹ���ߴ�."));

                TextBox* tb = self->_ash->ApplyExp(self->_ash, 100);
                if (tb != NULL)
                {
                    self->_fieldLog->PushBackForce(self->_fieldLog, tb);
                }
            }
            else
            {
                self->_fieldLog->PushBackForce(self->_fieldLog,
                                               CreateTextBox(6, 0, 40, 1, BG_WHITE | FG_D_MAGENTA, "�¿�(��) ģ���� �Ǿ���!!!!"));
                self->_fieldLog->PushBackForce(self->_fieldLog,
                                               CreateTextBox(6, 0, 40, 1, FG_D_MAGENTA, "    ���ʷα�"));
                self->_fieldLog->PushBackForce(self->_fieldLog,
                                               CreateTextBox(6, 0, 40, 1, FG_D_MAGENTA, "���ϸ��� �ο��� ������ �ƴ϶� ģ����"));
                self->_fieldLog->PushBackForce(self->_fieldLog,
                                               CreateTextBox(6, 0, 40, 1, FG_D_MAGENTA, "    ��"));
            }

            self->_pokemon->Destroy(self->_pokemon);
        }
        else
        {
            self->_battleSceneType = BattleSceneType_Idle;

            self->_battleLog->PushBackForce(self->_battleLog,
                                            CreateTextBox(6, 0, 40, 1, BG_WHITE, "ģ���� ���� ���ߴ�..."));
        }
    }
    break;
    }
}

void _Game_RenderOnField(Game* self)
{
    // debug message
    TextBox* debug = CreateTextBox(0, 29, 80, 1, BG_BLACK | FG_WHITE, "");
    sprintf_s(debug->_text, MAX_SIZE_OF_TEXT_IN_TEXTBOX,
              "DEBUG : POSITION (%d, %d) | END OF TEXTBOXES %d | CURSOR Y POSITION %d",
              self->_ash->_position.X, self->_ash->_position.Y,
              self->_textBoxes->_end,
              self->_cursorPosition.Y);
    self->_textBoxes->PushBack(self->_textBoxes, debug);

    // log message window
    self->_textBoxes->PushBack(self->_textBoxes, CreateTextBox(0, 19, 80, 1, BG_BLACK, ""));
    self->_textBoxes->PushBack(self->_textBoxes, CreateTextBox(3, 21, 46, 1, BG_BLACK, ""));
    self->_textBoxes->PushBack(self->_textBoxes, CreateTextBox(3, 27, 46, 1, BG_BLACK, ""));
    for (int i = 0; i < 5; ++i)
    {
        self->_textBoxes->PushBack(self->_textBoxes, CreateTextBox(2, 22 + i, 2, 1, BG_BLACK, ""));
        self->_textBoxes->PushBack(self->_textBoxes, CreateTextBox(48, 22 + i, 2, 1, BG_BLACK, ""));
    }

    // log message
    for (int i = 0; i < self->_fieldLog->_end; ++i)
    {
        TextBox* source = self->_fieldLog->_textBoxes[i];
        TextBox* clone = source->Duplicate(source);
        clone->_offset.Y = 22 + i;
        self->_textBoxes->PushBack(self->_textBoxes, clone);
    }

    // map
    MapType** map = self->_map->_map;
    for (int i = 0; i < self->_map->_sizeOfSide; ++i)
    {
        for (int j = 0; j < self->_map->_sizeOfSide; ++j)
        {
            switch (map[i][j])
            {
            case MapType_Wall:
            {
                self->_textBoxes->PushBack(self->_textBoxes, CreateTextBox(j * 4, i * 2, 4, 2, BG_GRAY, ""));
            }
            break;
            case MapType_Road:
            {
                self->_textBoxes->PushBack(self->_textBoxes, CreateTextBox(j * 4, i * 2, 4, 2, BG_D_YELLOW, ""));
            }
            break;
            case MapType_Grass:
            {
                self->_textBoxes->PushBack(self->_textBoxes, CreateTextBox(j * 4, i * 2, 4, 2, BG_D_GREEN, ""));
            }
            break;
            case MapType_TallGrass:
            {
                self->_textBoxes->PushBack(self->_textBoxes, CreateTextBox(j * 4, i * 2, 4, 2, BG_GREEN, ""));
                self->_textBoxes->PushBack(self->_textBoxes, CreateTextBox(j * 4, i * 2, 2, 1, BG_D_GREEN, ""));
                self->_textBoxes->PushBack(self->_textBoxes, CreateTextBox(j * 4 + 2, i * 2 + 1, 2, 1, BG_D_GREEN, ""));
            }
            break;
            case MapType_Switch:
            {
                self->_textBoxes->PushBack(self->_textBoxes, CreateTextBox(j * 4, i * 2, 4, 2, BG_D_RED, ""));
            }
            break;
            case MapType_Door:
            {
                self->_textBoxes->PushBack(self->_textBoxes, CreateTextBox(j * 4, i * 2, 4, 2, BG_WHITE, ""));
            }
            break;
            }
        }
    }

    // ash
    COORD ashPos = self->_ash->_position;
    self->_textBoxes->PushBack(self->_textBoxes, CreateTextBox(ashPos.X * 4 + 1, ashPos.Y * 2, 2, 1, BG_YELLOW, ".."));
    self->_textBoxes->PushBack(self->_textBoxes, CreateTextBox(ashPos.X * 4, ashPos.Y * 2 + 1, 4, 1, BG_RED, "d  b"));

    // cursor
    if (self->_isMenu)
    {
        // selection window
        self->_textBoxes->PushBack(self->_textBoxes, CreateTextBox(53, 21, 24, 1, BG_BLACK, ""));
        self->_textBoxes->PushBack(self->_textBoxes, CreateTextBox(53, 27, 24, 1, BG_BLACK, ""));
        for (int i = 0; i < 5; ++i)
        {
            self->_textBoxes->PushBack(self->_textBoxes, CreateTextBox(52, 22 + i, 2, 1, BG_BLACK, ""));
            self->_textBoxes->PushBack(self->_textBoxes, CreateTextBox(76, 22 + i, 2, 1, BG_BLACK, ""));
        }

        // selection texts
        self->_textBoxes->PushBack(self->_textBoxes, CreateTextBox(57, 23, 6, 1, BG_WHITE, "���̺�"));
        self->_textBoxes->PushBack(self->_textBoxes, CreateTextBox(57, 24, 11, 1, BG_WHITE, "�ε�"));
        self->_textBoxes->PushBack(self->_textBoxes, CreateTextBox(57, 25, 8, 1, BG_WHITE, "����"));

        self->_textBoxes->PushBack(self->_textBoxes, CreateTextBox(56, 23 + self->_cursorPosition.Y, 1, 1, BG_WHITE, ">"));
    }

    TextBox* time = CreateTextBox(40, 2, 40, 1, BG_WHITE, "");
    SYSTEMTIME st;
    GetSystemTime(&st);
    sprintf_s(time->_text, MAX_SIZE_OF_TEXT_IN_TEXTBOX, "%d�� %d�� %d�� %d�� %d�� %d��", st.wYear, st.wMonth, st.wDay, st.wHour + 9, st.wMinute, st.wSecond);
    self->_textBoxes->PushBack(self->_textBoxes, time);
    TextBox* turn = CreateTextBox(40, 3, 40, 1, BG_WHITE, "");
    sprintf_s(turn->_text, MAX_SIZE_OF_TEXT_IN_TEXTBOX, "�� : %d", self->_turn);
    self->_textBoxes->PushBack(self->_textBoxes, turn);
    TextBox* ashLevel = CreateTextBox(40, 4, 40, 1, BG_WHITE, "");
    sprintf_s(ashLevel->_text, MAX_SIZE_OF_TEXT_IN_TEXTBOX, "������ ���� : %d", self->_ash->_level);
    self->_textBoxes->PushBack(self->_textBoxes, ashLevel);
    TextBox* ashCurrentHp = CreateTextBox(40, 5, 40, 1, BG_WHITE, "");
    sprintf_s(ashCurrentHp->_text, MAX_SIZE_OF_TEXT_IN_TEXTBOX, "������ ���� ü�� : %d/%d", self->_ash->_currentHp, self->_ash->_maxHp);
    self->_textBoxes->PushBack(self->_textBoxes, ashCurrentHp);
    TextBox* ashCurrentExp = CreateTextBox(40, 6, 40, 1, BG_WHITE, "");
    sprintf_s(ashCurrentExp->_text, MAX_SIZE_OF_TEXT_IN_TEXTBOX, "������ ���� ����ġ : %d/%d", self->_ash->_currentExp, self->_ash->_maxExp);
    self->_textBoxes->PushBack(self->_textBoxes, ashCurrentExp);
    TextBox* ashCurrentPos = CreateTextBox(40, 7, 40, 1, BG_WHITE, "");
    sprintf_s(ashCurrentPos->_text, MAX_SIZE_OF_TEXT_IN_TEXTBOX, "������ ���� ��ġ : (%d, %d)", self->_ash->_position.X, self->_ash->_position.Y);
    self->_textBoxes->PushBack(self->_textBoxes, ashCurrentPos);
    TextBox* doorInfo = CreateTextBox(40, 8, 40, 1, BG_WHITE, "");
    if (self->_map->_map[5][6] == MapType_Road)
    {
        sprintf_s(doorInfo->_text, MAX_SIZE_OF_TEXT_IN_TEXTBOX, "�°� ������ �� ���� �� : ����");
    }
    else
    {
        sprintf_s(doorInfo->_text, MAX_SIZE_OF_TEXT_IN_TEXTBOX, "�°� ������ �� ���� �� : ����");
    }
    self->_textBoxes->PushBack(self->_textBoxes, doorInfo);

    TextBox* backupCoolDown = CreateTextBox(40, 9, 40, 1, BG_WHITE, "");
    sprintf_s(backupCoolDown->_text, MAX_SIZE_OF_TEXT_IN_TEXTBOX, "��� �� �ٿ� : %d��", self->_backupCoolDown / 1000);
    self->_textBoxes->PushBack(self->_textBoxes, backupCoolDown);

    self->_textBoxes->PushBack(self->_textBoxes, CreateTextBox(40, 11, 40, 1, BG_WHITE, "Z : ����"));
    self->_textBoxes->PushBack(self->_textBoxes, CreateTextBox(40, 12, 40, 1, BG_WHITE, "X : ���"));
    self->_textBoxes->PushBack(self->_textBoxes, CreateTextBox(40, 13, 40, 1, BG_WHITE, "C : �޴�"));
    self->_textBoxes->PushBack(self->_textBoxes, CreateTextBox(40, 14, 40, 1, BG_WHITE, "����Ű : �̵�"));
}

void _Game_RenderOnBattle(Game* self)
{
    // debug message
    TextBox* debug = CreateTextBox(0, 29, 80, 1, BG_BLACK | FG_WHITE, "");
    sprintf_s(debug->_text, MAX_SIZE_OF_TEXT_IN_TEXTBOX,
              "DEBUG : POSITION (%d, %d) | END OF TEXTBOXES %d | CURSOR Y POSITION %d",
              self->_ash->_position.X, self->_ash->_position.Y,
              self->_textBoxes->_end,
              self->_cursorPosition.Y);
    self->_textBoxes->PushBack(self->_textBoxes, debug);

    // log message window
    self->_textBoxes->PushBack(self->_textBoxes, CreateTextBox(0, 19, 80, 1, BG_BLACK, ""));
    self->_textBoxes->PushBack(self->_textBoxes, CreateTextBox(3, 21, 46, 1, BG_BLACK, ""));
    self->_textBoxes->PushBack(self->_textBoxes, CreateTextBox(3, 27, 46, 1, BG_BLACK, ""));
    for (int i = 0; i < 5; ++i)
    {
        self->_textBoxes->PushBack(self->_textBoxes, CreateTextBox(2, 22 + i, 2, 1, BG_BLACK, ""));
        self->_textBoxes->PushBack(self->_textBoxes, CreateTextBox(48, 22 + i, 2, 1, BG_BLACK, ""));
    }

    // log message
    for (int i = 0; i < self->_battleLog->_end; ++i)
    {
        TextBox* source = self->_battleLog->_textBoxes[i];
        TextBox* clone = source->Duplicate(source);
        clone->_offset.Y = 22 + i;
        self->_textBoxes->PushBack(self->_textBoxes, clone);
    }

    // ash status window
    self->_textBoxes->PushBack(self->_textBoxes, CreateTextBox(53, 14, 24, 1, BG_BLACK, ""));
    self->_textBoxes->PushBack(self->_textBoxes, CreateTextBox(43, 17, 34, 1, BG_BLACK, ""));
    for (int i = 0; i < 2; ++i)
    {
        self->_textBoxes->PushBack(self->_textBoxes, CreateTextBox(52, 15 + i, 2, 1, BG_BLACK, ""));
        self->_textBoxes->PushBack(self->_textBoxes, CreateTextBox(76, 15 + i, 2, 1, BG_BLACK, ""));
    }

    // ash hp
    self->_textBoxes->PushBack(self->_textBoxes, CreateTextBox(55, 15, 6, 1, BG_WHITE, "ü  ��"));
    int ashHpBarLength = self->_ash->_currentHp * 14 / self->_ash->_maxHp;
    TextBox* ashHpBar = CreateTextBox(62, 15, ashHpBarLength, 1, BG_GREEN, "");
    sprintf_s(ashHpBar->_text, MAX_SIZE_OF_TEXT_IN_TEXTBOX,
              "%4d/%4d", self->_ash->_currentHp, self->_ash->_maxHp);
    self->_textBoxes->PushBack(self->_textBoxes, ashHpBar);

    // ash exp
    self->_textBoxes->PushBack(self->_textBoxes, CreateTextBox(55, 16, 6, 1, BG_WHITE, "����ġ"));
    int ashExpBarLength = self->_ash->_currentExp * 14 / self->_ash->_maxExp;
    TextBox* ashExpBar = CreateTextBox(62, 16, ashExpBarLength, 1, BG_D_RED, "");
    sprintf_s(ashExpBar->_text, MAX_SIZE_OF_TEXT_IN_TEXTBOX,
              "%4d/%4d", self->_ash->_currentExp, self->_ash->_maxExp);
    self->_textBoxes->PushBack(self->_textBoxes, ashExpBar);

    // selection window
    self->_textBoxes->PushBack(self->_textBoxes, CreateTextBox(53, 21, 24, 1, BG_BLACK, ""));
    self->_textBoxes->PushBack(self->_textBoxes, CreateTextBox(53, 27, 24, 1, BG_BLACK, ""));
    for (int i = 0; i < 5; ++i)
    {
        self->_textBoxes->PushBack(self->_textBoxes, CreateTextBox(52, 22 + i, 2, 1, BG_BLACK, ""));
        self->_textBoxes->PushBack(self->_textBoxes, CreateTextBox(76, 22 + i, 2, 1, BG_BLACK, ""));
    }

    // selection texts
    switch (self->_battleSceneType)
    {
    case BattleSceneType_Idle:
    {
        self->_textBoxes->PushBack(self->_textBoxes, CreateTextBox(57, 23, 6, 1, BG_WHITE, "�ο��"));
        self->_textBoxes->PushBack(self->_textBoxes, CreateTextBox(57, 24, 11, 1, BG_WHITE, "ģ���� �Ǵ�"));
        self->_textBoxes->PushBack(self->_textBoxes, CreateTextBox(57, 25, 8, 1, BG_WHITE, "��������"));
    }
    break;
    case BattleSceneType_Skills:
    {
        self->_textBoxes->PushBack(self->_textBoxes, CreateTextBox(57, 23, 9, 1, BG_WHITE | FG_RED, "�Ҳ� ����"));
        self->_textBoxes->PushBack(self->_textBoxes, CreateTextBox(57, 24, 9, 1, BG_WHITE | FG_BLUE, "��ǰ ����"));
        self->_textBoxes->PushBack(self->_textBoxes, CreateTextBox(57, 25, 9, 1, BG_WHITE | FG_D_GREEN, "���� ä��"));
    }
    break;
    }

    // cursor
    self->_textBoxes->PushBack(self->_textBoxes, CreateTextBox(56, 23 + self->_cursorPosition.Y, 1, 1, BG_WHITE, ">"));

    // pokemon status window
    self->_textBoxes->PushBack(self->_textBoxes, CreateTextBox(3, 1, 24, 1, BG_BLACK, ""));
    self->_textBoxes->PushBack(self->_textBoxes, CreateTextBox(3, 3, 24, 1, BG_BLACK, ""));
    self->_textBoxes->PushBack(self->_textBoxes, CreateTextBox(2, 2, 2, 1, BG_BLACK, ""));
    self->_textBoxes->PushBack(self->_textBoxes, CreateTextBox(26, 2, 2, 1, BG_BLACK, ""));

    // pokemon hp
    self->_textBoxes->PushBack(self->_textBoxes, CreateTextBox(5, 2, 6, 1, BG_WHITE, "ü  ��"));
    int pokemonHpBarLength = self->_pokemon->_currentHp * 14 / self->_pokemon->_maxHp;
    TextBox* pokemonHpBar = CreateTextBox(12, 2, pokemonHpBarLength, 1, BG_GREEN, "");
    sprintf_s(pokemonHpBar->_text, MAX_SIZE_OF_TEXT_IN_TEXTBOX,
              "%5d/%5d", self->_pokemon->_currentHp, self->_pokemon->_maxHp);
    self->_textBoxes->PushBack(self->_textBoxes, pokemonHpBar);

    // pokemon shape
    switch (self->_pokemon->_characterType)
    {
    case CharacterType_Oddish:
    {
        self->_textBoxes->PushBack(self->_textBoxes, CreateTextBox(58, 6, 8, 3, BG_BLACK, ""));
        self->_textBoxes->PushBack(self->_textBoxes, CreateTextBox(60, 9, 1, 2, BG_BLACK, ""));
        self->_textBoxes->PushBack(self->_textBoxes, CreateTextBox(63, 9, 1, 2, BG_BLACK, ""));
        self->_textBoxes->PushBack(self->_textBoxes, CreateTextBox(59, 10, 1, 1, BG_BLACK, ""));
        self->_textBoxes->PushBack(self->_textBoxes, CreateTextBox(64, 10, 1, 1, BG_BLACK, ""));
        self->_textBoxes->PushBack(self->_textBoxes, CreateTextBox(59, 7, 1, 1, BG_WHITE, ""));
        self->_textBoxes->PushBack(self->_textBoxes, CreateTextBox(62, 7, 1, 1, BG_WHITE, ""));
        self->_textBoxes->PushBack(self->_textBoxes, CreateTextBox(58, 4, 2, 1, BG_D_GREEN, ""));
        self->_textBoxes->PushBack(self->_textBoxes, CreateTextBox(57, 3, 2, 1, BG_D_GREEN, ""));
        self->_textBoxes->PushBack(self->_textBoxes, CreateTextBox(59, 5, 2, 1, BG_D_GREEN, ""));
        self->_textBoxes->PushBack(self->_textBoxes, CreateTextBox(61, 4, 2, 2, BG_GREEN, ""));
        self->_textBoxes->PushBack(self->_textBoxes, CreateTextBox(62, 3, 2, 1, BG_GREEN, ""));
        self->_textBoxes->PushBack(self->_textBoxes, CreateTextBox(63, 5, 2, 1, BG_D_GREEN, ""));
        self->_textBoxes->PushBack(self->_textBoxes, CreateTextBox(64, 4, 2, 1, BG_D_GREEN, ""));
        self->_textBoxes->PushBack(self->_textBoxes, CreateTextBox(66, 3, 2, 1, BG_D_GREEN, ""));
    }
    break;
    case CharacterType_Mew:
    {
        self->_textBoxes->PushBack(self->_textBoxes, CreateTextBox(51, 2, 7, 3, BG_MAGENTA, ""));
        self->_textBoxes->PushBack(self->_textBoxes, CreateTextBox(57, 6, 4, 2, BG_MAGENTA, ""));
        self->_textBoxes->PushBack(self->_textBoxes, CreateTextBox(59, 4, 1, 2, BG_MAGENTA, ""));
        self->_textBoxes->PushBack(self->_textBoxes, CreateTextBox(58, 3, 1, 1, BG_MAGENTA, ""));
        self->_textBoxes->PushBack(self->_textBoxes, CreateTextBox(56, 8, 1, 3, BG_MAGENTA, ""));
        self->_textBoxes->PushBack(self->_textBoxes, CreateTextBox(59, 8, 1, 3, BG_MAGENTA, ""));
        self->_textBoxes->PushBack(self->_textBoxes, CreateTextBox(53, 10, 3, 1, BG_MAGENTA, ""));
        self->_textBoxes->PushBack(self->_textBoxes, CreateTextBox(60, 10, 3, 1, BG_MAGENTA, ""));
        self->_textBoxes->PushBack(self->_textBoxes, CreateTextBox(61, 8, 3, 1, BG_MAGENTA, ""));
        self->_textBoxes->PushBack(self->_textBoxes, CreateTextBox(64, 4, 1, 4, BG_MAGENTA, ""));
        self->_textBoxes->PushBack(self->_textBoxes, CreateTextBox(52, 3, 2, 1, BG_WHITE, ""));
        self->_textBoxes->PushBack(self->_textBoxes, CreateTextBox(55, 3, 2, 1, BG_WHITE, ""));
        self->_textBoxes->PushBack(self->_textBoxes, CreateTextBox(52, 3, 1, 1, BG_BLACK, ""));
        self->_textBoxes->PushBack(self->_textBoxes, CreateTextBox(55, 3, 1, 1, BG_BLACK, ""));
        self->_textBoxes->PushBack(self->_textBoxes, CreateTextBox(53, 5, 2, 1, BG_MAGENTA, ""));
    }
    break;
    }

    // ash shape
    self->_textBoxes->PushBack(self->_textBoxes, CreateTextBox(16, 7, 10, 5, BG_YELLOW, ""));
    self->_textBoxes->PushBack(self->_textBoxes, CreateTextBox(16, 8, 14, 1, BG_BLUE, ""));
    self->_textBoxes->PushBack(self->_textBoxes, CreateTextBox(16, 7, 10, 2, BG_BLUE, ""));
    self->_textBoxes->PushBack(self->_textBoxes, CreateTextBox(16, 9, 4, 3, BG_BLACK, ""));
    self->_textBoxes->PushBack(self->_textBoxes, CreateTextBox(24, 10, 1, 1, BG_BLACK, ""));
    self->_textBoxes->PushBack(self->_textBoxes, CreateTextBox(10, 13, 20, 6, BG_YELLOW, ""));
    self->_textBoxes->PushBack(self->_textBoxes, CreateTextBox(14, 13, 12, 6, BG_RED, ""));
    self->_textBoxes->PushBack(self->_textBoxes, CreateTextBox(20, 12, 3, 2, BG_YELLOW, ""));
}

void _Game_SetScene(Game* self, SceneType sceneType)
{
    self->_sceneType = sceneType;

    switch (sceneType)
    {
    case SceneType_Field:
    {
        self->HandleInput = self->HandleInputOnField;
        self->Update = self->UpdateOnField;
        self->Render = self->RenderOnField;
        self->_isMenu = FALSE;
    }
    break;
    case SceneType_Battle:
    {
        self->HandleInput = self->HandleInputOnBattle;
        self->Update = self->UpdateOnBattle;
        self->Render = self->RenderOnBattle;
        self->_battleSceneType = BattleSceneType_Idle;
        self->_battleLog->Clear(self->_battleLog);
    }
    break;
    }
}

int _Game_WriteToFile(Game* self, char* fileName)
{
    FILE* file = NULL;
    fopen_s(&file, fileName, "wt");
    if (file)
    {
        SYSTEMTIME st;
        GetSystemTime(&st);
        fprintf_s(file, "%d��_%d��_%d��_%d��_%d��_%d��\n", st.wYear, st.wMonth, st.wDay, st.wHour + 9, st.wMinute, st.wSecond);

        fprintf_s(file, "%s %d\n", "����_��_:", self->_turn);

        fprintf_s(file, "%s %d\n", "����_����_:", self->_ash->_level);
        fprintf_s(file, "%s %d\n", "����_����_ü��_:", self->_ash->_currentHp);
        fprintf_s(file, "%s %d\n", "����_�ִ�_ü��_:", self->_ash->_maxHp);
        fprintf_s(file, "%s %d\n", "����_����_����ġ_:", self->_ash->_currentExp);
        fprintf_s(file, "%s %d\n", "����_�ʿ�_����ġ_:", self->_ash->_maxExp);
        fprintf_s(file, "%s %d %d\n", "����_��ġ_:", self->_ash->_position.X, self->_ash->_position.Y);

        fprintf_s(file, "%s %d %d %d\n", "������_����ġ��_����_:", 
                  self->_map->_map[5][6], self->_map->_map[6][6], self->_map->_map[7][6]);

        fclose(file);
        return TRUE;
    }

    //fclose(file);
    return FALSE;
}

int _Game_ReadFromFile(Game* self, char* fileName)
{
    FILE* file = NULL;
    fopen_s(&file, fileName, "rt");
    if (file)
    {
        char temp[64];
        fscanf_s(file, "%s", temp, 64);
        
        int turn = 0;
        fscanf_s(file, "%s", temp, 64);
        fscanf_s(file, "%d", &turn);

        int level = 0;
        fscanf_s(file, "%s", temp, 64);
        fscanf_s(file, "%d", &level);

        int currentHp = 0;
        fscanf_s(file, "%s", temp, 64);
        fscanf_s(file, "%d", &currentHp);

        int maxHp = 0;
        fscanf_s(file, "%s", temp, 64);
        fscanf_s(file, "%d", &maxHp);

        int currentExp = 0;
        fscanf_s(file, "%s", temp, 64);
        fscanf_s(file, "%d", &currentExp);

        int maxExp = 0;
        fscanf_s(file, "%s", temp, 64);
        fscanf_s(file, "%d", &maxExp);

        int posX = 0;
        int posY = 0;
        fscanf_s(file, "%s", temp, 64);
        fscanf_s(file, "%d", &posX);
        fscanf_s(file, "%d", &posY);

        int door1 = 0;
        int door2 = 0;
        int door3 = 0;
        fscanf_s(file, "%s", temp, 64);
        fscanf_s(file, "%d", &door1);
        fscanf_s(file, "%d", &door2);
        fscanf_s(file, "%d", &door3);

        //TextBox* tb = CreateTextBox(6, 0, 40, 1, BG_WHITE, "");
        //sprintf_s(tb->_text, MAX_SIZE_OF_TEXT_IN_TEXTBOX, "%d %d %d %d %d %d %d %d %d %d %d", 
        //          turn, level, currentHp, maxHp, currentExp, maxExp, posX, posY, door1, door2, door3);
        //self->_fieldLog->PushBackForce(self->_fieldLog, tb);

        self->_turn = turn;
        self->_ash->_level = level;
        self->_ash->_currentHp = currentHp;
        self->_ash->_maxHp = maxHp;
        self->_ash->_currentExp = currentExp;
        self->_ash->_maxExp = maxExp;
        self->_ash->_position.X = posX;
        self->_ash->_position.Y = posY;
        self->_map->_map[5][6] = door1;
        self->_map->_map[6][6] = door2;
        self->_map->_map[7][6] = door3;

        fclose(file);
        return TRUE;
    }

    //fclose(file);
    return FALSE;
}

int _Game_Backup(Game* self, char* src, char* dst)
{
    FILE* srcf = NULL;
    FILE* dstf = NULL;
    fopen_s(&srcf, src, "rt");
    if (src == NULL)
        return FALSE;

    fopen_s(&dstf, dst, "wt");

    if (srcf && dstf)
    {
        int ch;
        while ((ch = fgetc(srcf)) != EOF)
        {
            fputc(ch, dstf);
        }

        fclose(srcf);
        fclose(dstf);
        return TRUE;
    }

    //fclose(srcf);
    //fclose(dstf);
    return FALSE;
}

Game* CreateGame()
{
    Game* game = (Game*)malloc(sizeof(Game));

    game->Destroy = _Game_Destroy;
    game->HandleInputOnField = _Game_HandleInputOnField;
    game->HandleInputOnBattle = _Game_HandleInputOnBattle;
    game->UpdateOnField = _Game_UpdateOnField;
    game->UpdateOnBattle = _Game_UpdateOnBattle;
    game->RenderOnField = _Game_RenderOnField;
    game->RenderOnBattle = _Game_RenderOnBattle;
    game->SetScene = _Game_SetScene;
    game->WriteToFile = _Game_WriteToFile;
    game->ReadFromFile = _Game_ReadFromFile;
    game->Backup = _Game_Backup;

    game->HandleInput = game->HandleInputOnField;
    game->Update = game->UpdateOnField;
    game->Render = game->RenderOnField;

    game->_random = CreateRandom();
    game->_time = CreateTime();
    game->_textBoxes = CreateTextBoxes(WINDOW_WIDTH * WINDOW_HEIGHT);
    game->_fieldLog = CreateTextBoxes(5);
    game->_battleLog = CreateTextBoxes(5);
    game->_map = CreateMap();
    game->_ash = CreateCharacter(CharacterType_Ash);
    game->_pokemon = NULL;
    
    game->_isFinished = FALSE;
    COORD cursorPosition = { 0, 0 };
    game->_cursorPosition = cursorPosition;

    game->_sceneType = SceneType_Field;
    game->_turn = 1;
    game->_battleSceneType = BattleSceneType_Idle;
    game->_isMenu = FALSE;

    game->_fieldLog->PushBackForce(game->_fieldLog, CreateTextBox(6, 0, 40, 1, BG_WHITE, "      ���ѷα�"));
    game->_fieldLog->PushBackForce(game->_fieldLog, CreateTextBox(6, 0, 40, 1, BG_WHITE, "���ϸ� ������ ����� �¸� ������ ���ؼ�"));
    game->_fieldLog->PushBackForce(game->_fieldLog, CreateTextBox(6, 0, 40, 1, BG_WHITE, "�� �� �ܵ� ���� �Դ�."));
    game->_fieldLog->PushBackForce(game->_fieldLog, CreateTextBox(6, 0, 40, 1, BG_WHITE, "�� �տ� �°� ������ Ǯ���̴�."));
    game->_fieldLog->PushBackForce(game->_fieldLog, CreateTextBox(6, 0, 40, 1, BG_WHITE, "������ ���� ��� �� �� �� ����."));

    game->_backupCoolTime = 10000;
    game->_backupCoolDown = 10000;
    game->_previousTime = GetTickCount();

    return game;
}