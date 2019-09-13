#include "swpch.hpp"

#include "PowerUp.hpp"

Speed::Speed()
{

}

Speed::~Speed()
{
	OnRemove();
}

void	Speed::OnAdd()
{

}

void	Speed::OnRemove()
{

}

void	Speed::OnUpdate(Swallow::Timestep& t)
{
	static_cast<void>(t);
}

