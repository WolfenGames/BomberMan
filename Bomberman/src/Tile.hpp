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

	inline void	SetDestructable(bool destructable) { m_isDestructable = destructable; }
	inline bool isDestructable() { return m_isDestructable; }
	inline bool isFilled() { return m_isFilled; }
	virtual void Explode() {}

	protected:
		bool m_isDestructable = false;
		bool m_isFilled = false;
};