#pragma once
#include <Swallow.hpp>
#include "Player.hpp"
#include "Enemy.hpp"

class Level
{
	struct Timer
	{
		float fuse;
		int x, y;
	};

	public:
		Level(uint32_t Width, uint32_t Height);
		Level(uint32_t Width, uint32_t Height, float chance);
		Level(uint32_t Width, uint32_t Height, uint32_t Seed, float chance);
		Level(const Level &rhs) = default;
		Level &operator=(const Level &rhs) = default;
		~Level();

		inline Swallow::Ref<Player> GetPlayer() { return m_Player; }
		inline uint32_t GetWidth() const { return m_Width; }
		inline uint32_t GetHeight() const { return m_Height; }
		inline char** GetMap() const { return m_Map; }

		bool IsEmpty(glm::vec3 check) const;

		void DropBomb(glm::vec3 pos);

		char MakeEnemy(int x, int y);

		void Update(Swallow::Timestep ts);
		void Draw();

	private:
		uint32_t m_Width, m_Height, m_Seed;
		uint32_t m_CurrentEnemies;
		Swallow::Ref<Player> m_Player;
		std::vector<Swallow::Ref<Enemy>> m_Enemies;
		Swallow::Ref<Swallow::GameObject> m_Cube;

		std::vector<Timer> m_BombTimers;
		Timer *m_TempTimer = nullptr;

		char **m_Map;
};