#pragma once

#include <Swallow.hpp>
#include "Level.hpp"
#include "Player.hpp"

class GameLayer : public Swallow::Layer {
private:
	Swallow::Ref<Level> m_Level;
	Swallow::Ref<Player> m_Player;

	Swallow::PerspectiveCamera m_Camera;
	glm::vec3	m_Position;
	std::string m_Save;
	float		chance;
	int 		m_Lives = 3;
	int			m_Score;
	bool		m_runGameOverOnce = false;
	float		m_Difficulty;



	Swallow::Ref<Swallow::AudioBuffer> x;
	Swallow::Ref<Swallow::AudioSource> s;

	Swallow::Ref<Swallow::AudioBuffer> m_OneUpBuffer;
	Swallow::Ref<Swallow::AudioSource> m_OneUpSource;

	Swallow::Ref<Swallow::AudioBuffer> m_MalletAudioBuffer;
	Swallow::Ref<Swallow::AudioSource> m_MalletAudioSource;

	Swallow::Ref<Swallow::AudioBuffer> m_ExplosionBuffer;
	Swallow::Ref<Swallow::AudioSource> m_ExplosionSource;

	Swallow::Ref<Swallow::AudioBuffer> m_DeadBuffer;
	Swallow::Ref<Swallow::AudioSource> m_DeadSource;

public:
	GameLayer();
	GameLayer(const GameLayer &s) = default;
	// GameLayer &operator=(const GameLayer &s) = default;
	virtual ~GameLayer() = default;

	bool OnMouseButtonPressed(Swallow::MouseButtonPressedEvent &e);
	bool OnMouseMovedEvent(Swallow::MouseMovedEvent &e);
	bool OnKeyPressed(Swallow::KeyPressedEvent &e);
	bool OnWindowResize(Swallow::WindowResizeEvent &e);
	static bool IsPaused;

	inline int GetLives() { return m_Lives; }
	inline int GetScore() { return m_Score; }

	inline Swallow::Ref<Swallow::AudioSource> GetOneUpAudio() {return m_OneUpSource; }
	inline Swallow::Ref<Swallow::AudioSource> GetMalletAudio() {return m_MalletAudioSource; }
	inline Swallow::Ref<Swallow::AudioSource> GetExplosionAudio() {return m_ExplosionSource; }
	inline Swallow::Ref<Swallow::AudioSource> GetDeadAudio() {return m_DeadSource; }

	inline float GetDifficulty() { return m_Difficulty; }
	inline void SetSpawnChance(const float chance) { this->chance = chance; }
	inline void SetSave(const std::string &save) { this->m_Save = save; }

	virtual void SetLives(int lives) { m_Lives = lives; }
	virtual void SetScore(int score) { m_Score = score; }
	virtual void SetDifficulty(float difficulty) { m_Difficulty = difficulty; }
	virtual void OnEvent(Swallow::Event &e) override;
	virtual void OnAttach() override;
	virtual void OnDetach() override;
	virtual void OnImGuiRender() override;
	virtual void OnUpdate(Swallow::Timestep ts) override;

	inline Swallow::Ref<Level> GetLevel() { return m_Level; }
};