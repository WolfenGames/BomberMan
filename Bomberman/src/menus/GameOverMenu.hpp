
# pragma once

#include "../MenuLayer.hpp"
 
class GameOverMenu: public MenuLayer
{
    public:
        GameOverMenu();
        GameOverMenu(const GameOverMenu &rhs) = delete;
        GameOverMenu &operator=(const GameOverMenu &rhs) = delete;
        virtual ~GameOverMenu() = default;

        virtual void OnAttach() override;
        virtual void OnUpdate(Swallow::Timestep ts) override;
        
    private:
        float m_Timer; 
        bool m_hasBeenReset;
    	Swallow::OrthographicCamera m_Camera;
    	glm::ivec2	map_size;
};