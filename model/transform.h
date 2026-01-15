#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <vector>

#include "../common/vertex.h"

/**
 * @file transform.h
 */

namespace s21 {

/**
 * @class ITransform
 *
 * @brief Abstract class for transformations
 *
 * @details Classic form of using `Strategy` pattern, abstract class that
 * represents transformation itself and different strategies for different
 * transformations
 */
class ITransform {
 public:
  virtual void Transform(std::vector<Vertex>& vertexes, const float number) = 0;
  virtual ~ITransform() = default;
};
/**
 * @class RotateX
 */
class RotateX : public ITransform {
  /**
   * @brief Rotates model around X axis
   * @param vertexes reference to vertexes array from `Model`
   * @param number degree by wich to rotate
   */
  void Transform(std::vector<Vertex>& vertexes, const float number) override;
};
/**
 * @class RotateY
 */
class RotateY : public ITransform {
  /**
   * @brief Rotates model around Y axis
   * @param vertexes reference to vertexes array from `Model`
   * @param number degree by wich to rotate
   */
  void Transform(std::vector<Vertex>& vertexes, const float number) override;
};
/**
 * @class RotateZ
 */
class RotateZ : public ITransform {
  /**
   * @brief Rotates model around Z axis
   * @param vertexes reference to vertexes array from `Model`
   * @param number degree by wich to rotate
   */
  void Transform(std::vector<Vertex>& vertexes, const float number) override;
};
/**
 * @class MoveX
 */
class MoveX : public ITransform {
  /**
   * @brief Moves the model along the X axis
   * @param vertexes reference to vertexes array from `Model`
   * @param number value by wich to move
   */
  void Transform(std::vector<Vertex>& vertexes, const float number) override;
};
/**
 * @class MoveY
 */
class MoveY : public ITransform {
  /**
   * @brief Moves the model along the Y axis
   * @param vertexes reference to vertexes array from `Model`
   * @param number value by wich to move
   */
  void Transform(std::vector<Vertex>& vertexes, const float number) override;
};
/**
 * @class MoveZ
 */
class MoveZ : public ITransform {
  /**
   * @brief Moves the model along the Z axis
   * @param vertexes reference to vertexes array from `Model`
   * @param number value by wich to move
   */
  void Transform(std::vector<Vertex>& vertexes, const float number) override;
};
/**
 * @class Resize
 */
class Resize : public ITransform {
  /**
   * @brief Scales the model
   * @param vertexes reference to vertexes array from `Model`
   * @param number value by wich to scale
   */
  void Transform(std::vector<Vertex>& vertexes, const float number) override;
};

}  // namespace s21

#endif  // TRANSFORM_H
