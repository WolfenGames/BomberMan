#pragma once

#include <Swallow.hpp>

class Level;

class Enemy : public Swallow::GameObject
{
public:
	Enemy(const glm::vec3&, Level&, uint64_t);
	Enemy(const Enemy&) = default;
	Enemy& operator=(const Enemy&) = default;
	
	void makeDecision();
	glm::vec3& Destination();
	void Update(Swallow::Timestep ts);

	~Enemy();

private:
	glm::vec3							m_Pos;
	Level								&m_Level;
	uint8_t								m_MaxMoves;
	Swallow::Ref<Swallow::GameObject>	m_Cube;
	glm::vec2							m_MoveDir;
	uint64_t							m_Seed;

protected:
	Enemy() = default;

};