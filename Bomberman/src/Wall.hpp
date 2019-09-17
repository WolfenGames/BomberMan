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

class LevelExit: public Tile
{
	public:
		LevelExit();
		LevelExit(const LevelExit&) = default;
		LevelExit &operator=(const LevelExit&) = default;
		virtual ~LevelExit() = default;
};