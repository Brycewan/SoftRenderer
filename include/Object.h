#pragma once

#include <vector>
#include "Maths.h"


class Vertex {
public:
  Vec3 pos;
  unsigned int color;

public:
  Vertex() = default;
  Vertex(Vec3 position, unsigned int col) : pos(position), color(col) {}
};


class Object {
public:
  std::vector<Vertex> VBO;

public:
  Object() = default;
  void addVertex(const Vertex vertex);
};
