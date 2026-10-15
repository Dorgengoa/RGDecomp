#include "types.h"
/* insect 0x005004F0 -- 3,052 bytes, 763 instructions, 115 calls, 27 conditional
 * branches, br/ins 0.035.  The most call-heavy, branch-light function left in
 * the overlay; found by the THRESHOLD band screen (x_band.py), not by the
 * bytes/(1+br) ranking, which put it outside its top 30.
 *
 * A ten-arm state dispatch on insect_InsectBattleGetStep_50d6a0(o, 2).  It is a `switch`, not
 * a chain: every converted `beql` carries the TAKEN ARM's own first instruction
 * (`lw $4,0x878($17)`, `addiu $4,$17,0x4F90`, the 0.125f `lui`), never the next
 * guard's constant.  The compare chain runs
 *   0xB, 0xA, 0x1D, 0x4B, 0x4A, 0x49, 0x46, 0x47, 0x1A, 0x19, 1
 * -- REVERSED -- and the block ADDRESSES run 1, 0x19, 0x1A, 0x47, 0x46, 0x49,
 * 0x4A, 0x4B, 0x1D, 0xA, which is that same order forwards.  So source case
 * order is the block order, with three fall-throughs (1 -> 0x19, 0x47 -> 0x46,
 * 0x4A -> 0x4B).
 *
 * `case 0xB: break;` IS IN THE SOURCE.  Its `beql` goes to 0x005010C4 with
 * `ld $31,0x40($29)` already in the delay slot, i.e. one instruction PAST the
 * epilogue head that the default's `b` targets (0x005010C0).  That is the
 * branch-likely-duplicates-the-merge's-first-instruction shape, so the empty
 * case costs exactly one branch and is invisible unless you read the two exit
 * addresses as different.
 *
 * The 0xB that case 0xA passes to insect_InsectBattleSetStep_50d7a0 is never materialised in
 * its own arm -- `$5` still holds the `addiu $5,$0,0xB` that the case-0xB
 * COMPARE emitted.  An argument with no instruction of its own is not a missing
 * instruction; it is the dispatch's constant CSE'd into the arm, which is also
 * why that one compare gets a real register instead of `$at`.
 *
 * D_00480EF0 / D_00480F00 are MAIN-image small data (the gp window is
 * 0x47D170..0x48D170), read with `lhu` at a stride of FOUR, so the element is a
 * halfword every other halfword; `[i * 2]` on a `u16` array is what gives
 * `sll $3,$18,2`.  They must stay non-`const` to keep `%gp_rel`, and the
 * declared size must stay at or under mwcc's 8-byte small-data threshold.
 */

typedef struct Widget {
    u8   pad00[0x20];
    void *f20;                  /* +0x20 */
    u8   pad24[0x2C - 0x24];
    void *f2C;                  /* +0x2C */
} Widget;

typedef struct Panel {
    s16 f00, f02, f04, f06, f08, f0A, f0C, f0E;
    f32 f10;                    /* +0x10 */
    f32 f14;                    /* +0x14 */
    s16 f18, f1A;
} Panel;

typedef struct Card { u8 pad00[0xA]; s8 fA; s8 fB; } Card;

typedef struct Ins {
    u8    pad000[0x878];
    void *f878;                 /* +0x0878 */
    void *f87C;                 /* +0x087C */
    u8    pad880[0x4F90 - 0x880];
    u8    f4F90[0x2C];          /* +0x4F90 */
    u8    f4FBC;                /* +0x4FBC */
    u8    pad4FBD[0x5D9C - 0x4FBD];
    f32   f5D9C;                /* +0x5D9C */
    s32   f5DA0;                /* +0x5DA0 */
    s32   f5DA4;                /* +0x5DA4 */
    u8    pad5DA8[0x5EF1 - 0x5DA8];
    u8    f5EF1;                /* +0x5EF1 */
} Ins;

extern u16 D_00480EF0[4];       /* 8 bytes: at the small-data threshold */
extern u16 D_00480F00[4];
extern const u8 D_00523C10[];
extern const u8 D_00523E10[];

extern void insect_InsectBattleRosterListTextClipCb_5102f0(void);
extern void insect_InsectBattleRosterListScissorCb_510130(void);

extern s32   insect_InsectBattleGetStep_50d6a0(Ins *o, s32 k);
extern void  insect_InsectBattleSetStep_50d7a0(Ins *o, s32 a, s32 b, s32 c);
extern s32   insect_InsectBattleTestFlag_50da40(Ins *o, s32 k);
extern s32   insect_InsectBattleGetPoolCount_50db60(Ins *o, s32 k);
extern void  insect_InsectBattleConfirmDialogOpen_50eaf0(s32 a, s32 b, void *c, s32 d);
extern s32   insect_InsectCursorSetGetEvents_5119f0(void *a, s32 mask);
extern void  insect_InsectCursorSetGetCell_511a40(void *a, s32 k, s32 *x, s32 *y);
extern Card *insect_InsectCursorSetFindPage_511e60(void *a, s32 k);
extern s32   insect_InsectMsgCenterX_512b10(void *a, s32 b, s32 c);
extern s32   insect_InsectMsgGet_512b70(void *a, s32 b);
extern void  insect_InsectBattleCursorUpdateDesc_4f4530(Ins *o, const u8 *t, s32 k);
extern void  insect_InsectBattleMemberListFill_4faa90(Ins *o, void *r);
extern void  insect_InsectBattleRosterListRefresh_4faf00(Ins *o, void *r);

extern void    func_28F510(void *h, s32 id, s32 a, s32 b);
extern void    func_28F590(void *h, s32 id, s32 a, s32 b);
extern void    func_28F5D0(void *h, s32 id, s32 a, s32 b, s32 c);
extern void    func_290010(void *h, s32 id, s32 a, s32 b);
extern Widget *func_290460(void *h, s32 id);
extern void    func_290690(void *h, s32 id, f32 a, f32 b, f32 c);
extern f32     func_290770(void *h, s32 id);
extern void    func_2907A0(void *h, s32 id, f32 v);
extern void    func_290A40(void *h, s32 id, s32 rgba, s32 i);
extern s32     func_290D30(void *h, s32 id);
extern void    func_290F50(void *h, s32 id, s32 a, s32 b, s32 c, f32 t);
extern void    func_290F60(void *h, s32 id, s32 a, s32 b);
extern void    func_290FC0(void *h, s32 id, s32 *a, s32 *b);
extern void    func_291110(void *h, s32 id, s32 a, s32 b);
extern void    func_392B20(void *g, void *w, s32 v);
extern f32     func_392E60(void *g, void *w, s32 a, s32 b, s32 c);
extern void    func_3930D0(void *g, void *w, s32 a, s32 b, s32 c);
extern void    func_3934D0(void *g, void *w, s32 a, s32 b, s32 c, s32 d);
extern void    func_393700(void *g, void *w, s32 a, s32 b, s32 c, s32 d, s32 e);
extern void    func_393820(void *g, void *w, s32 a, s32 b, s32 c);
extern void    func_3938F0(void *g, void *w, f32 a, f32 b);
extern void    func_393AC0(void *g, void *w, s32 a, s32 b, s32 c);

void insect_InsectBattleMenuTeamSelect_5004f0(Ins *o)
{
    s32 x6C;
    s32 x68;
    s32 x64;
    s32 x60;
    s32 x5C;
    s32 x58;
    void *g;
    void *p19;
    void *rec;
    Widget *w;
    Panel *q;
    Card *c;
    s32 i;
    s32 n;
    u8 b;

    g = (u8 *)o + 0x5054;
    p19 = (u8 *)o + 0x506C;

    switch (insect_InsectBattleGetStep_50d6a0(o, 2)) {
    case 1:
        o->f4FBC = o->f4FBC | 2;
        func_2907A0(o->f87C, 0xC3A3, 0.0f);
        func_2907A0(o->f87C, 0xC37E, 0.0f);
        func_290690(o->f87C, 0xC37E, 1.0f, 0.125f, -1.0f);
        func_2907A0(o->f878, 0x753C, 0.0f);
        func_290690(o->f878, 0x753C, 1.0f, 0.125f, -1.0f);
        func_393AC0(g, func_290460(o->f878, 0x753C), o->f5DA0 + 0x40, 0x24,
                    3 - o->f5EF1);
        func_2907A0(o->f878, 0x753E, 0.0f);
        func_290690(o->f878, 0x753E, 1.0f, 0.125f, -1.0f);
        func_393AC0(g, func_290460(o->f878, 0x7544), 0xC0, 0xB0, 0);
        func_393820(g, func_290460(o->f878, 0x7545), 0x1C, 2, -1);
        func_393700(g, func_290460(o->f878, 0x7545), 0, 0x1C, 4, 0x1C, 5);
        n = 0x44;
        if (insect_InsectBattleTestFlag_50da40(o, 2) != 0) {
            n = 0x26;
        }
        func_290F60(o->f878, 0x7556, 0xC8, 0xAE - n);
        func_3938F0(g, func_290460(o->f878, 0x7557), 188.0f, (f32)(n - 4));
        func_3934D0(g, func_290460(o->f878, 0x754B), 0x1B4, 0x1C, 5, o->f5EF1);
        func_3934D0(g, func_290460(o->f878, 0x7542), 0xB8, 0x1C, 5, o->f5EF1);
        func_393AC0(g, func_290460(o->f878, 0x7556), 0xC0, n, 0);
        func_2907A0(o->f878, 0x7547, 0.0f);
        func_290690(o->f878, 0x7547, 1.0f, 0.125f, -1.0f);
        func_3930D0(g, func_290460(o->f878, 0x7548), 0x1C0, 0xB2, 0);
        func_290690(o->f878, 0x7530, 1.0f, 0.125f, -1.0f);
        func_290690(o->f87C, 0xC37E, 1.0f, 0.125f, -1.0f);
        w = func_290460(o->f878, 0x753D);
        if (w != 0) {
            q = w->f20;
            if (q != 0) {
                q->f00 = 0;
                q->f02 = 0;
                q->f04 = 0xC;
                q->f06 = 0x10;
                q->f08 = 0x78;
                q->f0A = 0x12;
                q->f0C = 0xC;
                q->f0E = 0x10;
            }
        }
        q = func_290460(o->f878, 0x7546)->f20;
        q->f00 = 0;
        q->f02 = 0;
        q->f0C = q->f04 = 0;
        q->f0E = q->f06 = 0;
        q->f08 = 0xD8;
        q->f0A = 0x62;
        q->f10 = q->f14 = q->f18 = q->f1A = 0;
        i = 0;
        do {
            func_290A40(o->f878, 0x7545, 0xFF7F7F7F, i);
            i++;
        } while (i < 5);
        func_290F60(o->f878, 0x753E, 0, 0);
        func_290F60(o->f878, 0x753F, -0xC0, 0x40);
        func_290F50(o->f878, 0x753F, (o->f5DA0 - 0x1C0) / 2, 0x40, 0, 0.5f);
        func_290F60(o->f878, 0x7548, o->f5DA0 + 0x1C0, 0xF2);
        func_290F50(o->f878, 0x7548, (o->f5DA0 - 0x1C0) / 2, 0xF2, 0, 0.5f);
        func_28F510(o->f878, 0x7548, insect_InsectMsgGet_512b70(p19, 0xBB8), 0);
        func_28F510(o->f878, 0x7540, insect_InsectMsgGet_512b70(p19, 0xBB9), 0);
        func_28F590(o->f878, 0x7548, insect_InsectMsgCenterX_512b10(p19, 0xBB8, 0x1C0), 0);
        func_28F590(o->f878, 0x7540, insect_InsectMsgCenterX_512b10(p19, 0xBB9, 0xC0), 0);
        func_28F5D0(o->f878, 0x753C,
                    insect_InsectMsgCenterX_512b10(p19, 0, o->f5DA0 + 0x40), 8, 0);
        func_28F510(o->f878, 0x753C, insect_InsectMsgGet_512b70(p19, 0), 0);
        func_28F510(o->f878, 0x7558, insect_InsectMsgGet_512b70(p19, 2), 0);
        func_28F510(o->f878, 0x758C, insect_InsectMsgGet_512b70(p19, 3), 0);
        func_290010(o->f878, 0x753C, 1, -1);
        func_290010(o->f878, 0x753E, 1, -1);
        func_291110(o->f878, 0x7542, 0, 1);
        func_290010(o->f87C, 0xC37E, 1, -1);
        b = !(insect_InsectBattleTestFlag_50da40(o, 2) != 0);
        func_290010(o->f878, 0x758C, b, -1);
        i = 0;
        do {
            w = func_290460(o->f878, D_00480EF0[i * 2]);
            if (w != 0) {
                w->f2C = insect_InsectBattleRosterListTextClipCb_5102f0;
            }
            i++;
        } while (i < 4);
        i = 0;
        do {
            w = func_290460(o->f878, D_00480F00[i * 2]);
            i++;
            w->f2C = insect_InsectBattleRosterListScissorCb_510130;
        } while (i < 2);
        n = insect_InsectBattleGetPoolCount_50db60(o, o->f5EF1);
        func_290FC0(o->f878, 0x7549, &x6C, &x68);
        func_290F60(o->f878, 0x754B, x6C, x68);
        o->f5D9C = func_392E60(g, func_290460(o->f878, 0x7554), 0x8E, 5, n);
        func_290F60(o->f878, 0x754E, 0x1B4, 0x1A);
        insect_InsectBattleMemberListFill_4faa90(o, (u8 *)o + (o->f5EF1 << 5) + 0x4920);
        insect_InsectBattleSetStep_50d7a0(o, 0x19, 2, -1);
        /* fallthrough */
    case 0x19:
        if (func_290D30(o->f878, 0x7548) == 0) {
            insect_InsectBattleSetStep_50d7a0(o, 0x1A, 2, -1);
        }
        insect_InsectBattleCursorUpdateDesc_4f4530(o, D_00523E10, 0);
        insect_InsectBattleRosterListRefresh_4faf00(o, (u8 *)o + (o->f5EF1 << 5) + 0x4920);
        break;
    case 0x1A:
        rec = (u8 *)o + (o->f5EF1 << 5) + 0x4920;
        if (insect_InsectCursorSetGetEvents_5119f0(o->f4F90, 0xF0000) != 0) {
            if (insect_InsectCursorSetGetEvents_5119f0(o->f4F90, 0x10000) != 0) {
                func_290F50(o->f878, 0x7553, 0, 0x1C, 0, 0.5f);
            }
            if (insect_InsectCursorSetGetEvents_5119f0(o->f4F90, 0x20000) != 0) {
                func_290F50(o->f878, 0x7553, 0, -0x1C, 0, 0.5f);
            }
            o->f4FBC = o->f4FBC | 2;
        }
        c = insect_InsectCursorSetFindPage_511e60(o->f4F90, 1);
        x64 = c->fA;
        x60 = c->fB;
        func_290F50(o->f878, 0x7554, 0, (s32)((f32)x60 * o->f5D9C), 0, 0.5f);
        if (func_290D30(o->f878, 0x7553) == 0) {
            o->f4FBC = o->f4FBC & 0xFD;
            insect_InsectBattleRosterListRefresh_4faf00(o, rec);
        }
        insect_InsectBattleMemberListFill_4faa90(o, rec);
        insect_InsectCursorSetGetCell_511a40(o->f4F90, 1, &x64, &x60);
        insect_InsectBattleCursorUpdateDesc_4f4530(o, D_00523E10, 0);
        break;
    case 0x47:
        insect_InsectBattleConfirmDialogOpen_50eaf0(o->f5DA0, o->f5DA4, p19, 0x28);
        func_2907A0(o->f87C, 0xC378, 0.0f);
        func_290690(o->f87C, 0xC378, 1.0f, 0.125f, -1.0f);
        func_2907A0(o->f87C, 0xC37E, 0.0f);
        func_290690(o->f87C, 0xC37E, 1.0f, 0.125f, -1.0f);
        insect_InsectBattleSetStep_50d7a0(o, 0x46, 2, -1);
        insect_InsectBattleCursorUpdateDesc_4f4530(o, D_00523C10, 1);
        /* fallthrough */
    case 0x46:
        if (func_290770(o->f87C, 0xC378) >= 1.0f) {
            insect_InsectBattleSetStep_50d7a0(o, 0x49, 2, -1);
            insect_InsectBattleSetStep_50d7a0(o, 0x49, 0, -1);
            o->f4FBC = o->f4FBC & 0xFD;
            insect_InsectBattleCursorUpdateDesc_4f4530(o, D_00523C10, 1);
        }
        break;
    case 0x49:
        insect_InsectCursorSetGetCell_511a40(o->f4F90, 7, &x5C, &x58);
        insect_InsectBattleCursorUpdateDesc_4f4530(o, D_00523C10, 0);
        w = func_290460(o->f87C, 0xC37B);
        b = !(x5C != 0);
        func_392B20(g, w, b);
        func_392B20(g, func_290460(o->f87C, 0xC37C), x5C);
        break;
    case 0x4A:
    case 0x4B:
        func_290690(o->f87C, 0xC378, 0.0f, 0.125f, -1.0f);
        func_290690(o->f87C, 0xC37E, 0.0f, 0.125f, -1.0f);
        insect_InsectBattleSetStep_50d7a0(o, insect_InsectBattleGetStep_50d6a0(o, 2), 0, -1);
        insect_InsectBattleSetStep_50d7a0(o, 0, 2, -1);
        break;
    case 0x1D:
        func_290690(o->f878, 0x7530, 0.0f, 0.125f, -1.0f);
        func_290690(o->f87C, 0xC37E, 0.0f, 0.125f, -1.0f);
        if (func_290770(o->f878, 0x7530) <= 0.0f) {
            insect_InsectBattleSetStep_50d7a0(o, 0xB, 2, -1);
        }
        break;
    case 0xA:
        insect_InsectBattleSetStep_50d7a0(o, 0xB, 2, -1);
        break;
    case 0xB:
        break;
    }
}
