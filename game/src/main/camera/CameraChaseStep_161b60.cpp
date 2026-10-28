#include "camera_cpp.h"

/* vmC8: the eye lerp. Both the eye and the look-at point chase their targets
   by a fixed fraction each frame -- +0x50 moves a 1/lag2 step toward +0xE0,
   +0x60 a 1/lag step toward +0xF0. The lag divisors are what CameraSetLag_177170
   sets, and 8.0 in the town means "close an eighth of the gap per frame".

   MATCHED. The last two words were the residue written off as "retail reuses
   the dead float-argument register $f12 as a temp": it is not a temp at all --
   vtable slot +0x30 (`finish`) TAKES A FLOAT, and retail loads +0x70 straight
   into $f12 as the outgoing argument, then compares that same register against
   zero. The load IS the argument setup. Measured: named locals for the two
   1/lag scales, a named local for the tested value, and reusing the parameter
   `t` as the scratch all left the two words EXACTLY unchanged; declaring the
   argument closed both at once.

   +0x1FC is a one-shot skip: a camera that has just been placed does not
   chase on the frame it was placed.

   Written against the C++ class so the three vtable calls go through $t9 --
   see include/camera_cpp.h. */

extern "C" void CameraTweenStep_1771a0(Camera *camera);
extern "C" void VecSub_13be40(Vec4 *out, const Vec4 *a, const Vec4 *b);   /* out = a - b */
extern "C" void VecScale_13be00(Vec4 *out, const Vec4 *v, f32 scale);
extern "C" void VecAddInPlace_13e070(Vec4 *acc, const Vec4 *v);                  /* acc += v */

extern "C" void CameraChaseStep_161b60(Camera *self, f32 t)
{
    Vec4 stepEye __attribute__((aligned(16)));
    Vec4 stepAt __attribute__((aligned(16)));

    if (self->skipOnce == 1) {
        self->skipOnce = 0;
        return;
    }
    if (self->latch == 0) {
        CameraTweenStep_1771a0(self);
        return;
    }

    if (t < 0.0f) {
        if (self->hasRetarget != 0) {
            self->retarget(self->retargetT);
        }
    }

    VecSub_13be40(&stepEye, &self->eye, &self->eyeNow);
    VecScale_13be00(&stepEye, &stepEye, 1.0f / self->lag2);
    VecAddInPlace_13e070(&self->eyeNow, &stepEye);

    VecSub_13be40(&stepAt, &self->at, &self->atNow);
    VecScale_13be00(&stepAt, &stepAt, 1.0f / self->lag);
    VecAddInPlace_13e070(&self->atNow, &stepAt);

    if (self->latch != 0) {
        self->toView();
        if (self->unk70 != 0.0f) {
            self->finish(self->unk70);
        }
    }
}
