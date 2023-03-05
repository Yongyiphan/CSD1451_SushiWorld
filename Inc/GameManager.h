#pragma once
#include "pch.h"
#include <stack>

//IMPORTANT Global variables, possibly useful
//Window width, height
extern f32 winw, winh;

//window offset x and y
extern f32 wosx, wosy;

//Framerate cannot drop below this value
extern int FR;

namespace GM {
	class State;
	class Engine;
	struct Context;
}

namespace GM {
	enum GS_ID {
		INPRO,	//Default do nothing loop
		ADD,	//Adding state
		RESTART,//Free >> Re Init State
		RESUME,	//Resume previous state (after a transit state)
		QUIT	//Remove State
	};

	enum GS_Type {
		GAME_STATE, //actual game state
		TRANSIT_STATE // pause state, runs over game state e.g pause screen, item drop screen
	};

	struct RoomTracker {
		std::vector<int> ExplorableRooms;
		std::vector<int> ExploredRooms;
		int cRoom{}, TotalRoom{};
		RoomTracker() {
			ExplorableRooms = { 1,1,1,1 };
			ExploredRooms = { 0,0,0,0 };
		}
		void Reset() {
			ExplorableRooms = { 1,1,1,1 };
			ExploredRooms = { 0,0,0,0 };
		}
	};
	enum RoomMap {
		ARROW,
		//PLATFORM,
		SHOP,
		REST
	};
	static int TotalRooms{ 3 - 1 };
	static std::vector < std::string> RoomNames = {
		"Arrow Battle", 
		//"Platform Battle",
		"Shop", "Rest Room"
	};
	class State {
	protected:
		bool pause = false;
		std::shared_ptr<Context> m_context;
		//IMPORTANT: Change within State constructor when initializing transit state

		s32 mousex{}, mousey{};
		s8* FontID{};
	public:
		//Variables
		std::string StateName;
		GS_Type gs_type = GAME_STATE;

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


		virtual void Pause() { pause = true; };
		virtual void Resume() { pause = false; };
	};

	class Engine {
	private:
		std::stack<std::unique_ptr<State>> state_stack;

		std::stack<std::unique_ptr<State>> transit_stack;
		std::unique_ptr<State> new_state;
		GS_ID status = INPRO;
		bool restart = false;
		int StateCount = 0;


	public:
		Engine();
		~Engine();

		void AddState(std::unique_ptr<State> toAdd, GS_ID stat = ADD);
		void ProcessStateChange();
		void ProcessTransitState();
		void Update();
		void CleanUp();
		//Getters
		std::unique_ptr<State>& GetCurrent();
		int GetStateCount();
		bool CheckHaveState();
		GS_ID GetStatus();

		//Setters
		void SetStatus(GS_ID, bool restart = false);
	};

}
