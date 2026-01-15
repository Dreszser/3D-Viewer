#ifndef SAVEIMAGEWIDGET_H
#define SAVEIMAGEWIDGET_H

#include <QOpenGLWidget>
#include <QPushButton>
#include <QTimer>
#include <QWidget>

#include "gifimage/qgifimage.h"

/**
 * @file SaveImageWidget.h
 */

class SaveImageWidget : public QWidget {
  Q_OBJECT
 private:
  QPushButton* saveImageTo_;
  QPushButton* startRecord_;
  QPushButton* stopRecord_;
  QTimer* getFrameTimer_;
  QTimer* endRecord_;
  QOpenGLWidget* render_;
  QGifImage* gifImage_;
  QString GifImageFileName_;

 public:
  SaveImageWidget(QOpenGLWidget* Render, QWidget* parent = nullptr);
 signals:
  void SaveToFile(const QString& file_name);
 private slots:
  void SaveImg();
  void SaveFile(const QString& file_name);
  void StartRecord();
  void StopRecord();
  void AddImage();
};

#endif  // SAVEIMAGEWIDGET_H
