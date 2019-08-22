#pragma once
#include <Swallow.hpp>

class Level
{
	public:
		Level(uint32_t Width, uint32_t Height);
		Level(uint32_t Width, uint32_t Height, uint32_t Seed);
		Level(const Level &rhs) = default;
		Level &operator=(const Level &rhs) = default;
		~Level();

		void SetModels(Swallow::Ref<Swallow::VertexArray> &VA, Swallow::Ref<Swallow::Shader> &Shader);

		void Draw();

	private:
		uint32_t m_Width, m_Height, m_Seed;

		Swallow::Ref<Swallow::VertexArray> m_Cube;
		Swallow::Ref<Swallow::Shader> m_Shader;
		char **m_Map;
};