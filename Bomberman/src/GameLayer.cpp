#include "GameLayer.hpp"
#include "imgui.h"
#include "BombermanApp.hpp"
#include <gtc/type_ptr.hpp>
#include "Platform/OpenGL/OpenGLShader.hpp"

bool GameLayer::IsPaused = false;

GameLayer::GameLayer()
	:m_Camera(glm::radians(45.0f), Swallow::Application::Get().GetWindow().GetWidth() / (float)Swallow::Application::Get().GetWindow().GetHeight(), 0.01f, 100.0f)
{
	m_Camera.SetRotation(glm::vec3(glm::radians(-70.0f), glm::radians(0.0f), 0));
	m_Camera.Recalculate();
	
	x = Swallow::AudioBuffer::Create("assets/Sounds/Background.wav");
	s = Swallow::AudioSource::Create();
	s->SetPosition({0.0f, 0.0f, 0.0f});
	s->SetVelocity({0.f, 0.f, 0.f});
	s->SetLooping(true);
	s->SetBuffer(x);

	m_OneUpBuffer = Swallow::AudioBuffer::Create("assets/Sounds/1Up.wav");
	m_OneUpSource = Swallow::AudioSource::Create();
	m_OneUpSource->SetPosition({0.0f, 0.0f, 0.0f});
	m_OneUpSource->SetVelocity({0.f, 0.f, 0.f});
	m_OneUpSource->SetGain(0.8f);
	m_OneUpSource->SetLooping(false);
	m_OneUpSource->SetBuffer(m_OneUpBuffer);


	m_MalletAudioBuffer = Swallow::AudioBuffer::Create("assets/Sounds/Mallet.wav");
	m_MalletAudioSource = Swallow::AudioSource::Create();
	m_MalletAudioSource->SetPosition({0.0f, 0.0f, 0.0f});
	m_MalletAudioSource->SetVelocity({0.f, 0.f, 0.f});
	m_MalletAudioSource->SetGain(0.9f);
	m_MalletAudioSource->SetLooping(false);
	m_MalletAudioSource->SetBuffer(m_MalletAudioBuffer);


	m_ExplosionBuffer = Swallow::AudioBuffer::Create("assets/Sounds/Explosion.wav");
	m_ExplosionSource = Swallow::AudioSource::Create();
	m_ExplosionSource->SetPosition({0.0f, 0.0f, 0.0f});
	m_ExplosionSource->SetVelocity({0.f, 0.f, 0.f});
	m_ExplosionSource->SetGain(0.8f);
	m_ExplosionSource->SetLooping(false);
	m_ExplosionSource->SetBuffer(m_ExplosionBuffer);

	m_DeadBuffer = Swallow::AudioBuffer::Create("assets/Sounds/Dead.wav");
	m_DeadSource = Swallow::AudioSource::Create();
	m_DeadSource->SetPosition({0.0f, 0.0f, 0.0f});
	m_DeadSource->SetVelocity({0.f, 0.f, 0.f});
	m_DeadSource->SetGain(0.8f);
	m_DeadSource->SetLooping(false);
	m_DeadSource->SetBuffer(m_DeadBuffer);

}

void GameLayer::OnAttach()
{
	m_Difficulty = 0.6;
	m_Player = std::make_shared<Player>();
	m_Level = std::make_shared<Level>();
	m_Level->SetPlayer(m_Player);
	m_Player->SetLevel(m_Level);
	s->Play();
	m_Lives = 3;
	m_Score = 0;
	m_runGameOverOnce = false;
	std::string path = "Saves/";
	std::ifstream in;
	in.open(path + m_Save + ".sav", std::ios::binary);
	if (m_Save.empty() || !in.good())
		m_Level->Generate(m_Difficulty);
	else
		m_Level->Load(m_Save);
}

void GameLayer::OnDetach()
{
	s->Stop();
	m_ExplosionSource->Stop();
	m_MalletAudioSource->Stop();
	m_OneUpSource->Stop();
	m_Level.reset();
	m_Player.reset();
}

void GameLayer::OnEvent(Swallow::Event &e) {
	Swallow::EventDispatcher dispatcher(e);
	dispatcher.Dispatch<Swallow::MouseButtonPressedEvent>(BIND_EVENT_FN(GameLayer::OnMouseButtonPressed));
	dispatcher.Dispatch<Swallow::MouseMovedEvent>(BIND_EVENT_FN(GameLayer::OnMouseMovedEvent));
	dispatcher.Dispatch<Swallow::KeyPressedEvent>(BIND_EVENT_FN(GameLayer::OnKeyPressed));
	dispatcher.Dispatch<Swallow::WindowResizeEvent>(BIND_EVENT_FN(GameLayer::OnWindowResize));
}

bool GameLayer::OnMouseButtonPressed(Swallow::MouseButtonPressedEvent &e)
{
	if (!IsPaused)
		return true;
	static_cast<void>(e);
	return false;
}

bool GameLayer::OnWindowResize(Swallow::WindowResizeEvent &e)
{
	static_cast<void>(e);
	m_Camera.SetProjectionMatrix(glm::radians(45.0f), Swallow::Application::Get().GetWindow().GetWidth() / (float)Swallow::Application::Get().GetWindow().GetHeight(), 0.01f, 100.0f);
	m_Camera.Recalculate();
	return false;
}

bool GameLayer::OnMouseMovedEvent(Swallow::MouseMovedEvent &e)
{
	static_cast<void>(e);
	return false;
}

bool GameLayer::OnKeyPressed(Swallow::KeyPressedEvent &e)
{
	Swallow::Ref<Settings> s = static_cast<BombermanApp &>(Swallow::Application::Get()).GetSettings();
	if (e.GetKeyCode() == s->GetKeybindings()["Bomb"])
		m_Level->DropBomb(glm::vec3(m_Level->GetPlayer()->Destination().x, m_Level->GetPlayer()->Destination().y + 0.5f, m_Level->GetPlayer()->Destination().z));
	else if (e.GetKeyCode() == s->GetKeybindings()["Save"])
	{
		m_Level->Save(m_Save);
		SW_CORE_INFO("Save: {}", m_Save);
	}
	else
		return false;
	return true;
}

void GameLayer::OnImGuiRender() {
}


void GameLayer::OnUpdate(Swallow::Timestep ts)
{
	if (!IsPaused)
	{
		static_cast<void>(ts);
		m_Position = glm::vec3(glm::clamp(m_Level->GetPlayer()->GetTransform()->GetPosition().x, 10.f, 19.f), 15, 13);
		m_Camera.SetPosition(m_Position);
		m_Camera.Recalculate();
		m_Level->Update(ts);

		Swallow::Renderer::BeginScene(m_Camera);

		m_Level->Draw();
	

		Swallow::Renderer::EndScene();
		if (m_Level->GetDeadStatus())
		{
			m_Lives--;
			if (m_Lives < 1)
			{
				static_cast<BombermanApp &>(Swallow::Application::Get()).UnloadGame();	
				static_cast<BombermanApp &>(Swallow::Application::Get()).LoadGameOver();

				return;
			}
			m_Level->Generate();
		};
		if (m_Player->WON())
		{
			m_Score += 5000 * m_Difficulty;
			m_Difficulty += 0.05;
			m_Level->Generate(m_Difficulty);
		};
	}
}
