#pragma once

#include <Swallow.hpp>
#include "menus/Menu.hpp"

class MenuLayer : public Swallow::Layer {
protected:
	Swallow::Ref<Swallow::GameObject> m_Square;
	Swallow::Ref<Swallow::Text> m_Text;
	Swallow::Ref<Menu> m_Menu;
	std::string save;

	Swallow::OrthographicCamera m_Camera;

	glm::ivec2	map_size;
	float		chance;
public:
	MenuLayer();
	MenuLayer(const MenuLayer &s) = delete;
	MenuLayer &operator=(const MenuLayer &s) = delete;
	virtual ~MenuLayer() = default;

	bool OnMouseButtonPressed(Swallow::MouseButtonPressedEvent &e);
	bool OnMouseMovedEvent(Swallow::MouseMovedEvent &e);
	bool OnKeyPressed(Swallow::KeyPressedEvent &e);
	bool OnWindowResize(Swallow::WindowResizeEvent &e);

	inline const glm::ivec2 &GetMapSize() { return map_size; }
	inline float GetChance() { return this->chance; }
	inline std::string GetSave() { return this->save; }

	virtual void OnEvent(Swallow::Event &e) override;
	virtual void OnImGuiRender() override;
	virtual void OnUpdate(Swallow::Timestep ts) override;
};