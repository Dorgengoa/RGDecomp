/* rgp:protos */
#define RGP_SELF_CameraApplyLookAt_1773d0 1
#include "port/game_protos.h"
#line 1
#include "camera.h"

/* vm40: push the camera's pose into the view matrix and on to VU, but only
   when the camera has something at +0x10C to push. */

/*rgp*/

void CameraApplyLookAt_1773d0(Camera *this)
{
    if (this->target != NULL) {
        CameraBaseApplyLookAt_15fa80(this);
    }
}
