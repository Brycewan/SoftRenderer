#pragma once

#include "Maths.h"

class Camera {
public:
  Vec3 position;
  Vec3 target;
  Vec3 up;
  float fov;
  float aspect;
  float zNear;
  float zFar;

  Camera(Vec3 pos = Vec3(0.0f, 0.0f, 3.0f),
    Vec3 tar = Vec3(0.0f, 0.0f, 0.0f),
    Vec3 upVec = Vec3(0.0f, 1.0f, 0.0f),
    float fovAngle = 45.0f,
    float aspectRatio = 1.0f / 1.0f,
    float nearPlane = 0.1f,
    float farPlane = 100.0f)
    : position(pos), 
      target(tar), 
      up(upVec), 
      fov(fovAngle), 
      aspect(aspectRatio), 
      zNear(nearPlane), 
      zFar(farPlane) {}

  Transform4f getViewMatrix() const;
  Transform4f getProjectionMatrix() const;
};