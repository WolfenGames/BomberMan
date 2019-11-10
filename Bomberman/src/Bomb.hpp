#pragma once
#include <Swallow.hpp>
#include "Tile.hpp"

class Bomb: public Tile
{
	public:
	Bomb();
	Bomb(const Bomb &s) = default;
	Bomb &operator=(const Bomb &s) = default;
	virtual ~Bomb() = default;

	private:
};