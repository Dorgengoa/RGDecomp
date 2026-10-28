#include "types.h"
#include "vec.h"
#include "camera_cpp.h"

/* Push the two chase vectors through the camera's own matrix at +0x80 and
   hand both, plus the float at +0x70, to the virtual at table offset +0x20.
   This is the helper CameraApplyLookAt_1773d0 calls.

   ★ The two locals are 0x10 bytes each, not 0x40: the frame is 0x40 all in,
   which is what says MtxMulPoint_13c890's first argument is a Vec4 and its second
   a Mtx4 -- the same reading FrameTransformPoint_148f60 gives from the other side.

   ⚠ It has to be C++. The C form -- a `CameraVtbl *` struct of function
   pointers, as `camera.h` models it -- compiles to `lw v0 / lw v0 / jalr v0`
   and misses by exactly three words. This is the rule `camera_cpp.h` already
   states in its own header comment, met at a new site. */

extern "C" void MtxMulPoint_13c890(Vec4 *out, const Mtx4 *m, const Vec4 *v);

extern "C" void CameraBaseApplyLookAt_15fa80(Camera *self)
{
    Vec4 at __attribute__((aligned(16)));
    Vec4 eye __attribute__((aligned(16)));

    MtxMulPoint_13c890(&at, &self->xform, &self->atNow);
    MtxMulPoint_13c890(&eye, &self->xform, &self->eyeNow);
    self->slot20(self->unk70, &at, &eye);
}
