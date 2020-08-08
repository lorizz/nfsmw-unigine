#include "Vehicle.h"
#include <UnigineConsole.h>
#include <UnigineInput.h>
#include <UnigineString.h>
REGISTER_COMPONENT(Vehicle);

void Vehicle::generateWheels()
{
	const char *path = String::format("../data/vehicles/%s/%swheel.fbx/%swheel.mesh", vehicleId.get(), vehicleId.get(), vehicleId.get()).get();
	MeshPtr meshWheel = Mesh::create();
	ObjectMeshStaticPtr oms;
	if (!meshWheel->load(path))
	{
		Log::error("\nError opening .mesh file!\n");
		meshWheel.clear();
	}
	else
	{
		wheel_rf = ObjectMeshStatic::create(meshWheel);
		wheel_rf->setMaterial("mesh_base", "*");
		wheel_rf->setName("wheel_rf");
		node->addChild(wheel_rf);
		wheel_rf->setPosition(Vec3(-wheelLeftFrontPos.get().x, wheelLeftFrontPos.get().y, wheelLeftFrontPos.get().z));
		wheel_rf->setRotation(Math::quat(0.0f, 0.0f, -90.0f));

		ShapeCylinderPtr wheel_rf_col = ShapeCylinder::create();
		wheel_rf_col->setRadius(0.30668f);
		wheel_rf_col->setHeight(0.19606f);
		wheel_rf_col->setPosition(Vec3(0.72f, 1.25f, 0.15f));
		//Mat4 transMatrix = (Mat4)translate(Vec3(0.72f, 1.25f, 0.15f));
		Mat4 rotMatrix = (Mat4)rotateY(90.0f);
		Mat4 transform = rotMatrix * wheel_rf_col->getTransform();
		wheel_rf_col->setTransform(transform);
		mesh->getBodyRigid()->addShape(wheel_rf_col);

		//wheel_rf_col->setPosition();
		//wheel_rf_col->setTransform(Mat4(Math::quat(0.0f, 90.0f, 0.0f), Vec3(-wheelLeftFrontPos.get().x + 0.1f, wheelLeftFrontPos.get().y, wheelLeftFrontPos.get().z)));
		/*ShapeCylinderPtr wheelCol = ShapeCylinder::create();
		wheelCol->setPosition(Vec3(0.0f, -0.105f, 0.0f));
		wheelCol->setRadius(0.315f);
		wheelCol->setHeight(0.205f);
		wheel_rf = ObjectMeshStatic::create(mesh);
		wheel_rf->setMaterial("mesh_base", "*");
		wheel_rf->setName("wheel_rf");
		node->addChild(wheel_rf);
		wheel_rf->setPosition(Vec3(-wheelLeftFrontPos.get().x, wheelLeftFrontPos.get().y, wheelLeftFrontPos.get().z));
		wheel_rf->setRotation(Math::quat(0.0f, 0.0f, -90.0f));
		BodyRigid::create(wheel_rf);
		wheel_rf->getBodyRigid()->addShape(wheelCol);
		wheel_rf->getBodyRigid()->getShape(0)->setCollisionMask(0);*/
	}
}

void Vehicle::init()
{
	mesh = checked_ptr_cast<ObjectMeshStatic>(node);
	mesh->setBody(BodyRigid::create());
	ShapeConvex::create(mesh->getBodyRigid(), mesh, 0);
	mesh->getBodyRigid()->getShape(0)->setName("chassis_col");
	mesh->getBodyRigid()->getShape(0)->setMass(1000.0f);

	Vehicle::generateWheels();
	
	/*wheel_lf = ObjectMeshDynamic::create("../data/vehicles/rx7/rx7wheel.fbx/rx7wheel.mesh");
	wheel_lf->setPosition(wheelLeftFrontPos);
	wheel_lf->setRotation(Math::quat(0.0f, 0.0f, 90.0f));
	BodyRigidPtr wheelLfBody = BodyRigid::create(wheel_lf);
	node->addChild(wheel_lf);*/


	//wheel_lf->setPosition(wheelLeftFrontPos);
	//wheel_lr->setPosition(wheelLeftRearPos);

	Log::message("Init vehicle %s\n", vehicleDisplayName.get());

}

void Vehicle::update()
{
	/*float throttle = Input::isKeyPressed(Input::KEY_O) ? 1.0f : (Input::isKeyPressed(Input::KEY_P) ? -1.0f : 0.0f);
	Vec3 fTraction = node->getDirection(Math::AXIS_Y) * throttle;
	Vec3 finalForce = (fTraction) * Game::getIFps();
	node->getObjectBodyRigid()->setLinearVelocity(node->getObjectBodyRigid()->getLinearVelocity() + finalForce);*/
}

void Vehicle::shutdown()
{

}