#pragma once

#include <Swallow.hpp>

class Player
{
public:
	Player(const glm::vec3 &Pos = glm::vec3(0, 0, 0));
	Player(const Player &rhs) = default;
	Player &operator=(const Player &rhs) = default;
	~Player();

	inline glm::vec3 &Position() { return m_Positition; }

	void Update(Swallow::Timestep ts);
	void Draw();

	void SetModels(Swallow::Ref<Swallow::VertexArray> &VA, Swallow::Ref<Swallow::Shader> &Shader);

private:
	glm::vec3 m_Positition;

	Swallow::Ref<Swallow::Shader> m_Shader;
	Swallow::Ref<Swallow::VertexArray> m_Cube;
};