#pragma once
#include <Swallow.hpp>
#include "Player.hpp"
#include "Tile.hpp"
#include "Enemy.hpp"
#include "Flame.hpp"

class Level
{
	struct Timer
	{
		float fuse;
		int x, y;
		int power;
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
		inline const std::vector<Swallow::Ref<Tile>> &GetMap() const { return m_Map; }

		inline bool	GetDeadStatus() { return m_DEAD; }

		bool IsEmpty(glm::vec3 check) const;
		int Burn(int x, int y);
		int InBlock(Swallow::Ref<Swallow::GameObject> o, int x, int y);

		void DropBomb(glm::vec3 pos);
		void Explode(Timer &t);

		void MakeEnemy(int x, int y);

		void Update(Swallow::Timestep ts);
		void Draw();

	private:
		bool	m_DEAD;
		uint32_t m_Width, m_Height, m_Seed;
		Swallow::Ref<Player> m_Player;
		std::vector<Swallow::Ref<Enemy>> m_Enemies;
		std::list<Swallow::Ref<Flame>> m_Flames;

		std::vector<Timer> m_BombTimers;
		Timer *m_TempTimer = nullptr;

		std::vector<Swallow::Ref<Tile>> m_Map;
};