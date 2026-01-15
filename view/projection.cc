#include "projection.h"

/**
 * @file projection.cc
 */

void ParallelProjection::Apply(QMatrix4x4& projection, float radius, int w,
                               int h) const {
  constexpr float kFOV = 45.0f;
  constexpr float kNearPlane = 0.1f;
  constexpr float kFarPlaneModifier = 10.0f;

  projection.setToIdentity();
  projection.perspective(kFOV, float(w) / h, kNearPlane,
                         radius * kFarPlaneModifier);
}

void CentralProjection::Apply(QMatrix4x4& projection, float radius, int w,
                              int h) const {
  const float aspect = float(w) / h;

  projection.setToIdentity();
  projection.ortho(-radius * aspect, radius * aspect, -radius, radius,
                   -radius * 10.0f, radius * 10.0f);
}
