/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Settings.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppreez <ppreez@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 09:23:01 by ppreez            #+#    #+#             */
/*   Updated: 2019/11/07 17:50:28 by ppreez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Settings.hpp"

Settings::Settings()
:Settings("Settings.conf")
{
}

Settings::Settings(const char *SettingsPath)
:m_Path(SettingsPath)
{
    std::ifstream SettingsFile;
    std::stringstream SettingsStream;
    std::string config;
    
    SettingsFile.open(SettingsPath);
    if (SettingsFile.is_open())
    {
        while (std::getline(SettingsFile, config))
        {
            if (config == "sound:")
            {
                std::getline(SettingsFile, config);
                m_Volume = std::stof(config);
                if (m_Volume == 0.0f)
                    m_VolumeString = "Off";
                else if (m_Volume == 0.25f)
                    m_VolumeString = "Quiet";
                else if (m_Volume == 0.75f)
                    m_VolumeString = "Loud";
                else
                    m_VolumeString = "Full";
            }
            if (config == "resolution:")
            {
                std::getline(SettingsFile, config);
                m_ResolutionString = config;
                std::string width = config.substr(0, config.find("x"));
                std::string height = config.substr(config.find("x") + 1, config.npos);
                m_Resolution = glm::vec2(std::stoi(width), std::stoi(height));
            }
            if (config == "keybindings:")
            {
                while (std::getline(SettingsFile, config))
                {
                    std::string key = config.substr(0, config.find(":"));
                    std::string value = config.substr(config.find(":") + 1, config.npos);
                    m_Keybindings[key] = std::stoi(value);
                }
            }
        }
    }
    else
    {
        SW_CORE_INFO("creating settings");
        SetDefaultSettings();
        SaveSettings();
    }
}

Settings::Settings(const Settings &rhs)
{
    *this = rhs;
}

Settings &Settings::operator=(const Settings &rhs)
{
    if (this != &rhs)
    {
        *this = rhs;
    }
    return *this;
}

Settings::~Settings()
{
    
}

void Settings::SetKeybinding(std::string &key, int keycode)
{
    m_Keybindings[key] = keycode;
}

void Settings::SetDefaultSettings()
{
    m_Volume = 0.75f;
    m_VolumeString = "Loud";
    m_Resolution = glm::vec2(1280, 720);
    m_ResolutionString = "1280x720";
    m_Keybindings["UP"] = SW_KEY_W;
    m_Keybindings["DOWN"] = SW_KEY_S;
    m_Keybindings["LEFT"] = SW_KEY_A;
    m_Keybindings["RIGHT"] = SW_KEY_D;
    m_Keybindings["BOMB"] = SW_KEY_SPACE;
    m_Keybindings["SAVE"] = SW_KEY_F5;
}

void Settings::SaveSettings()
{
    std::ofstream output(m_Path);
    output << "sound:" << std::endl << m_Volume << "f" << std::endl;
    output << "resolution:" << std::endl << m_Resolution.x << "x" << m_Resolution.y << std::endl;
    output << "keybindings:" << std::endl;
    for (auto a : m_Keybindings)
    {
        output << a.first << ":" << a.second << std::endl;
    }
    output.close();

}

void Settings::CycleVolume()
{
    if (m_Volume == 0.0f)
    {
        m_VolumeString = "Quiet";
        m_Volume = 0.25f;
    }
    else if (m_Volume == 0.25f)
    {
        m_VolumeString = "Loud";
        m_Volume = 0.75f;
    }
    else if (m_Volume == 0.75f)
    {
        m_VolumeString = "Full";
        m_Volume = 1.0f;
    }
    else
    {
        m_VolumeString = "Off";
        m_Volume = 0.0f;
    }
}

void Settings::CycleResolution()
{
    if (m_ResolutionString == "800x600")
    {
        m_Resolution.x = 1280;
        m_Resolution.y = 720;
        m_ResolutionString = "1280x720";
    }
    else if (m_ResolutionString == "1280x720")
    {
        m_Resolution.x = 1600;
        m_Resolution.y = 900;
        m_ResolutionString = "1600x900";
    }
    else
    {
        m_Resolution.x = 800;
        m_Resolution.y = 600;
        m_ResolutionString = "800x600";
    }
}