/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Settings.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppreez <ppreez@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 09:23:01 by ppreez            #+#    #+#             */
/*   Updated: 2019/11/20 14:05:48 by ppreez           ###   ########.fr       */
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
    
    SetKeyMap();
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
    m_Keybindings["Up"] = SW_KEY_W;
    m_Keybindings["Down"] = SW_KEY_S;
    m_Keybindings["Left"] = SW_KEY_A;
    m_Keybindings["Right"] = SW_KEY_D;
    m_Keybindings["Bomb"] = SW_KEY_SPACE;
    m_Keybindings["Save"] = SW_KEY_F5;
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

void Settings::SetKeyMap()
{
    m_KeyMap[SW_KEY_0] = "0";
    m_KeyMap[SW_KEY_1] = "1";
    m_KeyMap[SW_KEY_2] = "2";
    m_KeyMap[SW_KEY_3] = "3";
    m_KeyMap[SW_KEY_4] = "4";
    m_KeyMap[SW_KEY_5] = "5";
    m_KeyMap[SW_KEY_6] = "6";
    m_KeyMap[SW_KEY_7] = "7";
    m_KeyMap[SW_KEY_8] = "8";
    m_KeyMap[SW_KEY_9] = "9";

    m_KeyMap[SW_KEY_A] = "A";
    m_KeyMap[SW_KEY_B] = "B";
    m_KeyMap[SW_KEY_C] = "C";
    m_KeyMap[SW_KEY_D] = "D";
    m_KeyMap[SW_KEY_E] = "E";
    m_KeyMap[SW_KEY_F] = "F";
    m_KeyMap[SW_KEY_G] = "G";
    m_KeyMap[SW_KEY_H] = "H";
    m_KeyMap[SW_KEY_I] = "I";
    m_KeyMap[SW_KEY_J] = "J";
    m_KeyMap[SW_KEY_K] = "K";
    m_KeyMap[SW_KEY_L] = "L";
    m_KeyMap[SW_KEY_M] = "M";
    m_KeyMap[SW_KEY_N] = "N";
    m_KeyMap[SW_KEY_O] = "O";
    m_KeyMap[SW_KEY_P] = "P";
    m_KeyMap[SW_KEY_Q] = "Q";
    m_KeyMap[SW_KEY_R] = "R";
    m_KeyMap[SW_KEY_S] = "S";
    m_KeyMap[SW_KEY_T] = "T";
    m_KeyMap[SW_KEY_U] = "U";
    m_KeyMap[SW_KEY_V] = "V";
    m_KeyMap[SW_KEY_W] = "W";
    m_KeyMap[SW_KEY_X] = "X";
    m_KeyMap[SW_KEY_Y] = "Y";
    m_KeyMap[SW_KEY_Z] = "Z";
    m_KeyMap[SW_KEY_UP] = "Up";
    m_KeyMap[SW_KEY_DOWN] = "Down";
    m_KeyMap[SW_KEY_LEFT] = "Left";
    m_KeyMap[SW_KEY_RIGHT] = "Right";    
    m_KeyMap[SW_KEY_ENTER] = "Enter";
    m_KeyMap[SW_KEY_SPACE] = "Space";
    m_KeyMap[SW_KEY_F1] = "F1";
    m_KeyMap[SW_KEY_F2] = "F2";
    m_KeyMap[SW_KEY_F3] = "F3";
    m_KeyMap[SW_KEY_F4] = "F4";
    m_KeyMap[SW_KEY_F5] = "F5";
    m_KeyMap[SW_KEY_F6] = "F6";
    m_KeyMap[SW_KEY_F7] = "F7";
    m_KeyMap[SW_KEY_F8] = "F8";
    m_KeyMap[SW_KEY_F9] = "F9";
}