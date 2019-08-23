#include "Level.hpp"
#include "gtc/random.hpp"
#include "gtx/transform.hpp"
#include <chrono>

Level::Level(uint32_t Width, uint32_t Height)
	:Level(Width, Height, std::chrono::system_clock::now().time_since_epoch().count())
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
	m_Map[playerstart.x][playerstart.y] = 'P';
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

void Level::SetModels(Swallow::Ref<Swallow::VertexArray> &VA, Swallow::Ref<Swallow::Shader> &Shader)
{
	m_Cube = VA;
	m_Shader = Shader;
}

void Level::Draw()
{
	static glm::vec3 origin(0, 0, 5);
	for (uint32_t x = 0; x < m_Width; x++)
	{
		for (uint32_t y = 0; y < m_Height; y++)
		{
			glm::vec3 position = glm::vec3(x * 3, 0, y * 3);
			std::dynamic_pointer_cast<Swallow::OpenGLShader>(m_Shader)->Bind();
			switch(m_Map[x][y])
			{
				case '#':
					std::dynamic_pointer_cast<Swallow::OpenGLShader>(m_Shader)->UploadUniformFloat3("u_Color", glm::vec3(0.9, 0.5, 0.2));
				break;
				case '@':
					std::dynamic_pointer_cast<Swallow::OpenGLShader>(m_Shader)->UploadUniformFloat3("u_Color", glm::vec3(0.5, 0.5, 0.5));
				break;
				case 'P':
					std::dynamic_pointer_cast<Swallow::OpenGLShader>(m_Shader)->UploadUniformFloat3("u_Color", glm::vec3(0.2, 0.5, 0.9));
				break;
				case '.':
					continue;
				break;
				default:
				break;
			}
			glm::mat4 look = glm::lookAt(position, origin, glm::vec3(0, 1, 0));
			Swallow::Renderer::Submit(std::dynamic_pointer_cast<Swallow::OpenGLShader>(m_Shader), m_Cube,
			look);//glm::translate(position));
		}
	}
}