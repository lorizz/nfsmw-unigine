#include "Vehicle.h"
#include <UnigineConsole.h>
#include <UnigineInput.h>
REGISTER_COMPONENT(Vehicle);

void Vehicle::init()
{
	Log::message("Init vehicle %s\n", vehicleName.get());
}

void Vehicle::update()
{
	float throttle = Input::isKeyPressed(Input::KEY_O) ? 1.0f : (Input::isKeyPressed(Input::KEY_P) ? -1.0f : 0.0f);
	Vec3 fGravity = node->getWorldDirection(Math::AXIS_NZ) * 9.81f;
	Vec3 fTraction = node->getDirection(Math::AXIS_Y) * throttle;
	Vec3 finalForce = (fGravity) * Game::getIFps();
	node->getObjectBodyRigid()->setLinearVelocity(node->getObjectBodyRigid()->getLinearVelocity() + finalForce);
}

void Vehicle::shutdown()
{

}