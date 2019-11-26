#pragma once
#include <Swallow.hpp>
#include "Tile.hpp"

class Wall : public Tile
{
public:
	Wall();
	Wall(const Wall &s) = default;
	Wall &operator=(const Wall &s) = default;
	virtual ~Wall() = default;
};

class Pillar : public Tile
{
	public:
	Pillar();
	Pillar(const Pillar &s) = default;
	Pillar &operator=(const Pillar &s) = default;
	virtual ~Pillar() = default;

	private:
};

class Floor : public Tile
{
	public:
	Floor();
	Floor(const Floor &s) = default;
	Floor &operator=(const Floor &s) = default;
	virtual ~Floor() = default;

	private:
};