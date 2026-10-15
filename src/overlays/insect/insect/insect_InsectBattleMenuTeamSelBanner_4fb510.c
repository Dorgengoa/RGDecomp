#include "types.h"
/* insect 0x004FB510 -- 684 bytes, 171 instructions, 23 calls, 9 conditional
 * branches, br/ins 0.053.  The 0xC38F-0xC392 confirm-panel driver on the
 * insect_InsectBattleGetStep_50d6a0(o, 2) state.
 *
 * Compare chain 4, 3, 2, 1 -- REVERSED -- so source order is 1, 2, 3, 4, and
 * `case 3: break;` is EMPTY: its `beql` targets 0x004FB7AC, the epilogue head
 * PLUS ONE, because the branch-likely already ran `ld $31` in its delay slot.
 * Case 4's block is the last one and falls straight into the epilogue head.
 *
 * o->f5054 and o->f506C are REMATERIALISED (bare `addiu $4, $16, K`) so they
 * are array members; o->f5F82 is HOISTED into $17 for its two uses, so that one
 * is a local -- insect-array-member-blocks-cse, both halves.
 *
 * ★ `daddiu $2, $0, 0x1` for the `v = 1` arm is the tell that `v` is an
 * UNSIGNED NARROW type: the trailing `andi $2, $2, 0xFF` before the `sll 4`
 * confirms `u8`.  An `s32` v drops the mask and is two words short.
 */

typedef struct Node {
    u8  pad00[8];
    s16 f8;                     /* +0x08 */
} Node;

typedef struct Widget {
    u8    pad00[0x20];
    Node *f20;                  /* +0x20 */
} Widget;

typedef struct Ins {
    u8    pad000[0x87C];
    void *f87C;                 /* +0x087C */
    u8    pad880[0x4FBC - 0x880];
    u8    f4FBC;                /* +0x4FBC */
    u8    pad4FBD[0x5054 - 0x4FBD];
    u8    f5054[0x506C - 0x5054]; /* +0x5054 */
    u8    f506C[4];             /* +0x506C */
    u8    pad5070[0x5DA0 - 0x5070];
    s32   f5DA0;                /* +0x5DA0 */
    s32   f5DA4;                /* +0x5DA4 */
    u8    pad5DA8[0x5EF1 - 0x5DA8];
    u8    f5EF1;                /* +0x5EF1 */
} Ins;

extern void    func_1343B8(void *p, s32 a, s32 b);
extern void    func_28F510(void *h, s32 id, void *p, s32 a);
extern void    func_28F5D0(void *h, s32 id, s32 a, s32 b, s32 c);
extern void    func_290010(void *h, s32 id, s32 a, s32 b);
extern Widget *func_290460(void *h, s32 id);
extern void    func_290690(void *h, s32 id, f32 a, f32 b, f32 c);
extern f32     func_290770(void *h, s32 id);
extern void    func_2907A0(void *h, s32 id, f32 v);
extern void    func_290F60(void *h, s32 id, s32 x, s32 y);
extern void    func_392BB0(void *g, void *w, s32 a, s32 b, s32 c);
extern void    func_3938F0(void *g, void *w, f32 a, f32 b);

extern s32  insect_InsectBattleGetStep_50d6a0(Ins *o, s32 k);
extern void insect_InsectBattleSetStep_50d7a0(Ins *o, s32 a, s32 b, s32 c);
extern s32  insect_InsectMsgGet_512b70(void *a, s32 k);

void insect_InsectBattleMenuTeamSelBanner_4fb510(Ins *o)
{
    void *p;
    Node *n;
    s32 m;
    u8 v;

    switch (insect_InsectBattleGetStep_50d6a0(o, 2)) {
    case 1:
        func_392BB0(o->f5054, func_290460(o->f87C, 0xC390), 0x168, 0x40, 0);
        func_3938F0(o->f5054, func_290460(o->f87C, 0xC391), 356.0f, 60.0f);
        p = (u8 *)o + 0x5F82;
        func_1343B8(p, insect_InsectMsgGet_512b70(o->f506C, 0x3EB), o->f5EF1 + 1);
        func_28F510(o->f87C, 0xC390, p, 0);
        func_28F5D0(o->f87C, 0xC390, 0x40, 8, 0);
        func_290010(o->f87C, 0xC38F, 1, -1);
        func_290010(o->f87C, 0xC392, 0, -1);
        func_290F60(o->f87C, 0xC390, (o->f5DA0 - 0x168) / 2,
                    (o->f5DA4 - 0x40) / 2);
        func_2907A0(o->f87C, 0xC38F, 0.0f);
        func_290690(o->f87C, 0xC38F, 1.0f, 0.125f, -1.0f);
        func_2907A0(o->f87C, 0xC3A3, 1.0f);
        n = func_290460(o->f87C, 0xC3A5)->f20;
        m = 4 << o->f5EF1;
        if (m == 0xFF) {
            v = o->f4FBC;
        } else if ((o->f4FBC & m) != 0) {
            v = 1;
        } else {
            v = 0;
        }
        n->f8 = v * 0x10 + 0x2C;
        insect_InsectBattleSetStep_50d7a0(o, 2, 2, -1);
        break;
    case 2:
        if (func_290770(o->f87C, 0xC38F) >= 1.0f) {
            insect_InsectBattleSetStep_50d7a0(o, 3, 2, -1);
            insect_InsectBattleSetStep_50d7a0(o, 3, 0, -1);
        }
        break;
    case 3:
        break;
    case 4:
        func_290690(o->f87C, 0xC38F, 0.0f, 0.125f, -1.0f);
        insect_InsectBattleSetStep_50d7a0(o, 3, 2, -1);
        insect_InsectBattleSetStep_50d7a0(o, 5, 0, -1);
        break;
    }
}
