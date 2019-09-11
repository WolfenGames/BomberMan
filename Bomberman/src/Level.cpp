#include "Level.hpp"
#include "gtc/random.hpp"
#include "gtx/transform.hpp"
#include "Swallow/AssetManager/Primatives.hpp"
#include "Swallow/Renderer/material/FlatColourMaterial.hpp"
#include "BombermanApp.hpp"
#include "Wall.hpp"
#include "Bomb.hpp"
#include <chrono>

Level::Level(uint32_t Width, uint32_t Height)
	:Level(Width, Height, static_cast<uint32_t>(std::chrono::system_clock::now().time_since_epoch().count()), 0.6f)
{}

Level::Level(uint32_t Width, uint32_t Height, float chance)
	: Level(Width, Height, static_cast<uint32_t>(std::chrono::system_clock::now().time_since_epoch().count()), chance)
{}

Level::Level(uint32_t Width, uint32_t Height, uint32_t Seed, float chance)
	:m_Width(Width * 2 + 1), m_Height(Height * 2 + 1), m_Seed(Seed)
{
	int desiredEnemies = ((m_Width + m_Height) / 2.0f) * chance;
	srand(m_Seed);
	m_Map.reserve(m_Width * m_Height);
	for (uint32_t x = 0; x < m_Width; x++)
	{
		for (uint32_t y = 0; y < m_Height; y++)
		{
			int	ispillar = (x % 2 && y % 2);
			if (ispillar || (glm::linearRand(0.0f, 1.0f) > chance))//glm::linearRand(0, 10) > 1)
			{
				if (ispillar)
					m_Map.push_back(std::make_shared<Pillar>());
				else
					m_Map.push_back(std::make_shared<Wall>());
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
	if (check.x < 0 || check.z < 0 || check.x > m_Width - 1 || check.z > m_Height - 1 || m_Map[(static_cast<int>(check.x)) * m_Height + (static_cast<int>(check.z))]->isFilled())
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
			tile = std::make_shared<Tile>();
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
			tile = std::make_shared<Tile>();
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
			tile = std::make_shared<Tile>();
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
			tile = std::make_shared<Tile>();
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
	static_cast<void>(pos);
	if (m_TempTimer)
	{
		delete m_TempTimer;
		m_TempTimer = nullptr;
	}
	Level::Timer timer;
	timer.fuse = 1.5f;
	timer.x = pos.x;
	timer.y = pos.z;
	timer.power = 10;
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
	for (auto &f : m_Flames)
	{
		f->Advance(ts);
	}
	m_Flames.remove_if([](Swallow::Ref<Flame> a) -> bool { return a->Out(); });
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
	{
		Swallow::Renderer::Submit(f);
	}
	Swallow::Renderer::Submit(m_Player);
}