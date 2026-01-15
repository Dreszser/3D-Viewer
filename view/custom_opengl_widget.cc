#include "custom_opengl_widget.h"

#include <QApplication>
#include <QCoreApplication>
#include <QDebug>
#include <QDir>
#include <cmath>

/**
 * @file custom_opengl_widget.cc
 */

CustomOpenGLWidget::CustomOpenGLWidget(QWidget* parent)
    : QOpenGLWidget(parent) {
  setFocusPolicy(Qt::StrongFocus);
  setFocus();
};

void CustomOpenGLWidget::initializeGL() {
  initializeOpenGLFunctions();
  LoadShaders();
  glEnable(GL_PROGRAM_POINT_SIZE);

  QColor color = this->palette().color(QPalette::Window);
  glClearColor(color.redF(), color.greenF(), color.blueF(), 1.0f);
}

void CustomOpenGLWidget::LoadShaders() {
  shader_program_lines_.addShaderFromSourceFile(
      QOpenGLShader::Vertex, ":/shaders/view/shaders/line_vertex_shader.vsh");
  shader_program_lines_.addShaderFromSourceFile(
      QOpenGLShader::Fragment,
      ":/shaders/view/shaders/line_fragment_shader.fsh");
  shader_program_lines_.addShaderFromSourceFile(
      QOpenGLShader::Geometry,
      ":/shaders/view/shaders/line_geometry_shader.gsh");

  shader_program_points_.addShaderFromSourceFile(
      QOpenGLShader::Vertex, ":/shaders/view/shaders/point_vertex_shader.vsh");
  shader_program_points_.addShaderFromSourceFile(
      QOpenGLShader::Fragment,
      ":/shaders/view/shaders/point_fragment_shader.fsh");

  if (!(shader_program_lines_.link() || shader_program_points_.link())) {
    qDebug() << "Shader linking failed:" << shader_program_lines_.log();
    qDebug() << "Shader linking failed:" << shader_program_points_.log();
  }
}

void CustomOpenGLWidget::FillVertexArray(std::span<const s21::Vertex> Vertexes,
                                         std::span<const s21::Edge> Edges) {
  for (size_t i = 0; i < Edges.size(); ++i) {
    const auto& v1 = Vertexes[Edges[i].GetStart()];
    const auto& v2 = Vertexes[Edges[i].GetEnd()];

    vertex_array_[i * 6] = v1.x;
    vertex_array_[i * 6 + 1] = v1.y;
    vertex_array_[i * 6 + 2] = v1.z;

    vertex_array_[i * 6 + 3] = v2.x;
    vertex_array_[i * 6 + 4] = v2.y;
    vertex_array_[i * 6 + 5] = v2.z;
  }
}

void CustomOpenGLWidget::InitializeGLBuffers() {
  makeCurrent();
  DestroyBuffers();

  vao_.create();
  vao_.bind();

  vbo_.create();
  vbo_.bind();
  vbo_.setUsagePattern(QOpenGLBuffer::DynamicDraw);
  vbo_.allocate(vertex_array_.data(), vertex_array_.size() * sizeof(GLfloat));
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
  vbo_.release();

  line_progress_vbo_.create();
  line_progress_vbo_.bind();
  line_progress_vbo_.allocate(edge_progress_.data(),
                              edge_progress_.size() * sizeof(GLfloat));
  glEnableVertexAttribArray(1);
  glVertexAttribPointer(1, 1, GL_FLOAT, GL_FALSE, 0, nullptr);
  line_progress_vbo_.release();

  edge_lengths_vbo_.create();
  edge_lengths_vbo_.bind();
  edge_lengths_vbo_.allocate(edge_lengths_.data(),
                             edge_lengths_.size() * sizeof(GLfloat));
  glEnableVertexAttribArray(2);
  glVertexAttribPointer(2, 1, GL_FLOAT, GL_FALSE, 0, nullptr);
  edge_lengths_vbo_.release();

  vao_.release();

  doneCurrent();
}

void CustomOpenGLWidget::DestroyBuffers() {
  if (vao_.isCreated()) vao_.destroy();
  if (vbo_.isCreated()) vbo_.destroy();
  if (edge_lengths_vbo_.isCreated()) edge_lengths_vbo_.destroy();
  if (line_progress_vbo_.isCreated()) line_progress_vbo_.destroy();
}

void CustomOpenGLWidget::resizeGL(int w, int h) {
  UpdateProjection();
  view_size_.setX(static_cast<float>(w));
  view_size_.setY(static_cast<float>(h));
}

void CustomOpenGLWidget::SetProjectionType(
    std::unique_ptr<ProjectionStrategy> strategy) {
  projection_strategy_ = std::move(strategy);
  UpdateProjection();
  update();
}

void CustomOpenGLWidget::SetEdgeType(const bool is_dashed) {
  is_dashed_ = is_dashed;
  update();
}

void CustomOpenGLWidget::SetEdgeColor(QColor& color) {
  edge_color_ = color;
  update();
}

void CustomOpenGLWidget::SetEdgeThickness(float thickness) {
  edge_thickness_px_ = thickness;
  update();
}

void CustomOpenGLWidget::SetBackgroundColor(QColor& color) {
  background_color_ = color;
  update();
}

void CustomOpenGLWidget::SetVertexColor(QColor& color) {
  vertex_color_ = color;
  update();
}

void CustomOpenGLWidget::SetVertexType(int vertex_type) {
  vertex_type_ = static_cast<VertexType>(vertex_type);
  update();
}

void CustomOpenGLWidget::SetVertexSize(float vertex_size) {
  vertex_size_ = vertex_size;
  update();
}

void CustomOpenGLWidget::UpdateProjection() {
  if (projection_strategy_) {
    projection_strategy_->Apply(projection_, 1.0f, width(), height());
  }
}

void CustomOpenGLWidget::paintGL() {
  if (!vao_.isCreated()) return;

  glClearColor(background_color_.redF(), background_color_.greenF(),
               background_color_.blueF(), 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  UpdateModelView();

  vao_.bind();
  vbo_.bind();

  vbo_.write(0, vertex_array_.data(), vertex_array_.size() * sizeof(GLfloat));

  BindLineShaders();
  glDrawArrays(GL_LINES, 0, vertex_count_);

  BindPointShaders();
  glDrawArrays(GL_POINTS, 0, vertex_count_);

  vbo_.release();
  vao_.release();
}

void CustomOpenGLWidget::UpdateModelView() {
  constexpr float kViewModifier = 5.0f;

  modelview_.setToIdentity();
  modelview_.translate(0.0f, 0.0f, -kViewModifier);
  modelview_.rotate(camera_rotation_x_, 1.0f, 0.0f, 0.0f);
  modelview_.rotate(camera_rotation_y_, 0.0f, 1.0f, 0.0f);
}

void CustomOpenGLWidget::BindLineShaders() {
  shader_program_lines_.bind();
  shader_program_lines_.setUniformValue("projection", projection_);
  shader_program_lines_.setUniformValue("modelview", modelview_);
  shader_program_lines_.setUniformValue("dash_length", is_dashed_ * 0.1f);
  shader_program_lines_.setUniformValue("edge_color", edge_color_.redF(),
                                        edge_color_.greenF(),
                                        edge_color_.blueF());
  shader_program_lines_.setUniformValue("view_size", view_size_);
  shader_program_lines_.setUniformValue("edge_thickness", edge_thickness_px_);
}

void CustomOpenGLWidget::BindPointShaders() {
  shader_program_points_.bind();
  shader_program_points_.setUniformValue("vertex_color", vertex_color_.redF(),
                                         vertex_color_.greenF(),
                                         vertex_color_.blueF());
  shader_program_points_.setUniformValue("projection", projection_);
  shader_program_points_.setUniformValue("modelview", modelview_);
  shader_program_points_.setUniformValue("vertex_size", vertex_size_);
  shader_program_points_.setUniformValue("vertex_type",
                                         static_cast<int>(vertex_type_));
}

void CustomOpenGLWidget::UpdateWidget(std::span<const s21::Vertex> Vertexes,
                                      std::span<const s21::Edge> Edges) {
  std::size_t size = Edges.size() * 2;
  bool size_changed = (size != vertex_count_);

  if (size_changed) {
    vertex_array_.clear();
    vertex_array_.resize(size * 3);
  }

  FillVertexArray(Vertexes, Edges);

  if (size_changed) {
    vertex_count_ = size;

    CreateEdgeProgressArray(size);

    CalculateEdgeLengths(Vertexes, Edges);

    InitializeGLBuffers();

    UpdateProjection();
  }

  update();
}

void CustomOpenGLWidget::mousePressEvent(QMouseEvent* event) {
  last_mouse_position_ = event->pos();
}

void CustomOpenGLWidget::mouseMoveEvent(QMouseEvent* event) {
  constexpr float kSensitivity = 0.5f;

  QPoint delta = event->pos() - last_mouse_position_;
  last_mouse_position_ = event->pos();

  if (event->buttons() & Qt::LeftButton) {
    camera_rotation_x_ += delta.y() * kSensitivity;
    camera_rotation_y_ += delta.x() * kSensitivity;
  }

  update();
}

void CustomOpenGLWidget::CreateEdgeProgressArray(const int& count) {
  edge_progress_.clear();
  edge_progress_.resize(count);

  for (int i = 0; i < count; ++i) {
    edge_progress_[i] = static_cast<float>(i & 1);
  }
}

void CustomOpenGLWidget::CalculateEdgeLengths(
    std::span<const s21::Vertex> Vertexes, std::span<const s21::Edge> Edges) {
  edge_lengths_.clear();
  edge_lengths_.resize(vertex_count_);

  int size = Edges.size();

  for (int i = 0; i < size; ++i) {
    const auto& v1 = Vertexes[Edges[i].GetStart()];
    const auto& v2 = Vertexes[Edges[i].GetEnd()];

    float dx = v1.x - v2.x;
    float dy = v1.y - v2.y;
    float dz = v1.z - v2.z;

    float length = sqrt(dx * dx + dy * dy + dz * dz);

    edge_lengths_[i * 2] = length;
    edge_lengths_[i * 2 + 1] = length;
  }
}
