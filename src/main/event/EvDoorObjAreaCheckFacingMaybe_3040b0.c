#include "types.h"

/* The case-1 arm FALLS THROUGH into case 2, which is why the same
   VecDot3_1cba90 sign test appears twice back to back.
   Stack locals are allocated in REVERSE declaration order: v4 (0xA0),
   v3 (0x90), m (0x70, 32 bytes), v1 (0x60), v0 (0x50). */

extern s32 EvDoorObjAreaCheck_3041f0(u8 *a, void *b);
extern void XformGetUnscaledMatrix_2e7760(u8 *a, f32 *m);
extern void VecSub_1cbd00(f32 *out, f32 *in, void *b);
extern f32 VecDot3_1cba90(f32 *a, f32 *b);
extern void VecScale_1cbca0(f32 *a, f32 *b, f32 t);
extern f32 Sinf_128fd0(f32 t);
extern f32 Cosf_128d30(f32 t);

s32 EvDoorObjAreaCheckFacingMaybe_3040b0(u8 *a, void *b, f32 t)
{
    f32 v4[4];
    f32 v3[4];
    f32 m[8];
    f32 v1[4];
    f32 v0[4];
    u8 *q;
    u32 n;
    s32 r;

    r = EvDoorObjAreaCheck_3041f0(a, b);
    if (r == 0) {
        return 0;
    }
    XformGetUnscaledMatrix_2e7760(a + 0x10, m);
    VecSub_1cbd00(v1, v4, b);
    VecScale_1cbca0(v1, v3, VecDot3_1cba90(v3, v1));
    q = (u8 *)v0;
    n = 0x10;
    if (q != 0) {
        do {
            *q = 0;
            n--;
            q++;
        } while (n != 0);
    }
    v0[0] = Sinf_128fd0(t);
    v0[2] = Cosf_128d30(t);
    switch (r) {
    case 1:
        if (VecDot3_1cba90(v1, v0) < 0.0f) {
            return 0;
        }
        /* falls through */
    case 2:
        if (VecDot3_1cba90(v1, v0) < 0.0f) {
            return 0;
        }
        break;
    }
    return r;
}
