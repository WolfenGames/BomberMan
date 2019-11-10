#pragma once

#include <Swallow.hpp>
#include <Swallow/AssetManager/GameObject.hpp>
#include "PowerUp.hpp"
#include <Swallow/Renderer/material/FlatColourMaterial.hpp>

class Tile : public Swallow::GameObject
{
	public:
		Tile() = default;
		Tile(const Tile &s) = default;
		Tile &operator=(const Tile &s) = default;
		virtual ~Tile() = default;

		inline void			SetDestructable(bool destructable) { m_isDestructable = destructable; }
		inline bool 		isDestructable() { return m_isDestructable; }
		inline bool			isFilled() { return m_isFilled; }
		inline bool 		CanPassThrough() { return m_canPassThrough; }
		virtual void 		Explode() {}
		
		inline void			SetExit(bool isExit) { m_isExit = isExit; };
		inline bool			IsExit() { return m_isExit;}

		inline bool			ContainsExit() { return m_containsExit; }
		inline void			SetContainsExit(bool containsExit) { m_containsExit = containsExit; }
		inline PowerUpTypes GetSecret() { return m_Secret; }

		//Disabled the return function for the colour here due to the texture instace not using it and crashing
		inline void 		SetSecret(PowerUpTypes secret) { m_Secret = secret; }// { std::dynamic_pointer_cast<Swallow::FlatColourMaterialInstance>(GetMaterial())->SetColour(glm::vec4(0.0, (static_cast<int>(secret) / 10.0f), 0.0f, 1.0f)); m_Secret = secret; }

	protected:
		PowerUpTypes m_Secret = PowerUpTypes::None;
		bool		m_isExit;
		bool		m_containsExit;
		bool 		m_canPassThrough = true;
		bool 		m_isDestructable = false;
		bool 		m_isFilled = false;
};