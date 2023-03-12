#include "pch.h"

#include "GameManager.h"

namespace GM {

	Engine::Engine() {
		std::cout << "Create Game Manager" << std::endl;
	}
	
	Engine::~Engine() {
		std::cout << "Exit Game Manager" << std::endl;
		CleanUp();
	};


	void Engine::AddState(std::unique_ptr<State> state, GS_ID ID) {
		status = ID;
		new_state = std::move(state);
		
	}


	/*
	Scenarios: Assuming init stack of [MainMenu]
	Adding State
	[MainField]
	[MainMenu]
	*/


	void Engine::ProcessStateChange() {
		/*TODO Adding Load and Unload to State Change Manager*/
		//Remove transitional state
		ProcessTransitState();
		//IF !State.pause unload;
		switch (status) {
		case ADD:
			//Only check if state exist if No of state > 0
			if (StateCount > 0) {
				//Check if state exist within stack
				if (CheckHaveState()) {
					//Everything in between should have been freed /and unload
					//	-> free/pop stack till top() == new_state <=> new_state = top;
					//Free current top
					state_stack.top()->Free();
					state_stack.top()->Init();
					break;
				}
				else {
					//If theres a prev state, pause it before adding
					state_stack.top()->Pause();
				}
			}
			//Finally, Add new state on top of stack
			if (new_state->gs_type == TRANSIT_STATE) {
				transit_stack.push(std::move(new_state));
				transit_stack.top()->Load();
				transit_stack.top()->Init();
				break;
			}
			state_stack.push(std::move(new_state));
			state_stack.top()->Load();
			state_stack.top()->Init();
			StateCount++;
			break;
		case RESUME:
			state_stack.top()->Resume();
			break;
		case RESTART:
			if (!state_stack.empty()) {
				state_stack.top()->Free();
				state_stack.top()->Init();
			}
			break;
		case QUIT:
			//Pop current state
			state_stack.top()->Free();
			state_stack.pop();
			StateCount--;
			if (!state_stack.empty()) {
				//Check if need to restart prev state
				if (restart) {
					state_stack.top()->Free();
					state_stack.top()->Init();

				}
				else {
					state_stack.top()->Resume();
				}
			}

			break;
		}
		status = INPRO;

	}

	void Engine::ProcessTransitState() {
		if (!transit_stack.empty()) {
			transit_stack.top()->Free();
			transit_stack.pop();
		}
	}

	void Engine::Update() {
		AESysFrameStart();
		//std::cout << utils::UGetDT() << std::endl;
		AEInputUpdate();
		if (state_stack.empty()) {
			status = QUIT;
		}
		else {
			if (!transit_stack.empty()) {
				transit_stack.top()->Update(utils::UGetDT());
				state_stack.top()->Draw();
				transit_stack.top()->Draw();
			}
			else {
				state_stack.top()->Update(utils::UGetDT());
				state_stack.top()->Draw();
			}
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
