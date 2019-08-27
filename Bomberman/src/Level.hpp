#pragma once
#include <Swallow.hpp>
#include "Player.hpp"

class Level
{
	public:
		Level(uint32_t Width, uint32_t Height);
		Level(uint32_t Width, uint32_t Height, uint32_t Seed);
		Level(const Level &rhs) = default;
		Level &operator=(const Level &rhs) = default;
		~Level();

		inline Swallow::Ref<Player> GetPlayer() { return m_Player; }
		inline uint32_t GetWidth() const { return m_Width; }
		inline uint32_t GetHeight() const { return m_Height; }
		inline char** GetMap() const { return m_Map; }

		bool IsEmpty(glm::vec3 check) const;

		void SetModels(Swallow::Ref<Swallow::VertexArray> &VA, Swallow::Ref<Swallow::Shader> &Shader);

		void Update(Swallow::Timestep ts);
		void Draw();

	private:
		uint32_t m_Width, m_Height, m_Seed;

		Swallow::Ref<Swallow::VertexArray> m_Cube;
		Swallow::Ref<Swallow::Shader> m_Shader;
		
		Swallow::Ref<Player> m_Player;

		char **m_Map;
};