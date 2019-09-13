#pragma once

#include "IPowerup.hpp"

class Speed: public IPowerup
{
	public:
		Speed();
		Speed(const Speed&) = default;
		Speed &operator=(const Speed&) = default;
		~Speed();

		virtual void OnUpdate(Swallow::Timestep&) override;
		virtual void OnAdd() override;
		virtual void OnRemove() override;
};