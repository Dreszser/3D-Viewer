#ifndef VERTEX_H
#define VERTEX_H

/**
 * @file vertex.h
 */

namespace s21 {

/**
 * @class Vertex
 *
 * @brief Represents a vertex in the model
 */
class Vertex {
 public:
  float x; /**< an float value for x coordinate */
  float y; /**< an float value for y coordinate */
  float z; /**< an float value for z coordinate */

  Vertex() = delete;
  ~Vertex() = default;
  Vertex(float new_x, float new_y, float new_z);
};

}  // namespace s21

#endif  // VERTEX_H
