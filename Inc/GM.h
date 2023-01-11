#pragma once
#include "AEEngine.h"
#include <string>
#include <stack>
#include <memory>

namespace GM {
	class State {
	private:
		std::string StateName;
	public:
		State();
		State(std::string);
		~State();
	
		virtual void Init() = 0;
		virtual void Exit() = 0;

		//f64 = typedef double
		virtual void Update(f64 dt) = 0;
		virtual void Draw() = 0;
		

		virtual void Pause() {};
		virtual void Resume() {};

	};

	class Engine {
	private:
		std::stack<std::unique_ptr<State>> stateStack;
		std::unique_ptr<State> new_state;

	public:
		Engine();
		~Engine();
	
		void AddState(std::unique_ptr<State> toAdd);
		void ReplaceState(std::unique_ptr<State> toReplace);
		void PopState();
		void ProcessStateChange();
		std::unique_ptr<State>& GetCurrent();



	};
}
