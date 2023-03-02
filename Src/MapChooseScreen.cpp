#include "pch.h"
#include "MapChooseScreen.h"
//MapChooseScreen::MapChooseScreen(const std::shared_ptr<Context>&context, int*kek) {
MapChooseScreen::MapChooseScreen(const std::shared_ptr<Context>&context) {
	StateName = "MapChooseScreen";
	m_context = context;
	//IMPORTANT
	gs_type = TRANSIT_STATE;
	

}

void MapChooseScreen::Load() {
	//FontID = *m_context->assets->LoadFont("./Assets/Font/roboto/Roboto-Medium.ttf", 15);
	FontID = m_context->assets->GetFont("./Assets/Font/roboto/Roboto-Medium.ttf", 15);
	//Resume Button
}
void MapChooseScreen::Unload(){
}

void MapChooseScreen::Init() {
	u32 grey = utils::RGBAtoHex(110, 110, 110);
	BGBlur.t = AM::Transform(
		f32(wosx), f32(wosy),
		f32(winw), f32(winh)
	);
	BGBlur.gfx.transparency = 0.5f;
	float ChoiceWidth = 150, ChoiceHeight = 300;
	ChoiceA.t = AM::Transform(
		winw / 3.f, f32(wosy),
		ChoiceWidth, ChoiceHeight
	);
	ChoiceA.gfx.Color = grey;

	ChoiceB.t = AM::Transform(
		2 * winw / 3.f, f32(wosy),
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
	AEInputGetCursorPosition(&mx, &my);
	
	if (AEInputCheckTriggered(AEVK_ESCAPE)) {
		m_context->gman->SetStatus(RESUME);
	}

	if (AEInputCheckTriggered(AEVK_LBUTTON)) {
		AEInputGetCursorPosition(&mx, &my);
		if (utils::AreaClicked(&ChoiceA.t, mx, my)) {
			Redirect(RoomA);
		}
		if (utils::AreaClicked(&ChoiceB.t, mx, my)) {
			Redirect(RoomB);
		}
	}

}



void MapChooseScreen::Draw() {
	utils::UDrawText(FontID, "Choose Room Type to Enter", f32(wosx), winh * 0.8f, 2.f, AM::Color(0,0,0));
	m_context->render->RenderRect(&BGBlur);
	utils::UDrawButton(m_context->render,&ChoiceA, FontID, GM::RoomNames.at(RoomA), AM::Color(0, 0, 0));
	utils::UDrawButton(m_context->render,&ChoiceB, FontID, GM::RoomNames.at(RoomB), AM::Color(0, 0, 0));
	
	
}


void MapChooseScreen::Redirect(RoomMap Selection) {
	switch(Selection){
	case ARROW:
		m_context->gman->AddState(std::make_unique<ArrowMap>(m_context));
		break;
	//case PLATFORM:
	//	m_context->gman->AddState(std::make_unique<PlatformMap>(m_context));
	//	break;
	case REST:
		m_context->gman->AddState(std::make_unique<RestState>(m_context));
		break;
	case SHOP:
		m_context->gman->AddState(std::make_unique<Shop>(m_context));
		break;
	}
	m_context->RT->ExplorableRooms.at(Selection)--;
	m_context->RT->ExploredRooms.at(Selection)++;
}

void MapChooseScreen::GenerateRoomChoice() {

	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis(0, GM::TotalRooms);

	std::vector<RoomMap> choices;
	while (choices.size() < 2) {
		RoomMap choice = RoomMap(dis(gen));
		if (std::find(choices.begin(), choices.end(), choice) == choices.end()) {
			choices.emplace_back(choice);
		}
	}
	RoomA = choices[0];
	RoomB = choices[1];
}
