#include "pch.h"
#include "GM.h"
/*
Engine Model
[PauseScreen ] <- Add On top
[PlayingField]
[MainMenu    ]

if Replace, store to state to replace
In ProcessChange
	if to remove, replace state with stored state
if Add, pause top state, push to top
*/
namespace GM {
	Engine::Engine() {
		std::cout << "Create Game Manger" << std::endl;
		new_state = nullptr;
	}
	
	Engine::~Engine() {};



	void Engine::Initialize() {
		std::cout << "Init Engine" << std::endl;
	}


	void Engine::AddState(std::unique_ptr<State> state, bool replace) {
		status = ADD;
		new_state = std::move(state);
	}

	/*
	Scenarios of state change
	MainMenu ->> GamePlay:
		[GamePlay] <- 1.Added (Pushed) >> 2.Load >> 3.Init
		[MainMenu] <- Paused
		=============================================
		Continue to Engine::Update() -> [GamePlay]

	GamePlay ->> Pause Screen:
		[Pause Screen] <- 1.Added (Pushed) >> 2.Load >> 3.Init >> 4.QUIT (Upon UI)
		[GamePlay] 5. Resume here
		[MainMenu]
		=============================================
		Continue to Engine::Update() -> [GamePlay]
	*/


	void Engine::ProcessStateChange() {
ProcessChange:
		switch (status) {
		case RESTART:
			state_stack.top()->Free();
			state_stack.top()->Init();
			break;
		case QUIT: //remove
			if (!state_stack.empty()) {
				state_stack.top()->Free();
				state_stack.top()->Unload();
				state_stack.pop();
				if (restart) {
					status = RESTART;
					restart = false;
					goto ProcessChange;
				}
			}
			break;
		case ADD:
			if(!state_stack.empty()){
				state_stack.top()->Pause();
			}
			state_stack.push(std::move(new_state));
			state_stack.top()->Load();
			state_stack.top()->Init();
			break;
		}
		status = INPRO;
	}

	void Engine::Update() {
		AESysFrameStart();
		state_stack.top()->Update(AEFrameRateControllerGetFrameTime());
		state_stack.top()->Draw();
		AESysFrameEnd();
	}

	std::unique_ptr< State>& Engine::GetCurrent() {
		return state_stack.top();
	}
	
	void Engine::SetStatus(GS_ID id, bool restart) {
		status = id;
		restart = restart;
	}
	

	
}
