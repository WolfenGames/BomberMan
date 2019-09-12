#pragma once
#include <Swallow.hpp>
#include "ModelInfo.hpp"

class Wall : public Swallow::GameObject, public ModelInfo
{
public:
	Wall() = default;
	Wall(const Wall &s) = default;
	Wall &operator=(const Wall &s) = default;
	virtual ~Wall() = default;
};