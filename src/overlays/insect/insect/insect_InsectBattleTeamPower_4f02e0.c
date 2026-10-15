#include "types.h"
/* insect 0x004F02E0 -- 580 bytes.  MATCHING (ix33).
 *
 * ix23 parked this at ONE word: 0x4F0478, a commutative add whose operands
 * were transposed (retail `addu $s0,$v0,$v1`, ours `addu $s0,$v1,$v0`), and
 * filed it as a canonicalisation "below the source language" after swapping
 * the source operands gave a BYTE-IDENTICAL object.
 *
 * *** THE RULE, read off the OTHER five adds in the same chain: mwcc puts
 * the SOURCE LEFT operand of `+` in rs -- b+a, c+(b+a), call1+prev,
 * call5+prev all obey it.  So retail's left operand at 0x4F0478 is the CALL.
 * But when the left operand is a CALL EXPRESSION and the right is a cheap
 * tree, mwcc NORMALISES the call into rt -- which is why the plain swap is
 * inert and why ix23 concluded the axis did not exist.
 *
 * *** `-` IS NOT COMMUTATIVE, so there is nothing to normalise: writing the
 * node as a subtraction of the negated operand pins the call in rs and the
 * double negation folds away.  Seven spellings give the identical object
 * (`X - (-G)`, `X - (0 - G)`, `X - (-c - (b+a))`, ...); `X - (-c - b - a)`
 * is a different TREE and is 2 bad.
 */
/* insect 0x004F02E0 -- 580 bytes, 145 instructions, 12 calls, 7 conditional
 * branches, br/ins 0.048.  A score accumulator with two completely different
 * summation loops and a RECURSIVE call in one switch arm.
 *
 * Compare chain 5, 4, 3 -- REVERSED -- so source order is 3, 4, 5, which is the
 * block order (0x4F0358, 0x4F036C, 0x4F037C).  Cases 4 and 5 both `b` into the
 * shared `cnt = 0` at 0x4F0398 and the DEFAULT branches one instruction further
 * to 0x4F039C with `daddu $8, $0, $0` in its own delay slot, so the default
 * enters the loop with p still NULL -- that is the game's code, not a misread.
 *
 * ★ ONE `return sum;` covers both arms, not two.  The `flag == 0` arm exits
 * `b .L004F04F4 / daddu $2, $21, $0` -- the return value in the DELAY SLOT --
 * while the other arm materialises the same `daddu` as its own block's last
 * word and falls in.  main-pass31-spellings #1: count the exits before reading
 * a value-carrying delay slot as a per-arm `return`.  Only `case 3` is a real
 * early return, and it is a tail call to this function.
 *
 * ★ insect-stmt-order-vs-decl-order, the SAME 0x994/0x20 record pair as
 * insect_FUN_004FF040: retail emits the 0x20 record's `addiu` FIRST (its
 * `mult` is issued early for latency) but keeps it in the LOWER register.  So
 * the statements are written 0x20-then-0x994 and the declarations are the other
 * way round.  Both levers, pulled in opposite directions.
 *
 * `k * 0xE0` comes out as `sll 3 / subu / sll 5` -- strength reduction, not a
 * source-level shift.
 */

typedef struct Rec {
    u8  pad00[0x10];
    u8  f10;                    /* +0x10 */
    u8  f11;
    u8  f12;
    u8  f13;
    u8  f14;
    u8  f15;
    u8  pad16[2];
    u8  f18;                    /* +0x18 */
    u8  pad19;
    u16 f1A;                    /* +0x1A */
    u16 f1C;                    /* +0x1C */
    u16 f1E;                    /* +0x1E */
    u8  pad20[8];
} Rec;                          /* sizeof 0x28 */

typedef struct Slot {
    u8  pad00[0x18];
    s8  f18;                    /* +0x18 */
    u8  pad19[0x1E - 0x19];
    s16 f1E;                    /* +0x1E */
    u8  pad20[6];
    u8  f26;                    /* +0x26 */
    u8  pad27;
    u8  f28;                    /* +0x28 */
} Slot;

typedef struct Sys {
    u8    pad00[0x24];
    void *f24;                  /* +0x24 */
} Sys;

typedef struct Ins {
    u8  pad000[0x5DA8];
    s32 f5DA8;                  /* +0x5DA8 */
} Ins;

extern Sys  *func_1FEDE0(void);
extern void *func_430B30(void *a, s32 k);
extern void *func_430B50(void *a, s32 k);

extern s32   insect_InsectPieceGetStat_512e20(Slot *r, s32 a, s32 b);
extern Slot *insect_InsectTeamGetPiece_5138d0(void *q, s32 i);
extern s32   insect_InsectTeamSlotGetMemberUsed_513ea0(void *e, s32 i);

s32 insect_InsectBattleTeamPower_4f02e0(Ins *o, s32 k, s32 flag)
{
    s32 d;
    s32 c;
    s32 b;
    s32 sum;
    u8 *q;
    u8 *e;
    s32 i;
    Slot *r;
    s32 s;
    s32 a;
    Sys *t;
    Rec *p;
    s32 kind;
    s32 cnt;

    sum = 0;
    t = func_1FEDE0();
    if (flag == 0) {
        kind = o->f5DA8;
        p = NULL;
        switch (kind) {
        case 3:
            return insect_InsectBattleTeamPower_4f02e0(o, k, 1);
        case 4:
            p = (Rec *)((u8 *)func_430B50(t->f24, kind) + 0x288);
            break;
        case 5:
            p = (Rec *)((u8 *)func_430B30(t->f24, kind) + k * 0xE0 + 0x28);
            break;
        }
        cnt = 0;
        do {
            cnt++;
            s = p->f18 * (p->f15 + (p->f14 + (p->f13 + (p->f12 + (p->f11 +
                (p->f10 + (p->f1E + (p->f1A + p->f1C))))))));
            p++;
            sum += s;
        } while (cnt < 5);
    } else {
        q = (u8 *)o + k * 0x994 + 0x35F8;
        e = (u8 *)o + k * 0x20 + 0x4920;
        i = 0;
        do {
            if (insect_InsectTeamSlotGetMemberUsed_513ea0(e, i) != -1) {
                r = insect_InsectTeamGetPiece_5138d0(q, i);
                a = r->f26;
                b = r->f1E;
                c = r->f28;
                d = r->f18;
                sum += d * (insect_InsectPieceGetStat_512e20(r, 5, 0) +
                            (insect_InsectPieceGetStat_512e20(r, 4, 0) +
                             (insect_InsectPieceGetStat_512e20(r, 3, 0) +
                              (insect_InsectPieceGetStat_512e20(r, 2, 0) +
                               (insect_InsectPieceGetStat_512e20(r, 1, 0) +
                                (insect_InsectPieceGetStat_512e20(r, 0, 0) - (-c - (b + a))))))));
            }
            i++;
        } while (i < 5);
    }
    return sum;
}
