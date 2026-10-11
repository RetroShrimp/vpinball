// license:GPLv3+

#pragma once

#include "math/matrix.h"

namespace VPX::VRSeatedView
{

// The headset's right axis remains horizontal when looking straight up. Using
// it avoids the undefined heading of the forward axis during reclined play.
inline float GetHeadYaw(const Matrix3D& headToWorld, float fallback)
{
   const float x = headToWorld.m[0][0];
   const float z = headToWorld.m[0][2];
   return x * x + z * z > 1e-6f ? atan2f(-z, x) : fallback;
}

// Matrices use row vectors. Remove the standing front-edge placement, then place
// the complete cabinet in a tilted seated frame anchored to the recentered eyes.
// Head tracking is applied afterwards, so this frame never follows head motion.
inline Matrix3D GetTransform(const Matrix3D& frontToWorld, const Matrix3D& viewOrientation, const Vertex3Ds& headPosition,
   float height, float distance, float tilt)
{
   return Matrix3D::MatrixInverse(frontToWorld)
      * Matrix3D::MatrixTranslate(0.f, CMTOVPU(distance), CMTOVPU(height))
      * Matrix3D::MatrixRotateX(ANGTORAD(tilt))
      * viewOrientation
      * Matrix3D::MatrixTranslate(headPosition.x, headPosition.y, headPosition.z);
}

}
