#pragma once
#include <Swallow.hpp>
#include "Player.hpp"
#include "Tile.hpp"
#include "Enemy.hpp"
#include "Flame.hpp"
#include "PowerUp.hpp"

class Level
{
	struct Timer
	{
		float fuse;
		int x, y;
		int power;
	};

	public:
		Level() = default;
		Level(const Level &rhs) = default;
		Level &operator=(const Level &rhs) = default;
		~Level();

		inline Swallow::Ref<Player> GetPlayer() { return m_Player; }
		inline uint32_t GetWidth() const { return m_Width; }
		inline uint32_t GetHeight() const { return m_Height; }
		inline const std::vector<Swallow::Ref<Tile>> &GetMap() const { return m_Map; }

		inline bool	GetDeadStatus() { return m_DEAD; }

		void Generate(float chance = 0.6);
		bool IsEmpty(glm::vec3 check, bool ghost) const;
		inline bool NoEnemies() { return m_Enemies.size() == 0; }
		void Burn(int x, int y);
		int InBlock(Swallow::Ref<Swallow::GameObject> o, int x, int y);
		void Load(const std::string &name);
		void Save(const std::string &name);

		void DropBomb(glm::vec3 pos);
		void Explode(Timer &t);

		void MakeEnemy(int x, int y);
		void MakePowerUp(int x, int y, bool predetermined = false, int type = -1);
		inline void SetPlayer(const Swallow::Ref<Player> &p) { m_Player = p; }

		void Update(Swallow::Timestep ts);
		void Draw();

	private:
		bool	m_DEAD = false;
		uint32_t m_Width = 29, m_Height = 11;
		Swallow::Ref<Player> m_Player;
		Swallow::Ref<Swallow::GameObject> m_Floor;
		std::list<Swallow::Ref<Enemy>> m_Enemies;
		std::list<Swallow::Ref<PowerUp>> m_PowerUps;
		std::list<Swallow::Ref<Flame>> m_Flames;

		std::vector<Timer> m_BombTimers;
		Timer *m_TempTimer = nullptr;

		std::vector<Swallow::Ref<Tile>> m_Map;

		PowerUpFactory		powerUpFactory;
};