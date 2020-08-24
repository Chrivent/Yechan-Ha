#pragma once

#include "Map.h"
#include "Player.h"
#include "Goblin.h"
#include "Oak.h"
#include "Werewolf.h"
#include "Ogre.h"
#include "SkeletonArcher.h"
#include "Rich.h"
#include "Subject.h"

#define SLOT_COUNT 10

enum WEAPON
{
	WEAPON_DAGGER,
	WEAPON_GUN,
	WEAPON_SWORD,
	WEAPON_WAND,
	WEAPON_BOW,
	WEAPON_HAMMER,
	WEAPON_COUNT
};

class RPG_Game : public Subject
{
private:
	Map m_map;
	Player* m_player;
	Enemy* m_goblin;
	Enemy* m_oak;
	Enemy* m_werewolf;
	Enemy* m_ogre;
	Enemy* m_skeletonArcher;
	Enemy* m_rich;
	Weapon* m_weapon;

public:
	RPG_Game();

	void DefaultLoad();
	void WeaponLoad(string type);
	int WeaponCount(string type);
	void AutoRun();
	void Play();
	void Dongeon();
	void Shop();
	void SelectWeapon(string type);
	void PlayerInfo();
	void MonsterInfo();
	void Save();
	void RecordCharacterData(ofstream& save, Character* character);
	bool Load();
	void ReadCharacterData(ifstream& load, Character* character);
	int CheckResult(int playerHand, int enemyHand);
	void Stage(Enemy* enemy);
	void MatchResult(Character* winner, Character* loser);
	bool CheckClear();

	void NotifyObserver();

	~RPG_Game();
};