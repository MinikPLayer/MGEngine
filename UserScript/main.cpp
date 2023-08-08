#include <Engine.h>
#include <GameObject.h>
#include <Log.h>
#include <Mesh.h>
#include <TimeUtils.h>

#include "Camera.h"
#include "TestObject.h"

int main() {
	Engine::Init();
	GameObject::Instantiate(new TestObject());
	Engine::Run();
}