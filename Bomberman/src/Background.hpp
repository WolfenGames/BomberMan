#pragma once

#include <Swallow.hpp>
#include "BackDrop.hpp"

class Background : public Swallow::Layer 
{

	public:
		Background();
		Background(const Background&) = default;
		Background &operator=(const Background&) = delete;
		// Background &operator=(const Background&) = default;

	private:
		Swallow::Ref<BackDrop> m_BackDrop;
		Swallow::OrthographicCamera m_Camera;

		bool OnMouseButtonPressed(Swallow::MouseButtonPressedEvent &e);
		bool OnMouseMovedEvent(Swallow::MouseMovedEvent &e);
		bool OnKeyPressed(Swallow::KeyPressedEvent &e);
		bool OnWindowResize(Swallow::WindowResizeEvent &e);

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnEvent(Swallow::Event &e) override;
		virtual void OnImGuiRender() override;
		virtual void OnUpdate(Swallow::Timestep ts) override;
};