#include "swpch.hpp"
#include "PowerUp.hpp"
#include "Player.hpp"

FireIncrease::FireIncrease(){
	m_Delete = false;
}

void	FireIncrease::OnAdd(Player* player)
{
	player->SetIncreaseFireDistance(this->range);
}

void	FireIncrease::OnUpdate(Swallow::Timestep& time)
{
	this->m_TimeRemaining -= time.GetMiliseconds();
	if (m_TimeRemaining <= 0)
		m_Delete = true;
}

void	FireIncrease::OnRemove(Player* player)
{
	player->SetDecreaseFireDistance(this->range);
}

bool	FireIncrease::CanDelete()
{
	return m_Delete;
}

FireDecrease::FireDecrease(){};

void	FireDecrease::OnAdd(Player* player)
{
	player->SetDecreaseFireDistance(this->range);
}

void	FireDecrease::OnUpdate(Swallow::Timestep& time)
{
	this->m_TimeRemaining -= time.GetMiliseconds();
	if (m_TimeRemaining <= 0)
		m_Delete = true;
}

void	FireDecrease::OnRemove(Player* player)
{
	player->SetIncreaseFireDistance(this->range);
}

bool FireDecrease::CanDelete()
{
	return m_Delete;
}

BombUp::BombUp(){}

void	BombUp::OnAdd(Player* player)
{
	player->SetIncreaseBombCount(this->increase);
}

void	BombUp::OnUpdate(Swallow::Timestep& time)
{
	this->m_TimeRemaining -= time.GetMiliseconds();
	if (m_TimeRemaining <= 0)
		m_Delete = true;
}

void	BombUp::OnRemove(Player* player)
{
	player->SetDecreaseBombCount(this->increase);
}

bool	BombUp::CanDelete()
{
	return m_Delete;
}

BombDown::BombDown(){}

void	BombDown::OnAdd(Player* player)
{
	player->SetDecreaseBombCount(this->decrease);
}

void BombDown::OnUpdate(Swallow::Timestep& time)
{
	this->m_TimeRemaining -= time.GetMiliseconds();
	if (m_TimeRemaining <= 0)
		m_Delete = true;
}

void BombDown::OnRemove(Player* player)
{
	player->SetIncreaseBombCount(this->decrease);
}

bool	BombDown::CanDelete()
{
	return m_Delete;
}

BombsCanBypassWalls::BombsCanBypassWalls(){}

void	BombsCanBypassWalls::OnAdd(Player* player)
{
	player->SetBombsCanBypassWalls(true);
}

void BombsCanBypassWalls::OnUpdate(Swallow::Timestep& time)
{
	this->m_TimeRemaining -= time.GetMiliseconds();
	if (m_TimeRemaining <= 0)
		m_Delete = true;
}

void BombsCanBypassWalls::OnRemove(Player* player)
{
	player->SetBombsCanBypassWalls(false);
}

bool	BombsCanBypassWalls::CanDelete()
{
	return m_Delete;
}

SoftBlockPass::SoftBlockPass(){}

void	SoftBlockPass::OnAdd(Player* player)
{
	player->SetGhost(true);
}

void SoftBlockPass::OnUpdate(Swallow::Timestep& time)
{
	this->m_TimeRemaining -= time.GetMiliseconds();
	if (m_TimeRemaining <= 0)
		m_Delete = true;
}

void SoftBlockPass::OnRemove(Player* player)
{
	player->SetGhost(false);
}

bool	SoftBlockPass::CanDelete()
{
	return m_Delete;
}