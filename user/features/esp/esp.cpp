#include "pch-il2cpp.h"

#include <iostream>
#include "ClientHelper.h"
#include "UnityEngine/Engine.hpp"
#include "players/players.h"
#include "helpers.h"
#include "esp.hpp"

static void DrawBox(float x, float y, float w, float h, ImColor color, float thickness)
{
	auto drawlist = ImGui::GetBackgroundDrawList();

	drawlist->AddLine(ImVec2{ x, y }, ImVec2{ x + w, y }, color, thickness);
	drawlist->AddLine(ImVec2{ x, y }, ImVec2{ x, y + h }, color, thickness);
	drawlist->AddLine(ImVec2{ x + w, y }, ImVec2{ x + w, y + h }, color, thickness);
	drawlist->AddLine(ImVec2{ x, y + h }, ImVec2{ x + w, y + h}, color, thickness);
}

static void DrawString(ImVec2 pos, ImColor color, std::string label)
{
	auto drawlist = ImGui::GetBackgroundDrawList();

	drawlist->AddText(pos, color, label.c_str());
}

static void DrawBoxESP(app::GameObject *it, float footOffset, float headOffset, std::string name, ImColor color, bool snapline = false, bool esp = false, float nameOffset = -0.5f, float widthOffset = 2.0f)
{
	ImGuiIO& io = ImGui::GetIO();
	app::Camera* cam = app::Camera_get_main(nullptr);
	if (!it || cam == nullptr)
		return;

	app::Transform* _transform = Transform::Get(it);
	if (_transform == nullptr)
		return;
		
	app::Vector3 pos = Transform::Position(_transform);

	app::Vector3 footpos = app::Camera_WorldToScreenPoint_1(cam, app::Vector3{pos.x, pos.y + footOffset, pos.z}, NULL);
	app::Vector3 headpos = app::Camera_WorldToScreenPoint_1(cam, app::Vector3{pos.x, pos.y + headOffset, pos.z}, NULL);
	app::Vector3 namepos = app::Camera_WorldToScreenPoint_1(cam, app::Vector3{pos.x, pos.y + nameOffset, pos.z}, NULL);

	if (esp && footpos.z > 0.0f) {
		float height = (headpos.y - footpos.y);
		float width = height / widthOffset;

		DrawBox(footpos.x - (width / 2), (float)io.DisplaySize.y - footpos.y - height, width, height, color, 2.0f);
		DrawString(ImVec2(namepos.x, (float)io.DisplaySize.y - namepos.y), color, name);
	}

	if (snapline && footpos.z > 0.f) {
		auto drawlist = ImGui::GetBackgroundDrawList();
		drawlist->AddLine(ImVec2(io.DisplaySize.x / 2, io.DisplaySize.y / 2), ImVec2(footpos.x, io.DisplaySize.y - footpos.y), color, 2.f);
	}
}

void ESP::RunPlayersESP() {
	app::GameObject__Array* players = Players::GetAllPlayers();

	if (players == NULL)
		return;

	for (int i = 0; i < players->max_length; i++) {
		app::GameObject* ent = players->vector[i];

		if (ent == nullptr || ent == Player::GetLocalPlayer())
			continue;
	
		DrawBoxESP(ent, -0.25, 1.75, "Player", ImColor{settings::player_esp_color[0], settings::player_esp_color[1], settings::player_esp_color[2], settings::player_esp_color[3]}, settings::player_snaplines, settings::player_esp);
	}
}