#pragma once

#include <Swallow.hpp>

class GUILayer : public Swallow::Layer {
private:
	Swallow::Ref<Swallow::GameObject> m_PinkThing;

	Swallow::OrthographicCamera m_Camera;

public:
	GUILayer();
	GUILayer(const GUILayer &s) = default;
	GUILayer &operator=(const GUILayer &s) = default;
	virtual ~GUILayer() = default;

	bool OnMouseButtonPressed(Swallow::MouseButtonPressedEvent &e);
	bool OnMouseMovedEvent(Swallow::MouseMovedEvent &e);
	bool OnKeyPressed(Swallow::KeyPressedEvent &e);
	bool OnWindowResize(Swallow::WindowResizeEvent &e);


	virtual void OnEvent(Swallow::Event &e) override;
	virtual void OnImGuiRender() override;
	virtual void OnUpdate(Swallow::Timestep ts) override;
};