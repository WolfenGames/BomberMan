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
	static_cast<void>(time);
	this->m_TimeRemaining -= time.GetMiliseconds();
	if (m_TimeRemaining <= 0)
		m_Delete = true;
}

void	FireIncrease::OnRemove(Player* player)
{
	player->SetDecreaseFireDistance(this->range);
	std::cout << "Reset PowerUp" << std::endl;
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
	static_cast<void>(time);
}

void	FireDecrease::OnRemove(Player* player)
{
	player->SetIncreaseFireDistance(this->range);
}

bool FireDecrease::CanDelete()
{
	return false;
}

BombUp::BombUp(){}

void	BombUp::OnAdd(Player* player)
{
	player->SetIncreaseBombCount(this->increase);
}

void	BombUp::OnUpdate(Swallow::Timestep& time)
{
	static_cast<void>(time);
}

void	BombUp::OnRemove(Player* player)
{
	player->SetDecreaseBombCount(this->increase);
}

bool	BombUp::CanDelete()
{
	return false;
}

BombDown::BombDown(){}

void	BombDown::OnAdd(Player* player)
{
	player->SetDecreaseBombCount(this->decrease);
}

void BombDown::OnUpdate(Swallow::Timestep& time)
{
	static_cast<void>(time);
}

void BombDown::OnRemove(Player* player)
{
	player->SetIncreaseBombCount(this->decrease);
}

bool	BombDown::CanDelete()
{
	return false;
}