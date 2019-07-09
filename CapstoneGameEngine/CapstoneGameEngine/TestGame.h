#pragma once

#include "Object.h"
#include "Update.h" // update types

// Collision behaviour between an otter an another object
// assumption that obj1 is an otter
void otterCollision(Object* otter, Object* obj2);

// Update behaviour between an otter and another object
// update type can be on creation, run time, or on deletion
void otterUpdate(Object* otter, Update::Type t);