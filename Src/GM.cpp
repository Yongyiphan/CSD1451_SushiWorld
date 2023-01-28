#include "pch.h"

#include "GM.h"

namespace GM {

	Engine::Engine() {
		std::cout << "Create Game Manager" << std::endl;
	}
	
	Engine::~Engine() {
		std::cout << "Exit Game Manager" << std::endl;
		CleanUp();
	};


	void Engine::AddState(std::unique_ptr<State> state, GS_ID stat) {
		status = stat;
		new_state = std::move(state);
	}

	/*
	Scenarios: Assuming init stack of [MainMenu]
	Adding State
	[MainField]
	[MainMenu]
	*/


	void Engine::ProcessStateChange() {
		//TODO
		//IF !State.pause unload;
		switch (status) {
		case ADD:
			//TODO
			/*1. Check if new_state within stack;
					true:
						free/pop stack till top() == new_state <=> new_state = top;
						new_state = nullptr;
						top()->Free() >> top->Init()
					false:
						top()->Pause()
						push on top of stack;
						top()->Load() >> top->Init()
			*/
			if (StateCount > 0) {
				if (CheckHaveState()) {
					state_stack.top()->Free();
					state_stack.top()->Init();
					break;
				}
				else {
					state_stack.top()->Pause();
				}
			}
			state_stack.push(std::move(new_state));
			state_stack.top()->Load();
			state_stack.top()->Init();
			StateCount++;
			break;
		case QUIT:
			/*	Clean up current state;
				Pop current state
				if restart:
					free() -> init()
				else:
					do nothing
			*/
			state_stack.top()->Free();
			state_stack.pop();
			StateCount--;
			if (restart && !state_stack.empty()) {
				state_stack.top()->Free();
				state_stack.top()->Init();
			}
			break;
		}
		status = INPRO;

	}

	void Engine::Update() {
		AESysFrameStart();
		AEInputUpdate();
		if (state_stack.empty()) {
			status = QUIT;
		}
		else {
			state_stack.top()->Update(AEFrameRateControllerGetFrameTime());
			state_stack.top()->Draw();
		}
		AESysFrameEnd();
	}

	std::unique_ptr< State>& Engine::GetCurrent() {
		return state_stack.top();
	}
	

	//Parameters for Restarting Prev state (e.g Pause screen)
	//	ID = QUIT, restart = true
	void Engine::SetStatus(GS_ID id, bool restart) {
		this->status  = id;
		this->restart = restart;
	}
	

	bool Engine::CheckHaveState() {
		std::stack<std::unique_ptr<State>>temp;
		bool found = false;
		while (!state_stack.empty()) {
			std::string Test = state_stack.top()->StateName;
			if (state_stack.top()->StateName == new_state->StateName) {
				found = true;
				break;
			}
			else{
				temp.push(std::move(state_stack.top()));
				state_stack.pop();
			}
		}
		while (!temp.empty()) {
			if (found) {
				temp.top()->Free();
				StateCount--;
			}
			else {
				state_stack.push(std::move(temp.top()));
			}
			temp.pop();
		}
		return found;
	}

	GS_ID Engine::GetStatus(){
		return this->status;
	}

	int Engine::GetStateCount() {
		return this->StateCount;
	}
	
	void GM::Engine::CleanUp() {
		while (!state_stack.empty()) {
			state_stack.top()->Free();
			state_stack.top()->Unload();
			state_stack.pop();
			StateCount--;
		}
	}
}
