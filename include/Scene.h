#pragma once

#include <vector>
#include "Camera.h"
#include "Object.h"
#include "Light.h"

class Scene {
private:
  Camera* camera;
  std::vector<Light*> lights;
  std::vector<Object*> objects;
public:
};