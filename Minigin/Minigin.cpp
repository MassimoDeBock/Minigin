#include "MiniginPCH.h"
#include "Minigin.h"
#include <thread>
#include "InputManager.h"
#include "SceneManager.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include "GameObject.h"
#include "TextureComponent.h"
#include "TextComponent.h"
#include "FPSComponent.h"
#include "MovementComponent.h"
#include "PeterPepperPlayerController.h"
#include "Scene.h"
#include "MessageCommand.h"

using namespace std;

void PrintSDLVersion()
{
	SDL_version compiled{};
	SDL_version linked{};

	SDL_VERSION(&compiled);
	SDL_GetVersion(&linked);
	printf("We compiled against SDL version %d.%d.%d ...\n",
		compiled.major, compiled.minor, compiled.patch);
	printf("We are linking against SDL version %d.%d.%d.\n",
		linked.major, linked.minor, linked.patch);
}

void dae::Minigin::Initialize()
{
	PrintSDLVersion();
	
	if (SDL_Init(SDL_INIT_VIDEO) != 0) 
	{
		throw std::runtime_error(std::string("SDL_Init Error: ") + SDL_GetError());
	}

	m_Window = SDL_CreateWindow(
		"Programming 4 assignment",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		640,
		480,
		SDL_WINDOW_OPENGL
	);
	if (m_Window == nullptr) 
	{
		throw std::runtime_error(std::string("SDL_CreateWindow Error: ") + SDL_GetError());
	}

	Renderer::GetInstance().Init(m_Window);
}

/**
 * Code constructing the scene world starts here
 */
void dae::Minigin::LoadGame() const
{
	auto& scene = SceneManager::GetInstance().CreateScene("Demo");

	auto go = std::make_shared<GameObject>();
	go->AddComponent<TextureComponent>("TextureComponent", new TextureComponent("background.jpg"));
	scene.Add("Background", go);


	go = std::make_shared<GameObject>();
	go->AddComponent<TextureComponent>("TextureComponent", new TextureComponent("logo.png"));
	go->SetAbsoluteTransform(216, 180);
	scene.Add("Logo", go);


	auto font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	go = std::make_shared<GameObject>();
	go->AddComponent<TextComponent>("TextComponent", new TextComponent("Programming 4 Assignment", font));
	go->SetAbsoluteTransform(80, 20);
	scene.Add("Text",go);
	
	
	go = std::make_shared<GameObject>();
	go->AddComponent<FPSComponent>("FPSComponent", new FPSComponent());
	go->SetParent(scene.GetGameObjects("Logo"));
	go->SetRelativeTransform(50, -40);
	scene.Add("FPSDisplay", go);


	go = std::make_shared<GameObject>();
	go->AddComponent<TextureComponent>("TextureComponent", new TextureComponent("Peter_Pepper.png"));
	go->SetAbsoluteTransform(400, 400);
	go->AddComponent<PeterPepperPlayerController>("PeterPepperPlayerController", new PeterPepperPlayerController(0));
	go->GetComponent<MovementComponent>("MovementComponent")->SetMovementSpeed(Transform(10,10,0));
	scene.Add("Peter_Pepper", go);


}

void dae::Minigin::Cleanup()
{
	Renderer::GetInstance().Destroy();
	SDL_DestroyWindow(m_Window);
	m_Window = nullptr;
	SDL_Quit();
}

void dae::Minigin::Run()
{
	Initialize();

	// tell the resource manager where he can find the game data
	ResourceManager::GetInstance().Init("../Data/");

	LoadGame();
	GameLoop();
	Cleanup();
}


void dae::Minigin::GameLoop()
{
	auto& renderer = Renderer::GetInstance();
	auto& sceneManager = SceneManager::GetInstance();
	sceneManager.SetFixedTimeStep(fixedTimeStep);
	auto& input = InputManager::GetInstance();

	// todo: this update loop could use some work.
	bool doContinue = true;
	auto lastTime = std::chrono::high_resolution_clock::now();
	float lag = 0.0f;

	input.CheckConnections();
	input.AddCommandsToController(0, ControllerButton::A, ButtonStates::Down, new MessageCommand(std::string("oo")));


	sceneManager.BeginPlay();
	while (doContinue)
	{
		const auto currentTime = std::chrono::high_resolution_clock::now();
		float deltaTime = std::chrono::duration<float>(currentTime - lastTime).count();
		lastTime = currentTime;
		lag += deltaTime;
		doContinue = input.ProcessInput();
		while (lag >= fixedTimeStep) {
			//FixedUpdate();
			lag -= fixedTimeStep;
		}
		sceneManager.Update(deltaTime);
		renderer.Render();
		const auto sleepTime = currentTime + std::chrono::milliseconds(MsPerFrame) - std::chrono::high_resolution_clock::now();
		std::this_thread::sleep_for(sleepTime);
	}
}