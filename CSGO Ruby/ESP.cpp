#include "ESP.h"

void ESP::Init() {
	entList = (EntList*)(clientModule + dwEntityList);
	localEnt = entList->ents[0].ent;
}

void ESP::Run() {
	memcpy(&viewMatrix, (PBYTE*)(clientModule + dwViewMatrix), sizeof(viewMatrix));
}

bool ESP::CheckValidEnt(Ent* ent) {
	if (ent == nullptr) return false;
	if (ent == localEnt) return false;
	if (ent->iHealth <= 0) return false;
	if (ent->isDormant) return false;
	return true;
}

bool ESP::WorldToScreen(Vec3 pos, Vec2& screen) {
	Vec4 clipCoords;
	clipCoords.x = pos.x * viewMatrix[0] + pos.y * viewMatrix[1] + pos.z * viewMatrix[2] + viewMatrix[3];
	clipCoords.y = pos.x * viewMatrix[4] + pos.y * viewMatrix[5] + pos.z * viewMatrix[6] + viewMatrix[7];
	clipCoords.z = pos.x * viewMatrix[8] + pos.y * viewMatrix[9] + pos.z * viewMatrix[10] + viewMatrix[11];
	clipCoords.w = pos.x * viewMatrix[12] + pos.y * viewMatrix[13] + pos.z * viewMatrix[14] + viewMatrix[15];

	if (clipCoords.w < 0.1f) return false;

	Vec3 NDC;
	NDC.x = clipCoords.x / clipCoords.w;
	NDC.y = clipCoords.y / clipCoords.w;
	NDC.z = clipCoords.z / clipCoords.w;

	screen.x = (windowWidth / 2 * NDC.x) + (NDC.x + windowWidth / 2);
	screen.y = -(windowHeight / 2 * NDC.y) + (NDC.y + windowHeight / 2);

	return true;
}

void ESP::Draw() {
	if (!this->isActive) return;
	for (int i = 1; i < 32; ++i) {
		Ent* curEnt = this->entList->ents[i].ent;
		if (!this->CheckValidEnt(curEnt)) continue;

		D3DCOLOR color;
		if (curEnt->iTeamNum == this->localEnt->iTeamNum)
			color = D3DCOLOR_ARGB(255, 0, 255, 0);
		else
			color = D3DCOLOR_ARGB(255, 255, 0, 0);


		Vec3 entHead3D = this->GetBonePos(curEnt, 8);
		entHead3D.z += 8;
		Vec2 entPos2D, entHead2D;
		if (this->WorldToScreen(curEnt->vecOrigin, entPos2D)) {
			DrawLine(entPos2D.x, entPos2D.y, static_cast<float>(windowWidth) / 2, static_cast<float>(windowHeight), 2, color);
			
			if (this->WorldToScreen(entHead3D, entHead2D)) {
				DrawESPBox2D(entPos2D, entHead2D, 2, color);
				
				int height = ABS(entPos2D.y - entHead2D.y);
				int dX = (entPos2D.x - entHead2D.x);

				float healthPerc = curEnt->iHealth / 100.f;
				float armorPerc = curEnt->armorValue / 100.f;

				Vec2 botHealth, topHealth, botArmor, topArmor;
				int healthHeight = height * healthPerc;
				int armorHeight = height * armorPerc;

				botHealth.y = botArmor.y = entPos2D.y;

				botHealth.x = entPos2D.x - (height / 4) - 2;
				botArmor.x = entPos2D.x + (height / 4) + 2;

				topHealth.y = entHead2D.y + height - healthHeight;
				topArmor.y = entHead2D.y + height - armorHeight;

				topHealth.x = entPos2D.x - (height / 4) - 2 - (dX * healthPerc);
				topArmor.x = entPos2D.x + (height / 4) + 2 - (dX * armorPerc);
				
				DrawLine(botHealth, topHealth, 5, D3DCOLOR_ARGB(255, 46, 139, 87));
				DrawLine(botArmor, topArmor, 5, D3DCOLOR_ARGB(255, 30, 144, 255));
			}
		}
	}
}

Vec3 ESP::GetBonePos(Ent* ent, int bone) {
	uintptr_t bonePtr = ent->boneMatrix;
	Vec3 bonePos;
	bonePos.x = *(float*)(bonePtr + 0x30 * bone + 0x0C);
	bonePos.y = *(float*)(bonePtr + 0x30 * bone + 0x1C);
	bonePos.z = *(float*)(bonePtr + 0x30 * bone + 0x2C);
	return bonePos;
}
