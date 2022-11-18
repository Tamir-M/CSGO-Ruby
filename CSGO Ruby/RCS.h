#include "Feature.h"
#include "Vector.h"

class RCS : public Feature
{
public:
	using Feature::Feature;
	void Init(); // Constructor called when injected, and won't have engine/localPlayer values.
	void Run();
private:
	Vec3* viewAngles;
	int* iShotsFired;
	Vec3* aimPunchAngle;
	Vec3 oPunch;
};
