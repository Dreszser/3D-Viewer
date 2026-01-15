#ifndef IVIEW_H
#define IVIEW_H
#include <span>
#include <string>

#include "edge.h"
#include "vertex.h"

/**
 * @file IView.h
 */

namespace s21 {

/**
 * @class IView
 *
 * @brief IView is an abstract View class
 */
class IView {
 public:
  virtual ~IView() = default;

  virtual void updateModelVertexes(const int vertexesSize) = 0;
  virtual void updateModelEdges(const int edgesSize) = 0;
  virtual void updateView(std::span<const Vertex> Vertexes,
                          std::span<const Edge> Edges) = 0;
  virtual void updateFileName(std::string FileName) = 0;
  virtual void initDefaultData() = 0;
  virtual void errorHandler() = 0;
};
}  // namespace s21

#endif  // IVIEW_H
