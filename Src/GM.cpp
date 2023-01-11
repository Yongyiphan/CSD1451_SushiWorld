#include "AEEngine.h"
#include "GM.h"
#include <iostream>
#include <vector>

GM::State::State() {

}
GM::State::State(std::string Name) {
	StateName = Name;
}
GM::State::~State() {

}


GM::Engine::Engine(){

}
GM::Engine::~Engine(){}

void GM::Engine::AddState(std::unique_ptr<State> toAdd) {
	
}
void GM::Engine::ReplaceState(std::unique_ptr<State> toReplace) {

}
void GM::Engine::PopState() {
	
}
void GM::Engine::ProcessStateChange() {

}

std::unique_ptr<GM::State>& GM::Engine::GetCurrent() {
	return stateStack.top();
}
