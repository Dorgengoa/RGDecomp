/* rgp:protos */
#define RGP_SELF_EvDoorObjAreaCheckFacingMaybe_3040b0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* The case-1 arm FALLS THROUGH into case 2, which is why the same
   VecDot3_1cba90 sign test appears twice back to back.
   Stack locals are allocated in REVERSE declaration order: v4 (0xA0),
   v3 (0x90), m (0x70, 32 bytes), v1 (0x60), v0 (0x50). */

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 EvDoorObjAreaCheckFacingMaybe_3040b0(u8 *a, void *b, f32 t)
{
    __attribute__((aligned(16))) unsigned char rgp_blk1[sizeof(union { char m0[0x0 + sizeof(f32[8])]; char m1[0x20 + sizeof(f32[4])]; char m2[0x30 + sizeof(f32[4])]; char m3[0x40]; char m4[0x30]; })]; typedef char rgp_blk1_chk0[(0x0) + sizeof(f32[8]) <= (0x20) && (0x0) >= 0 ? 1 : -1]; typedef char rgp_blk1_chk1[(0x20) + sizeof(f32[4]) <= (0x30) && (0x20) >= 0 ? 1 : -1];
    
    
    f32 v1[4] __attribute__((aligned(16)));
    f32 v0[4] __attribute__((aligned(16)));
    u8 *q;
    u32 n;
    s32 r;

    r = EvDoorObjAreaCheck_3041f0(a, b);
    if (r == 0) {
        return 0;
    }
    XformGetUnscaledMatrix_2e7760(a + 0x10, (*(f32 (*)[8])(rgp_blk1 + 0x0)));
    VecSub_1cbd00(v1, (*(f32 (*)[4])(rgp_blk1 + 0x30)), b);
    VecScale_1cbca0(v1, (*(f32 (*)[4])(rgp_blk1 + 0x20)), VecDot3_1cba90((*(f32 (*)[4])(rgp_blk1 + 0x20)), v1));
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
