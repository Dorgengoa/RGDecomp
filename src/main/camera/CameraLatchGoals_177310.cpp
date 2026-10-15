#include "camera_cpp.h"

/* vm58: the once-per-frame refresh, guarded by the +0x108 latch. Ask the
   camera for its eye and its look-at point, cache both, then derive the
   height difference between them and clamp it into the range the parameter
   block allows. Setting the latch is what makes the rest of the frame take
   the vmC0 path instead of this one. */

extern "C" void CameraLatchGoals_177310(Camera *self)
{
    Vec4 eye;
    Vec4 at;
    CamParams *p;
    f32 limit;

    if (self->latch == 0) {
        self->getEye(&eye);
        self->getAt(&at);
        self->eye = eye;
        self->at = at;

        p = self->getParams();
        p->e = at.y - eye.y;
        if (p->e < p->g) {
            p->e = p->g;
        }
        limit = p->f;
        if (p->e > limit) {
            p->e = limit;
        }
    }
    self->latch = 1;
}
