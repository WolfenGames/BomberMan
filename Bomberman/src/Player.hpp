#pragma once

#include <Swallow.hpp>

class Level;

class Player: public Swallow::GameObject
{
public:
	Player(const glm::vec3 &Pos, Level &l);
	Player(const Player &rhs) = delete;
	Player &operator=(const Player &rhs) = delete;
	~Player();

	inline glm::vec3 &Destination() { return m_Destination; }

	void Update(Swallow::Timestep ts);

private:

	Swallow::Ref<Swallow::GameObject> m_Cube;
	Level &m_Level;
	glm::vec3 m_Destination;
};