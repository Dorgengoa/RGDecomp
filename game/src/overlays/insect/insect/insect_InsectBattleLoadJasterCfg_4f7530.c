/* rgp:protos */
#define RGP_SELF_insect_InsectBattleLoadJasterCfg_4f7530 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* insect 0x004F7530 -- 384 bytes, 96 instructions, 14 calls, 4 conditional
 * branches, br/ins 0.042.  A two-arm `insect_InsectBattleGetStep_50d6a0(o, 1)` state
 * dispatch from x_band.py's branch-light band.
 *
 * Both tests are `beql $2, $3, <block>` -- branches INTO the arm, with the
 * arm's first argument load in the delay slot -- and the default falls to a
 * `b <epilogue>`.  That is the SWITCH shape, so unlike insect_InsectBattleFlowDetailInfoView_5077e0
 * (whose inverted `bnel`/`bne` made it a chain) this one is a real `switch`
 * and the compare chain 6, 1 is REVERSED from the source order 1, 6.
 *
 * The 0x88-byte record at $29+0x50 is ONE local struct, not eleven frame
 * slots: `sp90` and `spB0` lie INSIDE it (+0x40 and +0x60), so the two pointer
 * stores are `r.f2C = &r.f40;` and `r.f38 = &r.f60;` -- taking the address of
 * a sibling member of the record being filled.
 *
 * The record is 0x90 BYTES even though the memset clears only 0x88: `q` sits
 * at $29+0xEC and the frame is 0xF0, which fixes the record's size and not its
 * shape.  0x90 / 0x94 / 0x98 / 0x9C all give one identical object, so the tail
 * beyond 0x88 is not observable from this unit -- the smallest is taken.
 *
 * The record's fill ORDER is not m2c's.  Each count/buffer PAIR is written
 * count first -- `r.f30 = 8;` then `r.f2C = r.f40;` -- and m2c's order (buffer
 * first) is four words wrong.  Measured by enumerating all 360 orders of the
 * six leading assignments in one round trip: six land byte-identical and every
 * one of them has `f30` before `f2C`.
 *
 * `(u8 *)o + 0x138` is HOISTED into $17 and used at five sites; `o->f5000` is
 * REMATERIALISED at all three of its own, so the first is a named local and
 * the second an array member (insect-array-member-blocks-cse).
 */

typedef struct Rec {
    s32 f00;                        /* +0x00 */
    u8 *f04;                        /* +0x04 */
    u8 *f08;                        /* +0x08 */
    u8 *f0C;                        /* +0x0C */
    u8 *f10;                        /* +0x10 */
    s32 f14;                        /* +0x14 */
    s32 f18;                        /* +0x18 */
    u8  pad1C[0x2C - 0x1C];
    u8 *f2C;                        /* +0x2C */
    s32 f30;                        /* +0x30 */
    u8  pad34[0x38 - 0x34];
    u8 *f38;                        /* +0x38 */
    s32 f3C;                        /* +0x3C */
    u8  f40[0x60 - 0x40];           /* +0x40 */
    u8  f60[0x90 - 0x60];           /* +0x60 */
} Rec;

typedef struct Src {
    u8  pad000[0x4DC];
    s32 f4DC;                       /* +0x04DC */
} Src;

typedef struct Ins {
    u8    pad000[0x138];
    u8    f138[0x870 - 0x138];      /* +0x0138 */
    void *f870;                     /* +0x0870 */
    u8    pad874[0x5000 - 0x874];
    u8    f5000[0x20];              /* +0x5000 */
} Ins;

extern u8 insect_D_00524C60[];
extern u8 insect_D_00524C78[];

extern void  memset(Rec *p, s32 v, s32 n);
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

void insect_InsectBattleLoadJasterCfg_4f7530(Ins *o)
{
    Rec  r __attribute__((aligned(16)));
    s32  q;
    u8  *t;
    s32  n;
    Src *s;

    switch (insect_InsectBattleGetStep_50d6a0(o, 1)) {
    case 1:
        insect_InsectFileSlotRequest_512140(o->f5000, insect_D_00524C60, -1);
        insect_InsectBattleSetStep_50d7a0(o, 6, 1, -1);
        return;
    case 6:
        if (insect_InsectFileSlotIsLoaded_512010(o->f5000) != 0) {
            t = (u8 *)o + 0x138;
            MemStackHeapReinit_14de90(t);
            MemStackHeapAlloc_14db10(t, 2, 0, 0x40);
            n = insect_InsectFileSlotGetData_511fa0(o->f5000, &q);
            s = ((Src *)ObjRecGetLiveObject_1c4a90(o->f870, 0));
            if (s != 0) {
                memset(&r, 0, 0x88);
                r.f30 = 8;
                r.f2C = r.f40;
                r.f3C = 8;
                r.f38 = r.f60;
                r.f00 = n;
                r.f04 = insect_D_00524C78;
                r.f08 = t;
                r.f0C = t;
                r.f10 = t;
                r.f14 = s->f4DC;
                r.f18 = 0;
                InfoCfgParseAll_1afd00(s, &r);
            }
            MemStackReturnToOwnerMaybe_14dad0(t);
            insect_InsectFileSlotRelease_512020(o->f5000);
            insect_InsectBattleSetStep_50d7a0(o, 0xB, 1, -1);
            insect_InsectBattleSetStep_50d7a0(o, 0x1B, 0, -1);
        }
        return;
    }
}
