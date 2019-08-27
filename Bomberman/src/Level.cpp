#include "Level.hpp"
#include "gtc/random.hpp"
#include "gtx/transform.hpp"
#include <chrono>

Level::Level(uint32_t Width, uint32_t Height)
	:Level(Width, Height, static_cast<uint32_t>(std::chrono::system_clock::now().time_since_epoch().count()))
{
}

Level::Level(uint32_t Width, uint32_t Height, uint32_t Seed)
	:m_Width(Width * 2 + 1), m_Height(Height * 2 + 1), m_Seed(Seed)
{
	srand(m_Seed);
	m_Map = new char*[m_Width];
	for (uint32_t x = 0; x < m_Width; x++)
	{
		m_Map[x] = new char[m_Height];

		for (uint32_t y = 0; y < m_Height; y++)
		{
			m_Map[x][y] = (x % 2 && y % 2) ? '@' : '#';
		}
	}
	glm::ivec2 playerstart = glm::linearRand(glm::ivec2(0, 0), glm::ivec2(Width, Height));
	playerstart *= 2;
	m_Map[playerstart.x][playerstart.y] = '.';
	m_Player = std::make_shared<Player>(glm::vec3(playerstart.x + 0.5, 0, playerstart.y + 0.5), *this);
	if (playerstart.y != m_Height - 1)
		m_Map[playerstart.x][playerstart.y + 1] = '.';
	if (playerstart.y != 0)
		m_Map[playerstart.x][playerstart.y - 1] = '.';
	if (playerstart.x != m_Width - 1)
		m_Map[playerstart.x + 1][playerstart.y] = '.';
	if (playerstart.x != 0)
		m_Map[playerstart.x - 1][playerstart.y] = '.';
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
	timer.fuse = 3.0f;
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

void Level::SetModels(Swallow::Ref<Swallow::VertexArray> &VA, Swallow::Ref<Swallow::Shader> &Shader)
{
	m_Cube = VA;
	m_Shader = Shader;
	m_Player->SetModels(VA, Shader);
}

void Level::Update(Swallow::Timestep ts)
{
	if (m_TempTimer)
	{
		m_BombTimers.push_back(*m_TempTimer);
		delete m_TempTimer;
		m_TempTimer = nullptr;
	}
	int i = 0;
	for (auto &timer : m_BombTimers)
	{
		SW_INFO("{}: {}", i++, timer.fuse);
		timer.fuse -= ts.GetSeconds();
	}
	std::sort(m_BombTimers.begin(), m_BombTimers.end(), [](Level::Timer a, Level::Timer b) -> int { return a.fuse > b.fuse; });
	while (m_BombTimers.size() && m_BombTimers.back().fuse < 0.0)
	{
		if (m_BombTimers.back().y != m_Height - 1 && m_Map[m_BombTimers.back().x][m_BombTimers.back().y + 1] != '@')
			m_Map[m_BombTimers.back().x][m_BombTimers.back().y + 1] = '.';
		if (m_BombTimers.back().y != 0 && m_Map[m_BombTimers.back().x][m_BombTimers.back().y - 1] != '@')
			m_Map[m_BombTimers.back().x][m_BombTimers.back().y - 1] = '.';
		if (m_BombTimers.back().x != m_Width - 1 && m_Map[m_BombTimers.back().x + 1][m_BombTimers.back().y] != '@')
			m_Map[m_BombTimers.back().x + 1][m_BombTimers.back().y] = '.';
		if (m_BombTimers.back().x != 0 && m_Map[m_BombTimers.back().x - 1][m_BombTimers.back().y] != '@')
			m_Map[m_BombTimers.back().x - 1][m_BombTimers.back().y] = '.';
		m_Map[m_BombTimers.back().x][m_BombTimers.back().y] = '.';
		m_BombTimers.pop_back();
	}
	m_Player->Update(ts);
}

void Level::Draw()
{
	static float angle = 0.0f;
	angle += 0.001f;
	glm::mat4 scale = glm::scale(glm::vec3(0.9f));
	for (uint32_t x = 0; x < m_Width; x++)
	{
		for (uint32_t y = 0; y < m_Height; y++)
		{
			glm::vec3 position = glm::vec3(x, 0, y);
			std::dynamic_pointer_cast<Swallow::OpenGLShader>(m_Shader)->Bind();
			switch(m_Map[x][y])
			{
				case '#':
					std::dynamic_pointer_cast<Swallow::OpenGLShader>(m_Shader)->UploadUniformFloat3("u_Color", glm::vec3(0.9f, 0.5f, 0.2f));
				break;
				case '@':
					std::dynamic_pointer_cast<Swallow::OpenGLShader>(m_Shader)->UploadUniformFloat3("u_Color", glm::vec3(0.5f, 0.5f, 0.5f));
				break;
				case 'B':
					std::dynamic_pointer_cast<Swallow::OpenGLShader>(m_Shader)->UploadUniformFloat3("u_Color", glm::vec3(0.0f, 0.0f, 0.0f));
					break;
				case '.':
					continue;
				break;
				default:
				break;
			}
			Swallow::Renderer::Submit(std::dynamic_pointer_cast<Swallow::OpenGLShader>(m_Shader), m_Cube,
				glm::translate(position + glm::vec3(0.5f, 0.0f, 0.5f)) * scale);
		}
	}

	m_Player->Draw();
}