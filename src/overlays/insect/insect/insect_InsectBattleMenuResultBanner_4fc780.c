/* insect 0x004FC780 -- 1,124 B / 281 words.  MATCHES (ix81).
 *
 * The ix36 FAMILY WORD, closed by the UNION PUN -- see the full account in
 * src/wf/insect/insect_InsectBattleFlowTurnStart_508b30.c and levers.d/mwcc-union-address-pun.
 * Retail rematerialises the fill buffer's frame address after the call in a
 * caller-saved register (`addiu $v0,$sp,K` at 004FCA7C); writing the address
 * through QPun's INTEGER member and reading it back through its POINTER
 * member reproduces that exactly, because mwcc's propagator is member-typed
 * and cannot forward across the pun.  That took the unit 10 -> 2.
 *
 * ⚠ THE LAST TWO WORDS WERE THE FRAME SIZE, AND `t` IS DELIBERATELY DECLARED
 * ONE ELEMENT SHORT.  QPun is an AGGREGATE, so mwcc reserves a frame slot for
 * it above the existing aggregates even though the value never reaches
 * memory.  This frame's aggregate area is exactly full (`w` 16 B at 0x70,
 * the fill buffer 16 B at 0x80, frame 0x90), so the union pushed it to 0xA0.
 * Declaring the buffer as `f32 t[3]` with `qu` immediately after it puts the
 * two objects in ONE 16-byte region: insect_InsectBattleVoiceIdSplit_4f0220 writes 16 bytes
 * across both, and the 4 bytes it writes over `qu` are never read back from
 * memory, so the overlap is inert.  The adjacency of these two declarations
 * is LOAD-BEARING -- do not separate or reorder them.
 *
 * Measured alternatives that do NOT work (build/ix81/sweep_4fc780_ix81*.log):
 * an 8- or 16-byte union (still 0xA0, and +1 word); the union as the tail
 * member of a 16-byte struct (the pun then needs a SECOND union, 0xA0); the
 * union at function scope with `t[4]` (0xA0).
 */
#include "types.h"
/* insect 0x004FC780 -- 1124 bytes, 284 instructions, 35 calls, 25 branches.
 * The insect_InsectBattleGetStep_50d6a0(o, 2) state-dispatch family (template
 * insect_InsectBattleMenuPieceCmd_501810.c).  No jump table: a compare chain testing 9, 2, 1, so
 * source order is 1, 2, 9 -- and case 1 FALLS THROUGH into case 2, which the
 * block addresses (4FC7F4 < 4FC9CC < 4FCABC) confirm.
 * Every `/ 2` here is the signed bgez/sra strength reduction, not a `div`, so
 * the file carries no divide-by-zero trap and needs no pragma.
 * 0x3E000000 is 0.125f (not 0.25f).
 */

typedef struct Node {
    u8    pad00[0x58];
    s32   f58;                      /* +0x58 */
    u8    pad5C[0x6C - 0x5C];
    s16   f6C;                      /* +0x6C */
    u8    pad6E[0x1E8 - 0x6E];
} Node;

typedef struct Spr {
    u8    pad00[0x0A];
    s16   f0A;                      /* +0x0A */
} Spr;

typedef struct Han {
    u8    pad00[0x20];
    Spr  *f20;                      /* +0x20 */
} Han;

typedef struct V4 {
    s32 a;
    s32 b;
    s32 c;
    f32 d;
} V4;

typedef union QPun { V4 *p; s32 i; } QPun;

typedef struct Ins {
    u8    pad0000[0x870];
    void *f870;                     /* +0x0870 */
    u8    pad0874[0x878 - 0x874];
    void *f878;                     /* +0x0878 */
    u8    pad087C[0x35F8 - 0x87C];
    u8    f35F8[0x4940 - 0x35F8];   /* +0x35F8 */
    u8    f4940[0x5B08 - 0x4940];   /* +0x4940 */
    s32 (*f5B08)[12];               /* +0x5B08 */
    u8    pad5B0C[0x5B14 - 0x5B0C];
    s32   f5B14;                    /* +0x5B14 */
    u8    pad5B18[0x5DA0 - 0x5B18];
    s32   f5DA0;                    /* +0x5DA0 */
    s32   f5DA4;                    /* +0x5DA4 */
    s32   f5DA8;                    /* +0x5DA8 */
} Ins;

extern void  func_1CFC50(void *, s16);
extern void  func_2070F0(s32, s32, s32, f32);
extern void  func_207880(s32, s32);
extern void  func_290010(void *, s32, s32, s32);
extern Han  *func_290460(void *, s32);
extern void  func_290690(void *, s32, f32, f32, f32);
extern void  func_2907A0(void *, s32, f32);
extern s32   func_290D30(void *, s32);
extern void  func_290F50(void *, s32, s32, s32, s32, f32);
extern void  func_290F60(void *, s32, s32, s32);
extern void  insect_InsectBattleVoiceIdSplit_4f0220(f32 *, Ins *, s32, s32);
extern void  insect_InsectBattleRecordAddWin_4f0ad0(Ins *, s32);
extern s32   insect_InsectBattleGetStep_50d6a0(Ins *, s32);
extern void  insect_InsectBattleSetStep_50d7a0(Ins *, s32, s32, s32);
extern void  insect_InsectBattleSetState_50d8c0(Ins *, s32, s32, s32);
extern s32   insect_InsectBattleTestFlag_50da40(Ins *, s32);
extern void  insect_InsectPlayJingle_510760(s32);
extern s32   insect_InsectIsJingleDoneMaybe_510780(void);
extern s32   insect_InsectPieceTestStatus_513280(Node *, s32);
extern Node *insect_InsectTeamGetPiece_5138d0(void *, s32);
extern s32   insect_InsectTeamSlotGetEnemyRowMaybe_513e80(void *);

void insect_InsectBattleMenuResultBanner_4fc780(Ins *o)
{
    s32   n;
    u8   *p;
    s32   i;
    Node *e;
    s32   j;
    s32   id;
    s32   v;
    s32   k;
    void *q;
    Spr  *s;
    f32   t[3];
    QPun  qu;
    V4    w;

    n = 1;
    if (insect_InsectBattleTestFlag_50da40(o, 0x3E) != 0) {
        n = 0;
    }
    switch (insect_InsectBattleGetStep_50d6a0(o, 2)) {
    case 1:
        func_207880(0, 1);
        func_290F60(o->f878, 0x755C, o->f5DA0 + 0x180, (o->f5DA4 - 0x3E) / 2);
        func_290010(o->f878, 0x755C, 0, -1);
        if (n == 0) {
            if (insect_InsectBattleTestFlag_50da40(o, 2) != 0) {
                insect_InsectPlayJingle_510760(0x327);
            } else {
                q = o->f4940;
                if (q != 0) {
                    if (insect_InsectTeamSlotGetEnemyRowMaybe_513e80(q) >= 4) {
                        insect_InsectPlayJingle_510760(0x328);
                    } else {
                        insect_InsectPlayJingle_510760(0x327);
                    }
                }
            }
        } else {
            v = o->f5DA8;
            id = 0x329;
            if (v == 3 || v == 5) {
                id = 0x327;
            }
            insect_InsectPlayJingle_510760(id);
        }
        func_290010(o->f878, 0x755C, 1, -1);
        func_2907A0(o->f878, 0x755C, 0.0f);
        func_290690(o->f878, 0x755C, 1.0f, 0.125f, -1.0f);
        s = func_290460(o->f878, 0x755C)->f20;
        s->f0A = (n << 6) + 0x40;
        if (o->f5DA8 != 0) {
            s->f0A = s->f0A + 0xC0;
        }
        func_290F60(o->f878, 0x755C, o->f5DA0 + 0x180, (o->f5DA4 - 0x3E) / 2);
        func_290F50(o->f878, 0x755C, (o->f5DA0 - 0x180) / 2,
                    (o->f5DA4 - 0x3E) / 2, 0, 0.5f);
        insect_InsectBattleSetStep_50d7a0(o, 2, 2, -1);
        /* fallthrough */
    case 2:
        if (insect_InsectIsJingleDoneMaybe_510780() != 0 &&
            func_290D30(o->f878, 0x755C) == 0) {
            func_290F50(o->f878, 0x755C, -0x180, (o->f5DA4 - 0x3E) / 2, 0,
                        0.5f);
            insect_InsectBattleSetStep_50d7a0(o, 9, 2, -1);
            if (o->f5DA8 == 0) {
                k = o->f5B14;
                insect_InsectBattleVoiceIdSplit_4f0220(t, o, o->f5B08[k][6 - n], k);
                qu.i = (s32)t;
                w = *qu.p;
                func_2070F0(w.a, w.b, w.c, w.d);
            }
        }
        break;
    case 9:
        if (func_290D30(o->f878, 0x755C) == 0) {
            p = o->f35F8;
            for (i = 0; i < 2; i++) {
                e = insect_InsectTeamGetPiece_5138d0(p, 0);
                for (j = 0; j < 5; j++) {
                    if (insect_InsectPieceTestStatus_513280(e, 0x1B) == 0) {
                        v = e->f6C;
                        func_1CFC50(o->f870, v);
                        if (e->f58 != 0) {
                            func_1CFC50(o->f870, e->f6C + 0x40);
                        }
                    }
                    e++;
                }
                p += 0x994;
            }
            if (insect_InsectBattleTestFlag_50da40(o, 2) != 0) {
                insect_InsectBattleSetState_50d8c0(o, 0x28, 0, -1);
                insect_InsectBattleSetStep_50d7a0(o, 0xB, 2, -1);
                insect_InsectBattleRecordAddWin_4f0ad0(o, n);
            } else {
                insect_InsectBattleSetState_50d8c0(o, 0x20, 0, -1);
                insect_InsectBattleSetStep_50d7a0(o, 0xB, 2, -1);
            }
        }
        break;
    }
}
