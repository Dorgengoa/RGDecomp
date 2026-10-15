/* MATCH, ix66 (2026-09-14).  Closed by the ONE-CASE SWITCH lever:
 *  the `b->f38 != 0xC` early exit is a `switch (b->f38) { case 0xC: ... }`.
 *  Its DEFAULT edge is an unconditional jump to the `return r` join with an
 *  empty own block; mwcc fills it from the join's `move $v0,$s0` and MARKS the
 *  join, so the `b->f4C > 0` guard inside the case stays `blez`+`nop` (retail).
 *  As `if (...) return r;` the exit is an independent return block, the join
 *  is unmarked, and the guard gets the copy (`blezl`+`move`, the 2-bad park).
 *  `goto done;` / do-while(0)+break FOLD into the compare (one word short).
 *  build/ix66/sweep_4f3480_ix66a_switch.log.
 *
 * (ix29 park history follows.)  ix29: EXACT LENGTH, 2 bad.
 * 63 -> 2 bad this session, three independent fixes:
 *  (1) ARITY: insect_InsectBattleEffectsSpawn_51dc30 is MERGED and takes NINE args whose ninth is
 *      an `s64` (src/overlays/insect/insect_InsectBattleApplyDamage_50f350.c makes the identical
 *      call).  The ix17/ix22 park declared TEN s32 -> `sd $0,0(sp)` AND
 *      `sd $0,8(sp)` where retail emits one.  ONE EXTRA WORD.
 *  (2) The `bp` hoist: retail reuses $s0 (r, dead inside the branch) for
 *      `addiu $s0,$s5,0x5F82` and feeds both call sites from it.  ONE MISSING
 *      WORD -- (1) and (2) cancelled, which is why the park read EXACT LENGTH.
 *      The definition must be BLOCK-local; at function scope it takes a 7th
 *      callee-saved register (frame 0x80 -> 0x90, +3 words).
 *  (3) Declaration order == STATEMENT order (hh p1 p2 a b r): 37 -> 2.
 *      ix22's 719-permutation sweep bottomed at 63 because it was measured
 *      under (1) and (2).
 * The last 2 words are 0x4F3588/8C: retail `blez`+`nop` (plain, branch to the
 * shared join), ours `blezl`+`move $v0,$s0` (likely, threaded past the join).
 * MEASURED NULL on those 2: six guard-polarity/exit spellings, four
 * scheduler-side `pre` statements, four named-load spellings -- all ONE object.
 */
#include "types.h"
/* insect 0x004F3480 -- 408 bytes, 102 instructions, 13 calls. */

typedef struct Ent {
    u8  pad00[0x38];
    s8  f38;                        /* +0x38 */
    u8  pad39[0x4C - 0x39];
    s8  f4C;                        /* +0x4C */
    u8  pad4D[0x5C - 0x4D];
    s32 f5C;                        /* +0x5C */
} Ent;

typedef struct Obj {
    u8   pad00[0x506C];
    u8   f506C;                     /* +0x506C */
    u8   pad506D[0x5080 - 0x506D];
    u8   f5080;                     /* +0x5080 */
    u8   pad5081[0x5178 - 0x5081];
    u8   f5178;                     /* +0x5178 */
    u8   pad5179[0x5B20 - 0x5179];
    Ent *f5B20;                     /* +0x5B20 */
    Ent *f5B24;                     /* +0x5B24 */
    u8   pad5B28[0x5F82 - 0x5B28];
    u8   f5F82;                     /* +0x5F82 */
} Obj;

extern s32  insect_InsectBattleCalcBaseDamage_50ffb0(Ent *a, Ent *b, s32 c);
extern s32  insect_InsectBattleRollHit_50fb10(Ent *a, Ent *b);
extern void insect_InsectPieceSetStatus_5132d0(Ent *a, s32 k);
extern s32  insect_InsectPieceTestStatus_513280(Ent *a, s32 k);
extern void insect_InsectBattleClearTextBuf_50e120(Obj *h, s32 k);
extern s32  insect_InsectMsgGet_512b70(u8 *p, s32 k);
extern void func_1343B8(u8 *d, s32 s, s32 n);
extern void insect_InsectBattleLogPush_51c2f0(u8 *a, u8 *b, s32 c, s32 d, s32 e);
extern void insect_InsectPlaySe_510870(s32 k);
extern void insect_InsectBattleDamagePopupSpawn_50f730(Ent *b, s32 k, s32 c);
extern void insect_InsectPieceBallDamage_514f10(Ent *b, s32 r);
extern void insect_InsectPiecePlayMotion_5145e0(Ent *b, s32 a, s32 c, f32 x, f32 y);
extern void insect_InsectBattleEffectsSpawn_51dc30(u8 *p, Ent *b, s32 c, s32 d, s32 e,
                                s32 f, s32 g, s32 i, s64 j);

s32 insect_InsectBattleAttackResolve_4f3480(Obj *h)
{
    Obj *hh;
    u8 *p1;
    u8 *p2;
    Ent *a;
    Ent *b;
    s32 r;
    u8 *bp;

    hh = h;
    p1 = &hh->f506C;
    p2 = &hh->f5080;
    a = hh->f5B20;
    b = hh->f5B24;
    if (a == 0 || b == 0) {
        return 0;
    }
    r = insect_InsectBattleCalcBaseDamage_50ffb0(a, b, 0);
    if (insect_InsectBattleRollHit_50fb10(a, b) == 0) {
        insect_InsectPieceSetStatus_5132d0(a, 0xF);
    }
    if (insect_InsectPieceTestStatus_513280(a, 0xF) != 0) {
        insect_InsectBattleClearTextBuf_50e120(hh, 2);
        bp = &hh->f5F82;
        func_1343B8(bp, insect_InsectMsgGet_512b70(p1, 0x36), a->f5C);
        insect_InsectBattleLogPush_51c2f0(p2, bp, -5, -1, 0);
        insect_InsectPlaySe_510870(7);
        insect_InsectBattleDamagePopupSpawn_50f730(b, -1, 0x80402080);
        r = 0;
    } else {
        switch (b->f38) {
        case 0xC:
            if (b->f4C > 0) {
                insect_InsectPieceBallDamage_514f10(b, r);
                if (b->f4C <= 0) {
                    insect_InsectPiecePlayMotion_5145e0(b, 7, 6, 0.0f, 1.0f);
                    insect_InsectBattleEffectsSpawn_51dc30(&hh->f5178, b, 0x15, 2, 0, -1, -1, 1, 0);
                }
                r = 0;
            }
            break;
        }
    }
    return r;
}
