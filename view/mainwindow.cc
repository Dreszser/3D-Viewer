#include "mainwindow.h"

#include <QFileDialog>

/**
 * @file mainwindow.cc
 */

MainWindow::MainWindow() : controller_(nullptr) {
  QWidget* centralWidget = new QWidget(this);
  layout_ = new QGridLayout(centralWidget);
  controller_ = new s21::Controller(*this);
  render_ = new CustomOpenGLWidget(this);
  readFile_ = new QPushButton("Open File");
  connect(readFile_, &QPushButton::released, this, &MainWindow::handleOpenFile);
  InitSliders();
  fileName_ = new QLabel(QString("No Model File"));
  vertexes_ = new QLabel();
  edges_ = new QLabel();
  save_image_ = new SaveImageWidget(render_);
  InitSettings();

  SetUpLayout();
  setCentralWidget(centralWidget);
}

void MainWindow::InitSliders() {
  auto scaleCallback = [this](int value) {
    controller_->PerformAction(s21::TranformationType::SCALE, value);
  };
  auto rotateXCallback = [this](int value) {
    controller_->PerformAction(s21::TranformationType::ROTATE_X, value);
  };
  auto rotateYCallback = [this](int value) {
    controller_->PerformAction(s21::TranformationType::ROTATE_Y, value);
  };
  auto rotateZCallback = [this](int value) {
    controller_->PerformAction(s21::TranformationType::ROTATE_Z, value);
  };
  auto moveXCallback = [this](int value) {
    controller_->PerformAction(s21::TranformationType::MOVE_X, value);
  };
  auto moveYCallback = [this](int value) {
    controller_->PerformAction(s21::TranformationType::MOVE_Y, value);
  };
  auto moveZCallback = [this](int value) {
    controller_->PerformAction(s21::TranformationType::MOVE_Z, value);
  };

  scale_ = new ControlWidget(50, 150, scaleCallback, "Scale", this);
  rotateX_ = new ControlWidget(-179, 180, rotateXCallback, "Rotate X", this);
  rotateY_ = new ControlWidget(-179, 180, rotateYCallback, "Rotate Y", this);
  rotateZ_ = new ControlWidget(-179, 180, rotateZCallback, "Rotate Z", this);
  moveX_ = new ControlWidget(-99, 100, moveXCallback, "Move X", this);
  moveY_ = new ControlWidget(-99, 100, moveYCallback, "Move Y", this);
  moveZ_ = new ControlWidget(-99, 100, moveZCallback, "Move Z", this);
}

void MainWindow::SetUpLayout() {
  layout_->addWidget(save_image_, 0, 0, 1, 8);
  layout_->addWidget(render_, 1, 0, 9, 8);
  layout_->addWidget(readFile_, 0, 8, 1, 4);
  layout_->addWidget(fileName_, 1, 8, 1, 4);
  layout_->addWidget(vertexes_, 2, 8, 1, 2);
  layout_->addWidget(edges_, 2, 10, 1, 2);
  layout_->addWidget(scale_, 3, 8, 1, 4);
  layout_->addWidget(rotateX_, 4, 8, 1, 4);
  layout_->addWidget(rotateY_, 5, 8, 1, 4);
  layout_->addWidget(rotateZ_, 6, 8, 1, 4);
  layout_->addWidget(moveX_, 7, 8, 1, 4);
  layout_->addWidget(moveY_, 8, 8, 1, 4);
  layout_->addWidget(moveZ_, 9, 8, 1, 4);
  layout_->addWidget(settings_widget_, 10, 0, 2, 12);
}

void MainWindow::InitSettings() {
  settings_widget_ = new SettingsWidget(this);
  ConnectProjectionSignal();
  ConnectEdgeSignals();
  ConnectBackgroundSignal();
  ConnectVertexSignals();
  settings_widget_->LoadSettings();
}

void MainWindow::updateModelVertexes(const int vertexesSize) {
  vertexes_->setText(QString("Vertexes: %1").arg(vertexesSize));
}

void MainWindow::updateModelEdges(const int edgesSize) {
  edges_->setText(QString("Edges: %1").arg(edgesSize));
}

void MainWindow::updateFileName(std::string FileName) {
  fileName_->setText(
      QString("File name: %1").arg(QString::fromStdString((FileName))));
}

void MainWindow::initDefaultData() {
  scale_->setToDefault();
  rotateX_->setToDefault();
  rotateY_->setToDefault();
  rotateZ_->setToDefault();
  moveX_->setToDefault();
  moveY_->setToDefault();
  moveZ_->setToDefault();
}

void MainWindow::errorHandler() {
  fileName_->setText("Error while opening file");
}

void MainWindow::handleOpenFile() {
  QString file_name = QFileDialog::getOpenFileName(
      this, "Open file...", QDir::homePath(), "Object files (*.obj)");
  if (!file_name.isEmpty()) {
    QFile file(file_name);
    if (file.open(QIODevice::ReadOnly)) {
      controller_->LoadFile(file_name.toStdString());
      file.close();
    }
  }
}

void MainWindow::updateView(std::span<const s21::Vertex> Vertexes,
                            std::span<const s21::Edge> Edges) {
  render_->UpdateWidget(Vertexes, Edges);
}

void MainWindow::ConnectProjectionSignal() {
  connect(
      settings_widget_, &SettingsWidget::ProjectionChanged, this,
      [this](SettingsWidget::ProjectionType projection_type) {
        switch (projection_type) {
          case SettingsWidget::ProjectionType::kParallel:
            render_->SetProjectionType(std::make_unique<ParallelProjection>());
            break;
          case SettingsWidget::ProjectionType::kCentral:
            render_->SetProjectionType(std::make_unique<CentralProjection>());
            break;
        }
      });
}

void MainWindow::ConnectEdgeSignals() {
  connect(settings_widget_, &SettingsWidget::EdgesTypeChanged, this,
          [this](SettingsWidget::EdgesType edge_type) {
            switch (edge_type) {
              case SettingsWidget::EdgesType::kDashed:
                render_->SetEdgeType(true);
                break;
              case SettingsWidget::EdgesType::kSolid:
                render_->SetEdgeType(false);
                break;
            }
          });
  connect(settings_widget_, &SettingsWidget::EdgesColorChanged, this,
          [this](QColor& color) { render_->SetEdgeColor(color); });
  connect(settings_widget_, &SettingsWidget::EdgesThicknessChanged, this,
          [this](float thickness) { render_->SetEdgeThickness(thickness); });
}

void MainWindow::ConnectVertexSignals() {
  connect(settings_widget_, &SettingsWidget::VertexTypeChanged, this,
          [this](SettingsWidget::VertexType type) {
            render_->SetVertexType(static_cast<int>(type));
          });
  connect(settings_widget_, &SettingsWidget::VertexSizeChanged, this,
          [this](float size) { render_->SetVertexSize(size); });
  connect(settings_widget_, &SettingsWidget::VertexColorChanged, this,
          [this](QColor& color) { render_->SetVertexColor(color); });
}

void MainWindow::ConnectBackgroundSignal() {
  connect(settings_widget_, &SettingsWidget::BackgroundColorChanged, this,
          [this](QColor& color) { render_->SetBackgroundColor(color); });
}

void MainWindow::closeEvent(QCloseEvent* event) {
  settings_widget_->SaveSettings();
  QMainWindow::closeEvent(event);
}
