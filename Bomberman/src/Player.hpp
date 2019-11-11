#pragma once

#include "PowerUp.hpp"
#include "Swallow/Renderer/material/AnimationMaterial.hpp"

#include <Swallow.hpp>

class Level;
class PowerUp;

class Player: public Swallow::GameObject
{
public:
	Player();
	Player(const Player &rhs) = default;
	Player &operator=(const Player &rhs) = default;
	~Player();

	inline glm::vec3 &Destination() { return m_Destination; }

	bool		AddPower(Swallow::Ref<PowerUp> power);

	inline void	SetFireDistance(int i) { this->m_FireDistance = i; }
	inline	int GetFireDistance() { return m_FireDistance; }

	inline void	SetBombCount(int i) { this->m_BombCount = i; }
	inline	int GetBombCount() {return m_BombCount; }

	inline float GetSpeed() { return m_Speed; }
	inline void SetSpeed(float s) { m_Speed = s; }

	inline void SetBombsCanBypassWalls(bool b) { this->m_BombsCanBypassWalls = b; }
	inline bool GetBombsCanBypassWalls() { return this->m_BombsCanBypassWalls; }

	inline void SetGhost(bool g) { m_Ghost = g; }
	inline bool Ghost() { return this->m_Ghost; }

	inline void SetKey(bool g) { m_HasKey = g; }
	inline bool HasKey() { return this->m_HasKey; }
	
	inline bool WON() { return this->m_Won; }
	inline void SetLevel(const Swallow::Ref<Level> &l) { m_Level = l; }

	void Update(Swallow::Timestep ts);

private:
	Swallow::Ref<Level> m_Level;
	int		m_FireDistance = 2, m_BombCount = 1; 
	bool	m_BombsCanBypassWalls = false;
	bool	m_Ghost = false;
	bool	m_HasKey = false;
	bool	m_Won = false;
	float	m_Speed = 2.0f;
	Swallow::Ref<Swallow::GameObject> m_Cube;

	//Swallow::Ref<Swallow::GameObject> m_Cube;
	//Level &m_Level;
	glm::vec3 m_Destination;
	std::list<Swallow::Ref<PowerUp>>	m_PowerUps;
	Swallow::Ref<Swallow::AnimationMaterialInstance> 	animMaterial;
	Swallow::Ref<Swallow::AnimationController> 			m_WalkAnimation;
};