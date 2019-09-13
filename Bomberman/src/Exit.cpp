#include "swpch.hpp"
#include "Exit.hpp"

#include <Swallow.hpp>

Exit::Exit(glm::vec3 pos): m_Pos(pos)
{
	pos.x = static_cast<int>(pos.x);
	pos.z = static_cast<int>(pos.z);
	SW_CORE_INFO("{}:{}:{}", pos.x, pos.y, pos.z);
}

Exit::~Exit(){}