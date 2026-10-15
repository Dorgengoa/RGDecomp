#include "types.h"

/* Tear-down.  bnez $2 falls into the HudFadeInAll_2f4850 call, so the source tests
   == 0; the beql past the m14 block is the likely form of "if (m14 != 0)".
   ARITY: MemStackHeapFree_14dcb0 takes TWO arguments.  m14 is loaded into $5 and never
   moved -- it is argument two, already in place, which is why both delay
   slots around the call are nops.  Every one-argument spelling (six of them:
   named/unnamed local, two declaration orders, `register`, `&&`) is ONE
   object and two words wrong. */

struct S {
    u8 pad000[0x10];
    s32 m10;
    s32 m14;
};

extern s32 IsInBattle_288420(void);
extern void HudFadeInAll_2f4850(s32);
extern s32 GetDrawCtxNameTable_15de40(void);
extern void NameTableFreeGroup_158ac0(s32, s32);
extern void MemStackHeapFree_14dcb0(s32, s32);
extern void LoaderReleaseHandle_1ccb70(struct S *);
extern void MapCaptionInit_33fd90(struct S *);

void MapCaptionRelease_33fa10(struct S *p0)
{
    s32 r0;
    s32 r1;
    s32 v;
    s32 t;

    r0 = IsInBattle_288420();
    if (r0 == 0) {
        HudFadeInAll_2f4850(0xF);
    }
    r1 = GetDrawCtxNameTable_15de40();
    NameTableFreeGroup_158ac0(r1, 0x1C8);
    v = p0->m14;
    if (v != 0) {
        t = p0->m10;
        if (t != 0) {
            MemStackHeapFree_14dcb0(t, v);
        }
    }
    LoaderReleaseHandle_1ccb70(p0);
    MapCaptionInit_33fd90(p0);
}
