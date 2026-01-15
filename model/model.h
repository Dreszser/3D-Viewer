#ifndef S21_MODEL_H
#define S21_MODEL_H

#include <span>
#include <string>
#include <vector>

#include "../common/edge.h"
#include "../common/vertex.h"

/**
 * @file model.h
 */

namespace s21 {
/**
 * @class Model
 * @brief Stores all valuable information about currently loaded model
 */
class Model {
 public:
  Model() = default;
  ~Model() = default;

  /**
   * @brief Basic method to get vertexes size
   * @return `vertexes_` array size
   */
  size_t GetVertexesSize() const;

  /**
   * @brief Basic method to get edges size
   * @return `edges_` array size
   */
  size_t GetEdgesSize() const;

  /**
   * @return std::span of the `vertexes_` array
   */
  const std::span<const Vertex> GetVertexes() const;
  /**
   * @return std::span of the `edges_` array
   */
  const std::span<const Edge> GetEdges() const;
  /**
   * @return returns `vertexes_` reference to be used in the `Facade`
   */
  std::vector<Vertex>& GetVertexesUpdate();
  /**
   * @return returns `edges_` reference to be used in the `Facade`
   */
  std::vector<Edge>& GetEdgesUpdate();
  /**
   * @brief Sets new values for `vertexes_` field from `vertexes`
   * @param vertexes new or updated array of model vertexes
   */
  void SetVertexes(std::vector<Vertex>&& vertexes);
  /**
   * @brief Sets new values for `vertexes_` field from `vertexes`
   * @param edges new or updated array of model edges
   */
  void SetEdges(std::vector<Edge>&& edges);
  /**
   * @brief Sets new model name
   * @param name new file name string
   */
  void SetModelName(const std::string& name);
  /**
   * @return current model name string
   */
  std::string GetModelName() const;

 private:
  /**
   * @brief current vertex coordinates in a form of a vector
   */
  std::vector<Vertex> vertexes_;
  /**
   * @brief current edges in a form of a vector
   */
  std::vector<Edge> edges_;
  /**
   * @brief current model name
   */
  std::string modelName_;
};
}  // namespace s21
#endif  // S21_MODEL_H
