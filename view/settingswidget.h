#ifndef SETTINGSWIDGET_H
#define SETTINGSWIDGET_H

#include <QButtonGroup>
#include <QGroupBox>
#include <QRadioButton>
#include <QSettings>

#include "colorpickerlabel.h"
#include "controlW.h"

/**
 * @file settingswidget.h
 */

class SettingsWidget : public QWidget {
  Q_OBJECT
 public:
  explicit SettingsWidget(QWidget* parent = nullptr);
  void LoadSettings();
  void SaveSettings();
  enum class ProjectionType { kParallel, kCentral };
  enum class EdgesType { kSolid = 2, kDashed };
  enum class VertexType { kNone = 4, kCircle, kSquare };

 signals:
  void ProjectionChanged(ProjectionType type);
  void EdgesTypeChanged(EdgesType type);
  void EdgesThicknessChanged(float thickness);
  void EdgesColorChanged(QColor& color);
  void VertexTypeChanged(VertexType type);
  void VertexSizeChanged(int size);
  void VertexColorChanged(QColor& color);
  void BackgroundColorChanged(QColor& color);

 private:
  void InitializeProjectionSettings();
  void InitializeEdgesSettings();
  void InitializeVertexesSettings();
  void InitializeBackgroundSettings();

  void LoadProjection(const QSettings& settings);
  void LoadEdges(const QSettings& settings);
  void LoadEdgesColor(const QSettings& settings);
  void LoadBackgroundColor(const QSettings& settings);
  void LoadVertexes(const QSettings& settings);
  void LoadVertexColor(const QSettings& settings);

 private:
  QHBoxLayout* main_layout_;
  QButtonGroup* projection_;

  QButtonGroup* edges_type_;
  ControlWidget* edges_thickness_;
  ColorPickerLabel* edge_color_;

  QButtonGroup* vertex_type_;
  ControlWidget* vertex_size_;
  ColorPickerLabel* vertex_color_;

  ColorPickerLabel* background_color_;
};

#endif  // SETTINGSWIDGET_H
