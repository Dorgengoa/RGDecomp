/* rgp:protos */
#define RGP_SELF_insect_InsectBattleApplyDamage_50f350 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* insect 0x0050F350 -- 992 bytes, 248 instructions, 33 calls, 23 conditional
 * branches.  Five parameters: the fifth arrives in $8 (PS2 EABI) and is
 * spilled to 0xBC($29) in the prologue.
 *
 * `k = -1;` sits at the END of BOTH arms of the f38 == 0xC if/else and retail
 * emits it TWICE -- once in the `b .L0050F610` delay slot and once on the
 * fall-through at .L0050F60C.  That is round 1's "an assignment common to
 * both arms is written OUTSIDE the if" shape, so it is written after the
 * if/else, not inside each arm.
 *
 * `t == 8` and `t == 0xF` are two INDEPENDENT ifs, not an else-if chain:
 * the t == 8 body falls straight into the t == 0xF test at .L0050F64C.
 *
 * The `sd $0, 0x0($29)` is insect_InsectBattleEffectsSpawn_51dc30's NINTH argument, an s64.
 *
 * `k` and `k2` are TWO source variables, not one reassigned: retail keeps the
 * whole chain in $17, and writing `k = -1;` a second time after the if/else
 * splits our live range across $16/$17 for 11 bad words.  A fresh `k2` for the
 * post-join value is 0 bad.  Declaration-order permutation CANNOT see this --
 * all 23 orders of {k,mm,m,n} and all 119 of {w,flag,v,k,mm} are one object.
 */

typedef struct Ent {
    u8  pad00[0x38];
    s8  f38;                    /* +0x38 */
    u8  pad39[0x4C - 0x39];
    s8  f4C;                    /* +0x4C */
    u8  pad4D[0x5C - 0x4D];
    s32 f5C;                    /* +0x5C */
    u8  pad60[0x62 - 0x60];
    s8  f62;                    /* +0x62 */
} Ent;

typedef struct Ctx {
    u8 pad0000[0x506C];
    u8 f506C[0x5080 - 0x506C];      /* +0x506C */
    u8 f5080[0x5178 - 0x5080];      /* +0x5080 */
    u8 f5178[4];                    /* +0x5178 */
} Ctx;

extern void  Sprintf_1343b8();
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


s32 insect_InsectBattleApplyDamage_50f350(Ent *a, Ent *b, s32 c, Ent *d, s32 e)
{
    char  buf[0x40] __attribute__((aligned(16)));
    Ctx  *cx;
    void *w;
    s32   flag;
    s32   k;
    s32   k2;
    void *mm;
    s32   m;
    s32   n;
    void *v;
    s32   t;

    cx = ((Ctx *)InsectBattleGet_31a8d0());
    v  = cx->f5080;
    mm = cx->f506C;
    w  = cx->f5178;
    if (a == 0 || b == 0) {
        return 0;
    }
    if (d != 0 && insect_InsectPieceTestStatus_513280(a, 0x10) != 0) {
        Sprintf_1343b8(buf, ((s32)insect_InsectMsgGet_512b70(mm, 0x37)), a->f5C);
        if (v != 0) {
            insect_InsectBattleLogPush_51c2f0(v, buf, -5, -1, 0);
        }
        insect_InsectBattleDamagePopupSpawn_50f730(b, -1, 0x80402080);
        insect_InsectPlaySe_510870(7);
        return 0;
    }
    c = insect_InsectPieceTakeDamage_515020(b, c);
    if (c <= 0) {
        c = 0;
    }
    flag = 0;
    insect_InsectPieceClearStatus_513340(a, 0x11);
    insect_InsectPieceSetStatus_5132d0(a, 0x11);
    k = -1;
    if (b->f38 == 0xC) {
        if (c <= 0) {
            if (b->f4C <= 0) {
                Sprintf_1343b8(buf, ((s32)insect_InsectMsgGet_512b70(mm, 0x35)), b->f5C);
                insect_InsectPiecePlayMotion_5145e0(b, 7, 2, 0.0f, 1.0f);
                if (e != 0) {
                    insect_InsectBattleEffectsSpawn_51dc30(w, b, 0x15, 2, 0, k, k, 1, (int)(0));
                }
            } else {
                Sprintf_1343b8(buf, ((s32)insect_InsectMsgGet_512b70(mm, 0x69)), a->f5C);
                k = 2;
                flag = 1;
            }
        } else {
            k = 2;
            Sprintf_1343b8(buf, ((s32)insect_InsectMsgGet_512b70(mm, 0x32)), b->f5C, c);
            flag = 1;
        }
        if (insect_InsectPieceCanAct_514920(b) != 0) {
            insect_InsectPiecePlayMotion_5145e0(b, k, 6, 0.0f, 1.0f);
        }
        insect_InsectBattlePieceResetMotion_50f960(b);
    } else {
        if (c <= 0) {
            Sprintf_1343b8(buf, ((s32)insect_InsectMsgGet_512b70(mm, 0x33)), b->f5C);
            flag = 1;
        } else {
            Sprintf_1343b8(buf, ((s32)insect_InsectMsgGet_512b70(mm, 0x32)), b->f5C, c);
            if (insect_InsectPieceCanAct_514920(b) != 0) {
                insect_InsectPiecePlayMotion_5145e0(b, 2, 6, 0.0f, 1.0f);
                insect_InsectBattlePieceResetMotion_50f960(b);
            }
            flag = 1;
        }
    }
    k2 = -1;
    m = k2;
    n = k2;
    if (flag != 0) {
        if (d != 0) {
            t = d->f62;
            if (t == 8) {
                if (a->f38 == 2) {
                    m = 0x1C;
                    k2 = 0x23;
                }
            }
            if (t == 0xF) {
                if (a->f38 == 0x11) {
                    n = 6;
                }
            }
        } else {
            m = 0xF;
            n = 6;
        }
        if (m != -1) {
            insect_InsectBattleEffectsSpawn_51dc30(w, b, m, 2, 0, -1, -1, 1, (int)(0));
        }
        if (k2 != -1) {
            insect_InsectBattlePlayBankSe_5107d0(k2);
        }
        if (n != -1) {
            insect_InsectPlaySe_510870(n);
        }
    }
    if (v != 0) {
        insect_InsectBattleLogPush_51c2f0(v, buf, -5, -1, 0);
    }
    insect_InsectBattleDamagePopupSpawn_50f730(b, c, 0x80402080);
    return 1;
}
