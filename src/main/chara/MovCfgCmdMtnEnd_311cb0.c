#include "types.h"
#pragma divbyzerocheck on

typedef struct { u8 d[0x14]; } E20_311cb0;
typedef struct { u8 d[0xC]; } E12_311cb0;

extern void NamedCompListSetCount_312480(E12_311cb0 *, s32, s32);
extern E20_311cb0 *NamedCompListGetEntries_3124a0(E12_311cb0 *);
extern E20_311cb0 *D_004829A0;
extern s32 D_004829A4;
extern E12_311cb0 *D_004829A8;
extern s32 D_004829AC;

s32 MovCfgCmdMtnEnd_311cb0(void)
{
    E12_311cb0 *e;
    E20_311cb0 *r;

    if (D_004829A8 == NULL || D_004829A0 == NULL) {
        return 1;
    }
    e = &D_004829A8[D_004829AC];
    r = NamedCompListGetEntries_3124a0(e);
    NamedCompListSetCount_312480(e, &D_004829A0[D_004829A4] - r, D_004829A4);
    D_004829AC++;
    return 1;
}
