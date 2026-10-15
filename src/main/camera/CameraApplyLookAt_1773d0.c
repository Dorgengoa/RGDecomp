#include "camera.h"

/* vm40: push the camera's pose into the view matrix and on to VU, but only
   when the camera has something at +0x10C to push. */

extern void CameraBaseApplyLookAt_15fa80(Camera *camera);

void CameraApplyLookAt_1773d0(Camera *this)
{
    if (this->target != NULL) {
        CameraBaseApplyLookAt_15fa80(this);
    }
}
