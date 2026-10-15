#include "types.h"
typedef struct { s32 a, b; } E8_1626f0;
extern s32 SlotGetInt_15f720(E8_1626f0 *);
extern s32 strlen(s32);
extern s32 MemStackAllocQw_14d950(s32, s32);
extern s32 strcpy(s32, s32);
extern s32 VariantGetInt_15f780(E8_1626f0 *);
extern s32 D_0048113C;
extern s32 D_00481140;
extern s32 D_00481144;

s32 TexAnimeCfgTexAnimeCmd_1626f0(E8_1626f0 *p0)
{
    s32 r0;
    s32 r1;
    s32 r2;
    s32 r5;

    r0 = SlotGetInt_15f720(p0++);
    if (r0 != 0) {
        r1 = strlen(r0);
        r2 = MemStackAllocQw_14d950(D_0048113C, ((((u32)(r1 + 1)) >> 4) + 1));
        strcpy(r2, r0);
        D_00481140 = r2;
    }
    r5 = VariantGetInt_15f780(p0);
    D_00481144 = r5;
    return 1;
}
