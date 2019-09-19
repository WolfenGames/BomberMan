#pragma once

#include "Player.hpp"
#include <Swallow/Core/Timestep.hpp>
#include <Swallow.hpp>
#define POWERUP_DURATION 9.0f

class Player;

enum PowerUpTypes
{
	None = 0,
	eFireIncrease,
	eFireDecrease,
	eBombUp,
	eBombDown,
	eSpeedUp,
	eSpeedDown,
	eBombsCanBypassWalls,
	eSoftBlockPass,
	//Leave this last
	TotalPowerUps,
	eKey,
	eExit
};

class PowerUp: public Swallow::GameObject
{
	public:
		virtual void 	OnUpdate(Swallow::Timestep&) = 0;
		virtual bool	CanDelete() = 0;
		virtual void	SetDelete(bool val) = 0;
		virtual ~PowerUp() = default;
		virtual	PowerUpTypes	getPowerUpType() = 0;
};

class FireIncrease: public PowerUp
{
	public:
		FireIncrease();
		FireIncrease(const FireIncrease&) = default;
		FireIncrease &operator=(const FireIncrease&) = default;
		~FireIncrease() = default;

		void 	OnUpdate(Swallow::Timestep&) override;
		virtual inline void	SetDelete(bool val) override { m_Delete = val;}
		bool	CanDelete() override;
		virtual inline	PowerUpTypes	getPowerUpType() override { return PowerUpTypes::eFireIncrease; }

	private:
		float	m_TimeRemaining = POWERUP_DURATION;
		bool	m_Delete = false;
};

class FireDecrease: public PowerUp
{
	public:
		FireDecrease();
		FireDecrease(const FireDecrease&) = default;
		FireDecrease &operator=(const FireDecrease&) = default;
		~FireDecrease() = default;

		void 	OnUpdate(Swallow::Timestep&) override;
		bool	CanDelete() override;
		virtual inline void	SetDelete(bool val) override { m_Delete = val;}
		virtual inline	PowerUpTypes	getPowerUpType() override { return PowerUpTypes::eFireDecrease; }

	private:
		float	m_TimeRemaining = POWERUP_DURATION;
		bool	m_Delete = false;
};

class BombUp: public PowerUp
{
		public:
		BombUp();
		BombUp(const BombUp&) = default;
		BombUp &operator=(const BombUp&) = default;
		~BombUp() = default;

		void 	OnUpdate(Swallow::Timestep&) override;
		bool	CanDelete() override;
		virtual inline void	SetDelete(bool val) override { m_Delete = val;}
		virtual inline	PowerUpTypes	getPowerUpType() override { return PowerUpTypes::eBombUp; }

	private:
		float	m_TimeRemaining = POWERUP_DURATION;
		bool	m_Delete = false;
};


class BombDown: public PowerUp
{
		public:
		BombDown();
		BombDown(const BombDown&) = default;
		BombDown &operator=(const BombDown&) = default;
		~BombDown() = default;

		void 	OnUpdate(Swallow::Timestep&) override;
		bool	CanDelete() override;
		virtual inline void	SetDelete(bool val) override { m_Delete = val;}
		virtual inline	PowerUpTypes	getPowerUpType() override { return PowerUpTypes::eBombDown; }

	private:
		float	m_TimeRemaining = POWERUP_DURATION;
		bool	m_Delete = false;
};

class SpeedUp: public PowerUp
{
		public:
		SpeedUp();
		SpeedUp(const SpeedUp&) = default;
		SpeedUp &operator=(const SpeedUp&) = default;
		~SpeedUp() = default;

		void 	OnUpdate(Swallow::Timestep&) override;
		bool	CanDelete() override;
		virtual inline void	SetDelete(bool val) override { m_Delete = val;}
		virtual inline	PowerUpTypes	getPowerUpType() override { return PowerUpTypes::eSpeedUp; }

	private:
		float	m_TimeRemaining = POWERUP_DURATION;
		bool	m_Delete = false;
};


class SpeedDown: public PowerUp
{
		public:
		SpeedDown();
		SpeedDown(const SpeedDown&) = default;
		SpeedDown &operator=(const SpeedDown&) = default;
		~SpeedDown() = default;

		void 	OnUpdate(Swallow::Timestep&) override;
		bool	CanDelete() override;
		virtual inline void	SetDelete(bool val) override { m_Delete = val;}
		virtual inline	PowerUpTypes	getPowerUpType() override { return PowerUpTypes::eSpeedDown; }

	private:
		float	m_TimeRemaining = POWERUP_DURATION;
		bool	m_Delete = false;
};

class BombsCanBypassWalls: public PowerUp
{
	public:
		BombsCanBypassWalls();
		BombsCanBypassWalls(const BombsCanBypassWalls&) = default;
		BombsCanBypassWalls &operator=(const BombsCanBypassWalls&) = default;
		~BombsCanBypassWalls() = default;

		void 	OnUpdate(Swallow::Timestep&) override;
		bool	CanDelete() override;
		virtual inline void	SetDelete(bool val) override { m_Delete = val;}
		virtual inline	PowerUpTypes	getPowerUpType() override { return PowerUpTypes::eBombsCanBypassWalls; }

	private:
		float	m_TimeRemaining = POWERUP_DURATION;
		bool	m_Delete = false;
};

class SoftBlockPass: public PowerUp
{
	public:
		SoftBlockPass();
		SoftBlockPass(const SoftBlockPass&) = default;
		SoftBlockPass &operator=(const SoftBlockPass&) = default;
		~SoftBlockPass() = default;

		void 	OnUpdate(Swallow::Timestep&) override;
		bool	CanDelete() override;
		virtual inline void	SetDelete(bool val) override { m_Delete = val;}
		virtual inline	PowerUpTypes	getPowerUpType() override { return PowerUpTypes::eSoftBlockPass ; }

	private:
		float	m_TimeRemaining = POWERUP_DURATION;
		bool	m_Delete = false;
};

class Key: public PowerUp
{
	public:
		Key();
		Key(const Key&) = default;
		Key &operator=(const Key&) = default;
		~Key() = default;

		void 	OnUpdate(Swallow::Timestep&) override;
		bool	CanDelete() override;
		virtual inline void	SetDelete(bool val) override { m_Delete = val;}
		virtual inline	PowerUpTypes	getPowerUpType() override { return PowerUpTypes::eKey; }

	private:
		bool	m_Delete = false;
};

class Exit: public PowerUp
{
	public:
		Exit();
		Exit(const Exit&) = default;
		Exit &operator=(const Exit&) = default;
		~Exit() = default;

		void 	OnUpdate(Swallow::Timestep&) override;
		bool	CanDelete() override;
		virtual inline void	SetDelete(bool val) override { m_Delete = val;}
		virtual inline	PowerUpTypes	getPowerUpType() override { return PowerUpTypes::eExit; }

	private:
		bool	m_Delete = false;
};

class PowerUpFactory
{
	public:
		PowerUpFactory();
		PowerUpFactory(const PowerUpFactory&) = default;
		PowerUpFactory &operator=(const PowerUpFactory&) = default;
		virtual ~PowerUpFactory() = default;
		Swallow::Ref<PowerUp> newPowerUp(PowerUpTypes type);
};