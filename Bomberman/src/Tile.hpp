#pragma once

#include <Swallow.hpp>
#include <Swallow/AssetManager/GameObject.hpp>


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

	protected:
		bool		m_isExit;
		bool		m_containsExit;
		bool 		m_canPassThrough = true;
		bool 		m_isDestructable = false;
		bool 		m_isFilled = false;
};