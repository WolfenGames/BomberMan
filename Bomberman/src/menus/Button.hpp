/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Button.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppreez <ppreez@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/12 15:58:53 by ppreez            #+#    #+#             */
/*   Updated: 2019/11/06 14:03:31 by ppreez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <Swallow.hpp>
#include "Swallow/Renderer/material/MaterialInstance.hpp"
#include "../material/MenuMaterial.hpp"
 
class Button
{
    public:
        Button();
        Button(std::string text);
        Button(std::string text, float x, float y);
        Button(std::string text, float x, float y, Swallow::OrthographicCamera &camera);
        Button(Button const &rhs);
        Button &operator=(Button const &rhs);
        ~Button();

        inline static Swallow::Ref<Button> Create() { return std::make_shared<Button>(); }
        inline static Swallow::Ref<Button> Create(std::string text, float x, float y) { return std::make_shared<Button>(text, x, y); }
        inline static Swallow::Ref<Button> Create(std::string text, float x, float y, Swallow::OrthographicCamera &camera) { return std::make_shared<Button>(text, x, y, camera); }
        inline Swallow::Ref<Swallow::GameObject> GetBackground() { return m_Background; }
        inline Swallow::Ref<Swallow::Text> GetText() { return m_Text; }
        inline glm::vec2 GetBottomLeft() { return m_BottomLeft; };
        inline glm::vec2 GetTopRight() { return m_TopRight; };
        inline float GetBackgroundX() { return m_BackgroundX; }
        inline float GetBackgroundY() { return m_BackgroundY; }
        inline float GeTextX() { return m_TextX; }
        inline float GetTextY() { return m_TextY; }


        bool Press();
        bool Switch();
        void Recalculate();

        void GenerateBackgroundDimensions(Swallow::OrthographicCamera &camera);        
        void SetBackgroundScale(float x, float y);
        void SetBackgroundColour(glm::vec4 colour);
        void HighlightBackground();
        void UnhighlightBackground();
        bool MouseInBounds(float x, float y);
    private:
        bool m_Pressed;
        glm::vec2 m_BottomLeft;
        glm::vec2 m_TopRight;
        float m_BackgroundX;
        float m_BackgroundY;
        float m_TextX;
        float m_TextY;
        glm::vec4 m_BackgroundColour;
        glm::vec4 m_BackgroundHighlight;

        Swallow::Ref<Swallow::FlatColourMaterialInstance> m_Material;
        Swallow::Ref<Swallow::GameObject> m_Background;
	    Swallow::Ref<Swallow::Text> m_Text;
};