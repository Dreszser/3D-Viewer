#include "facade.h"

#include <filesystem>
#include <memory>

#include "parser.h"
#include "transform.h"
/**
 * @file facade.cc
 */

namespace s21 {

s21::Facade::Facade(IController& controller)
    : scale_(100),
      moveX_(0),
      moveY_(0),
      moveZ_(0),
      rotateX_(0),
      rotateY_(0),
      rotateZ_(0),
      controller_(&controller) {}

size_t Facade::GetVertexesSize() { return model_.GetVertexesSize(); }

size_t Facade::GetEdgesSize() { return model_.GetEdgesSize(); }

std::span<const Vertex> Facade::GetVertexes() const {
  return model_.GetVertexes();
}

std::span<const Edge> Facade::GetEdges() const { return model_.GetEdges(); }

void Facade::Transform(TranformationType transform, int num) {
  std::unique_ptr<ITransform> transformation;
  float number = 0;
  float move_step = 0.05f;
  switch (transform) {
    case TranformationType::MOVE_X:
      transformation = std::make_unique<MoveX>();
      number = (num - moveX_) * move_step;
      moveX_ = num;
      break;
    case TranformationType::MOVE_Y:
      transformation = std::make_unique<MoveY>();
      number = (num - moveY_) * move_step;
      moveY_ = num;
      break;
    case TranformationType::MOVE_Z:
      transformation = std::make_unique<MoveZ>();
      number = (num - moveZ_) * move_step;
      moveZ_ = num;
      break;
    case TranformationType::ROTATE_X:
      transformation = std::make_unique<RotateX>();
      number = num - rotateX_;
      rotateX_ = num;
      break;
    case TranformationType::ROTATE_Y:
      transformation = std::make_unique<RotateY>();
      number = num - rotateY_;
      rotateY_ = num;
      break;
    case TranformationType::ROTATE_Z:
      transformation = std::make_unique<RotateZ>();
      number = num - rotateZ_;
      rotateZ_ = num;
      break;
    case TranformationType::SCALE:
      transformation = std::make_unique<Resize>();
      number = static_cast<float>(num) / scale_;
      scale_ = num;
      break;
    default:
      return;
  }

  if (transformation) {
    transformation->Transform(model_.GetVertexesUpdate(), number);
  }
}

std::string Facade::GetModelName() { return model_.GetModelName(); }

void Facade::ReadModel(std::string file_name) {
  bool result = true;
  if (!std::filesystem::exists(file_name)) {
    result = false;
  }
  if (result) {
    if (file_name.ends_with(".obj")) {
      std::unique_ptr<IParser> parser = std::make_unique<ObjParser>();
      result = parser->ParseData(file_name, model_.GetVertexesUpdate(),
                                 model_.GetEdgesUpdate());
    } else {
      result = false;
    }
  }
  if (result) {
    model_.SetModelName(file_name.substr(file_name.find_last_of('/') + 1));
  }
  if (result) {
    selfReset();
    NormalizeModel();
    controller_->successFileOpen();
  } else {
    controller_->errorFileOpen();
  }
}

void Facade::selfReset() {
  scale_ = 100;
  moveX_ = 0;
  moveY_ = 0;
  moveZ_ = 0;
  rotateX_ = 0;
  rotateY_ = 0;
  rotateZ_ = 0;
}

void Facade::NormalizeModel() {
  Vertex min = Vertex(0, 0, 0);
  Vertex max = Vertex(0, 0, 0);

  CountBoundingBoxCorners(min, max);

  MoveToOrigin(min, max);

  ScaleToFit(min, max);
}

void Facade::CountBoundingBoxCorners(Vertex& min, Vertex& max) {
  std::span<const Vertex> vertexes = model_.GetVertexes();
  min = Vertex(vertexes[0].x, vertexes[0].y, vertexes[0].z);
  max = Vertex(vertexes[0].x, vertexes[0].y, vertexes[0].z);

  for (const auto& vertex : vertexes) {
    min.x = (std::min(vertex.x, min.x));
    min.y = (std::min(vertex.y, min.y));
    min.z = (std::min(vertex.z, min.z));

    max.x = (std::max(vertex.x, max.x));
    max.y = (std::max(vertex.y, max.y));
    max.z = (std::max(vertex.z, max.z));
  }
}

void Facade::MoveToOrigin(const Vertex& min, const Vertex& max) {
  std::unique_ptr<ITransform> transformation;
  float delta_x = (min.x + max.x) / 2;
  transformation = std::make_unique<MoveX>();
  transformation->Transform(model_.GetVertexesUpdate(), -delta_x);
  float delta_y = (min.y + max.y) / 2;
  transformation = std::make_unique<MoveY>();
  transformation->Transform(model_.GetVertexesUpdate(), -delta_y);
  float delta_z = (min.z + max.z) / 2;
  transformation = std::make_unique<MoveZ>();
  transformation->Transform(model_.GetVertexesUpdate(), -delta_z);
}

void Facade::ScaleToFit(const Vertex& min, const Vertex& max) {
  std::unique_ptr<ITransform> transformation;

  float max_delta = std::max(max.x - min.x, max.y - min.y);
  max_delta = std::max(max.z - min.z, max_delta);
  transformation = std::make_unique<Resize>();
  transformation->Transform(model_.GetVertexesUpdate(), 1.0f / max_delta);
}

}  // namespace s21
