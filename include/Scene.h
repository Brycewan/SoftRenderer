#pragma once

#include <vector>
#include "Camera.h"
#include "Object.h"
#include "Light.h"
#include "Maths.h"

class Scene {
public:
  Camera* camera;
  std::vector<Light*> lights;
  std::vector<Object*> objects;

  Transform4f model_transform;
  Transform4f view_transform;
  Transform4f projection_transform;

public:
  Scene() = default;
  Scene(Camera* c);
  void setCamera(Camera* c);
  void addObject(Object* obj);
  void addLight(Light* light);
  void setTransformationMatrix();
};