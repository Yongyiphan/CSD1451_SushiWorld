#include "AEEngine.h"
#include "GM.h"
#include <iostream>
#include <string>




void GM::Engine::AddState(std::unique_ptr<State> toAdd, bool replace) {
	
}

void GM::Engine::PopState() {
	
}
void GM::Engine::ProcessStateChange() {

}

std::unique_ptr<GM::State>& GM::Engine::GetCurrent() {
	return stateStack.top();
}
