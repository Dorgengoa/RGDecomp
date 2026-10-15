#include "types.h"

s32 ProgressValueGet_3cd2c0(s32, s32, s32);
s32 StateGetChapter_3cd5b0(s32);
s32 PlanetAreaMatrixLookupValue_4150d0(s32, s16, s16, s16, s16);

typedef struct {
    u8 pad0[0x34];
    struct { u8 pad0[0x24]; s32 x24; } *x34;
} Sub3ed840;

typedef struct {
    u8 pad0[0x8];
    Sub3ed840 *unk8;
    u8 padC[0x4];
    s32 unk10;
} T3ed840_arg0;

s32 PlanetAreaMatrixLookupByProgress_3ed840(T3ed840_arg0 *arg0, s32 arg1)
{
    s32 r;
    s32 i;
    s32 a;
    s32 b;
    s32 t;

    if (arg0->unk8 == NULL) {
        return 0;
    }
    if (arg1 < 0) {
        return 0;
    }
    a = StateGetChapter_3cd5b0(arg0->unk10);
    if (a < 0) {
        return 0;
    }
    r = 0;
    for (i = 4; i >= 0; i--) {
        b = ProgressValueGet_3cd2c0(arg0->unk10, a, i);
        if (b >= 0) {
            t = PlanetAreaMatrixLookupValue_4150d0(arg0->unk8->x34->x24, arg1, a, i, b);
            if (t != 0) {
                r = t;
                break;
            }
        }
    }
    return r;
}
