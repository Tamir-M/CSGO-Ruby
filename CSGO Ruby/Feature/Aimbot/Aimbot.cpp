#include "Aimbot.h"

float getDistance(uintptr_t* player, uintptr_t* entity) {
	Vec3* playerPos = (Vec3*)(*(uintptr_t*)player + m_vecOrigin);
	Vec3* entityPos = (Vec3*)(*(uintptr_t*)entity + m_vecOrigin);

	Vec3 delta = Vec3(entityPos->x - playerPos->x, entityPos->y - playerPos->y, entityPos->z - playerPos->z);

	return sqrt(pow(delta.x, 2) + pow(delta.y, 2) + pow(delta.z, 2));
}

uintptr_t* Aimbot::GetClosestEnemy() {
	float closestDistance = 10000;
	int closestDistanceIndex = -1;
	int localPlayerTeam = *(uintptr_t*)(localPlayer + m_iTeamNum);

	for (unsigned short int i = 1; i < 64; ++i) {
		uintptr_t entity = *(uintptr_t*)(clientModule + dwEntityList + (i * 0x10));

		if (entity == NULL) break;
		if (entity == localPlayer) continue;

		int entityTeam = *(uintptr_t*)(entity + m_iTeamNum);

		if (entityTeam == localPlayerTeam) continue;

		int entityHealth = *(uintptr_t*)(entity + m_iHealth);

		if (entityHealth < 1) continue;

		float currentDistance = getDistance(&localPlayer, &entity);

		if (currentDistance < closestDistance) {
			closestDistance = currentDistance;
			closestDistanceIndex = i;
		}
	}

	if (closestDistanceIndex == -1) return NULL;
	return (uintptr_t*)(clientModule + dwEntityList + (closestDistanceIndex * 0x10));
}

void Aimbot::AimAt(Vec3* target) {
	Vec3* viewAngles = (Vec3*)(*(uintptr_t*)(engineModule + dwClientState) + dwClientState_ViewAngles);

	Vec3 localPlayerPos = *(Vec3*)(*(uintptr_t*)&localPlayer + m_vecOrigin);
	Vec3 playerViewOffset = *(Vec3*)(*(uintptr_t*)&localPlayer + m_vecViewOffset);
	Vec3* myPos = &(localPlayerPos.add(playerViewOffset));

	Vec3 deltaVec = { target->x - myPos->x, target->y - myPos->y, target->z - myPos->z };
	float deltaVecLength = sqrt(pow(deltaVec.x, 2) + pow(deltaVec.y, 2) + pow(deltaVec.z, 2));

	float pitch = -asin(deltaVec.z / deltaVecLength) * (180 / PI);
	float yaw = atan2(deltaVec.y, deltaVec.x) * (180 / PI);


	if (pitch >= -89 && pitch <= 89 && yaw >= -180 && yaw <= 180) {
		viewAngles->x = pitch;
		viewAngles->y = yaw;
	}
}

Vec3* GetBonePos(uintptr_t* entity, int boneID) {
	uintptr_t boneMatrix = *(uintptr_t*)(*(uintptr_t*)entity + m_dwBoneMatrix);
	static Vec3 bonePos;
	bonePos.x = *(float*)(boneMatrix + 0x30 * boneID + 0x0C);
	bonePos.y = *(float*)(boneMatrix + 0x30 * boneID + 0x1C);
	bonePos.z = *(float*)(boneMatrix + 0x30 * boneID + 0x2C);
	return &bonePos;
}

void Aimbot::Run() {
	if (!this->isActive) return;

	int playerHealth = *(uintptr_t*)(localPlayer + m_iHealth);
	if (playerHealth < 1) return;

	uintptr_t* closestEnemy = GetClosestEnemy();

	if (closestEnemy != NULL)
		this->AimAt(GetBonePos(closestEnemy, 8));
}