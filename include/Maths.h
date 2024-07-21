#pragma once

class Vec3 {
public:
  float x, y, z;

public:
  Vec3();
  Vec3(float x, float y, float z);

  Vec3 operator+(const Vec3& other) const;
  Vec3 operator-(const Vec3& other) const;
  Vec3 operator*(float scalar) const;
  float dot(const Vec3& other) const;
  Vec3 cross(const Vec3& other) const;
  float length() const;
  Vec3 normalize() const;
};

class Transform4f {
public:
  float m[4][4];

  Transform4f();
  static Transform4f identity();
  static Transform4f translation(float x, float y, float z);
  static Transform4f rotationX(float angle);
  static Transform4f rotationY(float angle);
  static Transform4f rotationZ(float angle);
  static Transform4f perspective(float fov, float aspect, float zNear, float zFar);
  static Transform4f lookat(Vec3 origin, Vec3 target, Vec3 up);

  Vec3 operator*(const Vec3& v) const;
  Transform4f operator*(const Transform4f& other) const;
};