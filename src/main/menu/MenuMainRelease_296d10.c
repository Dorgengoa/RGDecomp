#include "types.h"

/* MAIN MenuMainRelease_296d10 -- the teardown counterpart of the MainMenuInit_297510
   registration list (same window, same globals, same Sys/Cfg structs).

   Two readings the listing forces:
     * `daddu $16,$2,$0` sits in the DELAY SLOT of `jal GetGameData_1fede0`, so it
       captures GetDrawCtxNameTable_15de40's return, not GetGameData_1fede0's.  $16 is the handle
       passed to the three NameTableFreeGroup_158ac0 calls.
     * retail issues `lw $4,%gp_rel(D_00482388)` and `lw $4,%gp_rel(D_00482334)`
       ABOVE their store blocks.  A LOAD WILL NOT CROSS A STORE TO A GLOBAL,
       so those two reads are NAMED LOCALS declared before the stores.
       Both named values are then ARGUMENTS: retail leaves D_00482388's value
       in $4 across the branch and calls MenuCatalogPageRelease_360d00 with it (whose own
       listing does `daddu $17,$4,$0` at +0xC, so it really reads $4).  The
       third test (D_00482338) has no store between it and its use, so it is
       written inline.  */

typedef struct Cfg00296d10 {
    u8 pad000[0x24C];
    u8 m24C;                 /* +0x24C, bit 0 tested */
} Cfg00296d10;

typedef struct Sys00296d10 {
    u8 pad00[0x20];
    Cfg00296d10 *m20;        /* +0x20 */
} Sys00296d10;

extern void *GetDrawCtxNameTable_15de40(void);
extern Sys00296d10 *GetGameData_1fede0(void);
extern void MenuModelRelease_2942c0(void);
extern void MenuItemModelRelease_2a7130(void);
extern void MenuCatalogPageRelease_360d00(void *);
extern void MemStackReset_14d830(void *);
extern void NameTableFreeGroup_158ac0(void *, s32);

extern void *D_00482334;
extern void *D_00482338;
extern s32 D_0048234C;
extern s32 D_00482370;
extern s32 D_00482374;
extern void *D_00482388;
extern s16 D_004823A8;
extern s16 D_004823AC;
extern s16 D_004823B0;
extern s16 D_0047EB90;
extern s16 D_0047EB94;

s32 MenuMainRelease_296d10(void)
{
    void *h;
    Sys00296d10 *p;
    void *t388;
    void *t334;

    h = GetDrawCtxNameTable_15de40();
    p = GetGameData_1fede0();
    if ((p->m20->m24C & 1) == 0) {
        MenuModelRelease_2942c0();
    }
    MenuItemModelRelease_2a7130();
    t388 = D_00482388;
    D_0048234C = 0;
    D_00482374 = 0;
    D_00482370 = 0;
    if (t388 != 0) {
        MenuCatalogPageRelease_360d00(t388);
    }
    t334 = D_00482334;
    D_00482388 = 0;
    D_004823A8 = 0;
    D_004823B0 = 0;
    D_004823AC = 0;
    D_0047EB90 = -1;
    D_0047EB94 = -1;
    if (t334 != 0) {
        MemStackReset_14d830(t334);
    }
    if (D_00482338 != 0) {
        MemStackReset_14d830(D_00482338);
    }
    NameTableFreeGroup_158ac0(h, 0x32D);
    NameTableFreeGroup_158ac0(h, 0x32F);
    NameTableFreeGroup_158ac0(h, 0x32E);
    return 0;
}
