#include "Scene.h"

//Scene::Scene() {
//  camera = nullptr;
//}

Scene::Scene(Camera* c) {
  camera = c;
}

void Scene::setCamera(Camera* c) {
  camera = c;
}

void Scene::addObject(Object* obj) {
  objects.push_back(obj);
}

void Scene::addLight(Light* light) {
  lights.push_back(light);
}

void Scene::setTransformationMatrix() {
  view_transform = camera->getViewMatrix();
  projection_transform = camera->getProjectionMatrix();
}
