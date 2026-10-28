extern "C" {
/* Normalize heading in place to preserve its floating-point register lifetime. */
#include "types.h"
#include "vec.h"

extern f32 Cosf_128d30(f32);
extern f32 Sinf_128fd0(f32);
extern f32 Atan2f_1291a8(f32, f32);
extern f32 VecLengthXZ_1cb490(const Vec4 *);
extern f32 VecLength_1cb4c0(const Vec4 *);
extern void VecSub_1cbd00(Vec4 *, const Vec4 *, const Vec4 *);
extern void VecAddXyzW1_1cbd80(s32, Vec4 *, Vec4 *);
extern f32 AngleWrap_1cbf30(f32);
extern f32 D_0047D8DC;
extern f32 D_0047D8E0;

void CameraOrbitCalcMaybe_1c9020(s32  raw_arg0,Vec4 * raw_arg1, Vec4 *arg2, Vec4 *arg3, f32 fparg0, f32 fparg1, f32 fparg2, f32 fparg3, f32 fparg4)
{
s32 arg0 = raw_arg0;
Vec4 *arg1 = raw_arg1;
    Vec4 sp70 __attribute__((aligned(16)));
    f32 dist3;
    f32 magXZ;
    f32 yaw;
    f32 heading;
    f32 sinH;
    f32 cosH;

    f32 pitch;
    f32 radius;
    f32 k;

    VecSub_1cbd00(&sp70, arg2, arg3);
    dist3 = VecLength_1cb4c0(&sp70);
    magXZ = VecLengthXZ_1cb490(&sp70);
    yaw = Atan2f_1291a8(sp70.y, magXZ);
    heading = Atan2f_1291a8(sp70.x, sp70.z);

    sinH = Sinf_128fd0(heading);
    cosH = Cosf_128d30(heading);
    arg1->x = arg3->x + fparg0 * cosH + fparg1 * sinH;
    arg1->y = arg3->y;
    cosH = Cosf_128d30(heading);
    sinH = Sinf_128fd0(heading);
    arg1->z = arg3->z - fparg0 * sinH + fparg1 * cosH;
    arg1->w = 1.0f;

    heading = AngleWrap_1cbf30(heading + fparg2);
    pitch = yaw + fparg3;
    radius = dist3 + fparg4;
    radius = radius > 10.0f ? radius : 10.0f;
    pitch = pitch < D_0047D8DC ? pitch : D_0047D8DC;
    pitch = pitch > D_0047D8E0 ? pitch : D_0047D8E0;

    sp70.x = (radius * Cosf_128d30(pitch)) * Sinf_128fd0(heading);
    sp70.y = radius * Sinf_128fd0(pitch);
    sp70.z = (radius * Cosf_128d30(pitch)) * Cosf_128d30(heading);
    sp70.w = 0.0f;
    VecAddXyzW1_1cbd80(arg0, arg1, &sp70);
}

}
