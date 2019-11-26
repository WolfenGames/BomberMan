#include "Level.hpp"
#include "gtc/random.hpp"
#include "gtx/transform.hpp"
#include "Swallow/AssetManager/Primatives.hpp"
#include "Swallow/Renderer/material/FlatColourMaterial.hpp"
#include "BombermanApp.hpp"
#include "Wall.hpp"
#include "Bomb.hpp"
#include <chrono>
#include "PowerUp.hpp"
#ifdef SW_MACOSX
	#include <sys/stat.h>
#endif

void Level::Load(const std::string &name)
{
	m_Player->Reset();
	m_DEAD = false;
	m_Enemies.clear();
	m_Flames.clear();
	m_PowerUps.clear();
	m_Map.clear();
	std::string path = "Saves/";
	std::ifstream in;
	in.open(path + name + ".sav", std::ios::binary);
	in.read(reinterpret_cast<char *>(&m_Width), 4);
	in.read(reinterpret_cast<char *>(&m_Height), 4);

	_MakeFloor();
	_MakeBoundry();
	m_Map.reserve(m_Width * m_Height);
	PowerUpTypes type;
	for (uint i = 0; i < (m_Width * m_Height); i++)
	{
		char what;
		in.read(&what, 1);
		in.read(reinterpret_cast<char*>(&type), sizeof(type));
		switch (what)
		{
		case 0:
			m_Map.push_back(std::make_shared<Tile>());
			break;
		case 1:
			m_Map.push_back(std::make_shared<Wall>());
			if (type != PowerUpTypes::None)
				m_Map[i]->SetSecret(type);
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
	float x, y;
	for (int i = 0; i < count; i++)
	{
		in.read(reinterpret_cast<char *>(&x), sizeof(float));
		in.read(reinterpret_cast<char *>(&y), sizeof(float));
		m_Enemies.push_back(std::make_shared<Enemy>(glm::vec3(x, 0, y), static_cast<BombermanApp &>(Swallow::Application::Get()).GetGameLayer()->GetLevel()));
		m_Enemies.back()->GetTransform()->Recalculate();
	}

	in.read(reinterpret_cast<char *>(&count), 4);
	for (int i = 0; i < count; i++)
	{
		in.read(reinterpret_cast<char *>(&x), sizeof(float));
		in.read(reinterpret_cast<char *>(&y), sizeof(float));
		in.read(reinterpret_cast<char *>(&type), sizeof(type));
		MakePowerUp(x, y, true, type);
	}

	in.read(reinterpret_cast<char *>(&x), sizeof(float));
	in.read(reinterpret_cast<char *>(&y), sizeof(float));
	m_Player->GetTransform()->SetPosition(glm::vec3(static_cast<int>(x) + 0.5f, 0, static_cast<int>(y) + 0.5f));
	m_Player->Destination() = m_Player->GetTransform()->GetPosition();
	int temp;
	in.read(reinterpret_cast<char *>(&temp), sizeof(int));
	SW_INFO("In Dist {}", temp);
	m_Player->SetFireDistance(temp);
	in.read(reinterpret_cast<char *>(&temp), sizeof(int));
	m_Player->SetBombCount(temp);
	in.read(reinterpret_cast<char *>(&temp), sizeof(int));
	m_Player->SetBombsCanBypassWalls(temp);
	in.read(reinterpret_cast<char *>(&temp), sizeof(int));
	m_Player->SetGhost(temp);
	in.read(reinterpret_cast<char *>(&temp), sizeof(int));
	m_Player->SetKey(temp);
	in.read(reinterpret_cast<char *>(&x), sizeof(float));
	m_Player->SetSpeed(x);
	in.read(reinterpret_cast<char *>(&temp), sizeof(int));
	static_cast<BombermanApp &>(Swallow::Application::Get()).GetGameLayer()->SetLives(temp);
	in.read(reinterpret_cast<char *>(&temp), sizeof(int));
	static_cast<BombermanApp &>(Swallow::Application::Get()).GetGameLayer()->SetScore(temp);
	in.read(reinterpret_cast<char *>(&x), sizeof(float));
	static_cast<BombermanApp &>(Swallow::Application::Get()).GetGameLayer()->SetDifficulty(x);
	in.close();
	SW_INFO("Done");
}

void Level::_MakeFloor()
{
	Swallow::Ref<Swallow::TextureMaterialInstance> floorMaterial = Swallow::TextureMaterial::Create();
	floorMaterial->SetTexture(Swallow::AssetManager::FetchTexture("Atlas"));

	m_FloorArray.reserve(m_Width * m_Height);
	for (uint i = 0; i < (m_Width * m_Height); i++)
	{
		m_FloorArray.push_back(std::make_shared<Floor>());

		m_FloorArray[i]->GetTransform()->SetPosition(glm::vec3(i / m_Height + 0.5f, -1, i % m_Height + 0.5f));

		m_FloorArray[i]->GetTransform()->Recalculate();
	}

}

void Level::_MakeBoundry()
{
	Swallow::Ref<Swallow::TextureMaterialInstance> floorMaterial = Swallow::TextureMaterial::Create();
	floorMaterial->SetTexture(Swallow::AssetManager::FetchTexture("Atlas"));

	m_Boundry.reserve(3 * 2 * (m_Height + 1) + m_Width);
	for (int i = 1; i <= (int)(m_Width); i++)
	{
		m_Boundry.push_back(std::make_shared<Pillar>());

		m_Boundry.back()->GetTransform()->SetPosition(glm::vec3(i - 0.5f, 0, -0.5f));

		m_Boundry.back()->GetTransform()->Recalculate();
	}
	for (int i = -1; i <= (int)(m_Height); i++)
	{
		m_Boundry.push_back(std::make_shared<Pillar>());
		m_Boundry.back()->GetTransform()->SetPosition(glm::vec3(-0.5f, 0, i - 0.5f));
		m_Boundry.back()->GetTransform()->Recalculate();
		m_Boundry.push_back(std::make_shared<Pillar>());
		m_Boundry.back()->GetTransform()->SetPosition(glm::vec3(-1.5f, 0, i - 0.5f));
		m_Boundry.back()->GetTransform()->Recalculate();
		m_Boundry.push_back(std::make_shared<Pillar>());
		m_Boundry.back()->GetTransform()->SetPosition(glm::vec3(-2.5f, 0, i - 0.5f));
		m_Boundry.back()->GetTransform()->Recalculate();
		m_Boundry.push_back(std::make_shared<Pillar>());
		m_Boundry.back()->GetTransform()->SetPosition(glm::vec3(m_Width + 0.5f, 0, i - 0.5f));
		m_Boundry.back()->GetTransform()->Recalculate();
		m_Boundry.push_back(std::make_shared<Pillar>());
		m_Boundry.back()->GetTransform()->SetPosition(glm::vec3(m_Width + 1.5f, 0, i - 0.5f));
		m_Boundry.back()->GetTransform()->Recalculate();
		m_Boundry.push_back(std::make_shared<Pillar>());
		m_Boundry.back()->GetTransform()->SetPosition(glm::vec3(m_Width + 2.5f, 0, i - 0.5f));
		m_Boundry.back()->GetTransform()->Recalculate();
	}

}

void Level::Generate(float chance)
{
	m_Player->Reset();
	m_DEAD = false;
	m_Enemies.clear();
	m_Flames.clear();
	m_PowerUps.clear();
	m_Map.clear();
	std::srand(static_cast<uint32_t>(std::chrono::system_clock::now().time_since_epoch().count()));
	int desiredEnemies = ((m_Width + m_Height) / 2.0f) * chance;


	_MakeFloor();
	_MakeBoundry();
	m_Map.reserve(m_Width * m_Height);
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
					auto newWall = std::make_shared<Wall>();
					if ((glm::linearRand(0, 10) >= 9))
						newWall->SetSecret(PowerUpTypes(glm::linearRand(PowerUpTypes::eFireIncrease + 0, PowerUpTypes::TotalPowerUps - 1)));
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
	bool hasExit = false;
	while (!hasExit)
	{
		uint source = glm::linearRand(static_cast<unsigned int>(0), m_Width * m_Height - 1);
		if (m_Map[source]->isDestructable())
		{
			hasExit = true;
			m_Map[source]->SetSecret(PowerUpTypes::eExit);
		}
	}
	hasExit = false;
	while (!hasExit)
	{
		uint source = glm::linearRand(static_cast<unsigned int>(0), m_Width * m_Height - 1);
		if (m_Map[source]->isDestructable() && m_Map[source]->GetSecret() != PowerUpTypes::eExit)
		{
			hasExit = true;
			m_Map[source]->SetSecret(PowerUpTypes::eKey);
		}
	}
	glm::ivec2 pos;

	glm::ivec2 playerstart = glm::linearRand(glm::ivec2(0, 0), glm::ivec2(m_Width / 2, m_Height / 2));
	playerstart *= 2;
	m_Map[(playerstart.x) * m_Height + (playerstart.y)] = std::make_shared<Tile>();
	m_Player->GetTransform()->SetPosition(glm::vec3(playerstart.x + 0.5, 0, playerstart.y + 0.5));
	m_Player->Destination() = m_Player->GetTransform()->GetPosition();
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
		pos = glm::linearRand(glm::ivec2(0, 0), glm::ivec2(m_Width / 2, m_Height / 2));
		pos *= 2;
		MakeEnemy(pos.x, pos.y);
	}
}

void Level::MakePowerUp(int x, int y, bool predetermined, int type)
{
	auto newpos = glm::vec3(x + 0.5f, 0, y + 0.5f);
	int	whichPowerUpToSpawn = (!predetermined) ? glm::linearRand(PowerUpTypes::eFireIncrease + 0, PowerUpTypes::TotalPowerUps - 1) : type;
	m_PowerUps.push_back(powerUpFactory.newPowerUp(PowerUpTypes(whichPowerUpToSpawn)));
	m_PowerUps.back()->GetTransform()->SetPosition(newpos);
	m_PowerUps.back()->GetTransform()->Recalculate();
}

void Level::MakeEnemy(int x, int y)
{
	Swallow::Ref<Enemy> newRef = std::make_shared<Enemy>(glm::vec3(x + 0.5f, 0, y + 0.5f), static_cast<BombermanApp &>(Swallow::Application::Get()).GetGameLayer()->GetLevel());
	glm::vec3 ePos = newRef->GetTransform()->GetPosition();
	glm::vec3 myPos = m_Player->GetTransform()->GetPosition();
	if (glm::length(ePos - myPos) < 5.0 || !IsEmpty(ePos, false))
		return ;
	m_Enemies.push_back(newRef);
}

Level::~Level()
{
}

bool Level::IsEmpty(glm::vec3 check, bool ghost) const
{
	check.x = glm::floor(check.x);
	check.z = glm::floor(check.z);
	if (check.x < 0 || check.z < 0 || check.x > m_Width - 1 || check.z > m_Height - 1 ||
		(m_Map[(static_cast<int>(check.x)) * m_Height + (static_cast<int>(check.z))]->isFilled() &&
		(!ghost || !m_Map[(static_cast<int>(check.x)) * m_Height + (static_cast<int>(check.z))]->isDestructable())))
		return false;
	return true;
}

int Level::InBlock(Swallow::Ref<Swallow::GameObject> o, int x, int y)
{
	return (static_cast<int>(o->GetTransform()->GetPosition().x) == x &&
	static_cast<int>(o->GetTransform()->GetPosition().z) == y);
}

void Level::Burn(int x, int y)
{
	Swallow::Ref<Flame> f = std::make_shared<Flame>();
	f->GetTransform()->SetPosition(glm::vec3(x + 0.5f, 0, y + 0.5f));
	f->GetTransform()->Recalculate();
	m_Flames.push_back(f);
}

void Level::Explode(Timer &t)
{
	m_Map[t.x * m_Height + t.y] = std::make_shared<Tile>();
	Burn(t.x, t.y);
	for (int i = 1; t.x - i >= 0 && i < t.power; i++)
	{
		int x = t.x - i;
		int y = t.y;
		Burn(x, y);
		auto &tile = m_Map[x * m_Height + y];
		if (!tile->isFilled())
			continue;
		if (tile->isDestructable())
		{

			if (tile->GetSecret() != PowerUpTypes::None)
				MakePowerUp(x, y, true, tile->GetSecret());
			tile = std::make_shared<Tile>();
			Swallow::Ref<GameLayer> g = static_cast<BombermanApp &>(Swallow::Application::Get()).GetGameLayer();
			g->SetScore(g->GetScore() + 100);
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
		Burn(x, y);
		auto &tile = m_Map[x * m_Height + y];
		if (!tile->isFilled())
			continue;
		if (tile->isDestructable())
		{
			if (tile->GetSecret() != PowerUpTypes::None)
				MakePowerUp(x, y, true, tile->GetSecret());
			tile = std::make_shared<Tile>();
			Swallow::Ref<GameLayer> g = static_cast<BombermanApp &>(Swallow::Application::Get()).GetGameLayer();
			g->SetScore(g->GetScore() + 100);
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
		Burn(x, y);
		auto &tile = m_Map[x * m_Height + y];
		if (!tile->isFilled())
			continue;
		if (tile->isDestructable())
		{
			if (tile->GetSecret() != PowerUpTypes::None)
				MakePowerUp(x, y, true, tile->GetSecret());
			tile = std::make_shared<Tile>();
			Swallow::Ref<GameLayer> g = static_cast<BombermanApp &>(Swallow::Application::Get()).GetGameLayer();
			g->SetScore(g->GetScore() + 100);
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
		Burn(x, y);
		auto &tile = m_Map[x * m_Height + y];
		if (!tile->isFilled())
			continue;
		if (tile->isDestructable())
		{
			if (tile->GetSecret() != PowerUpTypes::None)
				MakePowerUp(x, y, true, tile->GetSecret());
			tile = std::make_shared<Tile>();
			Swallow::Ref<GameLayer> g = static_cast<BombermanApp &>(Swallow::Application::Get()).GetGameLayer();
			g->SetScore(g->GetScore() + 100);
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
	if (m_BombTimers.size() == static_cast<unsigned long>(m_Player->GetBombCount()) + 1)
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
	if (IsEmpty(pos, false))
	{
		m_TempTimer = new Level::Timer;
		m_TempTimer->fuse = timer.fuse;
		m_TempTimer->x = timer.x;
		m_TempTimer->y = timer.y;
		m_TempTimer->power = timer.power;
		pos.y = 0;
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
		m_BombTimers.pop_back();
	}
	m_Player->Update(ts);
	for (auto &enemy : m_Enemies)
	{
		enemy->Update(ts);
		glm::vec3 ePos = enemy->GetTransform()->GetPosition();
		glm::vec3 myPos = m_Player->GetTransform()->GetPosition();
		if (glm::length(ePos - myPos) < 0.5)
		{
			m_DEAD = true;
		}
	}
	for (auto &powerInACan: m_PowerUps)
	{
		powerInACan->OnUpdate(ts);

		glm::vec3 ePos = powerInACan->GetTransform()->GetPosition();
		glm::vec3 myPos = m_Player->GetTransform()->GetPosition();
		if (glm::length(ePos - myPos) < 0.5)
		{
			Swallow::Ref<GameLayer> g = static_cast<BombermanApp &>(Swallow::Application::Get()).GetGameLayer();
			g->SetScore(g->GetScore() + 50);
			if (m_Player->AddPower(powerInACan))
				powerInACan->SetDelete(true);
		}
	}
	for (auto &f : m_Flames)
	{	
		glm::vec3 fPos = f->GetTransform()->GetPosition();
		for (auto &enemy : m_Enemies)
		{
			glm::vec3 ePos = enemy->GetTransform()->GetPosition();
			if (glm::length(ePos - fPos) < 0.5)
			{
				Swallow::Ref<GameLayer> g = static_cast<BombermanApp &>(Swallow::Application::Get()).GetGameLayer();
				g->SetScore(g->GetScore() + 500);
				enemy->SetDelete(true);
			}
		}
		glm::vec3 myPos = m_Player->GetTransform()->GetPosition();
		if (glm::length(fPos - myPos) < 0.5)
		{
			m_DEAD = true;
		}
		f->Advance(ts);
	}

	m_Enemies.remove_if([] (Swallow::Ref<Enemy> p) -> bool { return p->CanDelete(); });
	m_PowerUps.remove_if([] (Swallow::Ref<PowerUp> p) -> bool { return p->CanDelete(); });
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
			Swallow::Renderer::Submit(m_FloorArray[(x) * m_Height + (y)]);
		}
	}	

	//Left
	for (auto &boundry : m_Boundry)
		Swallow::Renderer::Submit(boundry);

	for (auto &x : m_Enemies)
		Swallow::Renderer::Submit((Swallow::Ref<Enemy>(x)));
	for (auto &f : m_Flames)
		Swallow::Renderer::Submit(f);
	for (auto p: m_PowerUps)
		Swallow::Renderer::Submit(p);
	Swallow::Renderer::Submit(m_Player);

	/* Olf Floor
	Swallow::Renderer::Submit(m_Floor);
	*/
}

void Level::Save(const std::string &name)
{
	if (name.length() < 1)
		return;
	#ifdef SW_PLATFORM_MACOSX
		mkdir("Saves", S_IRWXU | S_IRGRP | S_IXGRP | S_IROTH | S_IXOTH);
	#endif

	SW_INFO("Made dir");
	std::string path = "Saves/";
	std::ofstream f(path + name + ".sav", std::ios::binary);

	SW_INFO("file open");
	f.write(reinterpret_cast<char *>(&m_Width), 4);
	f.write(reinterpret_cast<char *>(&m_Height), 4);

	SW_INFO("WH");
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
		PowerUpTypes type = m_Map[i]->GetSecret();
		f.write(reinterpret_cast<char*>(&type), sizeof(type));
	}

	int count = m_Enemies.size();
	f.write(reinterpret_cast<char *>(&count), 4);
	for (auto &e : m_Enemies)
	{
		f.write(reinterpret_cast<char *>(&e->GetTransform()->GetPosition().x), sizeof(float));
		f.write(reinterpret_cast<char *>(&e->GetTransform()->GetPosition().z), sizeof(float));
	}

	count = m_PowerUps.size();
	f.write(reinterpret_cast<char *>(&count), 4);
	for (auto &e : m_PowerUps)
	{
		PowerUpTypes type = e->getPowerUpType();
		f.write(reinterpret_cast<char *>(&e->GetTransform()->GetPosition().x), sizeof(float));
		f.write(reinterpret_cast<char *>(&e->GetTransform()->GetPosition().z), sizeof(float));
		f.write(reinterpret_cast<char *>(&type), sizeof(type));
	}

	f.write(reinterpret_cast<char *>(&m_Player->GetTransform()->GetPosition().x), sizeof(float));
	f.write(reinterpret_cast<char *>(&m_Player->GetTransform()->GetPosition().z), sizeof(float));
	int temp = m_Player->GetFireDistance();
	SW_INFO("Dist {}", temp);
	f.write(reinterpret_cast<char *>(&temp), sizeof(int));
	temp = m_Player->GetBombCount();
	f.write(reinterpret_cast<char *>(&temp), sizeof(int));
	temp = m_Player->GetBombsCanBypassWalls();
	f.write(reinterpret_cast<char *>(&temp), sizeof(int));
	temp = m_Player->Ghost();
	f.write(reinterpret_cast<char *>(&temp), sizeof(int));
	temp = m_Player->HasKey();
	f.write(reinterpret_cast<char *>(&temp), sizeof(int));
	float x = m_Player->GetSpeed();
	f.write(reinterpret_cast<char *>(&x), sizeof(float));
	temp = static_cast<BombermanApp &>(Swallow::Application::Get()).GetGameLayer()->GetLives();
	f.write(reinterpret_cast<char *>(&temp), sizeof(int));
	temp = static_cast<BombermanApp &>(Swallow::Application::Get()).GetGameLayer()->GetScore();
	f.write(reinterpret_cast<char *>(&temp), sizeof(int));
	x = static_cast<BombermanApp &>(Swallow::Application::Get()).GetGameLayer()->GetScore();
	f.write(reinterpret_cast<char *>(&x), sizeof(float));
	f.close();
}