#pragma once

#include "IPowerup.hpp"

class Speed: public IPowerup
{
	public:
		Speed();
		Speed(const Speed&) = default;
		Speed &operator=(const Speed&) = default;
		~Speed();

		virtual void OnUpate();
		virtual void OnAdd();
		virtual void OnRemove();
};