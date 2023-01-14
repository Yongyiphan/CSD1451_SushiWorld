#pragma once
#include "pch.h"
#include <string>
#include <stack>
#include <memory>

namespace GM {
	enum GS_ID {
		RESTART,
		QUIT
		
	};
	class State {
	public:
		//Variables
		std::string StateName;

		//Constructor | Destructor
		State() {};
		virtual ~State() {};
		

		virtual void Load() = 0;
		virtual void Unload() = 0;
	
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
		Engine() {};
		~Engine() {};
		
		void Initialize();
		void AddState(std::unique_ptr<State> toAdd, bool replace);
		void PopState();
		void ProcessStateChange();
		std::unique_ptr<State>& GetCurrent();



	};
}
