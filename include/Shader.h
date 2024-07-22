#pragma once

#include "Scene.h"
#include "Framebuffer.h"

class Shader {
public:
  void wireframe(Scene* scene, Framebuffer& framebuffer) const;
  void direct(Scene* scene, Framebuffer& framebuffer) const;
};