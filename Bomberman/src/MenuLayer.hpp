#pragma once

#include <Swallow.hpp>

class MenuLayer : public Swallow::Layer {
private:
	Swallow::Ref<Swallow::VertexArray> m_Square;
	Swallow::Ref<Swallow::Shader> m_Shader;

	Swallow::OrthographicCamera m_Camera;
public:
	MenuLayer();
	MenuLayer(const MenuLayer &s) = default;
	MenuLayer &operator=(const MenuLayer &s) = default;
	virtual ~MenuLayer() = default;

	bool OnMouseButtonPressed(Swallow::MouseButtonPressedEvent &e);
	bool OnMouseMovedEvent(Swallow::MouseMovedEvent &e);
	bool OnKeyPressed(Swallow::KeyPressedEvent &e);
	bool OnWindowResize(Swallow::WindowResizeEvent &e);


	virtual void OnEvent(Swallow::Event &e) override;
	virtual void OnImGuiRender() override;
	virtual void OnUpdate(Swallow::Timestep ts) override;
};