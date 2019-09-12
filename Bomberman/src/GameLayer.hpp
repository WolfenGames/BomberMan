#pragma once

#include <Swallow.hpp>
#include "Level.hpp"

class GameLayer : public Swallow::Layer {
private:
	Swallow::Ref<Level> m_Level;

	Swallow::PerspectiveCamera m_Camera;
	glm::vec3	m_Position;
	glm::ivec2  map_size;
	std::string m_Save;
	float		chance;

	Swallow::Ref<Swallow::AudioBuffer> x;
	Swallow::Ref<Swallow::AudioSource> s;

public:
	GameLayer();
	GameLayer(const GameLayer &s) = default;
	GameLayer &operator=(const GameLayer &s) = default;
	virtual ~GameLayer() = default;

	bool OnMouseButtonPressed(Swallow::MouseButtonPressedEvent &e);
	bool OnMouseMovedEvent(Swallow::MouseMovedEvent &e);
	bool OnKeyPressed(Swallow::KeyPressedEvent &e);
	bool OnWindowResize(Swallow::WindowResizeEvent &e);

	inline void SetMapSize(const glm::ivec2 &v) {map_size = v;}
	inline void SetSpawnChance(const float chance) { this->chance = chance; }
	inline void SetSave(const std::string &save) { this->m_Save = save; }

	virtual void OnEvent(Swallow::Event &e) override;
	virtual void OnAttach() override;
	virtual void OnDetach() override;
	virtual void OnImGuiRender() override;
	virtual void OnUpdate(Swallow::Timestep ts) override;
};