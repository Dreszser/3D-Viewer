#ifndef COLORPICKERLABEL_H
#define COLORPICKERLABEL_H

#include <QColor>
#include <QColorDialog>
#include <QLabel>

/**
 * @file colorpickerlabel.h
 */

class ColorPickerLabel : public QLabel {
  Q_OBJECT
 public:
  explicit ColorPickerLabel(QWidget* parent = nullptr);
  void SetColor(const QColor& color);
  QColor GetColor() const;

 signals:
  void ColorPicked(QColor& color);

 protected:
  void mousePressEvent(QMouseEvent* event) override;

 private:
  QColor color_;
  void UpdateColor();
};

#endif  // COLORPICKERLABEL_H
