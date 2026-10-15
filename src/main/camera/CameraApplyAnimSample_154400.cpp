#include "camera_cpp.h"

/* Install a sampled keyframe onto a camera. The sample carries a flag per
   channel, so a track that animates only position leaves orientation alone.

   Two shapes. With a rotation channel the quaternion at +0x20 is turned into
   a matrix and handed to the camera through the vtable, and position goes the
   same way. Without one, the vectors are written straight into +0x50/+0x60 --
   the eye and look-at that CameraChaseStep_161b60 chases -- and the camera is told to
   refresh its view matrix.

   The angle channel is stored in RADIANS and handed over in DEGREES: the
   0x43340000 in the disassembly is 180.0f, divided by the PI at 0x47D1FC. */

typedef struct Sample {
    s32 hasRot;    /* +0x00 */
    s32 hasEye;    /* +0x04 */
    s32 hasAt;     /* +0x08 */
    s32 hasAngle;  /* +0x0C */
    s32 hasRoll;   /* +0x10 */
    f32 angle;     /* +0x14, radians */
    f32 roll;      /* +0x18 */
    u8 pad1c[0x4];
    Vec4 rot;      /* +0x20, quaternion */
    Vec4 at;       /* +0x30 */
    Vec4 eye;      /* +0x40 */
} Sample;

/* PI as the gp-relative constant the reference names, not a literal -- a
   literal would be mwcc's own @N label. See CameraTrackUpdate_305960. */
extern f32 D_0047D1FC;

extern "C" void MatFromQuatFull_13c4c0(Mtx4 *out, const Vec4 *quat);

extern "C" void CameraApplyAnimSample_154400(Sample *s, Camera *camera)
{
    Mtx4 m;

    if (s->hasRot != 0) {
        MatFromQuatFull_13c4c0(&m, &s->rot);
        camera->setMatrix(&m);
        if (s->hasAt != 0) {
            camera->setPos(&s->at);
        }
    } else {
        if (s->hasAt != 0) {
            camera->atNow = s->at;
        }
        if (s->hasEye != 0) {
            camera->eyeNow = s->eye;
        }
        if (s->hasRoll != 0) {
            camera->unk70 = s->roll;
        }
        camera->toView();
    }

    if (s->hasAngle != 0) {
        camera->setAngle(180.0f * s->angle / D_0047D1FC);
    }
}
