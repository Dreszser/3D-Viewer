#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QVBoxLayout>

#include "../common/IVIew.h"
#include "../controller/controller.h"
#include "SaveImageWidget.h"
#include "custom_opengl_widget.h"
#include "settingswidget.h"

/**
 * @file mainwindow.h
 */

class MainWindow : public QMainWindow, public s21::IView {
  Q_OBJECT

 public:
  MainWindow();

  void updateModelVertexes(const int vertexesSize) override;
  void updateModelEdges(const int edgesSize) override;
  void updateView(std::span<const s21::Vertex> Vertexes,
                  std::span<const s21::Edge> Edges) override;
  void updateFileName(std::string FileName) override;
  void initDefaultData() override;
  void errorHandler() override;

 protected:
  void closeEvent(QCloseEvent* event) override;

 private slots:
  void handleOpenFile();

 private:
  s21::Controller* controller_;
  CustomOpenGLWidget* render_;
  QLabel* fileName_;
  QLabel* vertexes_;
  QLabel* edges_;
  QPushButton* readFile_;
  ControlWidget* scale_;
  ControlWidget* rotateX_;
  ControlWidget* rotateY_;
  ControlWidget* rotateZ_;
  ControlWidget* moveX_;
  ControlWidget* moveY_;
  ControlWidget* moveZ_;
  SettingsWidget* settings_widget_;
  SaveImageWidget* save_image_;
  QGridLayout* layout_;

 private:
  void ConnectProjectionSignal();
  void ConnectEdgeSignals();
  void ConnectBackgroundSignal();
  void ConnectVertexSignals();
  void InitSliders();
  void InitSettings();
  void SetUpLayout();
};

#endif  // MAINWINDOW_H
