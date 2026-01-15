#ifndef EDGE_H
#define EDGE_H

/**
 * @file edge.h
 */

namespace s21 {
/**
 * @class Edge
 *
 * @brief Represents a line from model
 */
class Edge {
 private:
  int _StartV; /**< an integer value for the start of the line index */
  int _EndV;   /**< an integer value for the end of the line index */

 public:
  Edge() = delete;
  ~Edge() = default;
  Edge(int vertex_start, int vertex_end);
  int GetStart() const noexcept;
  int GetEnd() const noexcept;
  static bool Equal(Edge first, Edge second);
};
}  // namespace s21

#endif  // EDGE_H
