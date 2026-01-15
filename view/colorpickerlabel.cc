#include "colorpickerlabel.h"
/**
 * @file colorpickerlabel.cc
 */

ColorPickerLabel::ColorPickerLabel(QWidget* parent) : QLabel(parent) {
  setFixedSize(30, 30);
  setCursor(Qt::PointingHandCursor);
  UpdateColor();
}

void ColorPickerLabel::mousePressEvent(QMouseEvent* event) {
  QColor new_color = QColorDialog::getColor(color_, nullptr, "Select color");
  if (new_color.isValid()) {
    SetColor(new_color);
    emit ColorPicked(new_color);
  }
  QLabel::mouseMoveEvent(event);
}

void ColorPickerLabel::SetColor(const QColor& color) {
  color_ = color;
  UpdateColor();
}

void ColorPickerLabel::UpdateColor() {
  setStyleSheet(QString("background-color: %1; border: 1px solid gray;")
                    .arg(color_.name()));
}

QColor ColorPickerLabel::GetColor() const { return color_; }
