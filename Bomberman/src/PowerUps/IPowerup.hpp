#pragma once

#include <Swallow/Core/Timestep.hpp>

class IPowerup
{
	public:
		virtual void	OnUpdate(Swallow::Timestep&)	= 0;
		virtual void	OnRemove()						= 0;
		virtual void	OnAdd() 						= 0;
};