#pragma once

#include "PowerUp.hpp"

#include <Swallow.hpp>

class Level;
class PowerUp;

class Player: public Swallow::GameObject
{
public:
	Player(const glm::vec3 &Pos, Level &l);
	Player(const Player &rhs) = default;
	Player &operator=(const Player &rhs) = default;
	~Player();

	inline glm::vec3 &Destination() { return m_Destination; }

	void		AddPower(Swallow::Ref<PowerUp> power);

	inline void	SetIncreaseFireDistance(int i) { this->m_FireDistance += i; }
	inline void	SetDecreaseFireDistance(int d) { this->m_FireDistance -= d; std::cout << m_FireDistance << std::endl;};
	inline	int GetFireDistance() { return m_FireDistance; }

	inline void	SetIncreaseBombCount(int i) { this->m_BombCount += i; }
	inline void	SetDecreaseBombCount(int d) { this->m_BombCount -= d; }
	inline	int GetBombCount() {return m_BombCount; }

	void Update(Swallow::Timestep ts);

private:
	Level &m_Level;
	int		m_FireDistance, m_BombCount; 
	Swallow::Ref<Swallow::GameObject> m_Cube;
	glm::vec3 m_Destination;
	std::list<Swallow::Ref<PowerUp>>	m_PowerUps;
};