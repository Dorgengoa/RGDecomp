#include "types.h"

struct Obj0 {
    u8 pad000[0x10];
    s32 m10;
};

extern s32 StateGetChapterIndexMaybe_3cd500(s32);

extern struct Obj0 *D_00483890;

s32 PlayStatAddHealAmountMaybe_3c05c0(s32 p0, s32 p1, s32 p2)
{
    struct Obj0 *g;
    s32 t1;
    s32 r1;
    s64 *e;
    s64 w;
    s32 off;

    if (p1 < 0) {
        goto zero;
    }
    if (p1 < 0xA) {
        goto ok;
    }
zero:
    return 0;
ok:
    g = D_00483890;
    t1 = g->m10;
    r1 = StateGetChapterIndexMaybe_3cd500(t1);
    w = (s64)p2;
    off = (r1 * 5) << 4;
    e = (s64 *)((p1 << 3) + (off + p0) + 0x4488);
    *e = *e + w;
    return 1;
}
