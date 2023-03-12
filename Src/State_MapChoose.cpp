#include "pch.h"
#include "State_MapChoose.h"
MapChooseScreen::MapChooseScreen(const std::shared_ptr<Context>&context) {
	StateName = "MapChooseScreen";
	m_context = context;
	//IMPORTANT
	gs_type = TRANSIT_STATE;
	

}

void MapChooseScreen::Load() {
	FontID = m_context->assets->GetFont("./Assets/Font/roboto/Roboto-Bold.ttf", 100);
	//Resume Button
}
void MapChooseScreen::Unload(){
}

void MapChooseScreen::Init() {
	u32 grey = utils::RGBAtoHex(110, 110, 110);
	BGBlur.t = AM::Transform(
		wosx, wosy,
		winw, winh
	);
	BGBlur.gfx.transparency = 0.5f;
	float ChoiceWidth = 150, ChoiceHeight = 300;
	ChoiceA.t = AM::Transform(
		winw / 3.f, wosy,
		ChoiceWidth, ChoiceHeight
	);
	ChoiceA.gfx.Color = grey;

	ChoiceB.t = AM::Transform(
		2 * winw / 3.f, wosy,
		ChoiceWidth, ChoiceHeight
	);
	ChoiceB.gfx.Color = grey;
	srand(static_cast<unsigned int>(time(NULL)));
	GenerateRoomChoice();
	std::cout << "Init " << StateName << std::endl;
}

void MapChooseScreen::Free() {
	std::cout << "Free " << StateName << std::endl;
}

void MapChooseScreen::Update(f64 deltaTime) {
	AEInputGetCursorPosition(&mousex, &mousey);
	
	//if (AEInputCheckTriggered(AEVK_ESCAPE)) {
	//	m_context->gman->SetStatus(RESUME);
	//}

	if (AEInputCheckTriggered(AEVK_LBUTTON)) {
		AEInputGetCursorPosition(&mousex, &mousey);
		if (utils::AreaClicked(&ChoiceA.t, mousex, mousey)) {
			Redirect(RoomA);
		}
		if (utils::AreaClicked(&ChoiceB.t, mousex, mousey)) {
			Redirect(RoomB);
		}
	}

}



void MapChooseScreen::Draw() {
	utils::UDrawText(FontID, "Choose Room Type to Enter", f32(wosx), winh * 0.8f, 0.3f, AM::Color(0,0,0));
	m_context->render->RenderMesh(&BGBlur);
	utils::UDrawButton(m_context->render, &ChoiceA, FontID, GM::RoomNames.at(RoomA), AM::Color(0, 0, 0), 0, 0, 0.15f);
	utils::UDrawButton(m_context->render, &ChoiceB, FontID, GM::RoomNames.at(RoomB), AM::Color(0, 0, 0), 0, 0, 0.15f);
	
	
}


void MapChooseScreen::Redirect(RoomMap Selection) {
	switch(Selection){
	case ARROW:
		m_context->gman->AddState(std::make_unique<ArrowMap>(m_context));
		break;
	case PLATFORM:
		m_context->gman->AddState(std::make_unique<PlatformMap>(m_context));
		break;
	case REST:
		m_context->gman->AddState(std::make_unique<RestState>(m_context));
		break;
	case SHOP:
		m_context->gman->AddState(std::make_unique<Shop>(m_context));
		break;
	}
	m_context->RT->ExplorableRooms.at(Selection)--;
	m_context->RT->ExploredRooms.at(Selection)++;
		
	if (m_context->RT->cRoom == m_context->RT->TotalRoom - 1) {
		m_context->GameClear = true;
	}
}

void MapChooseScreen::GenerateRoomChoice() {

	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis(0, GM::TotalRooms);

	std::vector<RoomMap> choices;
	while (choices.size() < 2) {
		RoomMap choice = RoomMap(dis(gen));
		if (m_context->RT->ExplorableRooms.at(choice) == 1) {
			if (std::find(choices.begin(), choices.end(), choice) == choices.end()) {
				choices.emplace_back(choice);
			}

		}
	}
	RoomA = choices[0];
	RoomB = choices[1];
}
