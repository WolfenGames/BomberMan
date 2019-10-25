#pragma once

#include <Swallow.hpp>

class BackDrop: public Swallow::GameObject
{

	public:
		BackDrop(const glm::vec3 pos);
		BackDrop(const BackDrop&) = default;
		BackDrop &operator=(const BackDrop&) = default;
		~BackDrop();

		private:
			Swallow::Ref<Swallow::GameObject> m_BackDrop;
			glm::vec3 m_pos;
			

};