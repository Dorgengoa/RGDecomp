/* ====================================================================
 * SESSION 53 (2026-09-03), tag fg53.  Board 403 -> 404/409.  Arming pair held in EVERY scoring run
 * (005069e0 = MATCH / 1a0e9c68216b, 00500450 = 2 / 409c28db0188); every batch carried the cmp-verified
 * identity (7 / d7c9a6c54435) AND the recorded delivery cells SWAPPED = 10 / 2d995112db96,
 * ii{1}-first = 14 / 161d4fd9dd62.  Full detail: memory levers.d/factory-session53-levers.md;
 * arms build/fg53/arms/s53/, generator build/fg53/s53/mk53_32d0.py, maps build/fg53/s53/immmap32.py,
 * logs build/fg53/logs/s53_32d0_b1.log, s53_32d0_b2.log, s53_tree_identity_32d0.log.
 *
 * === factory_FactoryLayoutSave_5032d0: CLOSED, 7 -> BYTE-IDENTICAL, md5 29791c8bcf44, 182 w.  ONE EDIT, BASE order ===
 *     e4 = *(volatile s16 *)&e->f4;     <- the field read HOISTED ahead of p, volatile-pinned AT THE ACCESS
 *     p  = &c3[o->f6];
 *     w  = (e4 << 2) | (d & 3);
 * MECHANISM (read off the maps): retail's inner-loop colouring is reverse-creation / lowest-free over the
 * BASE statement order -- w's shift/andi/or are created AFTER p's chain, so w takes v1 and p's *3 chain
 * takes a0 once e->f4 dies -- but with e->f4's LOAD created BEFORE o->f6's, so the list scheduler emits
 * E first and o->f6, coloured last, lands in a1.  Ours-base creates O first (emission O,D,E; o->f6 = a2);
 * ours-SWAPPED creates the whole w chain first (emission E,D,O but p = v1, w = a1).  A plain hoisted
 * `e4 = e->f4;` (decl first / last, s16, the shift hoisted) is INERT -- mwcc forward-substitutes the
 * single-use local back to its use (mwcc-volatile-access-site-pin).  The volatile cast keeps the load
 * where it is written: V1 / V3 / V4 (decl last / first / s16) are ONE byte-identical object; the same pin
 * AT THE USE in base order (V2) is the baseline; e4 above the two calls is 183 w.
 * This is the "next lever must come from OUTSIDE the block" the s37 header asked for, and it refutes the
 * s49 reading aid's "no source spelling creates e->f4 before o->f6": the spelling exists, it has to
 * survive propagation.
 * ==================================================================== */
/* ====================================================================
 * SESSION 49 (2026-09-03), tags fg49/fg49b/fg49c/fg49k.  Board unchanged 400/409 = 97.80% / 91.88%.  Baseline RE-DERIVED at start; arming pair held in EVERY scoring run (005069e0 = MATCH / 1a0e9c68216b, 00509f10 = bad 11 / 977182cbe9b7); every batch carried a cmp-verified identity arm AND a recorded-live delivery cell that reproduced its recorded md5.  Full detail: memory levers.d/factory-session49-levers.md; arms build/fg49/arms/s49/, generators build/fg49/s49/, logs build/fg49/logs/s49_*.log.
 *
 * === factory_FactoryLayoutSave_5032d0: STILL 7 / d7c9a6c54435.  One screen, no arms spent ===
 * C++ (whole file extern "C", with (Cell3 *)/(RecA *) casts on the two func_1CACE0 results): BYTE-IDENTICAL d7c9a6c54435.
 * Callee signatures re-checked against the MERGED definitions (merged-callee-signature-oracle): factory_FactoryPartObjGetGridY_4fe0c0
 * and factory_FactoryPartObjGetGridX_4fe120 are one-parameter, func_1CACE0 is one-parameter everywhere in the corpus -- the s43
 * signature lever has no purchase here.  Reading aid: our base-order map (andi v1, e->f4 a0, x3 chain a1, o->f6 a2)
 * is exactly "colour caller-saved temps in REVERSE creation order, lowest free, creation = left-to-right expression
 * order"; retail's map is the same rule with e->f4 created before o->f6, i.e. the SWAPPED statement order that s37
 * measured at 10 because every register then permutes together.
 * ==================================================================== */
/* ====================================================================
 * SESSION 37 (2026-09-02), lane fg37d.  Board 393 -> 396/409 = 96.82% count,
 * 120,424/134,224 = 89.72% bytes.  Arming pair held in EVERY scoring run:
 * factory_FactoryStep_5069e0 = MATCH, factory_FactoryRectFrameCorner_509f10 = bad 11 / md5 977182cbe9b7.
 * "INERT" below means the arm's object md5 EQUALS this unit's baseline md5.
 *
 * === factory_FactoryLayoutSave_5032d0 -- still 7 (44 cells) ===
 * BASE (p first) d7c9a6c54435 7.  SWAPPED (w first = retail's emission order) 2d995112db96 10.
 * INSTRUMENT (1), region alias `ii` for the three `for (i = ...)` loops -- the axis IS LIVE on this unit at BOTH declaration ends and in BOTH statement orders, but it only permutes the CALLEE-SAVED map (i/e trade $18/$19) and never touches the caller-saved residue; every arm regresses:
 *   base order:  ii{1}=ii{1,2}=ii{1,3} first 161d4fd9dd62 14 | ii{1} LAST 48da9cf7900f 18 | ii{2}=ii{2,3} first c31981457669 19 | ii{3} first 3bdf0487957a 17
 *   swapped:     ii{1}=ii{1,2}=ii{1,3} first b2973dca08b5 17 | ii{1} LAST f034e53ad7b6 21 | ii{2}=ii{2,3} first b27aeb90e670 22 | ii{3} first 5055a67f6271 20
 *   (NOTE: the declared-LAST alias is a DISTINCT object here, so s33/s36's "declared last is coalesced" does not generalise.)
 * MEASURED INERT in the SWAPPED order (all 2d995112db96) -- s34 measured these in BASE order only, they are now dead in both:
 *   `kk = o->f6; p = &c3[kk];` decl FIRST and LAST;  `e4 = e->f4;` decl FIRST and LAST;  `d3 = d & 3;` decl FIRST and LAST;
 *   `w = e->f4 << 2; w = w | (d & 3);`;  `p = c3 + o->f6`;  `p = &c3[(u32)o->f6]`;  `p = (Cell3*)((u8*)c3 + o->f6*3)`;
 *   volatile pin `p = &c3[*(volatile s16*)&o->f6]`;  volatile pin `w = ((*(volatile s16*)&e->f4) << 2) | (d & 3)`;
 *   `(s32)e->f4 << 2` and `(u32)d & 3` in the FIRST `|` position.
 * DISTINCT OBJECTS, no gain:
 *   swapped, `|` operands swapped / `e->f4 * 4` in either position / `(u32)d & 3` or `(s32)e->f4 << 2` in the SECOND position -> dc5180043505 10 (allocation identical, only the `or` rs/rt flips);
 *   swapped, `w = d & 3; w |= e->f4 << 2;` and `w = d & 3; w = w | (e->f4 << 2);` -> 8a8d8dc54abf 11 (the compound-assign spelling is the same object as the plain split);
 *   base, `e->f4 * 4` in either position / `(s32)e->f4 << 2` or `(u32)d & 3` in the SECOND position -> 1a4fd93f05c4 7 (baseline except `or v1,v1,a0`);
 *   base, `(u32)d & 3` or `(s32)e->f4 << 2` in the FIRST position -> d7c9a6c54435 (INERT).
 * LENGTH-BREAKING, do not re-sweep: dropping `p` and storing through `c3[o->f6].fN` costs +8 words (190w, len 0x2f8 vs 0x2d8) in BOTH orders (f1fb13d10033 swapped / 1e14617ca3cd base) -- mwcc rebuilds the *3 address at each store; `(d << 30) >> 30` for `d & 3` is +1 word (183w, d3ace31efe3f swapped / fbcd342b0b91 base).
 * s35 NEIGHBOUR-STATEMENT LEVER SCREEN: NEGATIVE, no arms spent -- the inner block has no named-local constant assignment (`d = s->f26`, `y = FE0C0(s)`, `x = FE120(s)` are all non-constant).
 * WHAT IS LEFT: the swapped order is retail's exact emission and needs ONE allocator outcome -- `w` must take the andi's register ($3) and `p` the shift temp's ($4). 22 source spellings collapse to 3 objects there, so the next lever must come from OUTSIDE the block (pressure/liveness), not from respelling it.
 ==================================================================== */

#include "types.h"

/* SESSION 23, lane fz23j -- 7 bad, EXACT LENGTH, restored to the ORIGINAL
 * statement order (`p = &c3[o->f6];` then `w = ...`), still the best arm here.
 * The inner-loop residue is a REGISTER PERMUTATION and the two axes are
 * COUPLED -- every arm wins one and loses the other:
 *   original order (7 bad): correct `or $3,$4,$3`, correct w=$3, e->f4=$4,
 *     p=$4 and all three `sb`s CORRECT; wrong EMISSION ORDER (the o->f6 chain
 *     is interleaved into the w chain and o->f6 lands in $6).
 *   swapped order  (10 bad): retail's EXACT emission order, 1:1 word for word
 *     -- e->f4 chain (lh, sll, or) complete, THEN the o->f6 chain -- but every
 *     register permuted: ours e->f4=$5 w=$5 o->f6=$4 p=$3, retail e->f4=$4
 *     w=$3 o->f6=$5 p=$4.  The `or` flips to rd=rs there.
 * MEASURED INERT / WORSE this lane, on top of the swapped order:
 *  - splitting w so it is born from the andi: `w = d & 3; w = (e->f4 << 2) | w;`
 *    -> 11 bad.  It moves the andi's DESTINATION to $5 instead of pulling w
 *    into $3: the `or` still coalesces rd with rs and now `d & 3` is wrong too.
 *  - moving `s32 w;` to the FIRST declaration -> 10 bad, byte-identical to the
 *    plain swapped-order object.  Declaration order is a MEASURED NULL for the
 *    $3/$4/$5 temps on this unit.
 * Still needed: retail's emission order WITH rd coalescing to rt and the
 * first-loaded chain taking $4 (ours always gives the first-loaded $5).
 */

typedef struct Slot {
    u8 pad00[0x26];
    s8 f26;
    u8 pad27[0x19];
} Slot;

typedef struct Ent {
    u8    pad00[0x4];
    s16   f4;
    u8    pad06[0x6];
    s16   f0C;
    u8    pad0E[0x2];
    Slot *f10;
    u8    pad14[0x54];
} Ent;

typedef struct Pt {
    s16 x;
    s16 y;
    s16 d;
} Pt;

typedef struct Trace {
    Pt *f0;
    u8  pad04[0x2];
    s16 f6;
    u8  pad08[0x4];
} Trace;

typedef struct Zone {
    u8  pad00[0x4];
    s16 f4;
    s16 f6;
    u8  pad08[0x2];
    s16 fA;
    s16 fC;
    u8  pad0E[0x32];
} Zone;

typedef struct Map {
    u8     pad000[0x14];
    s16   *f14;
    u8     pad018[0xBC];
    Ent   *fD4;
    s32    fD8;
    u8     padDC[0x4];
    Zone   fE0[4];
    u8     pad1E0[0x54];
    s16   *f234;
    u8     pad238[0x74];
    Trace *f2AC;
    s16    f2B0;
} Map;

typedef struct Out {
    s16 f0;
    s16 f2;
    s16 f4;
    s16 f6;
    s16 f8;
    s16 fA;
    s16 fC;
    s16 fE;
    u8  f10;
} Out;

typedef struct Cell3 {
    u8 f0;
    u8 f1;
    u8 f2;
} Cell3;

typedef struct RecA {
    s16 f0;
    s16 f2;
    u8  pts[1][2];
} RecA;

typedef struct RecB {
    s16 f0;
    s16 f2;
    u8  f4;
    u8  f5;
} RecB;

extern void *func_1CACE0(void *p);
extern s32   factory_FactoryPartObjGetGridY_4fe0c0(Slot *s);
extern s32   factory_FactoryPartObjGetGridX_4fe120(Slot *s);

s32 factory_FactoryLayoutSave_5032d0(Map *m, Out *o, s32 n)
{
    Cell3 *c3;
    Cell3 *p;
    RecA  *ra;
    RecB  *rb;
    Ent   *e;
    Trace *t;
    Zone  *z;
    s32    i;
    Slot  *s;
    s32    j;
    s32    k;
    s32    d;
    s32    x;
    s32    y;
    s32    v;
    s32    w;
    s32    e4;

    if (o == 0 || n <= 0) {
        return 0;
    }
    o->f0 = 0x64;
    if (m->f234 != 0) {
        v = m->f234[0];
    } else {
        v = -1;
    }
    o->f2 = v;
    o->f4 = 0;
    o->f6 = 0;
    o->f8 = 0;
    o->fC = -1;
    o->fE = -1;
    o->fA = -1;
    if (m->f14 != 0) {
        o->fA = m->f14[0];
    }
    c3 = func_1CACE0(&o->f10);
    e = m->fD4;
    for (i = 0; i < m->fD8; i++, e++) {
        s = e->f10;
        for (j = 0; j < e->f0C; j++, s++) {
            d = s->f26;
            y = factory_FactoryPartObjGetGridY_4fe0c0(s);
            x = factory_FactoryPartObjGetGridX_4fe120(s);
            e4 = *(volatile s16 *)&e->f4;
            p = &c3[o->f6];
            w = (e4 << 2) | (d & 3);
            p->f0 = x;
            p->f1 = y;
            p->f2 = w;
            o->f6 = o->f6 + 1;
        }
    }
    ra = func_1CACE0(&c3[o->f6]);
    o->f4 = 0;
    t = m->f2AC;
    for (i = 0; i < m->f2B0; i++, t++) {
        if (t->f6 <= 1) {
            continue;
        }
        {
            ra->f0 = i;
            ra->f2 = t->f6;
            for (k = 0; k < t->f6; k++) {
                ra->pts[k][0] = t->f0[k].x;
                ra->pts[k][1] = t->f0[k].y;
            }
            ra = func_1CACE0(&ra->pts[ra->f2][0]);
            o->f4 = o->f4 + 1;
        }
    }
    rb = (RecB *)ra;
    o->f8 = 0;
    z = m->fE0;
    for (i = 0; i < 4; i++, z++) {
        if (z->f4 >= 0) {
            rb[o->f8].f0 = z->f4;
            rb[o->f8].f2 = z->f6;
            rb[o->f8].f4 = z->fA;
            rb[o->f8].f5 = z->fC;
            o->f8 = o->f8 + 1;
        }
    }
    func_1CACE0(&rb[o->f8]);
    return 1;
}
