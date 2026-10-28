/* rgp:protos */
#define RGP_SELF_CameraSetLag_177170 1
#include "port/game_protos.h"
#line 1
#include "camera.h"

/* Set the eye lag divisor (+0x100, measured 8.0 in the town) and its
   companion at +0x104. A negative companion means "same as the first" --
   and it is read back out of the struct rather than reused from the
   argument, which is what the second load is. */

void CameraSetLag_177170(Camera *this, f32 lag, f32 lag2)
{
    this->lag = lag;
    if (lag2 < 0.0f) {
        this->lag2 = this->lag;
    } else {
        this->lag2 = lag2;
    }
}
