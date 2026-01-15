
#include "controller.h"

#include <utility>

/**
 * @file controller.cc
 */

namespace s21 {

Controller::Controller(IView &View) : View_(&View) {
  Model_ = new Facade(*this);
}

Controller::~Controller() {
  delete Model_;
  Model_ = nullptr;
}

void Controller::PerformAction(s21::TranformationType Transform, int number) {
  Model_->Transform(Transform, number);
  View_->updateView(Model_->GetVertexes(), Model_->GetEdges());
}

void Controller::LoadFile(std::string str) {
  Model_->ReadModel(std::move(str));
}

void Controller::errorFileOpen() { View_->errorHandler(); }

void Controller::successFileOpen() {
  View_->initDefaultData();
  View_->updateModelEdges(Model_->GetEdgesSize());
  View_->updateModelVertexes(Model_->GetVertexesSize());
  View_->updateFileName(Model_->GetModelName());
  View_->updateView(Model_->GetVertexes(), Model_->GetEdges());
}

}  // namespace s21
