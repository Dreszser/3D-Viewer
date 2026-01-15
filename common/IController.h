#ifndef ICONTROLLER_H
#define ICONTROLLER_H

/**
 * @file IController.h
 */

namespace s21 {

/**
 * @class IController
 *
 * @brief Abstract class for Controller
 */
class IController {
 public:
  virtual ~IController() = default;

  virtual void errorFileOpen() = 0;
  virtual void successFileOpen() = 0;
};
}  // namespace s21

#endif  // ICONTROLLER_H
