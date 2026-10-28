/* rgp:protos */
#define RGP_SELF_factory_FactoryMergeInputsMatchType2Maybe_4f4c60 1
#include "port/game_protos.h"
#line 1
#include "types.h"

#pragma optimization_level 3

/* factory.bin overlay, 0x004F4C60 -- the "three-slot" variant of the equip
 * comparison: walk the caller's id list against the item table, collect one
 * key per slot into two parallel arrays and report whether they agree.
 * 560 bytes, 140 instructions, 13 conditional branches, 3 calls.
 *
 * * TWIN of `factory_FactoryMergeInputsMatchType2Maybe_4f4c60` at ratio 0.951 -- the same function with the
 * slot count fixed at TWO instead of THREE.  Found by ranking the OPEN
 * population against ITSELF; `f_sim.py` cannot see a pair of unsolved twins.
 *
 * * The FIRST parameter is never read.  The only call site
 * (`factory_FactoryMergeInputsMatchByTypeMaybe_4f6af0`) marshals NOTHING at all -- it is a pass-through of
 * its own parameters, which costs zero instructions when every argument keeps
 * its register -- so the count arrives in `$5` and the id list in `$6`, and a
 * two-parameter prototype would put them in `$4`/`$5`.
 *
 * * The two `func_131B60` clears BOTH take `b`; retail really does clear the
 * same array twice and never clears `a`.
 *
 * * `b` is declared FIRST because mwcc allocates stack locals in REVERSE
 * declaration order (the rule `factory_FactoryPartsShowNoStockMsgMaybe_4efa60` measured): `b` is at
 * 0x70($29) and `a` at 0x60($29).
 *
 * * The first loop's latch compare lands in `$at` and the other two land in a
 * GPR with no spelling difference between them: the `&& cont` makes this one's
 * consumer a `beql`, and in factory every compare feeding `beqz`/`beql` is in
 * `$at` (85 of 85 sites).
 *
 * ** #pragma optimization_level 3, exactly as its twin -- same +1 word
 * at -O4, same loop-invariant copy of the constant 1.
 */

typedef struct Val {
    s16 f00;
} Val;

typedef struct Ref {
    Val *f00;
    u8   pad04[0xC];
} Ref;                                          /* 0x10 */

typedef struct Item {
    u8  pad00[0x4];
    s16 f04;
    u8  pad06[0x2A];
    s16 f30;
    u8  pad32[0xE];
} Item;                                         /* 0x40 */

typedef struct Ctl {
    u8   pad00[0xC];
    Ref *f0C;
} Ctl;

typedef struct Mod {
    u8   pad00[0x70];
    Ctl *f70;
} Mod;

extern Mod *D_00484A48;                         /* _gp - 0x728 */

extern void  memset(void *p, s32 v, s32 n);
/*rgp*/

u8 factory_FactoryMergeInputsMatchType2Maybe_4f4c60(void *u, s32 unused, s32 *ids)
{
    s32   b[2];
    s32   a[2];
    Mod  *m;
    Ctl  *c;
    void *w;
    Item *tbl;
    Item *e;
    Ref  *q;
    Ref  *r;
    u8    found;
    u8    cont;
    u8    res;
    s32   cnt;
    s32   i;
    s32   j;
    s32   k;
    s32   x;
    s32   y;

    m = D_00484A48;
    if (m == 0) {
        return 0;
    }
    c = m->f70;
    if (c == 0) {
        return 0;
    }
    w = GetFactoryObj_367f30();
    if (w == 0) {
        return 0;
    }
    tbl = (Item *)((u8 *)w + 0xE0);
    cont = 1;
    found = 0;
    for (i = 0; i < 2 && cont; i++) {
        e = &tbl[ids[i]];
        if (e != 0 && e->f30 == 8) {
            cont = 0;
            found = 1;
        }
    }
    memset(b, -1, 0x8);
    memset(b, -1, 0x8);
    q = c->f0C;
    if (found) {
        for (j = 0; j < 2; j++) {
            e = &tbl[ids[j]];
            if (e != 0 && e->f30 != 8) {
                b[0] = e->f04;
            }
        }
        r = &q[2];
        if (r != 0) {
            a[0] = r->f00->f00;
        }
    } else {
        for (k = 0; k < 2; k++) {
            e = &tbl[ids[k]];
            if (e != 0) {
                r = &q[k];
                if (r != 0) {
                    b[k] = e->f04;
                    a[k] = r->f00->f00;
                }
            }
        }
    }
    res = 0;
    if (found) {
        if (a[0] == b[0]) {
            res = 1;
        }
    } else {
        cnt = 0;
        for (x = 0; x < 2; x++) {
            for (y = 0; y < 2; y++) {
                if (a[x] == b[y]) {
                    cnt++;
                }
            }
        }
        if (cnt == 2) {
            res = 1;
        }
    }
    return res;
}
