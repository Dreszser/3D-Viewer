#include "tests.h"

namespace fs = std::filesystem;

TEST(transformation_tests, move_x_test_1) {
  fs::path test_file_path = __FILE__;
  fs::path obj_path =
      test_file_path.parent_path() / "success_object" / "cube.obj";

  DummyController controller;
  s21::Facade facade(controller);

  facade.ReadModel(obj_path);
  ASSERT_NE(facade.GetEdgesSize(), static_cast<size_t>(0));

  std::vector<s21::Vertex> vertexes_before_transform(
      facade.GetVertexes().begin(), facade.GetVertexes().end());

  facade.Transform(s21::TranformationType::MOVE_X, 5);

  std::vector<s21::Vertex> vertexes_after_transform(
      facade.GetVertexes().begin(), facade.GetVertexes().end());

  for (size_t i = 0; i < facade.GetVertexesSize(); ++i) {
    ASSERT_NE(vertexes_before_transform[i].x, vertexes_after_transform[i].x);
  }
}

TEST(transformation_tests, move_y_test_1) {
  fs::path test_file_path = __FILE__;
  fs::path obj_path =
      test_file_path.parent_path() / "success_object" / "cube.obj";

  DummyController controller;
  s21::Facade facade(controller);

  facade.ReadModel(obj_path);

  std::vector<s21::Vertex> vertexes_before_transform(
      facade.GetVertexes().begin(), facade.GetVertexes().end());

  facade.Transform(s21::TranformationType::MOVE_Y, 15);

  std::vector<s21::Vertex> vertexes_after_transform(
      facade.GetVertexes().begin(), facade.GetVertexes().end());

  for (size_t i = 0; i < facade.GetVertexesSize(); ++i) {
    ASSERT_NE(vertexes_before_transform[i].y, vertexes_after_transform[i].y);
  }
}

TEST(transformation_tests, move_z_test_1) {
  fs::path test_file_path = __FILE__;
  fs::path obj_path =
      test_file_path.parent_path() / "success_object" / "cube.obj";

  DummyController controller;
  s21::Facade facade(controller);

  facade.ReadModel(obj_path);

  std::vector<s21::Vertex> vertexes_before_transform(
      facade.GetVertexes().begin(), facade.GetVertexes().end());

  facade.Transform(s21::TranformationType::MOVE_Z, 15);

  std::vector<s21::Vertex> vertexes_after_transform(
      facade.GetVertexes().begin(), facade.GetVertexes().end());

  for (size_t i = 0; i < facade.GetVertexesSize(); ++i) {
    ASSERT_NE(vertexes_before_transform[i].z, vertexes_after_transform[i].z);
  }
}

TEST(transformation_tests, scale_test_1) {
  fs::path test_file_path = __FILE__;
  fs::path obj_path =
      test_file_path.parent_path() / "success_object" / "cube.obj";

  DummyController controller;
  s21::Facade facade(controller);

  facade.ReadModel(obj_path);

  std::vector<s21::Vertex> vertexes_before_transform(
      facade.GetVertexes().begin(), facade.GetVertexes().end());

  facade.Transform(s21::TranformationType::SCALE, 150);

  std::vector<s21::Vertex> vertexes_after_transform(
      facade.GetVertexes().begin(), facade.GetVertexes().end());

  for (size_t i = 0; i < facade.GetVertexesSize(); ++i) {
    ASSERT_NE(vertexes_before_transform[i].x, vertexes_after_transform[i].x);
    ASSERT_NE(vertexes_before_transform[i].y, vertexes_after_transform[i].y);
    ASSERT_NE(vertexes_before_transform[i].z, vertexes_after_transform[i].z);
  }

  facade.Transform(s21::TranformationType::SCALE, 100);

  vertexes_after_transform = std::vector<s21::Vertex>(
      facade.GetVertexes().begin(), facade.GetVertexes().end());

  for (size_t i = 0; i < facade.GetVertexesSize(); ++i) {
    ASSERT_EQ(vertexes_before_transform[i].x, vertexes_after_transform[i].x);
    ASSERT_EQ(vertexes_before_transform[i].y, vertexes_after_transform[i].y);
    ASSERT_EQ(vertexes_before_transform[i].z, vertexes_after_transform[i].z);
  }
}

TEST(transformation_tests, rotate_x_test_1) {
  fs::path test_file_path = __FILE__;
  fs::path obj_path =
      test_file_path.parent_path() / "success_object" / "cube.obj";

  DummyController controller;
  s21::Facade facade(controller);

  facade.ReadModel(obj_path);

  std::vector<s21::Vertex> vertexes_before_transform(
      facade.GetVertexes().begin(), facade.GetVertexes().end());

  facade.Transform(s21::TranformationType::ROTATE_X, 15);

  std::vector<s21::Vertex> vertexes_after_transform(
      facade.GetVertexes().begin(), facade.GetVertexes().end());

  for (size_t i = 0; i < facade.GetVertexesSize(); ++i) {
    ASSERT_NE(vertexes_before_transform[i].y, vertexes_after_transform[i].y);
    ASSERT_NE(vertexes_before_transform[i].z, vertexes_after_transform[i].z);
  }
}

TEST(transformation_tests, rotate_y_test_1) {
  fs::path test_file_path = __FILE__;
  fs::path obj_path =
      test_file_path.parent_path() / "success_object" / "cube.obj";

  DummyController controller;
  s21::Facade facade(controller);

  facade.ReadModel(obj_path);

  std::vector<s21::Vertex> vertexes_before_transform(
      facade.GetVertexes().begin(), facade.GetVertexes().end());

  facade.Transform(s21::TranformationType::ROTATE_Y, 15);

  std::vector<s21::Vertex> vertexes_after_transform(
      facade.GetVertexes().begin(), facade.GetVertexes().end());

  for (size_t i = 0; i < facade.GetVertexesSize(); ++i) {
    ASSERT_NE(vertexes_before_transform[i].x, vertexes_after_transform[i].x);
    ASSERT_NE(vertexes_before_transform[i].z, vertexes_after_transform[i].z);
  }
}

TEST(transformation_tests, rotate_z_test_1) {
  fs::path test_file_path = __FILE__;
  fs::path obj_path =
      test_file_path.parent_path() / "success_object" / "cube.obj";

  DummyController controller;
  s21::Facade facade(controller);

  facade.ReadModel(obj_path);

  std::vector<s21::Vertex> vertexes_before_transform(
      facade.GetVertexes().begin(), facade.GetVertexes().end());

  facade.Transform(s21::TranformationType::ROTATE_Z, 15);

  std::vector<s21::Vertex> vertexes_after_transform(
      facade.GetVertexes().begin(), facade.GetVertexes().end());

  for (size_t i = 0; i < facade.GetVertexesSize(); ++i) {
    ASSERT_NE(vertexes_before_transform[i].x, vertexes_after_transform[i].x);
    ASSERT_NE(vertexes_before_transform[i].y, vertexes_after_transform[i].y);
  }
}

TEST(transformation_tests, transformation_that_does_not_exist) {
  fs::path test_file_path = __FILE__;
  fs::path obj_path =
      test_file_path.parent_path() / "success_object" / "cube.obj";

  DummyController controller;
  s21::Facade facade(controller);

  facade.ReadModel(obj_path);

  std::vector<s21::Vertex> vertexes_before_transform(
      facade.GetVertexes().begin(), facade.GetVertexes().end());

  facade.Transform(static_cast<s21::TranformationType>(19), 15);

  std::vector<s21::Vertex> vertexes_after_transform(
      facade.GetVertexes().begin(), facade.GetVertexes().end());

  for (size_t i = 0; i < facade.GetVertexesSize(); ++i) {
    ASSERT_EQ(vertexes_before_transform[i].x, vertexes_after_transform[i].x);
    ASSERT_EQ(vertexes_before_transform[i].y, vertexes_after_transform[i].y);
    ASSERT_EQ(vertexes_before_transform[i].z, vertexes_after_transform[i].z);
  }
}

TEST(transformation_tests, edges_save_between_transformations) {
  fs::path test_file_path = __FILE__;
  fs::path obj_path =
      test_file_path.parent_path() / "success_object" / "cube.obj";

  DummyController controller;
  s21::Facade facade(controller);

  facade.ReadModel(obj_path);

  std::vector<s21::Edge> edges_before_transform(facade.GetEdges().begin(),
                                                facade.GetEdges().end());

  facade.Transform(s21::TranformationType::MOVE_X, 15);

  std::vector<s21::Edge> edges_after_transform(facade.GetEdges().begin(),
                                               facade.GetEdges().end());

  for (size_t i = 0; i < facade.GetEdgesSize(); ++i) {
    ASSERT_EQ(
        s21::Edge::Equal(edges_before_transform[i], edges_after_transform[i]),
        true);
  }
}
