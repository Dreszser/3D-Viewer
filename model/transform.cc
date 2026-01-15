#include "transform.h"

#include <cmath>
#include <numbers>

/**
 * @file transform.cc
 */

namespace s21 {

void RotateX::Transform(std::vector<Vertex> &vertexes, const float number) {
  float rad = number * std::numbers::pi / 180.0f;
  float cosA = cosf(rad);
  float sinA = sinf(rad);

  for (auto &vertex : vertexes) {
    float y = vertex.y * cosA - vertex.z * sinA;
    float z = vertex.y * sinA + vertex.z * cosA;
    vertex.y = y;
    vertex.z = z;
  }
}

void RotateY::Transform(std::vector<Vertex> &vertexes, const float number) {
  float rad = number * std::numbers::pi / 180.0f;
  float cosA = cosf(rad);
  float sinA = sinf(rad);

  for (auto &vertex : vertexes) {
    float x = vertex.x * cosA + vertex.z * sinA;
    float z = -vertex.x * sinA + vertex.z * cosA;
    vertex.x = x;
    vertex.z = z;
  }
}

void RotateZ::Transform(std::vector<Vertex> &vertexes, const float number) {
  float rad = number * std::numbers::pi / 180.0f;
  float cosA = cosf(rad);
  float sinA = sinf(rad);

  for (auto &vertex : vertexes) {
    float x = vertex.x * cosA - vertex.y * sinA;
    float y = vertex.x * sinA + vertex.y * cosA;
    vertex.x = x;
    vertex.y = y;
  }
}

void MoveX::Transform(std::vector<Vertex> &vertexes, const float number) {
  for (auto &vertex : vertexes) {
    vertex.x += number;
  }
}

void MoveY::Transform(std::vector<Vertex> &vertexes, const float number) {
  for (auto &vertex : vertexes) {
    vertex.y += number;
  }
}

void MoveZ::Transform(std::vector<Vertex> &vertexes, const float number) {
  for (auto &vertex : vertexes) {
    vertex.z += number;
  }
}

void Resize::Transform(std::vector<Vertex> &vertexes, const float number) {
  for (auto &vertex : vertexes) {
    vertex.x *= number;
    vertex.y *= number;
    vertex.z *= number;
  }
}

}  // namespace s21
