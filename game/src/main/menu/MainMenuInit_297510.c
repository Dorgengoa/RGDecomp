/* rgp:protos */
#define RGP_SELF_MainMenuInit_297510 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* MAIN MainMenuInit_297510 -- subsystem registration / init list.
   16 calls interleaved with ~20 %gp_rel global stores, br=2. */

typedef struct Cfg00297510 {
    u8 pad000[0x24C];
    u8 m24C;                 /* +0x24C, bit 0 tested */
} Cfg00297510;

typedef struct Sys00297510 {
    u8 pad00[0x20];
    Cfg00297510 *m20;        /* +0x20 */
} Sys00297510;

typedef struct Node00297510 {
    s16 m00;                 /* +0x00 */
} Node00297510;

typedef struct Ctx00297510 {
    u8 pad00[0x28];
    Node00297510 *m28;       /* +0x28 */
} Ctx00297510;

typedef struct Obj0029a2a0 {
    s32 m00;
    s32 m04;
    s32 m08;
    s32 m0C;
    s32 m10;
    s32 m14;
    s16 m18;
    u8 m1A;
    u8 m1B;
} Obj0029a2a0;

typedef struct Obj0029a2d0 {
    s16 m00;
    s16 m02;
    s16 m04;
    s16 m06;
    s32 m08;
    u8 pad00C[0x4];
    s32 m10;
} Obj0029a2d0;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

extern s32 D_00482330;
extern void *D_00482334;
extern void *D_00482338;
extern void *D_0048233C;
extern s16 D_00482340;
extern u8 D_00482398;
extern s16 D_0048239C;
extern s16 D_004823A0;
extern s16 D_004823A4;
extern s16 D_004823A8;
extern s16 D_004823AC;
extern s16 D_004823B0;
extern u8 D_004823B4;
extern u8 D_004823CC;
extern s32 D_004823D0;
extern u8 D_004823E8;
extern u8 D_004823EC;
extern u8 D_004823F0;
extern void *D_004823F8;
extern s32 D_00482410;
extern s16 D_0047EB98;
extern Obj0029a2a0 D_004DB220;
extern Obj0029a2d0 D_004DB240;

/*  THE ONE LEVER: the seven-store block is written ZEROS FIRST, then the
    three `= 1` stores.  mwcc REORDERS stores to distinct known globals, so
    both orders emit retail's sh/sb sequence (A8, A4, EB98, A0, F0, B0, B4) --
    but only the zeros-first source order lets the scheduler keep
    `addiu $4,$4,%lo(D_004DB220)` immediately after its `lui`.  Written in
    emitted order the `sh $2,%gp_rel(D_004823A8)` steals that slot and the
    addiu lands one word later: TWO wrong words at the right length, and that
    residue survived 18 source spellings (13 of them one identical object,
    sha1 4b676bd4) and all 488 pragmas (473 inert).  Store SOURCE order is a
    real lever even when it does not change the emitted store order.

    The dead `lbu 0x24C / andi 1` is real: retail computes the bit and throws
    it away, then uses a constant 3.  `n = 3; if (bit) n = 3;` reproduces it
    exactly -- mwcc folds the select but leaves the condition.  The
    `dsll32/dsra32 ..,16` is the explicit `(s16)` cast on that s32 local.  */
void MainMenuInit_297510(void)
{
    void *h;
    void *w;
    Sys00297510 *p;
    Ctx00297510 *q;
    s32 n;

    D_004823E8 = 0;
    D_004823D0 = 0;
    D_00482398 = 0;
    D_004823CC = 0;
    D_00482330 = SceneSoundGetSlot0HandleCur_207df0();
    h = GetMenuMainStack_206ac0();
    D_00482334 = h;
    MemStackReset_14d830(h);
    w = GetMenuReadBufStack_206a90();
    D_00482338 = w;
    MemStackReset_14d830(w);
    MainMenuAllocIconMaskClut_2994e0();
    D_0048233C = GetMenuCapStack_206ab0();
    MenuCaptureTexAlloc_2989b0();
    D_004823AC = 0;
    D_0048239C = 1;
    D_00482410 = 0;
    D_004823EC = 0;
    p = ((Sys00297510 *)GetGameData_1fede0());
    if (p != 0) {
        n = 3;
        if ((p->m20->m24C & 1) != 0) {
            n = 3;
        }
        D_004823F8 = MemStackNew_14e1b0((s16)n * 0x38, D_00482334);
        MenuMainResLoad_299080();
        D_004823A0 = 0;
        D_004823F0 = 0;
        D_004823B0 = 0;
        D_004823B4 = 0;
        D_004823A8 = 1;
        D_004823A4 = 1;
        D_0047EB98 = 1;
        DebugItemListInit_29a2a0(&D_004DB220);
        DebugItemIconGridInit_29a2d0(&D_004DB240);
        D_00482340 = 0;
        q = ((Ctx00297510 *)GetWorldDataMgr_1fedf0());
        if (q->m28->m00 != 1) {
            WorldDataRequestKind_3f0960(q, 1);
            D_004823EC = 1;
        }
        MenuOpeningPanelSetupMaybe_298600();
    }
}
