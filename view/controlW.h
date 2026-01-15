#ifndef CONTROLW_H
#define CONTROLW_H

#include <QGridLayout>
#include <QHBoxLayout>
#include <QSlider>
#include <QSpinBox>
#include <QString>
#include <QWidget>

/**
 * @file controlW.h
 */

class ControlWidget : public QWidget {
  Q_OBJECT
 private:
  QSpinBox* SpinBox_;
  QSlider* Slider_;
  QGridLayout* Layout_;
  std::function<void(int)> Callback_;
  int defaultValue_;

 public:
  ControlWidget(int min, int max, std::function<void(int)> callback,
                QString description, QWidget* parent = nullptr);
  void SetValue(int value);
  int GetValue();
  void setToDefault();

 private slots:
  void SpinBoxSlot(int value);
  void SliderSlot(int value);
};

#endif  // CONTROLW_H
