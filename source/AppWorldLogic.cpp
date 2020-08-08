/* Copyright (C) 2005-2020, UNIGINE. All rights reserved.
 *
 * This file is a part of the UNIGINE 2 SDK.
 *
 * Your use and / or redistribution of this software in source and / or
 * binary form, with or without modification, is subject to: (i) your
 * ongoing acceptance of and compliance with the terms and conditions of
 * the UNIGINE License Agreement; and (ii) your inclusion of this notice
 * in any version of this software that you use or redistribute.
 * A copy of the UNIGINE License Agreement is available by contacting
 * UNIGINE. at http://unigine.com/
 */


#include "AppWorldLogic.h"
#include <UnigineComponentSystem.h>

// World logic, it takes effect only when the world is loaded.
// These methods are called right after corresponding world script's (UnigineScript) methods.

int AppWorldLogic::addMeshToScene(const char *file_name, const char *mesh_name, const char *material_name, Math::Vec3 position, const char *parent_node = NULL)
{
	MeshPtr mesh = Mesh::create();
	ObjectMeshStaticPtr oms;
	if (file_name)
	{
		if (!mesh->load(file_name))
		{
			Log::error("\nError opening .mesh file!\n");
			mesh.clear();

			return 0;
		}
		else oms = ObjectMeshStatic::create(mesh);
	}
	else
	{
		mesh->addBoxSurface("box_surface", Math::Vec3(0.5f));

		oms = ObjectMeshStatic::create(mesh);
	}

	if (parent_node != NULL)
	{
		if (!World::getNodeByName(parent_node).isValid() || World::getNodeByName(parent_node).isNull())
			Log::error("World node %s is not valid!", parent_node);
		else
		{
			oms->setParent(World::getNodeByName(parent_node));
			Log::warning("Setup parent %s for node %s", parent_node, mesh_name);
		}
	}

	oms->setMaterial(material_name, "*");
	oms->setName(mesh_name);
	oms->setWorldPosition(position);

	objects.append(oms);
	
	Log::message("-> Object %s added to the scene.\n", mesh_name);

	mesh.clear();

	return 1;
}

int AppWorldLogic::initObjects()
{
	addMeshToScene("../data/vehicles/rx7/rx7.fbx/rx7.mesh", "player_vehicle", "mesh_base", Math::Vec3(0.0f, 0.0f, 1.0f));
	playerVehicle = checked_ptr_cast<ObjectMeshStatic>(World::getNodeByName("player_vehicle"));
	playerVehicle->addProperty("VehicleRX7");
	Log::warning("Generated player vehicle!\n");

	return 1;
}

AppWorldLogic::AppWorldLogic()
{
}

AppWorldLogic::~AppWorldLogic()
{
}

int AppWorldLogic::init()
{
	// Write here code to be called on world initialization: initialize resources for your world scene during the world start.
	initObjects();
	return 1;
}

////////////////////////////////////////////////////////////////////////////////
// start of the main loop
////////////////////////////////////////////////////////////////////////////////

int AppWorldLogic::update()
{
	// Write here code to be called before updating each render frame: specify all graphics-related functions you want to be called every frame while your application executes.
	return 1;
}

int AppWorldLogic::postUpdate()
{
	// The engine calls this function after updating each render frame: correct behavior after the state of the node has been updated.
	return 1;
}

int AppWorldLogic::updatePhysics()
{
	// Write here code to be called before updating each physics frame: control physics in your application and put non-rendering calculations.
	// The engine calls updatePhysics() with the fixed rate (60 times per second by default) regardless of the FPS value.
	// WARNING: do not create, delete or change transformations of nodes here, because rendering is already in progress.
	return 1;
}

////////////////////////////////////////////////////////////////////////////////
// end of the main loop
////////////////////////////////////////////////////////////////////////////////

int AppWorldLogic::shutdown()
{
	// Write here code to be called on world shutdown: delete resources that were created during world script execution to avoid memory leaks.
	for (int i = 0; i < objects.size(); i++)
	{
		objects[i].get()->deleteLater();
	}
	objects.clear();
	return 1;
}

int AppWorldLogic::save(const Unigine::StreamPtr &stream)
{
	// Write here code to be called when the world is saving its state (i.e. state_save is called): save custom user data to a file.
	UNIGINE_UNUSED(stream);
	return 1;
}

int AppWorldLogic::restore(const Unigine::StreamPtr &stream)
{
	// Write here code to be called when the world is restoring its state (i.e. state_restore is called): restore custom user data to a file here.
	UNIGINE_UNUSED(stream);
	return 1;
}
