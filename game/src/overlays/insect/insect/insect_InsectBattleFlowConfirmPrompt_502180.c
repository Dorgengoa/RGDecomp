/* rgp:protos */
#define RGP_SELF_insect_InsectBattleFlowConfirmPrompt_502180 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* insect 0x00502180 -- 820 bytes, 208 instructions, 25 calls, 12 conditional
 * branches.  A real 7-entry jump table (insect_jtbl_00524DD0, `sltiu $1,$2,0x7`) on
 * insect_InsectBattleGetStep_50d6a0(o, 0); index 0 points at the shared exit, so case 0 is
 * absent and cases 1..6 are laid out ascending.
 *
 * `addiu $19,$20,0x5D18` is materialised BEFORE the dispatch and survives into
 * the tail, so the record block is a NAMED POINTER local, not `o->f5D18` at
 * each use ([[NAME THE VALUE OR POINTER RETAIL MATERIALISES]]).
 *
 * The tail's four guards index that block by a *24 offset held in $16, and
 * the two record arrays are `a[2]` at +0x00 and `b[2]` at +0x30 -- +0x30 is
 * 2*0x18, i.e. a SECOND array, not element i+2.
 *
 * insect_InsectCursorSetGetEvents_5119f0 returns s64 (see insect_InsectCursorSetGetEventsExcept_5119b0.c); the
 * `dsll32/dsra32 ..,0` pair is the `(s32)` narrowing of that return.
 */

typedef struct Slot {
    s32 f00;                        /* +0x00 */
    u8  pad04[4];
    s32 f08;                        /* +0x08 */
    u8  pad0C[0x18 - 0x0C];
} Slot;                             /* 0x18 */

typedef struct Blk {
    Slot a[2];                      /* +0x00 */
    Slot b[2];                      /* +0x30 */
    s32  f60;                       /* +0x60 */
} Blk;                              /* 0x64 */

typedef struct Ins {
    u8    pad000[0x87C];
    void *f87C;                     /* +0x087C */
    u8    pad880[0x4F90 - 0x880];
    u8    f4F90[0x2C];              /* +0x4F90 */
    u8    f4FBC;                    /* +0x4FBC */
    u8    pad4FBD[0x5054 - 0x4FBD];
    u8    f5054[0x506C - 0x5054];   /* +0x5054 */
    u8    f506C[0x5D18 - 0x506C];   /* +0x506C */
    Blk   f5D18;                    /* +0x5D18 */
    u8    pad5D7C[0x5DA0 - 0x5D7C];
    void *f5DA0;                    /* +0x5DA0 */
    void *f5DA4;                    /* +0x5DA4 */
} Ins;

extern u8 insect_D_00523C10[];

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
extern void  memset(void *p, s32 c, s32 n);

void insect_InsectBattleFlowConfirmPrompt_502180(Ins *o)
{
    s32  sx;
    s32  sy;
    Blk *b;
    s32  go;
    s32  ix;
    s32  n;
    s32  v;
    s32  k;
    s32  k2;

    b = &o->f5D18;
    go = 0;
    ix = 0;
    switch (insect_InsectBattleGetStep_50d6a0(o, 0)) {
    case 1:
        insect_InsectBattleConfirmDialogOpen_50eaf0(o->f5DA0, o->f5DA4, o->f506C, b->f60);
        insect_InsectBattleCursorUpdateDesc_4f4530(o, insect_D_00523C10, 1);
        insect_InsectBattleSetStep_50d7a0(o, 2, 0, -1);
        insect_InsectBattleSetStep_50d7a0(o, 0, 2, -1);
        break;
    case 2:
        if (UiGetWidgetAlpha_290770(o->f87C, 0xC378) >= 1.0f) {
            insect_InsectBattleSetStep_50d7a0(o, 3, 0, -1);
        }
        break;
    case 3:
        o->f4FBC = o->f4FBC & 0xFD;
        insect_InsectBattleSetStep_50d7a0(o, 4, 0, -1);
        break;
    case 4:
        insect_InsectBattleCursorUpdateDesc_4f4530(o, insect_D_00523C10, 0);
        insect_InsectCursorSetGetCurCell_511a90(o->f4F90, &sx, &sy);
        InsectUiConfirmButtonSetSelectedMaybe_392b20(o->f5054, UiFindWidget_290460(o->f87C, 0xC37B),
                    (u8)((sx != 0) ^ 1));
        InsectUiConfirmButtonSetSelectedMaybe_392b20(o->f5054, UiFindWidget_290460(o->f87C, 0xC37C), sx);
        n = (s32)insect_InsectCursorSetGetEvents_5119f0(o->f4F90, -1);
        v = -1;
        if (n & 0x80) {
            v = sx;
        }
        if (n & 0x20) {
            if (v == -1) {
                v = 1;
            }
        }
        if (v == -1) {
            break;
        }
        k2 = 5;
        k = 5;
        if (v != 0) {
            k = 6;
            k2 = 6;
        }
        insect_InsectBattleSetStep_50d7a0(o, k, 0, -1);
        UiFadeWidgetAlpha_290690(o->f87C, 0xC378, 0.0f, 0.125f, -1.0f);
        UiFadeWidgetAlpha_290690(o->f87C, 0xC37E, 0.0f, 0.125f, -1.0f);
        insect_InsectBattlePlaySe_4f45b0(o, k2);
        break;
    case 5:
        go = 1;
        break;
    case 6:
        ix = 1;
        go = 1;
        break;
    }
    if (go != 0) {
        if (b->a[ix].f00 != -1) {
            insect_InsectBattleSetState_50d8c0(o, b->a[ix].f00, 0, -1);
        }
        if (b->b[ix].f00 != -1) {
            insect_InsectBattleSetStep_50d7a0(o, b->b[ix].f00, 0, -1);
        }
        if (b->a[ix].f08 != -1) {
            insect_InsectBattleSetState_50d8c0(o, b->a[ix].f08, 2, -1);
        }
        if (b->b[ix].f08 != -1) {
            insect_InsectBattleSetStep_50d7a0(o, b->b[ix].f08, 2, -1);
        }
        insect_InsectCursorSetPopPage_511ca0(o->f4F90);
        o->f4FBC = o->f4FBC | 2;
        memset(b, 0, 0x64);
    }
}
