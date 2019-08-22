#pragma once

#include <Swallow.hpp>
#include "Level.hpp"

class GameLayer : public Swallow::Layer {
private:
	Swallow::Ref<Swallow::VertexArray> m_Cube;
	Swallow::Ref<Swallow::Shader> m_Shader;

	Swallow::Ref<Level> m_Level;

	Swallow::PerspectiveCamera m_Camera;
public:
	GameLayer();
	GameLayer(const GameLayer &s) = default;
	GameLayer &operator=(const GameLayer &s) = default;
	virtual ~GameLayer() = default;

	bool OnMouseButtonPressed(Swallow::MouseButtonPressedEvent &e);
	bool OnMouseMovedEvent(Swallow::MouseMovedEvent &e);
	bool OnKeyPressed(Swallow::KeyPressedEvent &e);
	bool OnWindowResize(Swallow::WindowResizeEvent &e);


	virtual void OnEvent(Swallow::Event &e) override;
	virtual void OnImGuiRender() override;
	virtual void OnUpdate(Swallow::Timestep ts) override;
};