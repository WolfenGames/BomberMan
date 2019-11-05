/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Settings.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppreez <ppreez@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 09:23:01 by ppreez            #+#    #+#             */
/*   Updated: 2019/11/05 14:53:14 by ppreez           ###   ########.fr       */
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
            }
            if (config == "resolution:")
            {
                std::getline(SettingsFile, config);
                std::string width = config.substr(0, config.find("x"));
                std::string height = config.substr(config.find("x") + 1, config.npos);
                m_Resolution = glm::vec2(std::stoi(width), std::stoi(height));
            }
            if (config == "keybindings:")
            {
                while (std::getline(SettingsFile, config))
                {
                    
                }
            }
        }
        m_Volume = 0.12f;
        m_Resolution = glm::vec2(200, 20);
        SaveSettings();
    }
    else
    {
        SW_CORE_INFO("creating settings");
        std::ofstream output(SettingsPath);
        output << "sound:" << std::endl << "0.5f" << std::endl;
        output << "resolution:" << std::endl << "800x600" << std::endl;
        output << "keybindings:" << std::endl;
        output.close();
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
    m_Volume = 0.5f;
    m_Resolution = glm::vec2(800, 600);
    m_Keybindings["UP"] = 1;
    m_Keybindings["DOWN"] = 2;
    m_Keybindings["LEFT"] = 3;
    m_Keybindings["RIGHT"] = 4;
    m_Keybindings["BOMB"] = 5;
    m_Keybindings["ESC"] = 6;
    m_Keybindings["SAVE"] = 7;
}

void Settings::SaveSettings()
{
    std::ofstream output(m_Path);
    output << "sound:" << std::endl << m_Volume << std::endl;
    output << "resolution:" << std::endl << m_Resolution.x << "x" << m_Resolution.y << std::endl;
    output << "keybindings:" << std::endl;

}