#pragma once
#include "pch.h"
#include <stack>

namespace GM {
	enum GS_ID {
		RESTART,
		QUIT,
		RESUME,
		INPRO,
		ADD
		
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
		virtual void Free() = 0;

		//f64 = typedef double
		virtual void Update(f64 dt) = 0;
		virtual void Draw() = 0;
		

		virtual void Pause() {};
		virtual void Resume() {};
	};

	class Engine {
	private:
		std::stack<std::unique_ptr<State>> state_stack;
		std::unique_ptr<State> new_state;

		GS_ID status = INPRO;

		bool restart = false;

		
	public:
		Engine();
		~Engine();
		
		void Initialize();
		void AddState(std::unique_ptr<State> toAdd, bool replace = false);
		void PopState();
		void ProcessStateChange();
		void Update();
		std::unique_ptr<State>& GetCurrent();
		
		void SetStatus(GS_ID, bool restart = false);

	};
}
