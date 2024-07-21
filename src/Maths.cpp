#include <cmath>
#include "Maths.h"

Vec3::Vec3() : x(0), y(0), z(0) {}

Vec3::Vec3(float x, float y, float z) : x(x), y(y), z(z) {}

Vec3 Vec3::operator+(const Vec3& other) const {
  return Vec3(x + other.x, y + other.y, z + other.z);
}

Vec3 Vec3::operator-(const Vec3& other) const {
  return Vec3(x - other.x, y - other.y, z - other.z);
}

Vec3 Vec3::operator*(float scalar) const {
  return Vec3(x * scalar, y * scalar, z * scalar);
}

float Vec3::dot(const Vec3& other) const {
  return x * other.x + y * other.y + z * other.z;
}

Vec3 Vec3::cross(const Vec3& other) const {
  return Vec3(
    y * other.z - z * other.y,
    z * other.x - x * other.z,
    x * other.y - y * other.x
  );
}

float Vec3::length() const {
  return std::sqrt(x * x + y * y + z * z);
}

Vec3 Vec3::normalize() const {
  float len = length();
  return Vec3(x / len, y / len, z / len);
}

Transform4f::Transform4f() {
  for (int i = 0; i < 4; ++i)
    for (int j = 0; j < 4; ++j)
      m[i][j] = 0.0f;
}

Transform4f Transform4f::identity() {
  Transform4f result;
  for (int i = 0; i < 4; ++i)
    result.m[i][i] = 1.0f;
  return result;
}

Transform4f Transform4f::translation(float x, float y, float z) {
  Transform4f result = identity();
  result.m[0][3] = x;
  result.m[1][3] = y;
  result.m[2][3] = z;
  return result;
}

Transform4f Transform4f::rotationX(float angle) {
  Transform4f result = identity();
  float c = std::cos(angle);
  float s = std::sin(angle);
  result.m[1][1] = c;
  result.m[1][2] = -s;
  result.m[2][1] = s;
  result.m[2][2] = c;
  return result;
}

Transform4f Transform4f::rotationY(float angle) {
  Transform4f result = identity();
  float c = std::cos(angle);
  float s = std::sin(angle);
  result.m[0][0] = c;
  result.m[0][2] = s;
  result.m[2][0] = -s;
  result.m[2][2] = c;
  return result;
}

Transform4f Transform4f::rotationZ(float angle) {
  Transform4f result = identity();
  float c = std::cos(angle);
  float s = std::sin(angle);
  result.m[0][0] = c;
  result.m[0][1] = -s;
  result.m[1][0] = s;
  result.m[1][1] = c;
  return result;
}

Transform4f Transform4f::perspective(float fov, float aspect, float zNear, float zFar) {
  Transform4f result;
  float tanHalfFov = std::tan(fov / 2.0f);
  result.m[0][0] = 1.0f / (aspect * tanHalfFov);
  result.m[1][1] = 1.0f / tanHalfFov;
  result.m[2][2] = -(zFar + zNear) / (zFar - zNear);
  result.m[2][3] = -2.0f * zFar * zNear / (zFar - zNear);
  result.m[3][2] = -1.0f;
  return result;
}

Transform4f Transform4f::lookat(Vec3 origin, Vec3 target, Vec3 up) {
  Vec3 zaxis = (origin - target).normalize();
  Vec3 xaxis = up.cross(zaxis).normalize();
  Vec3 yaxis = zaxis.cross(xaxis);

  Transform4f result = Transform4f::identity();

  result.m[0][0] = xaxis.x;
  result.m[0][1] = xaxis.y;
  result.m[0][2] = xaxis.z;
  result.m[0][3] = -xaxis.dot(origin);

  result.m[1][0] = yaxis.x;
  result.m[1][1] = yaxis.y;
  result.m[1][2] = yaxis.z;
  result.m[1][3] = -yaxis.dot(origin);

  result.m[2][0] = zaxis.x;
  result.m[2][1] = zaxis.y;
  result.m[2][2] = zaxis.z;
  result.m[2][3] = -zaxis.dot(origin);

  return result;
}

Vec3 Transform4f::operator*(const Vec3& v) const {
  Vec3 result;
  result.x = m[0][0] * v.x + m[0][1] * v.y + m[0][2] * v.z + m[0][3];
  result.y = m[1][0] * v.x + m[1][1] * v.y + m[1][2] * v.z + m[1][3];
  result.z = m[2][0] * v.x + m[2][1] * v.y + m[2][2] * v.z + m[2][3];
  float w = m[3][0] * v.x + m[3][1] * v.y + m[3][2] * v.z + m[3][3];
  if (w != 0.0f) {
    result.x /= w;
    result.y /= w;
    result.z /= w;
  }
  return result;
}

Transform4f Transform4f::operator*(const Transform4f& other) const {
  Transform4f result;
  for (int i = 0; i < 4; ++i) {
    for (int j = 0; j < 4; ++j) {
      result.m[i][j] = 0;
      for (int k = 0; k < 4; ++k) {
        result.m[i][j] += m[i][k] * other.m[k][j];
      }
    }
  }
  return result;
}