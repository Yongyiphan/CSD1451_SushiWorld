#include "pch.h"
#include "MainField.h"


MainField::MainField(char const* Name, std::shared_ptr<Context>& context) {
	StateName = Name;
	m_context = context;

}
MainField::~MainField() {};
void MainField::Load() {};
void MainField::Unload() {};
void MainField::Init() {};
void MainField::Free() {};
void MainField::Update(f64 dt) {};
void MainField::Draw() {
	

};
