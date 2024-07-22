#include "Camera.h"

Transform4f Camera::getViewMatrix() const {
  return Transform4f::lookat(position, target, up);
}

Transform4f Camera::getProjectionMatrix() const {
  return Transform4f::perspective(fov, aspect, zNear, zFar);
}