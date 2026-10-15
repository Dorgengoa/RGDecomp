#include "types.h"

extern f32 CharaGetHeightAboveGround_238380(void *);
extern const f32 D_0045B080;
extern f32 D_0047DB20;

s32 CharaIsLandedOrLockedMaybe_2109c0(void *arg0) {
    s64 f;
    s32 a;
    s32 b;

    f = *(s64 *)((u8 *)arg0 + 0x3D0);
    if (f & ((s64)0x80000 << 32)) return 1;
    a = *(s32 *)((u8 *)arg0 + 0xA44);
    if (a & 0x20000) return 1;
    if (a & 0x10000) return 1;
    if (f & ((s64)0x4000 << 32)) return 1;
    b = *(s32 *)((u8 *)arg0 + 0x3D8);
    if (b & 1) return 1;
    if (!(b & 4)) return 1;
    { f32 k = D_0045B080; if (CharaGetHeightAboveGround_238380(arg0) < D_0047DB20 * k) return 1; }
    return 0;
}
