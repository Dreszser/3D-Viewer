#include "controlW.h"

#include <QLabel>

/**
 * @file controlW.cc
 */

ControlWidget::ControlWidget(int min, int max,
                             std::function<void(int)> callback,
                             QString description, QWidget* parent)
    : QWidget(parent) {
  Callback_ = callback;
  Slider_ = new QSlider(Qt::Horizontal);
  Slider_->setRange(min, max);
  SpinBox_ = new QSpinBox();
  SpinBox_->setRange(min, max);
  defaultValue_ = min + (max - min) / 2;
  setToDefault();
  SpinBox_->setFixedWidth(50);
  Layout_ = new QGridLayout(this);
  QLabel* string = new QLabel(description);
  Layout_->addWidget(string, 0, 0, 1, 2);
  Layout_->addWidget(Slider_, 0, 2, 1, 4);
  Layout_->addWidget(SpinBox_, 0, 6, 1, 1);
  connect(Slider_, &QSlider::valueChanged, this, &ControlWidget::SpinBoxSlot);
  connect(SpinBox_, &QSpinBox::valueChanged, this, &ControlWidget::SliderSlot);
}

void ControlWidget::SpinBoxSlot(int value) {
  SpinBox_->blockSignals(true);
  SpinBox_->setValue(value);
  SpinBox_->blockSignals(false);
  if (Callback_) {
    Callback_(value);
  }
}

void ControlWidget::SliderSlot(int value) {
  Slider_->blockSignals(true);
  Slider_->setValue(value);
  Slider_->blockSignals(false);
  if (Callback_) {
    Callback_(value);
  }
}

void ControlWidget::SetValue(int value) {
  SpinBox_->setValue(value);
  Slider_->setValue(value);
}

int ControlWidget::GetValue() { return SpinBox_->value(); }

void ControlWidget::setToDefault() {
  Slider_->setValue(defaultValue_);
  SpinBox_->setValue(defaultValue_);
}
