#pragma once

#include <Swallow.hpp>
#include "ModelInfo.hpp"

class Level;

class Player: public Swallow::GameObject, public ModelInfo
{
public:
	Player(const glm::vec3 &Pos, Level &l);
	Player(const Player &rhs) = default;
	Player &operator=(const Player &rhs) = default;
	~Player();

	inline glm::vec3 &Destination() { return m_Destination; }

	void Update(Swallow::Timestep ts);

private:

	//Swallow::Ref<Swallow::GameObject> m_Cube;
	Level &m_Level;
	glm::vec3 m_Destination;
};