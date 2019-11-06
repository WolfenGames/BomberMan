/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Settings.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppreez <ppreez@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 09:22:50 by ppreez            #+#    #+#             */
/*   Updated: 2019/11/06 14:50:02 by ppreez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <Swallow.hpp>

class Settings
{
    public:
        Settings();
        Settings(const char *SettingsPath);
        Settings(const Settings &rhs);
        Settings &operator=(const Settings &rhs);
        ~Settings();

        void SetDefaultSettings();
        void SaveSettings();

        inline static Swallow::Ref<Settings> Create() { return std::make_shared<Settings>(); };
        inline void SetVolume(float volume) { m_Volume = volume; };
        inline void SetResolution(glm::vec2 newRes) { m_Resolution = newRes; };
        void SetKeybinding(std::string &key, int keycode);

        inline float GetVolume() { return m_Volume; };
        inline glm::vec2 GetResolution() { return m_Resolution; };
        inline std::map<std::string, int> GetKeybindings() { return m_Keybindings; };
    private:
        std::string m_Path;
        float m_Volume;
        glm::vec2 m_Resolution;
        std::map<std::string, int> m_Keybindings;
};