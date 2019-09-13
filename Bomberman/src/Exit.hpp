#pragma once

#include "Tile.hpp"
#include "Player.hpp"

class Exit: public Tile
{
	public:
		Exit(glm::vec3 pos);
		Exit(const Exit&) = default;
		Exit &operator=(const Exit&) = default;
		~Exit();

		bool OnEnter(const Player&);

	private:
		glm::vec3	m_Pos;
};