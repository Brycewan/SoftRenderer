#pragma once

#include "Scene.h"
#include "Framebuffer.h"

class Shader {
public:
  void direct(Scene* scene, Framebuffer& framebuffer);
};