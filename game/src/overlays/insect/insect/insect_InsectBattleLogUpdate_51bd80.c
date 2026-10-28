/* rgp:protos */
#define RGP_SELF_insect_InsectBattleLogUpdate_51bd80 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* insect 0x0051BD80 -- 852 bytes, 216 instructions, 9 calls, 28 branches.
 * The per-frame tick of the 0x50-slot queue hanging off o->f04 (stride 0x5A).
 * `hit` and `r` are u8 flags -- retail materialises their 1 with `daddiu`,
 * which is the u8/u16 register-resident tell (levers.d/mwcc-daddiu-unsigned-
 * narrow); every s32 counter here uses plain `addiu`.
 */

typedef struct Slot {
    u8  pad00[0x50];
    s8  f50;                        /* +0x50 */
    u8  pad51[0x54 - 0x51];
    s8  f54;                        /* +0x54 */
    u8  pad55[0x56 - 0x55];
    s16 f56;                        /* +0x56 */
    u8  pad58[0x5A - 0x58];
} Slot;

typedef struct Ctx {
    u8    pad00[0x04];
    Slot *f04;                      /* +0x04 */
    u8    pad08[0x0C - 0x08];
    s16   f0C;                      /* +0x0C */
    s16   f0E;                      /* +0x0E */
    u8    pad10[0x18 - 0x10];
    s16   f18;                      /* +0x18 */
    s16   f1A;                      /* +0x1A */
    u8    pad1C[0x1E - 0x1C];
    s16   f1E;                      /* +0x1E */
    s16   f20;                      /* +0x20 */
    s16   f22;                      /* +0x22 */
    u8    f24;                      /* +0x24 */
    u8    f25;                      /* +0x25 */
    u8    f26;                      /* +0x26 */
} Ctx;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

void insect_InsectBattleLogUpdate_51bd80(Ctx *o)
{
    u8 hit;
    s32 nd;
    s32 cnt;
    s32 lim;
    s32 last;
    s32 idx;
    s32 m;
    Slot *q;
    u8 r;
    s32 k;
    Slot *p;
    Slot *w;
    Slot *u;
    s32 n2;
    s32 n3;

    if (o->f04 == 0) {
        return;
    }
    o->f1E = 0;
    cnt = 0;
    p = o->f04;
    k = 0;
    while (k < 0x50) {
        if (p->f54 == 0) {
            break;
        }
        cnt++;
        k++;
        p++;
    }
    if (cnt == 0) {
        o->f25 = 0;
        o->f26 = 0;
        return;
    }

    if (o->f0E > 0) {
        if (o->f0C < o->f0E) {
            o->f0C = o->f0C + o->f1A;
            if (o->f0C >= o->f0E) {
                o->f0C = 0;
                o->f0E = 0;
                insect_InsectBattleLogScrollUp_51c180(o);
                cnt--;
                if (o->f22 > 0) {
                    o->f22 = o->f22 - 1;
                }
            }
        }
    }

    lim = cnt;
    if (o->f18 < cnt) {
        lim = o->f18;
    }

    q = o->f04;
    last = lim - 1;
    hit = 0;
    nd = 0;
    idx = -1;
    m = 0;
    while (m < lim) {
        if (!hit) {
            if (q->f56 > 0) {
                hit = 1;
                insect_InsectBattleLogLineRevealTick_51c650(q);
            } else {
                insect_InsectBattleLogLineFadeStep_51c740(q);
                nd++;
            }
        }
        if (q->f50 != 0) {
            idx = m;
        }
        m++;
        q++;
    }

    if (o->f0E == 0) {
        insect_InsectBattleLogWaitTick_51c140(o);
        if (o->f20 <= 0) {
            r = 0;
            o->f25 = o->f26;
            if (idx < 0) {
                r = 1;
            } else if (o->f22 > 0) {
                r = 1;
            } else if (hit) {
                if (lim >= o->f18 && nd == lim) {
                    r = 1;
                }
            } else {
                o->f1E = 1;
                if (PadIsHeld_183a20(((s32)GetPad0_1c6c60()), 0x4040) != 0) {
                    {
                        Slot *bp;
                        bp = o->f04 + idx;
                        bp->f50 = 0;
                    }
                    o->f22 = lim;
                    if ((lim * 2) < cnt) {
                        w = o->f04 + last + lim;
                        n2 = 0;
                        while (n2 < lim) {
                            if (w->f50 != 0) {
                                break;
                            }
                            n2++;
                            w--;
                            o->f22 = o->f22 - 1;
                        }
                    }
                    u = o->f04 + last;
                    n3 = 0;
                    while (last < cnt - 1 && n3 < o->f22) {
                        u->f50 = 0;
                        last++;
                        n3++;
                        u++;
                    }
                    insect_InsectBattleLogResetWait_51c0e0(o);
                    r = 1;
                }
            }
            if (r) {
                if (o->f24 == 0) {
                    insect_InsectBattleLogLineFadeTo_51c7d0(o->f04, 0, 0x10);
                    o->f0E = 0x18;
                    o->f0C = 0;
                } else {
                    o->f22 = 0;
                }
                insect_InsectBattleLogResetWait_51c0e0(o);
            }
        }
    }
}
