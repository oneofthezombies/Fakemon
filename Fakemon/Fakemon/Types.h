#pragma once

typedef enum _ComponentType
{
    ComponentType_Transform
} ComponentType;

typedef enum _TagType
{
    TagType_Idle
} TagType;

typedef enum _CharacterType
{
    CharacterType_Ash,
    CharacterType_Oddish,
    CharacterType_Mew
} CharacterType;

typedef enum _SkillType
{
    SkillType_Splash,
    SkillType_Ember,
    SkillType_WaterGun,
    SkillType_VineWhip,
    SkillType_Crouching,
    SkillType_Tackle,
    SkillType_Growth,
    SkillType_HyperBeam,
    SkillType_TriAttack
} SkillType;

typedef enum _MapType
{
    MapType_Road,
    MapType_Wall,
    MapType_Grass,
    MapType_TallGrass,
    MapType_Switch,
    MapType_Door
} MapType;

typedef enum _SceneType
{
    SceneType_Field,
    SceneType_Battle
} SceneType;

typedef enum _BattleSceneType
{
    BattleSceneType_Idle,
    BattleSceneType_Skills,
    BattleSceneType_Battle,
    BattleSceneType_BeFriend
} BattleSceneType;