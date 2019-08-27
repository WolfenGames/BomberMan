#pragma once

#include <Swallow.hpp>

class Level;

class Player
{
public:
	Player(const glm::vec3 &Pos, const Level &l);
	Player(const Player &rhs) = default;
	Player &operator=(const Player &rhs) = default;
	~Player();

	inline glm::vec3 &Position() { return m_Position; }

	void Update(Swallow::Timestep ts);
	void Draw();

	void SetModels(Swallow::Ref<Swallow::VertexArray> &VA, Swallow::Ref<Swallow::Shader> &Shader);

private:
	glm::vec3 m_Position;

	Swallow::Ref<Swallow::Shader> m_Shader;
	Swallow::Ref<Swallow::VertexArray> m_Cube;
	const Level &m_Level;
	glm::vec3 m_Destination;
};