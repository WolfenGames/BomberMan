/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Settings.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppreez <ppreez@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 09:22:50 by ppreez            #+#    #+#             */
/*   Updated: 2019/11/11 11:40:54 by ppreez           ###   ########.fr       */
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
        void CycleVolume();
        void CycleResolution();

        void SetKeybinding(std::string &key, int keycode);
        inline static Swallow::Ref<Settings> Create() { return std::make_shared<Settings>(); };
        inline void SetVolume(float volume) { m_Volume = volume; };
        inline void SetResolution(glm::vec2 newRes) { m_Resolution = newRes; };

        inline float GetVolume() { return m_Volume; };
        inline std::string GetVolumeString() { return m_VolumeString; };
        inline std::string GetResolutionString() { return m_ResolutionString; };
        inline glm::vec2 GetResolution() { return m_Resolution; };
        inline std::map<std::string, int> GetKeybindings() { return m_Keybindings; };
        inline std::map<int, std::string> GetKeyMap() { return m_KeyMap; };
    private:
        std::string m_Path;
        float m_Volume;
        std::string m_VolumeString;
        std::string m_ResolutionString;
        glm::vec2 m_Resolution;
        std::map<std::string, int> m_Keybindings;
        std::map<int, std::string> m_KeyMap;

        void SetKeyMap();
};