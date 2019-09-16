#pragma once

#include "Player.hpp"
#include <Swallow/Core/Timestep.hpp>
#include <Swallow.hpp>

class Player;

class PowerUp
{
	public:
		virtual void	OnAdd(Player*) = 0;
		virtual void 	OnUpdate(Swallow::Timestep&) = 0;
		virtual void 	OnRemove(Player*) = 0;
		virtual bool	CanDelete() = 0;
		virtual ~PowerUp() = default;
};

class FireIncrease: public PowerUp
{
	public:
		FireIncrease();
		FireIncrease(const FireIncrease&) = default;
		FireIncrease &operator=(const FireIncrease&) = default;
		~FireIncrease() = default;

		void 	OnAdd(Player*) override;
		void 	OnUpdate(Swallow::Timestep&) override;
		void	OnRemove(Player*) override;
		bool	CanDelete() override;

	private:
		int		range = 1;
		float	m_TimeRemaining = 12000.0f;
		bool	m_Delete;
};

class FireDecrease: public PowerUp
{
	public:
		FireDecrease();
		FireDecrease(const FireDecrease&) = default;
		FireDecrease &operator=(const FireDecrease&) = default;
		~FireDecrease() = default;

		void 	OnAdd(Player*) override;
		void 	OnUpdate(Swallow::Timestep&) override;
		void	OnRemove(Player*) override;
		bool	CanDelete() override;

	private:
		int		range = 1;
};

class BombUp: public PowerUp
{
		public:
		BombUp();
		BombUp(const BombUp&) = default;
		BombUp &operator=(const BombUp&) = default;
		~BombUp() = default;

		void 	OnAdd(Player*) override;
		void 	OnUpdate(Swallow::Timestep&) override;
		void	OnRemove(Player*) override;
		bool	CanDelete() override;

	private:
		int		increase = 1;
};


class BombDown: public PowerUp
{
		public:
		BombDown();
		BombDown(const BombDown&) = default;
		BombDown &operator=(const BombDown&) = default;
		~BombDown() = default;

		void 	OnAdd(Player*) override;
		void 	OnUpdate(Swallow::Timestep&) override;
		void	OnRemove(Player*) override;
		bool	CanDelete() override;

	private:
		int		decrease = 1;
};