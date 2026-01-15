#ifndef FACADE_H
#define FACADE_H

#include "../common/IController.h"
#include "../common/types.h"
#include "model.h"

/**
 * @file facade.h
 */

namespace s21 {

/**
 * @class Facade
 * @brief Represents Model in the MVC, has all important methods available for
 * user
 */
class Facade {
 private:
  Model model_;
  int scale_;
  int moveX_;
  int moveY_;
  int moveZ_;
  int rotateX_;
  int rotateY_;
  int rotateZ_;
  float move_step_;
  float bounding_box_diagonal_;
  IController* controller_;
  float radius_;

 public:
  Facade() = delete;
  Facade(IController& controller);
  ~Facade() = default;

  /**
   * @brief Basic method to get vertexes size
   * @return vertex array size from the ```Model```
   */
  size_t GetVertexesSize();

  /**
   * @brief Basic method to get edges size
   * @return edge array size from the ```Model```
   */
  size_t GetEdgesSize();

  /**
   * @brief Get vertexes array without copying or new objects
   * @return vertexes array from the ```Model```
   */
  std::span<const Vertex> GetVertexes() const;

  /**
   * @brief Get edges array without copying or new objects
   * @return edges array from the ```Model```
   */
  std::span<const Edge> GetEdges() const;

  /**
   * @brief Perform transformation
   *
   * @param transform type of transformation
   * @param num new value for the current transformation
   */
  void Transform(TranformationType transform, int num);

  /**
   * @brief Sets the file name string
   * @param str new file name
   */
  void SetModelName(std::string str);

  /**
   * @brief Gets file name of the currently loaded model
   * @return file name string
   */
  std::string GetModelName();

  /**
   * @brief Calls on parser to read and parse a file
   * @param file_name name of a file to read
   */
  void ReadModel(std::string file_name);

  /**
   * @brief Resets all private fields to default values
   * @details This method is called after loading a new object, to properly
   * adjust all values and correctly perform coming transformations
   */
  void selfReset();

  /**
   * @brief Places the model exactly in its center
   */
  void NormalizeModel();
  /**
   * @brief Calculates two corners of the model's bounding box
   * @param min corner with smallest coordinates
   * @param max corner with biggest coordinates
   */
  void CountBoundingBoxCorners(Vertex& min, Vertex& max);
  /**
   * @brief Moves the model so that its center is exactly in origin
   * @param min bounding box corner with smallest coordinates
   * @param max bounding box corner with biggest coordinates
   */
  void MoveToOrigin(const Vertex& min, const Vertex& max);
  /**
   * @brief Scales object so that it fits into default cube of 1x1
   * @param min bounding box corner with smallest coordinates
   * @param max bounding box corner with biggest coordinates
   */
  void ScaleToFit(const Vertex& min, const Vertex& max);
};
}  // namespace s21
#endif  // FACADE_H
