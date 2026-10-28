/* rgp:protos */
#define RGP_SELF_factory_FactoryBeltExtendToward_500630 1
#include "port/game_protos.h"
#line 1
/* ====================================================================
 * factory_FactoryBeltExtendToward_500630 -- CLOSED, byte-identical, FACTORY session 66
 * (2026-09-04, tag fg66).  This was the last open unit in the image:
 * FACTORY.BIN is now 409/409 = 100.00% count, 134,224/134,224 = 100.00%
 * bytes, relinked BYTE-IDENTICAL (md5 7d1b462cd45053841d00a41d86a6f1a8)
 * from a WIPED build/obj-fc with all 409 objects rebuilt from disk.
 *
 * THE RESIDUE, for 50 sessions: a pure s2<->s3 transposition of `tgt` and
 * `cur` at 187 words, 17 bad, no other difference of any kind.  Retail
 * colours the pair dir prev TGT CUR k cnt a b c; every source anyone wrote
 * gave dir prev CUR TGT k cnt a b c.
 *
 * THE LEVER -- TWO EDITS, NEITHER OF WHICH PAYS ALONE:
 *
 *   1. `prev` is spelled as CUR'S ADDRESS MINUS ONE ELEMENT, not as its own
 *      indexed address:
 *          prev = tgt->f00 + idx - 1;          <- MATCH
 *          prev = (Cell *)((u8 *)&tgt->f00[idx] - 6);   <- the same object
 *          prev = tgt->f00 + (idx - 1);        <- 192 w, FIVE WORDS LONGER
 *          prev = &tgt->f00[idx - 1];          <- 192 w
 *      The parentheses are the whole difference: `+ (idx - 1)` scales
 *      idx-1 and is a second address computation, `+ idx - 1` computes
 *      &tgt->f00[idx] and steps back, so the address cur will use is the
 *      common subexpression.  [[insect-cse-two-spellings]] run backwards.
 *
 *   2. `cur = &tgt->f00[idx];` is written BELOW the prev-guard.  The
 *      compiler hoists the instruction back to w51 either way -- the object
 *      is not moved by this -- but the vreg is CREATED later, and that is
 *      what the allocator sees.  One statement further down (below the
 *      dx/dy/cnt block) is 188 w; `cur = prev + 1;` there is 188 w.
 *
 * Four cells MATCH: {prev subm, prev bsub} x {cur = &tgt->f00[idx],
 * cur = tgt->f00 + idx}, all with cur below the guard.
 *
 * WHY EVERY EARLIER SESSION MISSED IT.  `prev = cur - 1;` forces cur to be
 * written above prev, and prev is used by the guard, so cur could never be
 * sunk below the guard while prev was derived FROM cur.  Sessions 55-65
 * swept eight positions for `tgt` and never one for `cur`
 * ([[factory-session66-levers]]).  s62's "unreachable at exact length,
 * PROVEN" rested on "later creation -> lower register" read off the
 * decompiled allocator; s65 refuted that rule on this unit, and this close
 * shows what replaces it -- creation order still decides, but the source
 * position that sets it is invisible in the finished object.
 *
 * ⚠ The object cannot tell you this.  Our object and retail's have the
 * IDENTICAL interference graph, degrees and simplify rounds (deg66.py,
 * armed and BLIND on the pair) -- so no measurement of the finished code
 * could ever have ranked the arms.  The two winning arms were found by
 * enumerating source positions, not by modelling.
 *
 * Full record: [[factory-session66-levers]], [[overlay-factory]].
 * ==================================================================== */

#include "types.h"

typedef struct Cell {
    s16 f00;
    s16 f02;
    s16 f04;
} Cell;                                         /* 6 */

typedef struct Blk {
    s16 f00;
    s16 f02;
    u16 f04;
} Blk;                                          /* 6 */

typedef struct Part {
    Cell *f00;
    s16   f04;
    s16   f06;
    s16   f08;
    u8    pad0A[0x2];
} Part;                                         /* 0xC */

typedef struct Grid {
    u8    pad000[0x2AC];
    Part *f2AC;
    s16   f2B0;
} Grid;

/*rgp*/
/*rgp*/
/*rgp*/

s32 factory_FactoryBeltExtendToward_500630(Grid *o, s32 a, s32 b, s32 c)
{
    Cell *cur;
    Cell *prev;
    Blk  *cc;
    Part *p;
    s32   buf[2];
    s32   sum;
    s32   n;
    s32   i;
    s32   lim;
    s32   m;
    s32   idx;
    s32   dx;
    s32   dy;
    s32   adx;
    s32   ady;
    s32   cnt;
    s32   k;
    s32   dir;
    s32   v;
    s32   t;
    Part *tgt;

    sum = 0;
    p = o->f2AC;
    n = o->f2B0;
    tgt = &o->f2AC[a];
    for (i = 0; i < n; i++, p++) {
        if (p != tgt) {
            sum += p->f06;
        }
    }
    lim = 0x12C - sum;
    m = tgt->f04;
    if (lim < 0) {
        lim = 0;
    }
    if (lim < m) {
        m = lim;
    }
    idx = tgt->f08;
    if (idx >= m) {
        return 1;
    }
    prev = tgt->f00 + idx - 1;
    if (prev->f00 == b && prev->f02 == c) {
        return 1;
    }
    cur = &tgt->f00[idx];
    dx = b - prev->f00;
    dy = c - prev->f02;
    adx = dx < 0 ? -dx : dx;
    ady = dy < 0 ? -dy : dy;
    cnt = 0;
    if (ady < adx) {
        if (dy != 0) {
            buf[cnt] = dy < 0 ? 2 : 0;
            cnt++;
        }
        if (dx != 0) {
            buf[cnt] = dx < 0 ? 3 : 1;
            cnt++;
        }
    } else {
        if (dx != 0) {
            buf[cnt] = dx < 0 ? 3 : 1;
            cnt++;
        }
        if (dy != 0) {
            buf[cnt] = dy < 0 ? 2 : 0;
            cnt++;
        }
    }
    for (k = 0; k < cnt; k++) {
        dir = *(s32 *)(s32)&buf[k];
        if (((dir - prev->f04) & 3) == 2) {
            continue;
        }
        cur->f04 = dir;
        cur->f00 = prev->f00 + factory_FactoryGridDirDx_4ff9f0((s16)dir);
        cur->f02 = prev->f02 + factory_FactoryGridDirDy_4ff9b0(cur->f04);
        cc = ((Blk *)factory_FactoryFineGridCellAt_503880(o, cur->f00, cur->f02));
        if (cc == 0) {
            continue;
        }
        t = !(cc->f04 & 0x8000);
        if (t == 0) {
            continue;
        }
        v = cc->f00;
        switch (v) {
        case -1:
            break;
        case 0x13:
        case 0x16:
            if ((((cc->f04 & 3) - dir) & 1) == 0) {
                continue;
            }
            break;
        default:
            continue;
        }
        tgt->f08 = tgt->f08 + 1;
        factory_FactoryBeltExtendToward_500630(o, a, b, c);
        return 1;
    }
    return 0;
}
