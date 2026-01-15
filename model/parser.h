#ifndef S21_PARSER_H
#define S21_PARSER_H

#include <fstream>
#include <sstream>
#include <string>
#include <unordered_set>
#include <vector>

#include "../common/edge.h"
#include "../common/vertex.h"

/**
 * @file parser.h
 */

namespace s21 {

/**
 * @struct pair_hash
 */
struct pair_hash {
  inline std::size_t operator()(const std::pair<int, int> &v) const {
    return static_cast<std::size_t>(v.first) << 32 |
           static_cast<std::size_t>(v.second);
  }
};

/**
 * @class IParser
 *
 * @brief Abstract parser class for potential other parsers
 */
class IParser {
 public:
  virtual ~IParser() = default;
  virtual bool ParseData(std::string &FilePath, std::vector<Vertex> &vertexes,
                         std::vector<Edge> &edges) = 0;
};

/**
 * @class ObjParser
 *
 * @brief Can parse `.obj` files and fill model info
 */
class ObjParser : public IParser {
 public:
  /**
   * @brief Main method that opens a file to parse
   * @param FilePath file to parse
   * @param vertexes reference to vertex array to fill
   * @param edges reference to edge array to fill
   * @return `true` if file opens correctly, `false` if not
   */
  bool ParseData(std::string &file_path, std::vector<Vertex> &vertexes,
                 std::vector<Edge> &edges) override;

 private:
  std::ifstream filestream;
  /**
   * @brief Reads file line by line and parse all its contents
   * @param file file to read
   * @param vertexes vertex array reference to fill
   * @param edges edge array reference to fill
   */
  static void ReadFile(std::ifstream *file, std::vector<Vertex> &vertexes,
                       std::vector<Edge> &edges);
  /**
   * @brief Extracts vertex from line
   * @param line_stream vertex line from `.obj` file
   * @param vertexes reference to vertexes array to add a vertex to
   * @return `true` if the vertex retrieval was successful
   */
  static bool ParseVertexLine(std::istringstream &line_stream,
                              std::vector<Vertex> &vertexes);
  /**
   * @brief Extracts vertex indexes from the face
   * @param line_stream face line from `.obj` file
   * @param size_of_vector value to prevent wrong indexes
   * @return vector of all vertexes from the face
   */
  static std::vector<int> ExtractVertexIndicesFromFace(
      std::istringstream &line_stream, std::size_t size_of_vector);
  /**
   * @brief Adds edges from the face
   * @param face_vertices vertex indexes from the face
   * @param edges unordered set pointer that contains all parsed edges
   */
  static void AddEdgesFromFaceVertices(
      const std::vector<int> &face_vertices,
      std::unordered_set<std::pair<int, int>, pair_hash> *edges);
};
}  // namespace s21

#endif