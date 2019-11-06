#pragma once

#include <Swallow.hpp>
#include "Level.hpp"
#include "Player.hpp"

class GameLayer : public Swallow::Layer {
private:
	Swallow::Ref<Level> m_Level;
	Swallow::Ref<Player> m_Player;

	Swallow::PerspectiveCamera m_Camera;
	glm::vec3	m_Position;
	std::string m_Save;
	float		chance;
	int 		m_Lives = 3;

	Swallow::Ref<Swallow::AudioBuffer> x;
	Swallow::Ref<Swallow::AudioSource> s;

public:
	GameLayer();
	GameLayer(const GameLayer &s) = default;
	// GameLayer &operator=(const GameLayer &s) = default;
	virtual ~GameLayer() = default;

	bool OnMouseButtonPressed(Swallow::MouseButtonPressedEvent &e);
	bool OnMouseMovedEvent(Swallow::MouseMovedEvent &e);
	bool OnKeyPressed(Swallow::KeyPressedEvent &e);
	bool OnWindowResize(Swallow::WindowResizeEvent &e);

	inline void SetSpawnChance(const float chance) { this->chance = chance; }
	inline void SetSave(const std::string &save) { this->m_Save = save; }

	virtual void OnEvent(Swallow::Event &e) override;
	virtual void OnAttach() override;
	virtual void OnDetach() override;
	virtual void OnImGuiRender() override;
	virtual void OnUpdate(Swallow::Timestep ts) override;

	inline Swallow::Ref<Level> GetLevel() { return m_Level; }
};