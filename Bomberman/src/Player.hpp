#pragma once

#include <Swallow.hpp>

class Level;

class Player
{
public:
	Player(const glm::vec3 &Pos, Level &l);
	Player(const Player &rhs) = default;
	Player &operator=(const Player &rhs) = default;
	~Player();

	inline glm::vec3 &Position() { return m_Position; }
	inline glm::vec3 &Destination() { return m_Destination; }

	void Update(Swallow::Timestep ts);
	void Draw();

	void SetModels(Swallow::Ref<Swallow::VertexArray> &VA, Swallow::Ref<Swallow::Shader> &Shader);

private:
	glm::vec3 m_Position;

	Swallow::Ref<Swallow::Shader> m_Shader;
	Swallow::Ref<Swallow::VertexArray> m_Cube;
	Level &m_Level;
	glm::vec3 m_Destination;
};