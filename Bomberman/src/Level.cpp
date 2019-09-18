#include "Level.hpp"
#include "gtc/random.hpp"
#include "gtx/transform.hpp"
#include "Swallow/AssetManager/Primatives.hpp"
#include "Swallow/Renderer/material/FlatColourMaterial.hpp"
#include "BombermanApp.hpp"
#include "Wall.hpp"
#include "Bomb.hpp"
#include "Exit.hpp"
#include <chrono>
#include "PowerUp.hpp"
#ifdef SW_MACOSX
	#include <sys/stat.h>
#endif

Level::Level(const std::string &name)
{
	std::string path = "Saves/";
	std::ifstream in;
	in.open(path + name + ".sav", std::ios::binary);
	in.read(reinterpret_cast<char *>(&m_Width), 4);
	in.read(reinterpret_cast<char *>(&m_Height), 4);
	m_Floor = std::make_shared<Swallow::GameObject>();
	m_Floor->SetVertexArray(Swallow::AssetManager::FetchObject("Cube", "Cube"));
	m_Floor->GetTransform()->SetScale(glm::vec3(m_Width, 1, m_Height));
	m_Floor->SetMaterial(Swallow::FlatColourMaterial::Create());
	m_Floor->GetTransform()->SetPosition(glm::vec3(m_Width / 2.0, -1, m_Height / 2.0));
	m_Floor->GetTransform()->Recalculate();
	std::dynamic_pointer_cast<Swallow::FlatColourMaterialInstance>(m_Floor->GetMaterial())->SetColour(glm::vec4(1, 1, 1, 1));
	m_Map.reserve(m_Width * m_Height);
	for (uint i = 0; i < (m_Width * m_Height); i++)
	{
		char what;
		in.read(&what, 1);
		switch (what)
		{
		case 0:
			m_Map.push_back(std::make_shared<Tile>());
			break;
		case 1:
			m_Map.push_back(std::make_shared<Wall>());
			break;
		case 2:
			if((i / m_Height) % 2 && (i % m_Height) % 2)
				m_Map.push_back(std::make_shared<Pillar>());
			else
				m_Map.push_back(std::make_shared<Tile>());
			break;
		default:
			break;
		}
		m_Map[i]->GetTransform()->SetPosition(glm::vec3(i / m_Height + 0.5f, 0, i % m_Height + 0.5f));
		m_Map[i]->GetTransform()->Recalculate();
	}
	int count;
	in.read(reinterpret_cast<char *>(&count), 4);
	SW_INFO("Enemy Count: {}", count);
	float x, y;
	for (int i = 0; i < count; i++)
	{
		in.read(reinterpret_cast<char *>(&x), sizeof(float));
		in.read(reinterpret_cast<char *>(&y), sizeof(float));
		SW_INFO("Enemy at: {} x {}", x, y);
		m_Enemies.push_back(std::make_shared<Enemy>(glm::vec3(x, 0, y), *this));
		// m_Enemies.back()->GetTransform()->Recalculate();
	}
	SW_INFO("Enemies In");
	in.read(reinterpret_cast<char *>(&x), sizeof(float));
	in.read(reinterpret_cast<char *>(&y), sizeof(float));
	m_Player = std::make_shared<Player>(glm::vec3(static_cast<int>(x) + 0.5f, 0, static_cast<int>(y) + 0.5f), *this);
	in.close();
	SW_INFO("Done");
}

static bool	dieded = false;
static bool hasExit = false;

Level::Level(uint32_t Width, uint32_t Height)
	:Level(Width, Height, static_cast<uint32_t>(std::chrono::system_clock::now().time_since_epoch().count()), 0.6f)
{}

Level::Level(uint32_t Width, uint32_t Height, float chance)
	: Level(Width, Height, static_cast<uint32_t>(std::chrono::system_clock::now().time_since_epoch().count()), chance)
{}

Level::Level(uint32_t Width, uint32_t Height, uint32_t Seed, float chance)
	:m_Width(Width * 2 + 1), m_Height(Height * 2 + 1), m_Seed(Seed)
{
	dieded = false;
	int desiredEnemies = ((m_Width + m_Height) / 2.0f) * chance;
	srand(m_Seed);
	m_Floor = std::make_shared<Swallow::GameObject>();
	m_Floor->SetVertexArray(Swallow::AssetManager::FetchObject("Cube", "Cube"));
	m_Floor->GetTransform()->SetScale(glm::vec3(m_Width, 1, m_Height));
	m_Floor->SetMaterial(Swallow::FlatColourMaterial::Create());
	m_Floor->GetTransform()->SetPosition(glm::vec3(m_Width / 2.0, -1, m_Height / 2.0));
	m_Floor->GetTransform()->Recalculate();
	std::dynamic_pointer_cast<Swallow::FlatColourMaterialInstance>(m_Floor->GetMaterial())->SetColour(glm::vec4(1, 1, 1, 1));
	m_Map.reserve(m_Width * m_Height);
	hasExit = false;
	uint source = glm::linearRand(static_cast<unsigned int>(0), m_Width * m_Height);
	for (uint32_t x = 0; x < m_Width; x++)
	{
		for (uint32_t y = 0; y < m_Height; y++)
		{
			int	ispillar = (x % 2 && y % 2);
			if (ispillar || (glm::linearRand(0.0f, 1.0f) > chance))
			{
				if (ispillar)
					m_Map.push_back(std::make_shared<Pillar>());
				else
				{
					bool possim;
					if (!hasExit)
					{
						uint target = (x * m_Height + y);
						possim = (source < target);
					}
					auto newWall = std::make_shared<Wall>();
					bool	PowerUpChance = ((glm::linearRand(0, 10) >= 9));
					if (PowerUpChance) MakePowerUp(x, y);
					if (!hasExit && possim)
					{
						hasExit = true;
						newWall->SetExit(true);
					}
					m_Map.push_back(newWall);
				}
				m_Map[(x) * m_Height + (y)]->GetTransform()->SetPosition(glm::vec3(x + 0.5f, 0, y + 0.5f));
				m_Map[(x) * m_Height + (y)]->GetTransform()->Recalculate();
			}
			else
			{
				m_Map.push_back(std::make_shared<Tile>());
			}
		}
	}
	m_Enemies.reserve(desiredEnemies);
	glm::ivec2 pos;

	glm::ivec2 playerstart = glm::linearRand(glm::ivec2(0, 0), glm::ivec2(Width, Height));
	playerstart *= 2;
	m_Map[(playerstart.x) * m_Height + (playerstart.y)] = std::make_shared<Tile>();
	m_Player = std::make_shared<Player>(glm::vec3(playerstart.x + 0.5, 0, playerstart.y + 0.5), *this);
	if (static_cast<uint32_t>(playerstart.y) != m_Height - 1)
		m_Map[(playerstart.x) * m_Height + (playerstart.y + 1)] = std::make_shared<Tile>();
	if (playerstart.y != 0)
		m_Map[(playerstart.x) * m_Height + (playerstart.y - 1)] = std::make_shared<Tile>();
	if (static_cast<uint32_t>(playerstart.x) != m_Width - 1)
		m_Map[(playerstart.x + 1) * m_Height + (playerstart.y)] = std::make_shared<Tile>();
	if (playerstart.x != 0)
		m_Map[(playerstart.x - 1) * m_Height + (playerstart.y)] = std::make_shared<Tile>();
	
	for (int i = 0; i < desiredEnemies; i++)
	{
		pos = glm::linearRand(glm::ivec2(0, 0), glm::ivec2(Width, Height));
		pos *= 2;
		MakeEnemy(pos.x, pos.y);
	}
	// int	desiredPowerUps = ((m_Width + m_Height) / 2.0f) * (chance);
	// for(int i = 0; i < desiredPowerUps; i++)
	// {
	// 	pos = glm::linearRand(glm::ivec2(0, 0), glm::ivec2(Width, Height));
	// 	pos *= 2;	
	// }
}

void Level::MakePowerUp(int x, int y)
{
	SW_INFO("I HAVE BEEN MADE");
	auto newpos = glm::vec3(x + 0.5f, 0, y + 0.5f);
	int	whichPowerUpToSpawn = glm::linearRand(0, static_cast<int>(PowerUpTypes::TotalPowerUps) - 2);
	m_PowerUps.push_back(powerUpFactory.newPowerUp(PowerUpTypes(whichPowerUpToSpawn)));
	m_PowerUps.back()->GetTransform()->SetPosition(newpos);
	m_PowerUps.back()->GetTransform()->Recalculate();
}

void Level::MakeEnemy(int x, int y)
{
	Swallow::Ref<Enemy> newRef = std::make_shared<Enemy>(glm::vec3(x + 0.5f, 0, y + 0.5f), *this);
	glm::vec3 ePos = newRef->GetTransform()->GetPosition();
	glm::vec3 myPos = m_Player->GetTransform()->GetPosition();
	if (glm::length(ePos - myPos) < 2.0)
	{
		return ;
	}
	m_Enemies.push_back(newRef);
	return ;
}

Level::~Level()
{
}

bool Level::IsEmpty(glm::vec3 check) const
{
	check.x = glm::floor(check.x);
	check.z = glm::floor(check.z);
	if (check.x < 0 || check.z < 0 || check.x > m_Width - 1 || check.z > m_Height - 1 ||
		(m_Map[(static_cast<int>(check.x)) * m_Height + (static_cast<int>(check.z))]->isFilled()))
		return false;
	return true;
}

bool Level::IsExit(glm::vec3 check) const
{
	check.x = glm::floor(check.x);
	check.z = glm::floor(check.z);
	if (check.x < 0 || check.z < 0 || check.x > m_Width - 1 || check.z > m_Height - 1 ||
		!m_Map[(static_cast<int>(check.x)) * m_Height + (static_cast<int>(check.z))]->IsExit())
		return false;
	return true;
}

int Level::InBlock(Swallow::Ref<Swallow::GameObject> o, int x, int y)
{
	return (static_cast<int>(o->GetTransform()->GetPosition().x) == x &&
	static_cast<int>(o->GetTransform()->GetPosition().z) == y);
}

int Level::Burn(int x, int y)
{
	Swallow::Ref<Flame> f = std::make_shared<Flame>();
	f->GetTransform()->SetPosition(glm::vec3(x + 0.5f, 0, y + 0.5f));
	f->GetTransform()->Recalculate();
	m_Flames.push_back(f);
	if (InBlock(m_Player, x, y))
		return 1;
	std::vector<Swallow::Ref<Enemy>> Enemies;
	for (auto &e : m_Enemies)
	{
		if (!InBlock(e, x, y))
			Enemies.push_back(e);
	}
	m_Enemies = Enemies;
	return 0;
}

void Level::Explode(Timer &t)
{
	if (Burn(t.x, t.y))
	{
		m_DEAD = true;
		return ;
	}
	for (int i = 1; t.x - i >= 0 && i < t.power; i++)
	{
		int x = t.x - i;
		int y = t.y;
		if (Burn(x, y))
		{
			m_DEAD = true;
			return ;
		}
		auto &tile = m_Map[x * m_Height + y];
		if (!tile->isFilled())
			continue;
		if (tile->isDestructable())
		{
			if (!tile->IsExit())
				tile = std::make_shared<Tile>();
			else
			{
				tile = std::make_shared<LevelExit>();
				tile->GetTransform()->SetPosition(glm::vec3(x + 0.5f, 0, y + 0.5f));
				tile->GetTransform()->Recalculate();
			}
			
			if (!m_Player->GetBombsCanBypassWalls())
				break;
		}
		else
		{
			for (auto &timer : m_BombTimers)
			{
				if (timer.x == x && timer.y == y)
				{
					timer.fuse = 0.0f;
				}
			}
			break;
		}
	}
	for (int i = 1; t.x + i < static_cast<int>(m_Width) && i < t.power; i++)
	{
		int x = t.x + i;
		int y = t.y;
		if (Burn(x, y))
		{
			m_DEAD = true;
			return ;
		}
		auto &tile = m_Map[x * m_Height + y];
		if (!tile->isFilled())
			continue;
		if (tile->isDestructable())
		{
			if (!tile->IsExit())
				tile = std::make_shared<Tile>();
			else
			{
				tile = std::make_shared<LevelExit>();
				tile->GetTransform()->SetPosition(glm::vec3(x + 0.5f, 0, y + 0.5f));
				tile->GetTransform()->Recalculate();
			}
			if (!m_Player->GetBombsCanBypassWalls())
				break;
		}
		else
		{
			for (auto &timer : m_BombTimers)
			{
				if (timer.x == x && timer.y == y)
				{
					timer.fuse = 0.0f;
				}
			}
			break;
		}
	}
	for (int i = 1; t.y - i >= 0 && i < t.power; i++)
	{
		int x = t.x;
		int y = t.y - i;
		if (Burn(x, y))
		{
			m_DEAD = true;
			return ;
		}
		auto &tile = m_Map[x * m_Height + y];
		if (!tile->isFilled())
			continue;
		if (tile->isDestructable())
		{
			if (!tile->IsExit())
				tile = std::make_shared<Tile>();
			else if (tile->IsExit())
			{
				tile = std::make_shared<LevelExit>();
				tile->GetTransform()->SetPosition(glm::vec3(x + 0.5f, 0, y + 0.5f));
				tile->GetTransform()->Recalculate();
			}
			if (!m_Player->GetBombsCanBypassWalls())
				break;
		}
		else
		{
			for (auto &timer : m_BombTimers)
			{
				if (timer.x == x && timer.y == y)
				{
					timer.fuse = 0.0f;
				}
			}
			break;
		}
	}
	for (int i = 1; t.y + i < static_cast<int>(m_Height) && i < t.power; i++)
	{
		int x = t.x;
		int y = t.y + i;
		if (Burn(x, y))
		{
			m_DEAD = true;
			return ;
		}
		auto &tile = m_Map[x * m_Height + y];
		if (!tile->isFilled())
			continue;
		if (tile->isDestructable())
		{
			if (!tile->IsExit())
				tile = std::make_shared<Tile>();
			else
			{
				tile = std::make_shared<LevelExit>();
				tile->GetTransform()->SetPosition(glm::vec3(x + 0.5f, 0, y + 0.5f));
				tile->GetTransform()->Recalculate();
			}
			if (!m_Player->GetBombsCanBypassWalls())
				break;
		}
		else
		{
			for (auto &timer : m_BombTimers)
			{
				if (timer.x == x && timer.y == y)
				{
					timer.fuse = 0.0f;
				}
			}
			break;
		}
	}
}

void Level::DropBomb(glm::vec3 pos)
{
	if (m_BombTimers.size() == static_cast<unsigned long>(m_Player->GetBombCount()))
		return;
	static_cast<void>(pos);
	if (m_TempTimer)
	{
		delete m_TempTimer;
		m_TempTimer = nullptr;
	}
	Level::Timer timer;
	timer.fuse = 3.f;
	timer.x = pos.x;
	timer.y = pos.z;
	timer.power = m_Player->GetFireDistance();
	if (IsEmpty(pos))
	{
		m_TempTimer = new Level::Timer;
		m_TempTimer->fuse = timer.fuse;
		m_TempTimer->x = timer.x;
		m_TempTimer->y = timer.y;
		m_TempTimer->power = timer.power;
		m_Map[(static_cast<uint32_t>(pos.x)) * m_Height + (static_cast<uint32_t>(pos.z))] = std::make_shared<Bomb>();
		m_Map[(static_cast<uint32_t>(pos.x)) * m_Height + (static_cast<uint32_t>(pos.z))]->GetTransform()->SetPosition(pos);
		m_Map[(static_cast<uint32_t>(pos.x)) * m_Height + (static_cast<uint32_t>(pos.z))]->GetTransform()->Recalculate();
	}
}

void Level::Update(Swallow::Timestep ts)
{
	if (m_TempTimer)
	{
		m_BombTimers.push_back(*m_TempTimer);
		delete m_TempTimer;
		m_TempTimer = nullptr;
	}
	for (auto &timer : m_BombTimers)
	{
		timer.fuse -= ts.GetSeconds();
	}
	std::sort(m_BombTimers.begin(), m_BombTimers.end(), [](Level::Timer a, Level::Timer b) -> int { return a.fuse > b.fuse; });
	while (m_BombTimers.size() && m_BombTimers.back().fuse < 0.0)
	{
		Explode (m_BombTimers.back());
		auto tileCheck = m_Map[(m_BombTimers.back().x) * m_Height + (m_BombTimers.back().y)];
		if (tileCheck->IsExit())
			 m_Map[(m_BombTimers.back().x) * m_Height + (m_BombTimers.back().y)] = std::make_shared<Exit>(glm::vec3({(m_BombTimers.back().x), 0, (m_BombTimers.back().y)}));
		else
		 	 m_Map[(m_BombTimers.back().x) * m_Height + (m_BombTimers.back().y)] = std::make_shared<Tile>();
		m_BombTimers.pop_back();
	}
	m_Player->Update(ts);
	for (auto enemy : m_Enemies)
	{
		enemy->Update(ts);
		glm::vec3 ePos = enemy->GetTransform()->GetPosition();
		glm::vec3 myPos = m_Player->GetTransform()->GetPosition();
		if (glm::length(ePos - myPos) < 0.5)
		{
			m_DEAD = true;
		}
	}
	for (auto powerInACan: m_PowerUps)
	{
		glm::vec3 ePos = powerInACan->GetTransform()->GetPosition();
		glm::vec3 myPos = m_Player->GetTransform()->GetPosition();
		if (glm::length(ePos - myPos) < 0.5)
		{
			std::vector<Swallow::Ref<PowerUp>> newList;
			m_Player->AddPower(powerInACan);
			for (auto oldPowerInACan: m_PowerUps)
			{
				if (oldPowerInACan != powerInACan)
				{
					newList.push_back(oldPowerInACan);
				}
			}
			m_PowerUps = newList;
		}
	}
	for (auto &f : m_Flames)
	{
		f->Advance(ts);
	}
	m_Flames.remove_if([](Swallow::Ref<Flame> a) -> bool { return a->Out(); });

	if (m_Enemies.size() == 0 && !dieded)
	{
		dieded = true;
		SW_CORE_INFO("EMEINES DIEDED");
		//Some CanExit thing...
	}
}

void Level::Draw()
{
	for (uint32_t x = 0; x < m_Width; x++)
	{
		for (uint32_t y = 0; y < m_Height; y++)
		{
			if (m_Map[(x) * m_Height + (y)]->isFilled())
			{
				Swallow::Ref<Swallow::Transform> t = m_Map[(x) * m_Height + (y)]->GetTransform();
				Swallow::Ref<Swallow::FlatColourMaterialInstance> mat = std::dynamic_pointer_cast<Swallow::FlatColourMaterialInstance>(m_Map[(x) * m_Height + (y)]->GetMaterial());
				Swallow::Renderer::Submit(m_Map[(x) * m_Height + (y)]);
			}
		}
	}
	for (auto x : m_Enemies)
		Swallow::Renderer::Submit((Swallow::Ref<Enemy>(x)));
	for (auto &f : m_Flames)
		Swallow::Renderer::Submit(f);
	for (auto p: m_PowerUps)
		Swallow::Renderer::Submit(p);
	Swallow::Renderer::Submit(m_Player);
	Swallow::Renderer::Submit(m_Floor);
}

void Level::Save(const std::string &name)
{
	#ifdef SW_MACOSX
		mkdir("Saves", S_IRWXU | S_IRGRP | S_IXGRP | S_IROTH | S_IXOTH);
	#endif
	std::string path = "Saves/";
	std::ofstream f(path + name + ".sav", std::ios::binary);
	f.write(reinterpret_cast<char *>(&m_Width), 4);
	f.write(reinterpret_cast<char *>(&m_Height), 4);
	for (uint i = 0; i < (m_Width * m_Height); i++)
	{
		char v = 0;
		if (m_Map[i]->isFilled())
		{
			if (m_Map[i]->isDestructable())
			{
				v = 1;
			}
			else
			{
				v = 2;
			}
			
		}
		f.write(&v, 1);
	}
	int count = m_Enemies.size();
	f.write(reinterpret_cast<char *>(&count), 4);
	for (auto &e : m_Enemies)
	{
		f.write(reinterpret_cast<char *>(&e->GetTransform()->GetPosition().x), sizeof(float));
		f.write(reinterpret_cast<char *>(&e->GetTransform()->GetPosition().z), sizeof(float));
	}
	f.write(reinterpret_cast<char *>(&m_Player->GetTransform()->GetPosition().x), sizeof(float));
	f.write(reinterpret_cast<char *>(&m_Player->GetTransform()->GetPosition().z), sizeof(float));
	f.close();
}