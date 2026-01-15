#include "test_parser.h"

#include <filesystem>

class ObjFile {
 public:
  std::string fileName;
  bool result;

  friend std::ostream& operator<<(std::ostream& os, const ObjFile& obj) {
    return os << "File: '" << obj.fileName
              << "', Result: " << (obj.result ? "true" : "false");
  }
};

class ParserFixture : public ::testing::TestWithParam<ObjFile> {
 protected:
  std::unique_ptr<s21::IParser> parser;
};

TEST_P(ParserFixture, TestFiles) {
  ObjFile File = GetParam();
  parser = std::make_unique<s21::ObjParser>();
  std::vector<s21::Vertex> vertexes;
  std::vector<s21::Edge> edges;
  ASSERT_EQ(parser->ParseData(File.fileName, vertexes, edges), File.result);
}

const std::vector<ObjFile> test_files = {
    {"./tests/fail_objects/no_file.obj", false},
    // empty file
    {"./tests/fail_objects/clear_fail.obj", false},
    // 1 vertex without coordinates
    {"./tests/fail_objects/vertex_fail.obj", false},
    // 1 vertex only 1 coordinate
    {"./tests/fail_objects/vertex_fail_2.obj", false},
    // 1 vertex 2 coordinates no int
    {"./tests/fail_objects/vertex_fail_3.obj", false},
    // 8 vertexes, 1 face without vertexes
    {"./tests/fail_objects/face_fail.obj", false},
    // 8 vertexes, 1 face only 1 vertex
    {"./tests/fail_objects/face_fail_2.obj", false},
    // 8 vertexes, 8 faces, has invalid vertex 0 (face 1)
    {"./tests/fail_objects/face_fail_3.obj", false},
    // 8 vertexes, face has vertex -9
    {"./tests/fail_objects/face_fail_4.obj", false},
    // 8 vertexes, 1 face with 2 vertexes no int
    {"./tests/fail_objects/face_fail_5.obj", false},
    // 8 vertexes, 8 faces, has invalid vertex 9
    {"./tests/fail_objects/face_fail_6.obj", false},
    {"./tests/fail_objects/face_fail_7.obj", false},
    {"./tests/fail_objects/face_fail_8.obj", false},
    {"./tests/fail_objects/face_fail_9.obj", false},
    {"./tests/fail_objects/face_fail_10.obj", false},
    {"./tests/fail_objects/face_fail_11.obj", false},
    // valid file
    {"./tests/success_object/cube.obj", true},
    // valid file with coordinate w
    {"./tests/success_object/cube_vertex_coor_w.obj", true},
    // valid file with negative indexes of vertexes in faces
    {"./tests/success_object/cube_negative.obj", true},
    // valid file with faces only 2 vertexes
    {"./tests/success_object/cube_frame.obj", true}};

INSTANTIATE_TEST_SUITE_P(ParserTest, ParserFixture,
                         ::testing::ValuesIn(test_files));