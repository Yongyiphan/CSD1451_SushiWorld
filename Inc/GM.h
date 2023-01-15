#pragma once
#include "pch.h"
#include <stack>

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
		
		void Initialize();
		void AddState(std::unique_ptr<State> toAdd, GS_ID stat = ADD);
		void ProcessStateChange();
		GS_ID Update();
		std::unique_ptr<State>& GetCurrent();
		
		void SetStatus(GS_ID, bool restart = false);
		bool CheckHaveState();
		GS_ID GetStatus();
	};
}
    /*while (current != GS_QUIT)
    {
        if (current != GS_RESTART) {
			GSM_Update();
            fpLoad();
        }
        else {
            current = previous;
            next = previous;
        }
        fpInitialize();
        while (current == next) {
            Input_Handle();
            fpUpdate();
            fpDraw();
        }
        fpFree();
        if (next != GS_RESTART) {
            fpUnload();
        }
        previous = current;
        current = next;
    }
    //Systems exit (terminate)
    System_Exit();
	*/
