#ifndef S21_CONTROLLER_H
#define S21_CONTROLLER_H

#include "../common/IController.h"
#include "IVIew.h"
#include "facade.h"

/**
 * @file controller.h
 */

namespace s21 {

/**
 * @class Controller
 *
 * @brief Thin controller between model and view
 *
 * @details Can perform transformations and update infromation in View
 */
class Controller : public IController {
 private:
  s21::Facade*
      Model_;   /**< model pointer that is represented by Facade object */
  IView* View_; /**< View pointer to send the data after transformations */

 public:
  Controller() = delete;
  Controller(IView& View);
  ~Controller();

  /**
   * @brief Performs transformation on the model
   *
   * @param Transform type of the transformation
   * @param number new value from the ui slider
   */
  void PerformAction(s21::TranformationType Transform, int number);

  /**
   * @brief Sends file to the parser
   *
   * @param str file name
   */
  void LoadFile(std::string str);

  /**
   * @brief Called in case of an error while opening a file
   */
  void errorFileOpen() override;

  /**
   * @brief Called if file opened successfully
   */
  void successFileOpen() override;
};
}  // namespace s21
#endif  // S21_CONTROLLER_H
