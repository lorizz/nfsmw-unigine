#pragma once

#include <UnigineGame.h>
#include <UnigineControls.h>
#include <UnigineComponentSystem.h>

using namespace Unigine;
using namespace Math;

class Vehicle : public ComponentBase
{
public:
	COMPONENT_DEFINE(Vehicle, ComponentBase)

	COMPONENT_INIT(init);
	COMPONENT_UPDATE(update);
	COMPONENT_SHUTDOWN(shutdown);

	PROP_PARAM(String, vehicleId, "veh1");
	PROP_PARAM(String, vehicleDisplayName, "Vehicle1");
	PROP_PARAM(Vec3, wheelLeftFrontPos, Vec3(0.0f));
	PROP_PARAM(Vec3, wheelLeftRearPos, Vec3(0.0f));
protected:
	void init();
	void update();
	void shutdown();

	void generateWheels();

private:
	ControlsPtr controls;
	ObjectMeshStaticPtr mesh;
	ObjectMeshStaticPtr wheel_lf, wheel_rf, wheel_lr, wheel_rr;

};

