#include "Shader.h"
#include "Maths.h"

// Helper function to clip against a single plane
static bool clipLine(float d0, float d1, Vec3& v0, Vec3& v1) {
  if (d0 >= 0 && d1 >= 0) return false;
  if (d0 < 0 && d1 < 0) return true;
  float t = d0 / (d0 - d1);
  if (d0 < 0) v0 = v0 + t * (v1 - v0);
  else v1 = v0 + t * (v1 - v0);
  return false;
}

// Clip against the six frustum planes
static bool clipTriangle(Vec3& v0, Vec3& v1, Vec3& v2) {
  if (clipLine(v0.x + v0.z, v1.x + v1.z, v0, v1) ||
    clipLine(v0.x + v0.z, v2.x + v0.z, v0, v2) ||
    clipLine(v1.x + v1.z, v2.x + v1.z, v1, v2) ||
    clipLine(v0.x - v0.z, v1.x - v0.z, v0, v1) ||
    clipLine(v0.x - v0.z, v2.x - v0.z, v0, v2) ||
    clipLine(v1.x - v1.z, v2.x - v1.z, v1, v2) ||
    clipLine(v0.y + v0.z, v1.y + v1.z, v0, v1) ||
    clipLine(v0.y + v0.z, v2.y + v0.z, v0, v2) ||
    clipLine(v1.y + v1.z, v2.y + v1.z, v1, v2) ||
    clipLine(v0.y - v0.z, v1.y - v0.z, v0, v1) ||
    clipLine(v0.y - v0.z, v2.y - v0.z, v0, v2) ||
    clipLine(v1.y - v1.z, v2.y - v1.z, v1, v2) ||
    clipLine(v0.z, v1.z, v0, v1) ||
    clipLine(v0.z, v2.z, v0, v2) ||
    clipLine(v1.z, v2.z, v1, v2)) {
    return true;
  }
  return false;
}

void Shader::wireframe(Scene* scene, Framebuffer& framebuffer) const {
  // MVP transformation
  scene->setTransformationMatrix();
  Transform4f vp = scene->projection_transform * scene->view_transform;
  for (auto obj : scene->objects) {
    const std::vector<Vertex>& vertices = obj->VBO;

    for (size_t i = 0; i < vertices.size(); i += 3) {
      Vec3 v0 = vertices[i].pos;
      Vec3 v1 = vertices[i + 1].pos;
      Vec3 v2 = vertices[i + 2].pos;

      // Transform vertices by the MVP matrix
      Vec3 p0 = vp * scene->model_transform * v0;
      Vec3 p1 = vp * scene->model_transform * v1;
      Vec3 p2 = vp * scene->model_transform * v2;

      // clipping
      if (clipTriangle(p0, p1, p2)) continue;

      // Convert to screen space
      int width = framebuffer.getWidth();
      int height = framebuffer.getHeight();
      p0.x = (p0.x / p0.z + 1) * 0.5f * width;
      p0.y = (1 - p0.y / p0.z) * 0.5f * height;
      p1.x = (p1.x / p1.z + 1) * 0.5f * width;
      p1.y = (1 - p1.y / p1.z) * 0.5f * height;
      p2.x = (p2.x / p2.z + 1) * 0.5f * width;
      p2.y = (1 - p2.y / p2.z) * 0.5f * height;

      // Draw lines between the vertices
      framebuffer.drawLineBresenham(p0.x, p0.y, p1.x, p1.y, 0xFFFFFF);
      framebuffer.drawLineBresenham(p1.x, p1.y, p2.x, p2.y, 0xFFFFFF);
      framebuffer.drawLineBresenham(p2.x, p2.y, p0.x, p0.y, 0xFFFFFF);
    }
  }
}


void Shader::direct(Scene* scene, Framebuffer& framebuffer) const {
  // MVP transformation

  // clipping
}