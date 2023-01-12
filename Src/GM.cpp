#include "AEEngine.h"
#include "GM.h"
#include <iostream>
#include <string>

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

GM::Engine::Engine() {
	toAdd = toReplace = toRemove = false;
}
GM::Engine::~Engine() {

}

void GM::Engine::AddState(std::unique_ptr<State> state, bool replace) {
	toAdd = true;
	new_state = std::move(state);
	toReplace = replace;
}

void GM::Engine::PopState() {
	toRemove = true;
}
void GM::Engine::ProcessStateChange() {
	if (toRemove && (!stateStack.empty())) {
		stateStack.top()->Exit();
		stateStack.pop();
		if (!stateStack.empty()) {
			stateStack.top()->Resume();
		}
		toRemove = false;
	}

	if (toAdd) {
		if (toReplace && (!stateStack.empty())) {
			stateStack.top()->Exit();
			stateStack.pop();
		}
		if (!stateStack.empty()) {
			stateStack.top()->Pause();
		}
		stateStack.push(std::move(new_state));
		stateStack.top()->Init();
		stateStack.top()->Resume();
		toAdd = false;
	}
}
std::unique_ptr<GM::State>& GM::Engine::GetCurrent() {
	return stateStack.top();
}
