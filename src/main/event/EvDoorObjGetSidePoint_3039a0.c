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

f32 VecDotDiff_1cba40(s32, V4_003039A0 *, V4_003039A0 *);
s32 TargetRefIsActive_2e6f00(void *);
void XformTransformPointUnscaled_2e7550(void *, s32, V4_003039A0 *);
void XformGetUnscaledMatrix_2e7760(void *, Buf003039A0 *);
f32 EvDoorObjGetHeight_304060(Obj003039A0 *);
extern f32 D_0047F100;
extern f32 D_0047F104;
extern f32 D_0047F108;
extern f32 D_0047F10C;

s32 EvDoorObjGetSidePoint_3039a0(Obj003039A0 *arg0, s32 arg1, s32 arg2, s32 arg3) {
    V4_003039A0 v;
    V4_003039A0 a;
    V4_003039A0 b;
    Buf003039A0 m;
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
        XformGetUnscaledMatrix_2e7760((u8 *)arg0 + 0x10, &m);
        if (VecDotDiff_1cba40(arg2, &a, &b) < 0.0f) {
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
