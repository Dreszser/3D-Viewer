#include "edge.h"

/**
 * @file edge.cc
 */

namespace s21 {

Edge::Edge(int vertex_start, int vertex_end)
    : _StartV(vertex_start), _EndV(vertex_end) {}

int Edge::GetStart() const noexcept { return _StartV; }

int Edge::GetEnd() const noexcept { return _EndV; }

bool Edge::Equal(const s21::Edge first, const s21::Edge second) {
  if ((first._StartV == second._StartV && first._EndV == second._EndV) ||
      (first._EndV == second._StartV && first._StartV == second._EndV))
    return true;
  else
    return false;
}

}  // namespace s21
