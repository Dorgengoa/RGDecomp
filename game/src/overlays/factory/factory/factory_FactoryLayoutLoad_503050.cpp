/* rgp:protos */
#line 1
/* ====================================================================
 * SESSION 58 (2026-09-03), tag fg58 / bulk tags ba58 ba58A ba58B.
 * *** CLOSED: MATCH, md5 0d8647b066ae, 157 w, census exact. ***
 * Arming reproduced before any arm was scored: factory_FactoryStep_5069e0 = MATCH /
 * 1a0e9c68216b, factory_FactoryLayoutSave_5032d0 = MATCH / 29791c8bcf44, and the s57
 * delivery cell factory_FactoryLayoutLoad_503050 = 17 / ee255854c3fa.  573 arms in two
 * batches; every batch carried the identity arm and a wrong-LENGTH negative
 * (`#pragma optimization_level 0`, 280 / 283 w).
 *
 * === THE PREMISE THAT WAS WRONG, AND THE INSTRUMENT THAT KILLED IT ===
 * s37..s57 all read the residue as "rc coalesces into $16 where i1 dies" and
 * hunted for the source spelling that reorders the colouring; s58 was briefed
 * to attack it as a LIVENESS / EXTENT defect instead ("make rc's range overlap
 * i1's").  Both readings are refuted by measurement.  build/fg58/s58/ifg58.py
 * builds the real per-program-point interference graph -- reaching-definition
 * webs, a MIPS delay-slot CFG (branch-LIKELY: the slot is on the taken edge
 * only), backward liveness -- and run on OUR object and on RETAIL's it returns
 * the SAME 16 webs at the SAME def indices with the SAME 65 edges, zero
 * difference.  Of course it does: the two objects are the same instruction
 * sequence, so nothing machine-visible can differ.  lfcheck.py then shows BOTH
 * maps are lowest-free-consistent colourings of that one graph.  So the residue
 * was never extent and never coalescing: it was purely the ORDER in which the
 * webs are coloured, which is front-end information -- declaration order.
 * ⚠ ifg58.py also found a real off-by-one in build/fg55/s55/webs.py: dis()
 * prints `simm*4+4`, the displacement from the BRANCH word, so a target index
 * is i + off//4, NOT i + off//4 + 1.  webs.py's loop-region detector (and hence
 * every `depth`/`wuses` feature s55/s56 fitted over the corpus) is off by one.
 * rcscreen.py (s54) has it right.
 *
 * === THE CLOSE: THREE LEVERS, NONE OF WHICH PAYS ALONE ===
 *   (1) a SEPARATE loop-1 counter `i1` (the source had one `i` doing loop 1 and
 *       the loop-3 clamp; mwcc splits it into two webs but colours them as one
 *       name), PLUS
 *   (2) `rc` declared LAST -- the s48 R9 plateau, which alone is 47 bad, and
 *   (3) the k-loop group declared in DESCENDING colour order: `k` first, `e`
 *       middle, `i2` last, with the `e = (Ent *)(s32)e;` round trip DELETED.
 * (1)+(2) = 10 bad (4994aca9379b); alone they are 52 and 47.  Adding (3) closes
 * it.  The last two steps were PREDICTED, not swept: s48 fact #3 recorded that
 * {k,i2} colour in DESCENDING declaration order and that `e` WITH the round
 * trip colours FIRST in its group regardless of slot.  Once (1)+(2) had put rc
 * on $21 and the params back where retail has them, the residue was a 3-cycle
 * over {e,k,i2}; retail's colour order is i2,e,k, so descending declaration is
 * k,e,i2 and the round trip has to go.  P_kei2_N is that arm and it MATCHES.
 * Route, all 157 w and census exact:  17 -> 10 -> 6 -> 0.
 *
 * === WHY EVERY EARLIER SWEEP MISSED IT ===
 * s55's 578-arm sweep moved ONE local through every position; s54/s57 swept
 * creation order.  The close needs THREE simultaneous changes, one of which
 * (splitting `i`) is not a declaration move at all -- s23 and s37 had both
 * tried splitting the counter ALONE (49 and 47 bad) and recorded it as a "large
 * regression, retail really does reuse ONE register for all three loop
 * counters".  That verdict was wrong: retail reuses one REGISTER for three
 * separate NAMES.  Do not trust a lever screened only at the wrong baseline.
 *
 * === MEASURED NULLS THIS SESSION (armed, do not re-run) ===
 *  - DECLARATION COUNT, 190 arms: one unused dummy local (`s32` and `Rec *`) at
 *    each of 19 slots x 5 rc slots.  The hypothesis was s48 fact #4, that the
 *    params sit at an INDEX in the local list and an extra local would shift
 *    them back.  Every arm is byte-identical to its rc-slot's own baseline
 *    (117 at ee255854c3fa, 79 at cf7b019bc1c2 / 47).  An unused local does not
 *    exist for the allocator; declaration COUNT is not an axis.
 *  - the EXTENT arms the brief asked for: `&pl[i]` to stretch i1 to rc's
 *    definition 21; + rc last 50; `rc = (Rec *)pl;` before loop 1 then
 *    `&((Plc *)rc)[b->f06]` BYTE-IDENTICAL (mwcc propagates the copy, as s37
 *    recorded for the dead initialiser); the same with a volatile pin at the
 *    use 161 w; `func_1CACE0(p)` off the loop-1 cursor 154 w.  Extent is dead
 *    here, exactly as the identical-graph result predicts.
 *  - merging i2 into `i` at the rc-last slot (s54's untried half) 44.
 * Generators build/fg58/s58/mk58_{a,b}.py, logs build/fg58/logs/s58_g{A,B}.txt,
 * instruments ifg58.py + lfcheck.py.  Detail: memory
 * levers.d/factory-session58-levers.md.
 ==================================================================== */

#include "types.h"

#pragma optimization_level 3

/* factory.bin overlay, 0x00503050 -- 628 B.  Replay a saved factory layout
 * blob: validate its header, walk the 3-byte placement records, then the
 * variable-length link records, then the 6-byte spawn records -- each section
 * separated by a func_1CACE0 alignment step on the cursor.
 *
 * .cpp is REQUIRED for the ONE `jalr $25` at 0x00503220 (target in $t9 = a real
 * `virtual`): the h->f08->f40->f08 chain with the vptr at the object's own
 * offset 0 and slot 0x70 = index (0x70-8)/4 = 26 -- the same object
 * factory_FactoryMarkerAddSlot_4f6fe0.cpp already records.  There is no `jr $25` tail call, so
 * a .c conversion is not available and must not be re-tried.
 *
 * `dsll32/dsra32 ..,16` off a plain `lh` = an s32 local plus an explicit
 * `(s16)` cast at the second use ([[normal-s16-cast-sign-extension]]).
 * `slt $1` on the clamp is the `$at` compare class -- the member goes on the
 * LEFT, so the spelling is `m > n`.
 * The compare at 0x005030C0 needs the s57 typed pin: `h0` is a REAL s16 local
 * holding the `lh`, so the load is created where it is written and `b->f02`
 * lands on the left of the `beql` ([[mwcc-volatile-access-site-pin]]).
 *
 * DECLARATION ORDER IS LOad-BEARING -- see the session-58 header.  `k` before
 * `e` before `i2`, `i1` split out of `i`, `rc` last.  Any single-name move off
 * this order costs 6-18 bad words.
 */

struct ResV {
    u8  pad00[0x2C];
    s16 f2C;
};

struct ObjV {
    VC_VPTR_MEMBER;    
        
        
        
        
      void s16() { VCM0(void, 0x48); }  
        
        
      
    ResV * f70(s32 k) { return VCM(ResV *, (void *, s32), 0x70, k); }
};

struct H2 { u8 pad00[0x8]; ObjV *f08; };
struct H1 { u8 pad00[0x40]; H2 *f40; };
struct H0 { u8 pad00[0x8]; H1 *f08; u8 pad0C[0x18 - 0xC]; void *f18; };

struct Ent { u8 pad00[0x6]; s16 f06; s32 f08; };     /* 0xC */

struct A {
    u8   pad000[0x234];
    s16 *f234;
    u8   pad238[0x2AC - 0x238];
    Ent *f2AC;
};

struct Hdr {
    s16 f00;
    s16 f02;
    s16 f04;
    s16 f06;
    s16 f08;
    s16 f0A;
    u8  pad0C[0x10 - 0xC];
    u8  data[4];
};

struct Plc { s8 f00; s8 f01; u8 f02; };              /* 3 */

struct Pair { s8 a; s8 b; };
struct Rec  { s16 f00; s16 f02; Pair e[1]; };        /* 6 */

extern "C" void  factory_FactoryBlueprintSelectById_4e9f90(s32 k);
extern "C" void  factory_FactoryMaterialSlotsValidate_4ea020(void);
extern "C" void *AlignUp4_1cace0(void *p);
extern "C" H0   *GetGameData_1fede0(void);
extern "C" s32   InvCountById_3c78d0(void *h, s32 id, s32 a, s32 b);
extern "C" void  factory_FactoryPartPlaceAtCell_501950(A *a, s32 p, s32 x, s32 y, s32 q);
extern "C" void  factory_FactoryBeltAppendPoint_504b20(Ent *e, s32 x, s32 y);
extern "C" void  factory_FactoryBeltRebuildTiles_500b00(A *a);
extern "C" void  factory_FactorySlotFill_500160(A *a, ResV *r, s32 n, s32 x, s32 y);

extern "C" s32 factory_FactoryLayoutLoad_503050(A *a, Hdr *b, s32 c);

s32 factory_FactoryLayoutLoad_503050(A *a, Hdr *b, s32 c)
{
    s32   k;
    s16  *hd;
    Plc  *pl;
    Plc  *p;
    Ent  *e;
    H0   *h;
    ObjV *ob;
    ResV *res;
    s32   j;
    s32   i1;
    s32   i;
    s32   i2;
    s32   id;
    s32   n;
    s32   x;
    s32   y;
    s32   v;
    s16   h0;
    Rec  *rc;

    if (b == NULL || c <= 0) {
        return 0;
    }
    hd = a->f234;
    if (hd == NULL) {
        return 0;
    }
    if (b->f00 != 0x64) {
        return 0;
    }
    h0 = *(volatile s16 *)&hd[0];
    if (b->f02 != h0) {
        return 0;
    }

    factory_FactoryBlueprintSelectById_4e9f90(b->f0A);
    pl = (Plc *)AlignUp4_1cace0(b->data);

    p = pl;
    for (i1 = 0; i1 < b->f06; i1++, p++) {
        v = p->f02;
        factory_FactoryPartPlaceAtCell_501950(a, v >> 2, p->f00, p->f01, v & 3);
    }
    rc = (Rec *)AlignUp4_1cace0(&pl[b->f06]);

    if (b->f04 > 0) {
        for (k = 0; k < b->f04; k++) {
            i2 = 1;
            e = &a->f2AC[rc->f00];
            e->f06 = 1;
            for (; i2 < rc->f02; i2++) {
                factory_FactoryBeltAppendPoint_504b20(e, rc->e[i2].a, rc->e[i2].b);
            }
            rc = (Rec *)AlignUp4_1cace0(&rc->e[rc->f02]);
        }
        factory_FactoryBeltRebuildTiles_500b00(a);
    }

    h = GetGameData_1fede0();
    for (j = 0; j < b->f08; j++) {
        id = rc[j].f00;
        i = rc[j].f02;
        x = rc[j].e[0].a;
        y = rc[j].e[0].b;
        n = InvCountById_3c78d0(h->f18, id, 0, 0);
        ob = h->f08->f40->f08;
        res = ob->f70((s16)id);
        if (n > 0 && res != NULL) {
            if (i > n) {
                i = n;
            }
            factory_FactorySlotFill_500160(a, res, i, x, y);
        }
    }
    AlignUp4_1cace0(&rc[b->f08]);
    factory_FactoryMaterialSlotsValidate_4ea020();
    return 1;
}
