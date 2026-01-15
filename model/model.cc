#include "model.h"

/**
 * @file model.cc
 */

namespace s21 {
size_t Model::GetVertexesSize() const { return vertexes_.size(); }

size_t Model::GetEdgesSize() const { return edges_.size(); }

const std::span<const Vertex> Model::GetVertexes() const { return vertexes_; }

const std::span<const Edge> Model::GetEdges() const { return edges_; }

std::vector<Vertex> &Model::GetVertexesUpdate() { return vertexes_; }

std::vector<Edge> &Model::GetEdgesUpdate() { return edges_; }

void Model::SetVertexes(std::vector<Vertex> &&vertexes) {
  vertexes_ = std::move(vertexes);
}

void Model::SetEdges(std::vector<Edge> &&edges) { edges_ = std::move(edges); }

void Model::SetModelName(const std::string &name) { modelName_ = name; }

std::string s21::Model::GetModelName() const { return modelName_; }
}  // namespace s21
