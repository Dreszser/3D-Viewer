#include "settingswidget.h"

/**
 * @file settingswidget.cc
 */

SettingsWidget::SettingsWidget(QWidget* parent) : QWidget{parent} {
  main_layout_ = new QHBoxLayout(this);
  setLayout(main_layout_);

  InitializeBackgroundSettings();
  InitializeProjectionSettings();
  InitializeEdgesSettings();
  InitializeVertexesSettings();
  // QSettings settings("TammyandTeam", "3d_viewer");
  // settings.clear();
}

void SettingsWidget::InitializeProjectionSettings() {
  auto* projection_group = new QGroupBox("Projection");
  auto* projection_layout = new QVBoxLayout();
  projection_ = new QButtonGroup(this);

  QRadioButton* perspective_button_ = new QRadioButton("Perspective");
  QRadioButton* ortho_button_ = new QRadioButton("Orthographic");

  projection_->addButton(perspective_button_,
                         static_cast<int>(ProjectionType::kParallel));
  projection_->addButton(ortho_button_,
                         static_cast<int>(ProjectionType::kCentral));

  projection_layout->addWidget(perspective_button_);
  projection_layout->addWidget(ortho_button_);
  projection_group->setLayout(projection_layout);

  main_layout_->addWidget(projection_group, 1);

  connect(projection_, &QButtonGroup::idClicked, this, [this](int id) {
    emit ProjectionChanged(static_cast<SettingsWidget::ProjectionType>(id));
  });
}

void SettingsWidget::InitializeEdgesSettings() {
  auto* edges_group = new QGroupBox("Edges");
  auto* edges_layout = new QGridLayout();

  edges_type_ = new QButtonGroup(this);
  QRadioButton* solid_button = new QRadioButton("Solid");
  QRadioButton* dashed_button = new QRadioButton("Dashed");
  edges_type_->addButton(solid_button, static_cast<int>(EdgesType::kSolid));
  edges_type_->addButton(dashed_button, static_cast<int>(EdgesType::kDashed));

  auto ChangeThickness = [this](float thickness) {
    emit EdgesThicknessChanged(thickness);
  };
  edges_thickness_ =
      new ControlWidget(0, 10, ChangeThickness, "Thickness", this);

  edge_color_ = new ColorPickerLabel(this);

  edges_layout->addWidget(solid_button, 0, 0, 1, 1);
  edges_layout->addWidget(dashed_button, 0, 1, 1, 1);
  edges_layout->addWidget(edges_thickness_, 1, 0, 1, 3);
  edges_layout->addWidget(edge_color_, 0, 2, 1, 1);

  edges_group->setLayout(edges_layout);

  main_layout_->addWidget(edges_group, 3);

  connect(edges_type_, &QButtonGroup::idClicked, this, [this](int id) {
    emit EdgesTypeChanged(static_cast<SettingsWidget::EdgesType>(id));
  });

  connect(edge_color_, &ColorPickerLabel::ColorPicked, this,
          [this](QColor& color) { emit EdgesColorChanged(color); });
}

void SettingsWidget::InitializeVertexesSettings() {
  auto* vertex_group = new QGroupBox("Vertexes");
  auto* vertex_layout = new QGridLayout();

  vertex_type_ = new QButtonGroup(this);
  QRadioButton* none_button = new QRadioButton("None");
  QRadioButton* circle_button = new QRadioButton("Circle");
  QRadioButton* square_button = new QRadioButton("Square");
  vertex_type_->addButton(none_button, static_cast<int>(VertexType::kNone));
  vertex_type_->addButton(circle_button, static_cast<int>(VertexType::kCircle));
  vertex_type_->addButton(square_button, static_cast<int>(VertexType::kSquare));

  auto ChangeSize = [this](int size) { emit VertexSizeChanged(size); };
  vertex_size_ = new ControlWidget(0, 10, ChangeSize, "Size", this);

  vertex_color_ = new ColorPickerLabel(this);

  vertex_layout->addWidget(none_button, 0, 0, 1, 1);
  vertex_layout->addWidget(circle_button, 0, 1, 1, 1);
  vertex_layout->addWidget(square_button, 0, 2, 1, 1);
  vertex_layout->addWidget(vertex_size_, 1, 0, 1, 4);
  vertex_layout->addWidget(vertex_color_, 0, 3, 1, 1);

  vertex_group->setLayout(vertex_layout);

  main_layout_->addWidget(vertex_group, 3);

  connect(vertex_type_, &QButtonGroup::idClicked, this, [this](int id) {
    emit VertexTypeChanged(static_cast<SettingsWidget::VertexType>(id));
  });

  connect(vertex_color_, &ColorPickerLabel::ColorPicked, this,
          [this](QColor& color) { emit VertexColorChanged(color); });
}

void SettingsWidget::InitializeBackgroundSettings() {
  auto* background_group = new QGroupBox("Background");
  auto* background_layout = new QHBoxLayout();

  background_color_ = new ColorPickerLabel(this);

  background_layout->addWidget(background_color_);

  background_group->setLayout(background_layout);

  main_layout_->addWidget(background_group, 1);

  connect(background_color_, &ColorPickerLabel::ColorPicked, this,
          [this](QColor& color) { emit BackgroundColorChanged(color); });
}

void SettingsWidget::LoadSettings() {
  QSettings settings("TammyandTeam", "3d_viewer");

  LoadProjection(settings);
  LoadEdges(settings);
  LoadBackgroundColor(settings);
  LoadVertexes(settings);
}

void SettingsWidget::SaveSettings() {
  QSettings settings("TammyandTeam", "3d_viewer");

  settings.setValue("ProjectionType", projection_->checkedId());
  settings.setValue("EdgeType", edges_type_->checkedId());
  settings.setValue("EdgeColorRed", edge_color_->GetColor().redF());
  settings.setValue("EdgeColorGreen", edge_color_->GetColor().greenF());
  settings.setValue("EdgeColorBlue", edge_color_->GetColor().blueF());
  settings.setValue("EdgeThickness", edges_thickness_->GetValue());

  settings.setValue("BackgroundColorRed", background_color_->GetColor().redF());
  settings.setValue("BackgroundColorGreen",
                    background_color_->GetColor().greenF());
  settings.setValue("BackgroundColorBlue",
                    background_color_->GetColor().blueF());

  settings.setValue("VertexColorRed", vertex_color_->GetColor().redF());
  settings.setValue("VertexColorGreen", vertex_color_->GetColor().greenF());
  settings.setValue("VertexColorBlue", vertex_color_->GetColor().blueF());
  settings.setValue("VertexSize", vertex_size_->GetValue());
  settings.setValue("VertexType", vertex_type_->checkedId());
}

void SettingsWidget::LoadProjection(const QSettings& settings) {
  int saved_button = settings.value("ProjectionType").toInt();
  QAbstractButton* button = projection_->button(saved_button);
  if (!button) {
    saved_button = static_cast<int>(ProjectionType::kParallel);
    button = projection_->button(saved_button);
  }
  button->setChecked(true);
  emit ProjectionChanged(
      static_cast<SettingsWidget::ProjectionType>(saved_button));
}

void SettingsWidget::LoadEdges(const QSettings& settings) {
  int saved_button = settings.value("EdgeType").toInt();
  QAbstractButton* button = edges_type_->button(saved_button);
  if (!button) {
    saved_button = static_cast<int>(EdgesType::kSolid);
    button = edges_type_->button(saved_button);
  }
  button->setChecked(true);
  emit EdgesTypeChanged(static_cast<SettingsWidget::EdgesType>(saved_button));

  int saved_thickness = settings.value("EdgeThickness", 1).toInt();
  if (saved_thickness < 0) saved_thickness = 1;
  edges_thickness_->SetValue(saved_thickness);

  LoadEdgesColor(settings);
}

void SettingsWidget::LoadEdgesColor(const QSettings& settings) {
  QColor color;
  float red = settings.value("EdgeColorRed", 1.0f).toFloat();
  float green = settings.value("EdgeColorGreen", 1.0f).toFloat();
  float blue = settings.value("EdgeColorBlue", 1.0f).toFloat();

  color.setRedF(red);
  color.setGreenF(green);
  color.setBlueF(blue);
  emit EdgesColorChanged(color);
  edge_color_->SetColor(color);
}

void SettingsWidget::LoadBackgroundColor(const QSettings& settings) {
  QColor color;
  float red = settings.value("BackgroundColorRed", 0.0f).toFloat();
  float green = settings.value("BackgroundColorGreen", 0.0f).toFloat();
  float blue = settings.value("BackgroundColorBlue", 0.0f).toFloat();

  color.setRedF(red);
  color.setGreenF(green);
  color.setBlueF(blue);
  emit BackgroundColorChanged(color);
  background_color_->SetColor(color);
}

void SettingsWidget::LoadVertexes(const QSettings& settings) {
  int saved_button = settings.value("VertexType").toInt();
  QAbstractButton* button = vertex_type_->button(saved_button);
  if (!button) {
    saved_button = static_cast<int>(VertexType::kNone);
    button = vertex_type_->button(saved_button);
  }
  button->setChecked(true);
  emit VertexTypeChanged(static_cast<SettingsWidget::VertexType>(saved_button));

  int saved_size = settings.value("VertexSize", 0).toInt();
  if (saved_size < 0) saved_size = 0;
  vertex_size_->SetValue(saved_size);

  LoadVertexColor(settings);
}

void SettingsWidget::LoadVertexColor(const QSettings& settings) {
  QColor color;
  float red = settings.value("VertexColorRed", 1.0f).toFloat();
  float green = settings.value("VertexColorGreen", 1.0f).toFloat();
  float blue = settings.value("VertexColorBlue", 1.0f).toFloat();

  color.setRedF(red);
  color.setGreenF(green);
  color.setBlueF(blue);
  emit VertexColorChanged(color);
  vertex_color_->SetColor(color);
}
