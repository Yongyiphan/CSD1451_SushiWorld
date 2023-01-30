#pragma once
#include "pch.h"
#include <stack>

//Window width, height
extern int winw, winh;

//window offset x and y
extern int wosx, wosy;

namespace GM {
	enum GS_ID {
		INPRO,	//Default do nothing loop
		ADD,	//Adding state
		REPLACE,//Replacing state
		RESTART,//Free >> Re Init State
		QUIT	//Remove State
		
	};
	class State {
	protected:
		bool pause = false;
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
		

		virtual void Pause()	{ pause = true; };
		virtual void Resume()	{ pause = false; };
	};

	class Engine {
	private:
		std::stack<std::unique_ptr<State>> state_stack;
		std::unique_ptr<State> new_state;

		GS_ID status = INPRO;

		bool restart = false;
		int StateCount = 0;

		
	public:
		Engine();
		~Engine();
		
		void AddState(std::unique_ptr<State> toAdd, GS_ID stat = ADD);
		void ProcessStateChange();
		void Update();
		void CleanUp();
		std::unique_ptr<State>& GetCurrent();
		int GetStateCount();
		
		void SetStatus(GS_ID, bool restart = false);
		bool CheckHaveState();
		GS_ID GetStatus();
	};
}
