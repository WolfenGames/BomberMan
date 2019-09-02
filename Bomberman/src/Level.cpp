#include "Level.hpp"
#include "gtc/random.hpp"
#include "gtx/transform.hpp"
#include "Swallow/Renderer/Primatives.hpp"
#include "Swallow/Renderer/material/FlatColourMaterial.hpp"
#include <chrono>

Level::Level(uint32_t Width, uint32_t Height)
	:Level(Width, Height, static_cast<uint32_t>(std::chrono::system_clock::now().time_since_epoch().count()), 0.6f)
{
}

Level::Level(uint32_t Width, uint32_t Height, float chance)
	: Level(Width, Height, static_cast<uint32_t>(std::chrono::system_clock::now().time_since_epoch().count()), chance)
{
}

Level::Level(uint32_t Width, uint32_t Height, uint32_t Seed, float chance)
	:m_Width(Width * 2 + 1), m_Height(Height * 2 + 1), m_Seed(Seed)
{
	m_CurrentEnemies = 0;
	m_Cube = Swallow::Primatives::Cube();
	srand(m_Seed);
	m_Map = new char*[m_Width];
	for (uint32_t x = 0; x < m_Width; x++)
	{
		m_Map[x] = new char[m_Height];

		for (uint32_t y = 0; y < m_Height; y++)
		{
			m_Map[x][y] = (x % 2 && y % 2) ? '@' : 
				(((rand() % 10)/10.f) > chance) ? 
				(((rand() % 100/100.f) > 0.8f) ?  MakeEnemy(x, y) : '#') : '.';
		}
	}
	glm::ivec2 playerstart = glm::linearRand(glm::ivec2(0, 0), glm::ivec2(Width, Height));
	playerstart *= 2;
	m_Map[playerstart.x][playerstart.y] = '.';
	m_Player = std::make_shared<Player>(glm::vec3(playerstart.x + 0.5, 0, playerstart.y + 0.5), *this);
	if (static_cast<uint32_t>(playerstart.y) != m_Height - 1)
		m_Map[playerstart.x][playerstart.y + 1] = '.';
	if (playerstart.y != 0)
		m_Map[playerstart.x][playerstart.y - 1] = '.';
	if (static_cast<uint32_t>(playerstart.x) != m_Width - 1)
		m_Map[playerstart.x + 1][playerstart.y] = '.';
	if (playerstart.x != 0)
		m_Map[playerstart.x - 1][playerstart.y] = '.';
	m_Cube->SetMaterial(Swallow::FlatColourMaterial::Create());
	m_Player->SetVertexArray(m_Cube->GetVertexArray());
	Swallow::Ref<Swallow::FlatColourMaterialInstance> mat = Swallow::FlatColourMaterial::Create();
	mat->SetColour(glm::vec4(0.2f, 0.5f, 1.0f, 1.0f));
	m_Player->SetMaterial(mat);
	m_Player->GetTransform()->SetScale(glm::vec3(0.5f));
	Swallow::Ref<Swallow::FlatColourMaterialInstance> mat2 = Swallow::FlatColourMaterial::Create();
	mat2->SetColour(glm::vec4(0.9f, 0.1f, 0.2f, 1.0f));
	for (auto x : m_Enemies)
	{
		x->SetMaterial(Swallow::FlatColourMaterial::Create());
		x->SetVertexArray(m_Cube->GetVertexArray());
		x->SetMaterial(mat2);
		x->GetTransform()->SetScale(glm::vec3(0.4f));
	}
}

char Level::MakeEnemy(int x, int y)
{
	Enemy* newEnemy = new Enemy(glm::vec3(x + 0.5f, 0, y + 0.5f), *this, m_Seed);
	Swallow::Ref<Enemy> newRef = static_cast<Swallow::Ref<Enemy>>(newEnemy);
	m_Enemies.push_back(newRef);
	x+=y;
	return '.';
}

Level::~Level()
{
	for (uint32_t x = 0; x < m_Width; x++)
	{
		delete[] m_Map[x];
	}
	delete[] m_Map;
}

bool Level::IsEmpty(glm::vec3 check) const
{
	check.x = glm::floor(check.x);
	check.z = glm::floor(check.z);
	if (check.x < 0 || check.z < 0 || check.x > m_Width - 1 || check.z > m_Height - 1 || m_Map[static_cast<int>(check.x)][static_cast<int>(check.z)] != '.')
		return false;
	return true;
}

void Level::DropBomb(glm::vec3 pos)
{
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
		m_Map[static_cast<uint32_t>(pos.x)][static_cast<uint32_t>(pos.z)] = 'B';
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
		if (static_cast<uint32_t>(m_BombTimers.back().y) != m_Height - 1 && m_Map[m_BombTimers.back().x][m_BombTimers.back().y + 1] != '@')
			m_Map[m_BombTimers.back().x][m_BombTimers.back().y + 1] = '.';
		if (static_cast<uint32_t>(m_BombTimers.back().y) != 0 && m_Map[m_BombTimers.back().x][m_BombTimers.back().y - 1] != '@')
			m_Map[m_BombTimers.back().x][m_BombTimers.back().y - 1] = '.';
		if (static_cast<uint32_t>(m_BombTimers.back().x) != m_Width - 1 && m_Map[m_BombTimers.back().x + 1][m_BombTimers.back().y] != '@')
			m_Map[m_BombTimers.back().x + 1][m_BombTimers.back().y] = '.';
		if (static_cast<uint32_t>(m_BombTimers.back().x) != 0 && m_Map[m_BombTimers.back().x - 1][m_BombTimers.back().y] != '@')
			m_Map[m_BombTimers.back().x - 1][m_BombTimers.back().y] = '.';
		m_Map[m_BombTimers.back().x][m_BombTimers.back().y] = '.';
		m_BombTimers.pop_back();
	}
	m_Player->Update(ts);
	for (auto enemy : m_Enemies)
		enemy->Update(ts);
}

void Level::Draw()
{
	m_Cube->GetTransform()->SetScale(glm::vec3(0.9f));
	Swallow::Ref<Swallow::FlatColourMaterialInstance> mat = std::dynamic_pointer_cast<Swallow::FlatColourMaterialInstance>(m_Cube->GetMaterial());
	for (uint32_t x = 0; x < m_Width; x++)
	{
		for (uint32_t y = 0; y < m_Height; y++)
		{
			glm::vec3 position = glm::vec3(x, 0, y);
			switch(m_Map[x][y])
			{
				case '#':
					mat->SetColour(glm::vec4(0.9f, 0.5f, 0.2f, 1.0f));
				break;
				case '@':
					mat->SetColour(glm::vec4(0.5f, 0.5f, 0.5f, 1.0f));
				break;
				case 'B':
					mat->SetColour(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
					break;
				case '.':
					continue;
				break;
				default:
				break;
			}
			m_Cube->GetTransform()->SetPosition(position + glm::vec3(0.5f, 0.0f, 0.5f));
			m_Cube->GetTransform()->Recalculate();
			Swallow::Renderer::Submit(m_Cube);
		}
	}
	for (auto x : m_Enemies)
		Swallow::Renderer::Submit((Swallow::Ref<Enemy>(x)));
	Swallow::Renderer::Submit(m_Player);
}