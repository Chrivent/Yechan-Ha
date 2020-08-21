#include "RPG_Game.h"

RPG_Game::RPG_Game()
{
	m_goblin = new Goblin;
	m_oak = new Oak;
	m_werewolf = new Werewolf;
	m_ogre = new Ogre;
	m_skeletonArcher = new SkeletonArcher;
	m_rich = new Rich;
}

void RPG_Game::DefaultLoad()
{
	ifstream load;
	load.open("Default.txt");
	if (load.is_open())
	{
		ReadCharacterData(load, m_goblin);
		ReadCharacterData(load, m_oak);
		ReadCharacterData(load, m_werewolf);
		ReadCharacterData(load, m_ogre);
		ReadCharacterData(load, m_skeletonArcher);
		ReadCharacterData(load, m_rich);
		ReadCharacterData(load, m_player);
	}
}

void RPG_Game::WeaponLoad(string type)
{
	if (type == "Dagger")
		m_weapon = new Dagger[WeaponCount("Dagger")];
	else if (type == "Gun")
		m_weapon = new Gun[WeaponCount("Gun")];
	else if (type == "Sword")
		m_weapon = new Sword[WeaponCount("Sword")];
	else if (type == "Wand")
		m_weapon = new Wand[WeaponCount("Wand")];
	else if (type == "Bow")
		m_weapon = new Bow[WeaponCount("Bow")];
	else if (type == "Hammer")
		m_weapon = new Hammer[WeaponCount("Hammer")];

	int count = 0;
	ifstream load;
	load.open("WeaponList.txt");
	if (load.is_open())
	{
		while (!load.eof())
		{
			string type_tmp;
			string name;
			int price;
			int damage;

			load >> type_tmp;
			load >> name;
			load >> price;
			load >> damage;

			if (type_tmp == type)
			{
				m_weapon[count].SetStatus(type_tmp, name, price, damage);
				count++;
			}
		}
		load.close();
	}
}

int RPG_Game::WeaponCount(string type)
{
	int count = 0;

	ifstream load;
	load.open("WeaponList.txt");
	if (load.is_open())
	{
		while (!load.eof())
		{
			string tmp;
			load >> tmp;
			if (tmp == type)
				count++;
		}
		load.close();
	}

	return count;
}

void RPG_Game::AutoRun()
{
	SetScreenSize(m_map.GetScale().width * 32, m_map.GetScale().height * 32);
	m_map.DrawBox();

	while (true)
	{
		m_map.EraseBoxInner();
		m_map.DrawMain();

		switch (m_map.MenuSelectCursor(3, m_map.GetScale().height * 3, m_map.GetScale().width * 12, m_map.GetScale().height * 15))
		{
		case 1:
			m_player = new Player;
			DefaultLoad();
			m_map.EraseBoxInner();
			m_player->SetName(m_map.GetScale().width * 16, m_map.GetScale().height * 16);
			Play();
			break;
		case 2:
			m_player = new Player;
			if (Load())
				Play();
			break;
		case 3:
			return;
		default:
			break;
		}
	}
}

void RPG_Game::Play()
{
	while (true)
	{
		m_map.EraseBoxInner();
		m_map.DrawPlay();

		switch (m_map.MenuSelectCursor(6, m_map.GetScale().height * 2, m_map.GetScale().width * 10, m_map.GetScale().height * 11))
		{
		case 1:
			Dongeon();
			break;
		case 2:
			PlayerInfo();
			break;
		case 3:
			MonsterInfo();
			break;
		case 4:
			Shop();
			break;
		case 5:
			Save();
			break;
		case 6:
			delete m_player;
			m_player = NULL;
			return;
		default:
			break;
		}
	}
}

void RPG_Game::Dongeon()
{
	Enemy* enemy;

	while (true)
	{
		m_map.EraseBoxInner();
		m_map.DrawDongeon();

		switch (m_map.MenuSelectCursor(7, m_map.GetScale().height * 2, m_map.GetScale().width * 8, m_map.GetScale().height * 11))
		{
		case 1:
			enemy = m_goblin;
			break;
		case 2:
			enemy = m_oak;
			break;
		case 3:
			enemy = m_werewolf;
			break;
		case 4:
			enemy = m_ogre;
			break;
		case 5:
			enemy = m_skeletonArcher;
			break;
		case 6:
			enemy = m_rich;
			break;
		case 7:
			return;
		default:
			continue;
		}
		break;
	}

	Stage(enemy);

	if (CheckClear())
		NotifyObserver();
}

void RPG_Game::Shop()
{
	while (true)
	{
		m_map.EraseBoxInner();
		m_map.DrawShop();

		switch (m_map.MenuSelectCursor(7, m_map.GetScale().height * 2, m_map.GetScale().width * 8, m_map.GetScale().height * 11))
		{
		case 1:
			SelectWeapon("Dagger");
			break;
		case 2:
			SelectWeapon("Gun");
			break;
		case 3:
			SelectWeapon("Sword");
			break;
		case 4:
			SelectWeapon("Wand");
			break;
		case 5:
			SelectWeapon("Bow");
			break;
		case 6:
			SelectWeapon("Hammer");
			break;
		case 7:
			return;
		default:
			break;
		}
	}
}

void RPG_Game::SelectWeapon(string type)
{
	WeaponLoad(type);

	int page = 1;
	int count = WeaponCount(type);
	while (true)
	{
		m_map.EraseBoxInner();
		m_map.DrawSelectWeapon(m_player->GetGold(), type);

		int count_inPage = 0;
		for (int i = 0; i < count; i++)
		{
			if (i >= (page - 1) * 5 && i < page * 5)
			{
				m_weapon[i].DrawStatus(m_map.GetScale().width * 16, m_map.GetScale().height * (7 + count_inPage * 3));
				count_inPage++;
			}
		}
		m_map.DrawSelectPage(7 + count_inPage * 3);

		int select = m_map.MenuSelectCursor(count_inPage + 3, m_map.GetScale().height * 3, m_map.GetScale().width * 5, m_map.GetScale().height * 7);
		if (select <= count_inPage)
		{
			Weapon* purchase = &(m_weapon[(page - 1) * 5 + select - 1]);
			int price = purchase->GetPrice();

			if (m_player->GetGold() >= price)
			{
				m_player->SetWeapon(purchase, type);
				m_player->DecreaseGold(price);
			}
		}
		else if (select == count_inPage + 1 && page > 1)
			page--;
		else if (select == count_inPage + 2 && page <= (count - 1) / 5)
			page++;
		else if (select == count_inPage + 3)
			return;
	}
}

void RPG_Game::PlayerInfo()
{
	m_map.EraseBoxInner();
	m_player->DrawStatus(m_map.GetScale().width * 16, m_map.GetScale().height * 15, YELLOW);
	getch();
}

void RPG_Game::MonsterInfo()
{
	m_map.EraseBoxInner();
	m_goblin->DrawStatus(m_map.GetScale().width * 16, m_map.GetScale().height * 3);
	m_oak->DrawStatus(m_map.GetScale().width * 16, m_map.GetScale().height * 7);
	m_werewolf->DrawStatus(m_map.GetScale().width * 16, m_map.GetScale().height * 11);
	m_ogre->DrawStatus(m_map.GetScale().width * 16, m_map.GetScale().height * 15);
	m_skeletonArcher->DrawStatus(m_map.GetScale().width * 16, m_map.GetScale().height * 19);
	m_rich->DrawStatus(m_map.GetScale().width * 16, m_map.GetScale().height * 23);
	getch();
}

void RPG_Game::Save()
{
	m_map.EraseBoxInner();
	for (int i = 1; i <= SLOT_COUNT; i++)
	{
		ifstream load;

		load.open("SaveData" + to_string(i) + ".txt");
		m_map.DrawSlot(i, load.is_open(), SLOT_COUNT);
		if (load.is_open())
			load.close();
	}

	ofstream save;
	int select = m_map.MenuSelectCursor(SLOT_COUNT + 1, m_map.GetScale().height * 2, m_map.GetScale().width * 8, m_map.GetScale().height * 5);
	if (select <= SLOT_COUNT)
	{
		save.open("SaveData" + to_string(select) + ".txt");

		RecordCharacterData(save, m_goblin);
		RecordCharacterData(save, m_oak);
		RecordCharacterData(save, m_werewolf);
		RecordCharacterData(save, m_ogre);
		RecordCharacterData(save, m_skeletonArcher);
		RecordCharacterData(save, m_rich);
		RecordCharacterData(save, m_player);

		Weapon* weapon = m_player->GetWeapon();
		if (weapon != NULL)
		{
			save << "무기" << endl;
			save << weapon->GetType() << " ";
			save << weapon->GetName() << " ";
			save << weapon->GetDamage() << " ";
			save << weapon->GetPrice() << endl;
		}

		m_map.EraseBoxInner();
		m_map.DrawSaved();
		getch();
	}
	else
		return;
}

void RPG_Game::RecordCharacterData(ofstream& save, Character* character)
{
	save << character->GetName() << " ";
	save << character->GetRank() << " ";
	save << character->GetDamage() << " ";
	save << character->GetHp() << " ";
	save << character->GetHpMax() << " ";
	save << character->GetExp() << " ";
	save << character->GetExpMax() << " ";
	save << character->Get_getExp() << " ";
	save << character->GetGold() << endl;
}

bool RPG_Game::Load()
{
	while (true)
	{
		m_map.EraseBoxInner();
		for (int i = 1; i <= SLOT_COUNT; i++)
		{
			ifstream load;
			load.open("SaveData" + to_string(i) + ".txt");
			m_map.DrawSlot(i, load.is_open(), SLOT_COUNT);
			if (load.is_open())
				load.close();
		}

		int select = m_map.MenuSelectCursor(SLOT_COUNT + 1, m_map.GetScale().height * 2, m_map.GetScale().width * 8, m_map.GetScale().height * 5);
		if (select <= SLOT_COUNT)
		{
			ifstream load;
			load.open("SaveData" + to_string(select) + ".txt");
			if (load.is_open())
			{
				ReadCharacterData(load, m_goblin);
				ReadCharacterData(load, m_oak);
				ReadCharacterData(load, m_werewolf);
				ReadCharacterData(load, m_ogre);
				ReadCharacterData(load, m_skeletonArcher);
				ReadCharacterData(load, m_rich);
				ReadCharacterData(load, m_player);

				string check;
				load >> check;
				if (check == "무기")
				{
					string type;
					string name;
					int damage;
					int price;

					load >> type;
					load >> name;
					load >> damage;
					load >> price;

					Weapon* weapon = NULL;
					if (type == "Dagger")
						weapon = new Dagger;
					else if (type == "Gun")
						weapon = new Gun;
					else if (type == "Sword")
						weapon = new Sword;
					else if (type == "Wand")
						weapon = new Wand;
					else if (type == "Bow")
						weapon = new Bow;
					else if (type == "Hammer")
						weapon = new Hammer;
					weapon->SetStatus(type, name, price, damage);

					m_player->SetWeapon(weapon, type);
					delete weapon;
				}

				m_map.EraseBoxInner();
				m_map.DrawLoaded();
				getch();

				return true;
			}
			else
			{
				m_map.EraseBoxInner();
				m_map.DrawNoData();
				getch();
			}
		}
		else
			return false;
	}
}

void RPG_Game::ReadCharacterData(ifstream& load, Character* character)
{
	string name;
	int rank;
	int damage;
	int hp;
	int hpMax;
	int exp;
	int expMax;
	int getExp;
	int gold;

	load >> name;
	load >> rank;
	load >> damage;
	load >> hp;
	load >> hpMax;
	load >> exp;
	load >> expMax;
	load >> getExp;
	load >> gold;
	character->SetStatus(name, rank, damage, hp, hpMax, exp, expMax, getExp, gold);
}

int RPG_Game::CheckResult(int playerHand, int enemyHand)
{
	if (playerHand == enemyHand)
		return RESULT_TIE;

	if (playerHand == HAND_SCISSORS)
	{
		if (enemyHand == HAND_ROCK)
			return RESULT_LOSE;
		else if (enemyHand == HAND_PAPER)
			return RESULT_WIN;
	}
	else if (playerHand == HAND_ROCK)
	{
		if (enemyHand == HAND_PAPER)
			return RESULT_LOSE;
		else if (enemyHand == HAND_SCISSORS)
			return RESULT_WIN;
	}
	else if (playerHand == HAND_PAPER)
	{
		if (enemyHand == HAND_SCISSORS)
			return RESULT_LOSE;
		else if (enemyHand == HAND_ROCK)
			return RESULT_WIN;
	}
}

void RPG_Game::Stage(Enemy* enemy)
{
	m_map.EraseBoxInner();
	m_map.DrawStage();
	m_player->DrawStatus(m_map.GetScale().width * 16, m_map.GetScale().height * 3);
	enemy->DrawStatus(m_map.GetScale().width * 16, m_map.GetScale().height * 25);

	while (true)
	{
		int playerHand = getch() - '0';
		int enemyHand = RandNum(HAND_SCISSORS, HAND_PAPER);

		if (playerHand >= HAND_SCISSORS && playerHand <= HAND_PAPER)
		{
			int result = CheckResult(playerHand, enemyHand);

			string pl_result;
			string en_result;
			switch (result)
			{
			case RESULT_WIN:
				pl_result = "Win";
				en_result = "Lose";
				break;
			case RESULT_LOSE:
				pl_result = "Lose";
				en_result = "Win";
				break;
			case RESULT_TIE:
				pl_result = "Draw";
				en_result = "Draw";
				break;
			default:
				break;
			}
			m_map.EraseBoxInner();
			m_map.DrawStage();
			m_map.DrawHand(playerHand, enemyHand, pl_result, en_result);

			m_player->Event(m_map.GetScale().width * 16, m_map.GetScale().height * 14, enemy, result);
			m_player->DrawStatus(m_map.GetScale().width * 16, m_map.GetScale().height * 3);
			enemy->DrawStatus(m_map.GetScale().width * 16, m_map.GetScale().height * 25);
		}

		if (m_player->GetHp() <= 0)
		{
			MatchResult(enemy, m_player);
			getch();
			break;
		}
		else if (enemy->GetHp() <= 0)
		{
			MatchResult(m_player, enemy);
			m_player->IncreaseGold(enemy->GetGold());
			enemy->SetLive(false);
			getch();
			break;
		}
	}

	m_player->ResetHp();
	enemy->ResetHp();
}

void RPG_Game::MatchResult(Character* winner, Character* loser)
{
	winner->IncreaseExp(loser->Get_getExp());
	m_map.EraseBoxInner();
	m_map.DrawMatchResult(winner->GetName(), loser->Get_getExp());
}

bool RPG_Game::CheckClear()
{
	if (m_goblin->CheckLive())
		return false;
	else if (m_oak->CheckLive())
		return false;
	else if (m_werewolf->CheckLive())
		return false;
	else if (m_ogre->CheckLive())
		return false;
	else if (m_skeletonArcher->CheckLive())
		return false;
	else if (m_rich->CheckLive())
		return false;
	else
		return true;
}

void RPG_Game::NotifyObserver()
{
	m_goblin->Update();
	m_oak->Update();
	m_werewolf->Update();
	m_ogre->Update();
	m_skeletonArcher->Update();
	m_rich->Update();
}

RPG_Game::~RPG_Game()
{
	if (m_player != NULL)
		delete m_player;

	delete m_goblin;
	delete m_oak;
	delete m_werewolf;
	delete m_ogre;
	delete m_skeletonArcher;
	delete m_rich;

	delete[] m_weapon;
}