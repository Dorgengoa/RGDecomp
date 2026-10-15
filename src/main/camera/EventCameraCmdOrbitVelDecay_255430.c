#include "types.h"

typedef unsigned __int128 u128;

f32 Cosf_128d30(f32);
f32 Sinf_128fd0(f32);
void VecScale_13be00(void *, void *, f32);
extern f32 D_0047D1FC;
extern f32 D_0047DBBC;
extern f32 D_0047DBC0;
extern f32 D_0047DBC4;
extern f32 D_0047DBC8;
extern f32 D_0047DBCC;

s32 EventCameraCmdOrbitVelDecay_255430(u8 *arg0, u8 *arg1)
{
    f32 t;
    f32 d;
    f32 e;
    s32 n;

    n = *(s32 *)(arg1 + 0x3C);
    if (n <= 0) {
        *(s32 *)(arg1 + 0x3C) = n + 1;
        return 1;
    }
    if (n >= *(s32 *)(arg0 + 0x34)) {
        *(s32 *)(arg1 + 0x3C) = 0;
        *(u128 *)(arg1 + 0x170) = 0;
        return 0;
    }
    VecScale_13be00(arg1 + 0x170, arg1 + 0x170, *(f32 *)(arg0 + 0x30));
    if (*(s32 *)(arg1 + 0x7C) != 0) {
        e = *(f32 *)(arg1 + 0x170);
        t = *(f32 *)(arg1 + 0xA0) + e;
        d = D_0047D1FC;
        *(f32 *)(arg1 + 0xA0) = t;
        if (t > d) {
            *(f32 *)(arg1 + 0xA0) = t - D_0047DBBC;
        } else if (t <= D_0047DBC0) {
            *(f32 *)(arg1 + 0xA0) = t + D_0047DBC4;
        }
        *(f32 *)(arg1 + 0xA4) = *(f32 *)(arg1 + 0xA4) + *(f32 *)(arg1 + 0x174);
        *(f32 *)(arg1 + 0xA8) = *(f32 *)(arg1 + 0xA8) + *(f32 *)(arg1 + 0x178);
    } else {
        e = *(f32 *)(arg1 + 0x170);
        t = *(f32 *)(arg1 + 0x70) + e;
        d = D_0047D1FC;
        *(f32 *)(arg1 + 0x70) = t;
        if (t > d) {
            *(f32 *)(arg1 + 0x70) = t - D_0047DBC4;
        } else if (t <= D_0047DBC8) {
            *(f32 *)(arg1 + 0x70) = t + D_0047DBCC;
        }
        *(f32 *)(arg1 + 0x74) = *(f32 *)(arg1 + 0x74) + *(f32 *)(arg1 + 0x174);
        *(f32 *)(arg1 + 0x78) = *(f32 *)(arg1 + 0x78) + *(f32 *)(arg1 + 0x178);
        *(f32 *)(arg1 + 0x50) = *(f32 *)(arg1 + 0x60) + (*(f32 *)(arg1 + 0x78) * Sinf_128fd0(*(f32 *)(arg1 + 0x70)));
        *(f32 *)(arg1 + 0x54) = *(f32 *)(arg1 + 0x74) + *(f32 *)(arg1 + 0x64);
        *(f32 *)(arg1 + 0x58) = *(f32 *)(arg1 + 0x68) + (*(f32 *)(arg1 + 0x78) * Cosf_128d30(*(f32 *)(arg1 + 0x70)));
    }
    *(s32 *)(arg1 + 0x3C) = *(s32 *)(arg1 + 0x3C) + 1;
    return 1;
}
