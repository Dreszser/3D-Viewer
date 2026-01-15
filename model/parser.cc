#include "parser.h"

/**
 * @file parser.cc
 */

namespace s21 {

bool ObjParser::ParseData(std::string &file_path, std::vector<Vertex> &vertexes,
                          std::vector<Edge> &edges) {
  std::ifstream File(file_path);
  if (!File.is_open()) {
    return false;
  }
  vertexes.clear();
  edges.clear();
  ReadFile(&File, vertexes, edges);

  if (vertexes.empty() || edges.empty()) {
    vertexes.clear();
    edges.clear();
    return false;
  }
  return true;
}

void ObjParser::ReadFile(std::ifstream *file, std::vector<Vertex> &vertexes,
                         std::vector<Edge> &edges) {
  std::string line;
  std::unordered_set<std::pair<int, int>, pair_hash> edges_set;
  while (getline(*file, line)) {
    std::istringstream line_stream(
        line);  // извлечение первого элемента из строки в переменную lineType
    std::string lineType;  // с помощью потока line_stream
    line_stream >> lineType;

    if (lineType == "v") {
      if (!ParseVertexLine(line_stream, vertexes)) {
        vertexes.clear();
        break;
      }
    } else if (lineType == "f") {
      auto face_vertices =
          ExtractVertexIndicesFromFace(line_stream, vertexes.size());
      if (face_vertices.empty()) {
        vertexes.clear();
        break;
      } else {
        AddEdgesFromFaceVertices(face_vertices, &edges_set);
      }
    }
  }

  for (auto edgePair : edges_set) {
    Edge edge = {edgePair.first, edgePair.second};
    edges.emplace_back(edge);
  }
}

bool ObjParser::ParseVertexLine(std::istringstream &line_stream,
                                std::vector<Vertex> &vertexes) {
  Vertex vertex = {0, 0, 0};
  if (!(line_stream >> vertex.x >> vertex.y >> vertex.z) ||
      line_stream.fail()) {
    return false;
  }
  vertexes.push_back(vertex);
  return true;
}

std::vector<int> ObjParser::ExtractVertexIndicesFromFace(
    std::istringstream &line_stream, std::size_t size_of_vector) {
  std::vector<int> face_indexes;
  std::string vertex_data;
  int count_vertexes = 0;
  while (line_stream >> vertex_data) {
    std::istringstream vertex_data_stream(vertex_data);  // извлекаем 'хх/хх/хх'
    std::string vertex_index;
    getline(vertex_data_stream, vertex_index,
            '/');  // берём всё, что до первого '/'

    int index = 0;
    try {
      index = std::stoi(vertex_index);
    } catch (std::exception &ex) {
      face_indexes.clear();
      break;
    }

    int vector_size = static_cast<int>(size_of_vector);
    if (index > 0 && index <= vector_size) {
      index = index - 1;
    } else if (index < 0 && vector_size + index >= 0) {
      index = vector_size + index;
    } else {
      face_indexes.clear();
      break;
    }

    count_vertexes += 1;
    face_indexes.push_back(index);
  }

  if (count_vertexes < 2) {
    face_indexes.clear();
  }
  return face_indexes;
}

void ObjParser::AddEdgesFromFaceVertices(
    const std::vector<int> &face_vertices,
    std::unordered_set<std::pair<int, int>, pair_hash> *edges_set) {
  for (size_t i = 0; i < face_vertices.size(); ++i) {
    int start_index = face_vertices[i];
    int end_index =
        face_vertices[(i + 1) %
                      face_vertices.size()];  // берём следующий элемент, либо
                                              // замыкаем последний на первый
    if (start_index != end_index) {
      std::pair<int, int> new_edge = {std::min(start_index, end_index),
                                      std::max(start_index, end_index)};
      edges_set->insert(new_edge);
    }
  }
}

}  // namespace s21