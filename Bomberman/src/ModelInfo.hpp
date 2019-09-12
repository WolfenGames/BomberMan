#pragma once

#include <Swallow.hpp>

class ModelInfo
{
public:
	ModelInfo() = default;
	ModelInfo(const ModelInfo &s) = default;
	ModelInfo &operator=(const ModelInfo &s) = default;
	virtual ~ModelInfo() = default;
    
    inline void setModelName(const std::string &modelName) { m_ModelName = modelName; }
    inline void setModelAnimations(const std::vector<std::string> &animations) { for (auto anim: animations) { m_Animations.push_back(anim); } m_HasAnimations = true; }

	inline std::string getModelName() {return m_ModelName; }
    inline std::vector<std::string> &getAnimations() {return m_Animations; }

    inline void addAnimationKeyframe(std::string keyFrame) { m_Animations.push_back(keyFrame); m_HasAnimations = true; }
private:
	std::string m_ModelName;
	std::vector<std::string> m_Animations;
    bool m_HasAnimations;
};