/* rgp:protos */
#define RGP_SELF_EvDoorObjGetSidePoint_3039a0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct {
    u8 pad0[0xD0];
    s32 unkD0;
    u8 padD4[0x184 - 0xD4];
    s16 *unk184;
    u8 pad188[0x18A - 0x188];
    s16 unk18A;
} Obj003039A0;

typedef struct {
    f32 x, y, z, w;
} V4_003039A0;

typedef struct {
    u8 b[0x20];
} Buf003039A0;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern f32 D_0047F100;
extern f32 D_0047F104;
extern f32 D_0047F108;
extern f32 D_0047F10C;

s32 EvDoorObjGetSidePoint_3039a0(Obj003039A0 *arg0, s32 arg1, s32 arg2, s32 arg3) {
    V4_003039A0 v __attribute__((aligned(16)));
    __attribute__((aligned(16))) unsigned char rgp_blk1[sizeof(union { char m0[0x30 + sizeof(V4_003039A0)]; char m1[0x20 + sizeof(V4_003039A0)]; char m2[0x0 + sizeof(Buf003039A0)]; char m3[0x40]; char m4[0x30]; })]; typedef char rgp_blk1_chk0[(0x0) + sizeof(Buf003039A0) <= (0x20) && (0x0) >= 0 ? 1 : -1]; typedef char rgp_blk1_chk1[(0x20) + sizeof(V4_003039A0) <= (0x30) && (0x20) >= 0 ? 1 : -1];
    
    
    s32 n;
    s32 i;

    if (!(arg0->unkD0 & 0x10000000)) {
        return 0;
    }
    if (TargetRefIsActive_2e6f00((u8 *)arg0 + 0xA0) == 0) {
        return 0;
    }
    v.x = D_0047F100;
    v.y = D_0047F104;
    v.z = D_0047F108;
    v.w = D_0047F10C;
    v.y = EvDoorObjGetHeight_304060(arg0);
    n = arg0->unk18A;
    if (n == 1 || (n == 2 && arg0->unk184[0] == arg0->unk184[1])) {
        XformGetUnscaledMatrix_2e7760((u8 *)arg0 + 0x10, &(*(Buf003039A0 *)(rgp_blk1 + 0x0)));
        if (VecDotDiff_1cba40(arg2, &(*(V4_003039A0 *)(rgp_blk1 + 0x30)), &(*(V4_003039A0 *)(rgp_blk1 + 0x20))) < 0.0f) {
            v.z = v.z * -1.0f;
        }
    } else {
        for (i = 1; i < n; i++) {
            if (arg3 == arg0->unk184[i]) {
                break;
            }
        }
        if (i < n) {
            v.z = v.z * -1.0f;
        }
    }
    XformTransformPointUnscaled_2e7550((u8 *)arg0 + 0x10, arg1, &v);
    return 1;
}
