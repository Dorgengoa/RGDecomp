/* rgp:protos */
#define RGP_SELF_insect_InsectBattleCalcSpecialDamage_50fce0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* insect 0x0050FCE0 -- 720 B / 180 words.  DIV-TRAP MID TIER (lane L2).
 *
 * Skill/attack resolution: pick a percentage from the move kind, scale the
 * target's 0x1E stat by it, then dispatch on the move's flag byte.
 *
 * The kind dispatch is a SWITCH -- every arm is entered by `beql` with the
 * percentage in the delay slot, so the compare chain 15,14,13,8,6,2,1 is the
 * source order REVERSED ([[insect-dispatch-branch-polarity]]).  The flag
 * dispatch is the OPPOSITE polarity (`beql` PAST the arm to the next test) so
 * it is an if / else-if chain in the order 1,2,4,8,0x10,0x20 AS WRITTEN.
 *
 * `adda.s $f1,$f2 / madd.s $f0,$f3,$f0` is the CONTRACTION of
 * `(f32)prod + 15.0f * ret` -- do NOT name the product
 * ([[normal-named-product-local]] in reverse).
 *
 * `dsll32 $3,$22,16 / dsra32 $3,$3,16` off a plain `lh` held across the call
 * is an s32 local + an explicit `(s16)` cast.
 *
 * One `div $0,$3,$2` by a literal 100 with `bnez $2 / break 0,7`:
 * `#pragma divbyzerocheck on`.
 */

#pragma divbyzerocheck on

typedef struct ActorFCE0 {
    u8  pad00[0x18];
    s8  m18;                    /* +0x18 */
    u8  pad19[0x38 - 0x19];
    s8  m38;                    /* +0x38 */
    u8  pad39[0x4F - 0x39];
    s8  m4F;                    /* +0x4F */
} ActorFCE0;

typedef struct TargetFCE0 {
    u8  pad00[0x1E];
    s16 m1E;                    /* +0x1E */
} TargetFCE0;

typedef struct MoveFCE0 {
    u8  pad00[0x62];
    s8  m62;                    /* +0x62 */
    u8  pad63[0x67 - 0x63];
    u8  m67;                    /* +0x67 */
    u8  pad68[2];
    s16 m6A;                    /* +0x6A */
} MoveFCE0;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 insect_InsectBattleCalcSpecialDamage_50fce0(ActorFCE0 *a, TargetFCE0 *t, s32 unused, MoveFCE0 *m)
{
    s32 pct;
    s32 acc;
    s32 base;
    s32 flags;
    s32 dmg;
    s32 n;
    s32 k;

    if (a == 0 || t == 0) {
        return 0;
    }
    pct = 100;
    flags = m->m67;
    base = t->m1E;
    acc = 0;
    switch (m->m62) {
    case 1:
        switch (a->m38) {
        case 0:
            pct = 0x28;
            break;
        case 1:
            pct = 0x2D;
            break;
        }
        break;
    case 2:
        pct = 0x30;
        break;
    case 6:
        pct = 0x1E;
        break;
    case 8:
        switch (a->m38) {
        case 2:
            pct = 0x28;
            break;
        case 15:
            pct = 0x2D;
            break;
        }
        break;
    case 13:
        pct = 0x1E;
        break;
    case 14:
        pct = m->m6A;
        break;
    case 15:
        k = a->m4F;
        n = m->m6A;
        acc += k;
        pct = (s32)((f32)((s16)n * (k + 1)) + 15.0f * insect_InsectPieceGetHpRatio_512e70(a));
        break;
    }
    acc += a->m18;
    dmg = base * pct / 100;
    if (flags & 1) {
        if (insect_InsectPieceRollVsResist_512bf0(t, insect_InsectPieceGetStat_512e20(t, 0, 0), acc) != 0) {
            return dmg;
        }
    } else if (flags & 2) {
        if (insect_InsectPieceRollVsResist_512bf0(t, insect_InsectPieceGetStat_512e20(t, 2, 0), acc) != 0) {
            return dmg;
        }
    } else if (flags & 4) {
        if (insect_InsectPieceRollVsResist_512bf0(t, insect_InsectPieceGetStat_512e20(t, 4, 0), acc) != 0) {
            return dmg;
        }
    } else if (flags & 8) {
        if (insect_InsectPieceRollVsResist_512bf0(t, insect_InsectPieceGetStat_512e20(t, 1, 0), acc) != 0) {
            return dmg;
        }
    } else if (flags & 0x10) {
        if (insect_InsectPieceRollVsResist_512bf0(t, insect_InsectPieceGetStat_512e20(t, 3, 0), acc) != 0) {
            return dmg;
        }
    } else if (flags & 0x20) {
        if (insect_InsectPieceRollVsResist_512bf0(t, insect_InsectPieceGetStat_512e20(t, 5, 0), acc) != 0) {
            return dmg;
        }
    }
    insect_InsectPieceSetStatus_5132d0(a, 0x10);
    return 0;
}
