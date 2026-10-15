#include "types.h"

void CharaTintRequest_21f0e0(s8 *arg0, s32 v, s8 arg2, f32 f0, f32 f1, f32 f2, f32 f3, f32 f4) {
    s32 cur;

    if (v != 0) {
        cur = arg0[0x18];
        switch (cur) {
        case 0:
        case -1:
            goto a;
        case 6:
            if (v != -1) break;
            goto a;
        case 1:
        case 2:
            if (!(v < cur) && v != -1) break;
        default:
            if (cur < v && v != -1) break;
        a:
            if (v == -1) v = 0;
            arg0[0x18] = v;
            arg0[0x19] = arg2;
            *(s32 *)(arg0 + 0xC) = 0;
            *(f32 *)(arg0 + 0x10) = f3;
            *(f32 *)(arg0 + 0x14) = f4;
            *(f32 *)(arg0 + 0x0) = f0;
            *(f32 *)(arg0 + 0x4) = f1;
            *(f32 *)(arg0 + 0x8) = f2;
            break;
        }
    }
}
