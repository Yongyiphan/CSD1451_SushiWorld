#include "AEEngine.h"
#include <iostream>
#include <vector>

namespace GM{
	class GameState {

	protected: 
		GameState() {};
		GameState(std::string Name) {
			this->Name = Name;
			IsRunning = false;
		}

		std::string Name;
		bool IsRunning = false;


	public:
		GameState();
		virtual void Init();
		virtual void Exit();
		virtual void Update();
		virtual void Draw();

	};



	class GameEngine {

	public:
		GameEngine() {};
		void Init() {
			this->IsRunning = true;
		}
		void Exit() {
			this->IsRunning = false;
		};

		void ChangeState(GameState* state);
		void PushState(GameState* state);
		void PopState(GameState* state);


		GameState *GetState() { return this->currentState; };
		
		void ChangeState(GameState* state) {
			this->currentState = state;
		}

		void PushState(GameState* state) {
			this->states.push_back(state);
		}

		void PopState(GameState* state) {
			this->states.pop_back();
		}

		


	private:
		std::vector<GameState*> states;
		GameState *currentState;
		bool IsRunning = false;
		

	};

	GameState::GameState()
	{
	}

}


namespace Game {

	class MainMenu : GM::GameState {
	private:

	public:
		MainMenu() {};

		void Init() {

		}
		void Update() {
			while (this->IsRunning) {

			}

		}

		void Exit() {

		}
	};



}
