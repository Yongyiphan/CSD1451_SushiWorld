#pragma once
#include "AEEngine.h"
#include <string>
#include <stack>
#include <memory>

namespace GM {
	class State {
	protected:
		State();
		State(std::string);
		~State();
		std::string StateName;
	public:
	
		virtual void Init() = 0;
		virtual void Exit() = 0;

		//f64 = typedef double
		virtual void Update() = 0;
		virtual void Draw() = 0;
		
		virtual void Pause() = 0;
		virtual void Resume() = 0;

		virtual ~State() {};
	};

	class Engine {
	private:
		std::stack<std::unique_ptr<State>> stateStack;
		std::unique_ptr<State> new_state;

		bool m_add;
		bool m_replce;
		bool m_remove;

	public:
		Engine();
	
		void AddState(std::unique_ptr<State> toAdd);
		void ReplaceState(std::unique_ptr<State> toReplace);
		void PopState();
		void ProcessStateChange();
		std::unique_ptr<State>& GetCurrent();



		~Engine();
	};
}
