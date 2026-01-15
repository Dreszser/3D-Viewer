#ifndef PROJECTION_H
#define PROJECTION_H

#include <QMatrix4x4>

/**
 * @file projection.h
 */

class ProjectionStrategy {
 public:
  virtual ~ProjectionStrategy() = default;
  virtual void Apply(QMatrix4x4& projection, float radius, int w,
                     int h) const = 0;
};

class ParallelProjection : public ProjectionStrategy {
  void Apply(QMatrix4x4& projection, float radius, int w, int h) const override;
};

class CentralProjection : public ProjectionStrategy {
  void Apply(QMatrix4x4& projection, float radius, int w, int h) const override;
};

#endif  // PROJECTION_H
