#include "types.h"
#pragma divbyzerocheck on

typedef struct { s32 a; s32 b; s32 c; } E12;
extern void ActCfgTableSetEvntCount_223c10(void *, s32);
extern void ActInfoEvntSetCount_22f1b0(E12 *, s32, s32);
extern E12 *ActInfoEvntGetList_22f1c0(E12 *);
extern E12 *D_00481E78;
extern s32 D_00481E7C;
extern u8 D_004BCE20[0x10];
extern E12 *D_004BCE64[4];
extern s16 D_004BCE8E[8];

s32 ActInfoEvntEnd_23d5e0(s32 arg0, s32 arg1) {
    E12 *p;
    E12 *q;
    s32 n;

    if (arg1 != 0) {
        return 0;
    }
    if (D_004BCE64[0] == 0 || D_004BCE8E[0] >= 0x40) {
        return 1;
    }
    {
        p = D_004BCE64[0] + D_004BCE8E[0];
        q = ActInfoEvntGetList_22f1c0(p);
        n = ((s32)(D_00481E78 + D_00481E7C) - (s32)q) / 12;
        if (n <= 0) {
            return 1;
        }
        ActInfoEvntSetCount_22f1b0(p, n, D_00481E7C);
        ActCfgTableSetEvntCount_223c10(D_004BCE20, D_004BCE8E[0] + 1);
    }
end:
    return 1;
}
