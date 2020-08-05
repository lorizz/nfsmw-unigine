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

	PROP_PARAM(String, vehicleName, "Vehicle1");
protected:
	void init();
	void update();
	void shutdown();

private:
	ControlsPtr controls;

};

