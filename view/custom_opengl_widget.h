#ifndef CUSTOM_OPENGL_WIDGET_H
#define CUSTOM_OPENGL_WIDGET_H

#include <QKeyEvent>
#include <QOpenGLBuffer>
#include <QOpenGLFunctions>
#include <QOpenGLShader>
#include <QOpenGLShaderProgram>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLWidget>
#include <span>

#include "edge.h"
#include "projection.h"
#include "vertex.h"

/**
 * @file custom_opengl_widget.h
 */

class CustomOpenGLWidget : public QOpenGLWidget, protected QOpenGLFunctions {
 public:
  enum VertexType { kNone = 4, kCircle, kSquare };

  explicit CustomOpenGLWidget(QWidget *parent = nullptr);

  // Updates vertex/edges info and calls update()
  void UpdateWidget(std::span<const s21::Vertex> Vertexes,
                    std::span<const s21::Edge> Edges);

  void SetProjectionType(std::unique_ptr<ProjectionStrategy> strategy);

  void SetEdgeType(const bool is_dashed);
  void SetEdgeColor(QColor &color);
  void SetEdgeThickness(float thickness);

  void SetBackgroundColor(QColor &color);

  void SetVertexColor(QColor &color);
  void SetVertexType(int vertex_type);
  void SetVertexSize(float vertex_size);

 protected:
  void initializeGL() override;

  void resizeGL(int w, int h) override;

  void paintGL() override;

  void mousePressEvent(QMouseEvent *event) override;

  void mouseMoveEvent(QMouseEvent *event) override;

 private:
  void FillVertexArray(std::span<const s21::Vertex> Vertexes,
                       std::span<const s21::Edge> Edges);
  void InitializeGLBuffers();
  void DestroyBuffers();
  void CalculateEdgeLengths(std::span<const s21::Vertex> Vertexes,
                            std::span<const s21::Edge> Edges);
  void CreateEdgeProgressArray(const int &count);
  void FitModelIntoView(std::span<const s21::Vertex> Vertexes);
  void LoadShaders();
  void UpdateModelView();
  void BindLineShaders();
  void BindPointShaders();
  void UpdateProjection();

 private:
  std::unique_ptr<ProjectionStrategy> projection_strategy_;

  QColor background_color_;

  QOpenGLBuffer line_progress_vbo_;
  std::vector<float> edge_progress_;
  QOpenGLBuffer edge_lengths_vbo_;
  std::vector<float> edge_lengths_;
  bool is_dashed_;
  QColor edge_color_;
  float edge_thickness_px_;

  QOpenGLShaderProgram shader_program_points_;
  QColor vertex_color_;
  float vertex_size_;
  VertexType vertex_type_;

  QOpenGLShaderProgram shader_program_lines_;
  QOpenGLVertexArrayObject vao_;
  QOpenGLBuffer vbo_;
  QMatrix4x4 projection_;
  QMatrix4x4 modelview_;
  std::vector<GLfloat> vertex_array_;
  std::size_t vertex_count_ = 0;
  QVector2D view_size_;

  QPoint last_mouse_position_;
  GLfloat camera_rotation_x_ = 0.0f;
  GLfloat camera_rotation_y_ = 0.0f;
};

#endif  // CUSTOM_OPENGL_WIDGET_H
