#include "Level.hpp"
#include "gtc/random.hpp"
#include "gtx/transform.hpp"
#include "Swallow/AssetManager/Primatives.hpp"
#include "Swallow/Renderer/material/FlatColourMaterial.hpp"
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
	m_Cube = Swallow::Primatives::Cube();
	srand(m_Seed);
	m_Map.reserve(m_Width * m_Height);
	Swallow::Ref<Swallow::FlatColourMaterialInstance> Pillar = Swallow::FlatColourMaterial::Create();
	Pillar->SetColour(glm::vec4(0.5, 0.5, 0.5, 1.0));
	Swallow::Ref<Swallow::FlatColourMaterialInstance> Brick = Swallow::FlatColourMaterial::Create();
	Brick->SetColour(glm::vec4(0.9, 0.5, 0.2, 1.0));
	for (uint32_t x = 0; x < m_Width; x++)
	{
		for (uint32_t y = 0; y < m_Height; y++)
		{
			m_Map.push_back(std::make_shared<Wall>());
			m_Map[x * m_Height + y]->SetVertexArray(m_Cube->GetVertexArray());
			m_Map[x * m_Height + y]->GetTransform()->SetPosition(glm::vec3(x + 0.5f, 0.0f, y + 0.5f));
			m_Map[x * m_Height + y]->SetMaterial((x % 2 && y % 2) ? Pillar : Brick);
			m_Map[(x) * m_Height + (y)]->GetTransform()->Recalculate();
		}
	}
	m_Enemies.reserve(desiredEnemies);
	glm::ivec2 pos;
	for (int i = 0; i < desiredEnemies; i++)
	{
		pos = glm::linearRand(glm::ivec2(0, 0), glm::ivec2(Width, Height));
		pos *= 2;
		SW_INFO("{}, {}", pos.x, pos.y);
		MakeEnemy(pos.x, pos.y);
	}
	glm::ivec2 playerstart = glm::linearRand(glm::ivec2(0, 0), glm::ivec2(Width, Height));
	playerstart *= 2;
	m_Map[(playerstart.x) * m_Height + (playerstart.y)].reset();
	m_Player = std::make_shared<Player>(glm::vec3(playerstart.x + 0.5, 0, playerstart.y + 0.5), *this);
	if (static_cast<uint32_t>(playerstart.y) != m_Height - 1)
		m_Map[(playerstart.x) * m_Height + (playerstart.y + 1)].reset();
	if (playerstart.y != 0)
		m_Map[(playerstart.x) * m_Height + (playerstart.y - 1)].reset();
	if (static_cast<uint32_t>(playerstart.x) != m_Width - 1)
		m_Map[(playerstart.x + 1) * m_Height + (playerstart.y)].reset();
	if (playerstart.x != 0)
		m_Map[(playerstart.x - 1) * m_Height + (playerstart.y)].reset();
	m_Cube->SetMaterial(Swallow::FlatColourMaterial::Create());
	m_Player->SetVertexArray(Swallow::AssetManager::FetchObject("Bomberman", "Bomberman"));
	Swallow::Ref<Swallow::FlatColourMaterialInstance> mat = Swallow::FlatColourMaterial::Create();
	mat->SetColour(glm::vec4(0.2f, 0.5f, 1.0f, 1.0f));
	m_Player->SetMaterial(mat);
	m_Player->GetTransform()->SetScale(glm::vec3(0.20f));
	Swallow::Ref<Swallow::FlatColourMaterialInstance> mat2 = Swallow::FlatColourMaterial::Create();
	mat2->SetColour(glm::vec4(0.9f, 0.1f, 0.2f, 1.0f));
	for (auto x : m_Enemies)
	{
		x->SetMaterial(Swallow::FlatColourMaterial::Create());
		x->SetVertexArray(Swallow::AssetManager::FetchObject("Bomberman", "Bomberman"));
		x->SetMaterial(mat2);
		x->GetTransform()->SetScale(glm::vec3(0.18f));
	}
}

char Level::MakeEnemy(int x, int y)
{
	Swallow::Ref<Enemy> newRef = std::make_shared<Enemy>(glm::vec3(x + 0.5f, 0, y + 0.5f), *this);
	m_Enemies.push_back(newRef);
	return '.';
}

Level::~Level()
{
}

bool Level::IsEmpty(glm::vec3 check) const
{
	check.x = glm::floor(check.x);
	check.z = glm::floor(check.z);
	if (check.x < 0 || check.z < 0 || check.x > m_Width - 1 || check.z > m_Height - 1 || m_Map[(static_cast<int>(check.x)) * m_Height + (static_cast<int>(check.z))])
		return false;
	return true;
}

void Level::DropBomb(glm::vec3 pos)
{
	static_cast<void>(pos);
	Swallow::Ref<Swallow::FlatColourMaterialInstance> Bomb = Swallow::FlatColourMaterial::Create();
	Bomb->SetColour({0.0f, 0.0f, 0.0f, 1.0f});
	if (m_TempTimer)
	{
		delete m_TempTimer;
		m_TempTimer = nullptr;
	}
	Level::Timer timer;
	timer.fuse = 1.5f;
	timer.x = pos.x;
	timer.y = pos.z;
	if (IsEmpty(pos))
	{
		m_TempTimer = new Level::Timer;
		m_TempTimer->fuse = timer.fuse;
		m_TempTimer->x = timer.x;
		m_TempTimer->y = timer.y;
		m_Map[(static_cast<uint32_t>(pos.x)) * m_Height + (static_cast<uint32_t>(pos.z))] = std::make_shared<Wall>();
		m_Map[(static_cast<uint32_t>(pos.x)) * m_Height + (static_cast<uint32_t>(pos.z))]->SetVertexArray(Swallow::AssetManager::FetchObject("Bomb", "Bomb"));
		m_Map[(static_cast<uint32_t>(pos.x)) * m_Height + (static_cast<uint32_t>(pos.z))]->SetMaterial(Bomb);
		m_Map[(static_cast<uint32_t>(pos.x)) * m_Height + (static_cast<uint32_t>(pos.z))]->GetTransform()->SetPosition(pos);
		m_Map[(static_cast<uint32_t>(pos.x)) * m_Height + (static_cast<uint32_t>(pos.z))]->GetTransform()->SetScale(glm::vec3(0.5f));
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
		if (static_cast<uint32_t>(m_BombTimers.back().y) != m_Height - 1 && m_Map[(m_BombTimers.back().x) * m_Height + (m_BombTimers.back().y + 1)])
			m_Map[(m_BombTimers.back().x) * m_Height + (m_BombTimers.back().y + 1)].reset();
		if (static_cast<uint32_t>(m_BombTimers.back().y) != 0 && m_Map[(m_BombTimers.back().x) * m_Height + (m_BombTimers.back().y - 1)])
			m_Map[(m_BombTimers.back().x) * m_Height + (m_BombTimers.back().y - 1)].reset();
		if (static_cast<uint32_t>(m_BombTimers.back().x) != m_Width - 1 && m_Map[(m_BombTimers.back().x + 1) * m_Height + (m_BombTimers.back().y)])
			m_Map[(m_BombTimers.back().x + 1) * m_Height + (m_BombTimers.back().y)].reset();
		if (static_cast<uint32_t>(m_BombTimers.back().x) != 0 && m_Map[(m_BombTimers.back().x - 1) * m_Height + (m_BombTimers.back().y)])
			m_Map[(m_BombTimers.back().x - 1) * m_Height + (m_BombTimers.back().y)].reset();
		m_Map[(m_BombTimers.back().x) * m_Height + (m_BombTimers.back().y)].reset();
		m_BombTimers.pop_back();
	}
	m_Player->Update(ts);
	for (auto enemy : m_Enemies)
		enemy->Update(ts);
}

void Level::Draw()
{
	m_Cube->GetTransform()->SetScale(glm::vec3(0.9f));
	for (uint32_t x = 0; x < m_Width; x++)
	{
		for (uint32_t y = 0; y < m_Height; y++)
		{
			if (m_Map[(x) * m_Height + (y)])
			{
				Swallow::Ref<Swallow::Transform> t = m_Map[(x) * m_Height + (y)]->GetTransform();
				Swallow::Ref<Swallow::FlatColourMaterialInstance> mat = std::dynamic_pointer_cast<Swallow::FlatColourMaterialInstance>(m_Map[(x) * m_Height + (y)]->GetMaterial());
				Swallow::Renderer::Submit(m_Map[(x) * m_Height + (y)]);
			}
		}
	}
	for (auto x : m_Enemies)
		Swallow::Renderer::Submit((Swallow::Ref<Enemy>(x)));
	Swallow::Renderer::Submit(m_Player);
}