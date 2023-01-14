#include "pch.h"
#include "GM.h"
#include <string>


GM::Engine::Engine() {
	std::cout << "Create Game Manger" << std::endl;
}

void GM::Engine::Initialize() {
	std::cout << "Init Engine" << std::endl;
}


void GM::Engine::AddState(std::unique_ptr<State> toAdd, bool replace) {
	
}

void GM::Engine::PopState() {
	
}
void GM::Engine::ProcessStateChange() {

}

std::unique_ptr<GM::State>& GM::Engine::GetCurrent() {
	return stateStack.top();
}
