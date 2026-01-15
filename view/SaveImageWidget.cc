#include "SaveImageWidget.h"

#include <QFileDialog>
#include <QHBoxLayout>
#include <QImageWriter>
#include <QLabel>

/**
 * @file SaveImageWidget.cc
 */

SaveImageWidget::SaveImageWidget(QOpenGLWidget* Render, QWidget* parent)
    : QWidget(parent), render_(Render), gifImage_(nullptr) {
  QHBoxLayout* Layout_ = new QHBoxLayout(this);
  saveImageTo_ = new QPushButton("Save image");
  startRecord_ = new QPushButton("Start record");
  stopRecord_ = new QPushButton("Stop record");
  startRecord_->setEnabled(false);
  stopRecord_->setEnabled(false);
  getFrameTimer_ = new QTimer();
  endRecord_ = new QTimer();
  Layout_->addWidget(saveImageTo_);
  Layout_->addWidget(startRecord_);
  getFrameTimer_->setInterval(100);
  endRecord_->setInterval(5099);
  Layout_->addWidget(stopRecord_);
  connect(saveImageTo_, &QPushButton::clicked, this, &SaveImageWidget::SaveImg);
  connect(this, &SaveImageWidget::SaveToFile, this, &SaveImageWidget::SaveFile);
  connect(startRecord_, &QPushButton::clicked, this,
          &SaveImageWidget::StartRecord);
  connect(getFrameTimer_, &QTimer::timeout, this, &SaveImageWidget::AddImage);
  connect(endRecord_, &QTimer::timeout, this, &SaveImageWidget::StopRecord);
}

void SaveImageWidget::SaveImg() {
  QString selected_format;
  QString file_name =
      QFileDialog::getSaveFileName(this, "Save file...", QDir::homePath(),
                                   "Bitmap image file (*.bmp);;JPEG image file "
                                   "(*.jpg);;GIF slideshow(*.gif)",
                                   &selected_format);

  if (!file_name.isEmpty()) {
    if (!file_name.contains('.')) {
      if (selected_format.contains("bmp"))
        file_name += ".bmp";
      else if (selected_format.contains("jpg"))
        file_name += ".jpg";
      else if (selected_format.contains("gif"))
        file_name += ".gif";
    }
    if (selected_format.contains("gif")) {
      startRecord_->setEnabled(true);
      GifImageFileName_ = file_name;
    } else {
      emit SaveToFile(file_name);
    }
  }
}

void SaveImageWidget::SaveFile(const QString& file_name) {
  render_->grabFramebuffer().save(file_name);
}

void SaveImageWidget::StartRecord() {
  if (gifImage_) {
    delete gifImage_;
    gifImage_ = nullptr;
  }
  stopRecord_->setEnabled(true);
  startRecord_->setEnabled(false);
  saveImageTo_->setEnabled(false);
  gifImage_ = new QGifImage(QSize(640, 480));
  gifImage_->setDefaultDelay(100);
  getFrameTimer_->start();
  endRecord_->start();
}

void SaveImageWidget::StopRecord() {
  stopRecord_->setEnabled(false);
  saveImageTo_->setEnabled(true);
  getFrameTimer_->stop();
  endRecord_->stop();
  gifImage_->save(GifImageFileName_);
  delete gifImage_;
  gifImage_ = nullptr;
}

void SaveImageWidget::AddImage() {
  QImage img =
      render_->grabFramebuffer().scaled(640, 480, Qt::IgnoreAspectRatio);
  gifImage_->addFrame(img);
}
