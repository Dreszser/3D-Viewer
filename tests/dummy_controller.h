#ifndef DUMMY_CONTROLLER_H
#define DUMMY_CONTROLLER_H

#include "../common/IController.h"

class DummyController : public s21::IController {
 public:
  DummyController() : s21::IController() {};
  ~DummyController() override { (void)0; };

  void errorFileOpen() override {};
  void successFileOpen() override {};
};

#endif  // DUMMY_CONTROLLER_H