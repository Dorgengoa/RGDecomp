/* rgp:protos */
#define RGP_SELF_factory_FactoryPartPlace_5013f0 1
#include "port/game_protos.h"
#line 1
/* ====================================================================
 * SESSION 63 (2026-09-04), tag fg63 / bulk tag ba63b.  *** CLOSED: 15 -> MATCH,
 * 342 words, byte-identical (bulkarm MATCH + rd63.py "bad 0"). ***
 *
 * THE SIX CLEAR LOOPS ARE NOT LOOPS IN THE SOURCE.  THEY ARE ARRAY
 * INITIALISERS.  `f32 vN[4] = {0};` declared in its own BLOCK, at the point
 * the clear happens, expands to exactly the object's
 *      addiu q,sp,K / addiu m,zero,16 / beq q,zero,+36 / sb zero,0(q)
 *      / addiu m,m,-1 / addiu q,q,1 / bne m,zero,-20
 * -- the pointer guard included (that guard is the tell: no hand-written C
 * null-checks the address of its own local array).
 *
 * WHY IT MOVES THE RESIDUE, and why eight sessions of loop spellings could not.
 * The 15 bad words were one fact: retail puts the short-lived constant
 * (`lui a1,0x3F00` at w173, `addiu a0,zero,-1` at w259) ABOVE the clear
 * cursors, ours below.  mwcc numbers vregs in creation order and colours them
 * in REVERSE creation, lowest free ([[mwcc-allocator-decompiled]]), and it
 * creates every DECLARED LOCAL before any expression temp.  So while `q`/`m`
 * were declared locals they were created before the constant, no matter where
 * their statements sat -- that is why declaration order, assignment order,
 * loop form, guard site, block scope, `register`, the inline-helper family,
 * named constants, 6,592 pragma cells and 65 command-line flag sets were all
 * null.  An initialiser's cursor and counter are COMPILER TEMPS created at the
 * initialiser, i.e. AFTER the constant temp, so the constant is coloured last
 * and takes the higher register.  Confirmed in a 42-word synthetic model
 * before the transplant: hand loop -> (const=v0 q=v1 m=a1) = OURS,
 * `f32 v[4] = {0};` -> (const=a1 q=v1 m=v0) = RETAIL.
 *
 * DELIVERY CELL: all six sites converted, `nd = X->f20;` left OUTSIDE the
 * block (inside it costs 89 bad).  Partial conversions are all WORSE than the
 * hand-loop baseline (loops 1+4 only = 36, loop 1 only = 45, loop 4 only = 20)
 * -- the six sites are one allocation problem and must move together.
 * `{0}` and `{0.0f, 0.0f, 0.0f, 0.0f}` are the same object.
 * Arming: identity 15 / 29fb5f791a84, negative `#pragma optimization_level 0`
 * 519 w, recorded delivery cell q-before-m 19 / bc91f321e864, all reproduced.
 * Detail: memory levers.d/mwcc-array-initialiser-clear-loop.md,
 * levers.d/factory-session63-levers.md.
 ==================================================================== */

#include "types.h"

/* factory.bin overlay, 0x005013F0 -- stamp a rectangle of grid cells for a new
 * placement, then build the two attached nodes (the object itself and its
 * shadow/marker) with position, rotation and unit scale.  1368 bytes.
 */

/* ** SESSION 23 (lane fz23i): 24 -> 19 bad, 342 words.  ONE TOKEN:
 *     extern f32 D_0045B080[];  ->  extern const f32 D_0045B080[];
 * MECHANISM: in loop 4 the `hz = 30.0f * D_0045B080[0];` load sat 5 slots LATE
 * (`lwc1 $f0,-0x4F80($2)` at 0x0050182C where retail has it at 0x00501818),
 * because mwcc would not move a GLOBAL LOAD above the `g->f24/f25/f26/f27/f28`
 * stores it might alias.  `const` removes the alias hazard, the lwc1 rises into
 * the store block exactly as retail schedules it, $2 dies early and the clear
 * loop's counter `m` recovers retail's $2.  Loop 4: 15 -> 10 bad.
 * ⇒ THIS IS A SEPARATE CELL FROM THE RECORDED `extern f32 D_x;` SCALAR ARM.
 * Keep the INCOMPLETE ARRAY (scalar still costs a word) and ADD `const` --
 * [[factory-gp-load-placement]] priced `const` for SINKING past a call; this
 * prices it for RISING past a store, which is the commoner shape.
 *
 * ! RESIDUE, 19 words, and BOTH halves are now the SAME single defect:
 *   loop 1 (0x005016A4-D4, 9 words): retail (m,q,const)=($2,$3,$5), ours
 *          (const,m,q)=($2,$3,$5).
 *   loop 4 (0x005017FC-868, 10 words): retail (m,q,const)=($2,$3,$4), ours
 *          (m,const,q)=($2,$3,$5).
 * In BOTH the INSTRUCTION SEQUENCE is byte-for-byte retail's; only the register
 * numbers move, and the mover is always the SHORT-LIVED CONSTANT -- retail ranks
 * it LAST among the live temps (so it lands in an argument register $4/$5 that
 * is about to be reloaded anyway) and ours ranks it EARLIER, stealing $2 or $3
 * from the loop cursor.  The same class is open on factory_FactoryRemoveStateTick_4ef5e0 group 2.
 * MEASURED INERT / REGRESSIVE, do not re-sweep: swapping q/m in all six loops
 * (24 -> 48); swapping in loop 1 only (identical damage, the pair is GLOBAL);
 * hoisting `hz` to the top of the `if (g != NULL)` block (loop 4 15 -> 22);
 * `extern f32 D_0045B080;` as a scalar (costs a word).
 *
 */
/* ** SESSION 23 (lane fz23l): 19 -> 15 bad, 342 words.  ONE TOKEN AGAIN --
 * DECLARATION ORDER of the clear-loop pair:
 *     s8 *q;  u32 m;      ->      u32 m;  s8 *q;
 * `m` FIRST.  Loop 1 goes 9 -> 5 bad: `q` recovers retail's $3 at all four of
 * its sites (0x005016AC/B8/C0/C8).  So the recorded "the q/m pair is ONE GLOBAL
 * allocation" is REFINED -- the pair's RANK is set by SOURCE DECLARATION ORDER,
 * and it is the ASSIGNMENT order that must NOT be touched (that arm is the
 * recorded 24 -> 48 regression).  Two distinct axes on the same two names.
 *
 * ! RESIDUE, 15 words:
 *   loop 1 (0x005016A4/B0/B4/C4/D4, 5 words): now a PURE TWO-REGISTER SWAP.
 *          retail m=$2, const(0.5f)=$5; ours m=$5, const=$2.  q=$3 in both.
 *   loop 4 (0x005017FC-0x0050185C, 10 words): retail const(-1)=$4, q=$3, m=$2;
 *          ours const=$3, q=$5, m=$2.  Declaration order did NOT reach this one.
 * The class is unchanged: RETAIL RANKS THE SHORT-LIVED CONSTANT LAST among the
 * live temps, ours ranks it above the loop cursor.  Loops 2/3/5/6 have no
 * competing constant and are byte-identical in both.
 * MEASURED INERT THIS SESSION, do not re-sweep: giving each of the six
 * expansions its OWN BLOCK SCOPE with block-local `q`/`m` (byte-identical --
 * mwcc's allocation is not keyed on the name or the scope, which is also why
 * the earlier "the pair is global" reading survives); a SECOND SPELLING of the
 * clear target, `q = (s8 *)((s32)v1);` and `(s8 *)((s32)v4);`, against the call
 * argument's plain `v1`/`v4` (byte-identical -- the integer-add cast does NOT
 * split this object the way it splits an address in the recorded lever).
 * Still recorded INERT/REGRESSIVE from earlier lanes: swapping the q/m
 * ASSIGNMENT order in all six loops (24 -> 48) or in loop 1 only; hoisting `hz`
 * to the top of the `if (g != NULL)` block (loop 4 15 -> 22); the scalar
 * `extern f32 D_0045B080;`.
 */
typedef struct Cell {
    s16 f00;
    s16 f02;
    u16 f04;
} Cell;

typedef struct Node {
    u8  pad00[0x32];
    s16 f32;
} Node;

typedef struct Slot {
    u8    pad00[0x20];
    Node *f20;
    s8    f24;
    s8    f25;
    s8    f26;
    s8    f27;
    s16   f28;
    s16   f2A;
    u8    pad2C[0x4];
    s16   f30;
    s16   f32;
    s16   f34;
    s16   f36;
    s32   f38;
    s32   f3C;
} Slot;

typedef struct List {
    u8  pad00[0xA];
    s16 f0A;
    s16 f0C;
} List;

typedef struct Ctx {
    u8    pad000[0x294];
    Cell *f294;
    s16   f298;
    u8    pad29A[0x6];
    Cell *f2A0;
    s16   f2A4;
    u8    pad2A6[0xE];
    s32   f2B4;
} Ctx;

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
extern f32 D_0045B080[];

/* ** SESSION 35 (2026-09-02): STILL 15, EXACT LENGTH.  9 new cells.
 * THE "SHORT-LIVED CONSTANT RANKS LAST" CLASS WAS SOLVED ELSEWHERE TODAY AND
 * DOES **NOT** TRANSFER HERE.  factory_FactoryRemoveStateTick_4ef5e0 closed (4 -> 0) on exactly
 * this class, and the lever there is that you do not touch the constant at all
 * -- you move the THIRD statement standing next to it, and which assignment
 * OPENS the block decides which web takes $2.  Applied here it is INERT:
 *   `sum = A + B;` split out and `cy = 0.5f * sum;` SUNK below the
 *   `nd/q/m` setup  -- BYTE-IDENTICAL to the baseline (md5 29fb5f791a84)
 *   the same split with cy left in place       -- byte-identical
 *   `nd = h->f20;` moved to last / to the middle of the setup -- byte-identical
 *   `nd = g->f20;` moved to last in the loop-4 setup          -- byte-identical
 * mwcc re-hoists the `lui 0x3F00` regardless of where the multiply is written,
 * because it is an IMMEDIATE materialisation and not an assignment to a local.
 * ⇒ THE BOUNDARY OF THE 004EF5E0 LEVER: it moves a constant that is BORN BY AN
 * ASSIGNMENT TO A NAMED LOCAL (`ok = 1;`).  A constant born inside an
 * EXPRESSION is scheduled freely and statement position cannot reach it.
 * WORSE, not to be re-run: `cy = 0.5f * sum;` deferred all the way to the
 * `v1[0] = cx;` store is 25; `hz = 30.0f * D_0045B080[0];` sunk below the
 * loop-4 setup is 20, moved after it 38, hoisted to the first `g->` store 25.
 */

s32 factory_FactoryPartPlace_5013f0(Ctx *c, s16 tag, s32 kind, f32 px, f32 py)
{
    s16   a[4];
    s16   b[4];
    s16   e[4];
    s16   d[4];
    List *l;
    Slot *h;
    Slot *g;
    Node *nd;
    Cell *p;
    f32   cx;
    f32   cy;
    f32   rot;
    f32   hz;
    f32   sum;
    s32   i;
    s32   row;
    s32   col;
    s16   n;
    s16   k;

    l = ((List *)factory_FactoryPartGroupFindById_504080((void *)c, (int)tag));
    if (l == NULL) {
        return 0;
    }
    n = l->f0C;
    if (l->f0A <= n) {
        return 0;
    }
    h = ((Slot *)factory_FactoryPartGroupGetObj_4fea80(l, n));
    if (h == NULL) {
        return 0;
    }
    if (factory_FactoryPartCanPlace_502ba0(c, l, kind, px, py) == 0) {
        return 0;
    }
    if (factory_FactoryPartFootprintRect_502760(c, a, l, kind, px, py) == 0) {
        return 0;
    }
    i = 0;
    while (factory_FactoryPartDefGetGridRect_4fe480(l, b, a, kind, i) != 0) {
        i++;
        for (row = b[1]; row <= b[3]; row++) {
            for (col = b[0]; col <= b[2]; col++) {
                p = c->f2A0 + row * c->f2A4 + col;
                if (p == NULL) {
                    return 0;
                }
                p->f00 = tag;
                p->f02 = l->f0C;
                p->f04 = (((p->f04 & ~3) | kind) & 3);
            }
        }
    }
    i = 0;
    e[0] = a[0] * c->f2B4;
    e[1] = a[1] * c->f2B4;
    e[2] = ((a[2] + 1) * c->f2B4) - 1;
    e[3] = ((a[3] + 1) * c->f2B4) - 1;
    while (factory_FactoryPartDefGetFineGridRect_4fe4a0(l, d, e, kind, i) != 0) {
        i++;
        for (row = d[1]; row <= d[3]; row++) {
            for (col = d[0]; col <= d[2]; col++) {
                p = c->f294 + row * c->f298 + col;
                if (p == NULL) {
                    return 0;
                }
                p->f00 = tag;
                p->f02 = l->f0C;
            }
        }
    }
    cx = 0.5f * (factory_FactoryGridCellCenterX_503760(c, a[0]) + factory_FactoryGridCellCenterX_503760(c, a[2]));
    cy = 0.5f * (factory_FactoryGridCellCenterZ_503730(c, a[1]) + factory_FactoryGridCellCenterZ_503730(c, a[3]));

    nd = h->f20;
    {
        f32 v1[4] __attribute__((aligned(16))) = {0};
        v1[0] = cx;
        v1[1] = 0.0f;
        v1[2] = cy;
        NodeSetTranslation_1866b0(nd, v1);
    }

    rot = factory_FactoryGridDirToAngle_4ff990(kind);
    nd = h->f20;
    {
        f32 v2[4] __attribute__((aligned(16))) = {0};
        v2[0] = 0.0f;
        v2[1] = rot;
        v2[2] = 0.0f;
        NodeSetRotation_186620(nd, v2);
    }

    nd = h->f20;
    {
        f32 v3[4] __attribute__((aligned(16))) = {0};
        v3[0] = 1.0f;
        v3[1] = 1.0f;
        v3[2] = 1.0f;
        NodeSetScale_1865b0(nd, v3);
    }

    h->f20->f32 = 1;
    h->f24 = 0;
    h->f25 = 2;
    h->f26 = (s8)((h->f26 & ~3) | (kind & 3));
    h->f27 = 0;
    h->f28 = 0;
    h->f30 = a[0];
    h->f32 = a[1];
    h->f34 = a[2];
    h->f36 = a[3];
    k = l->f0C + 1;
    l->f0C = k;
    g = ((Slot *)factory_FactoryPartGroupGetObj_4fea80(l, k));
    if (g != NULL) {
        g->f24 = -1;
        g->f25 = 0;
        g->f26 = 0;
        g->f27 = 0;
        g->f28 = 0;
        g->f2A = 0;
        hz = 30.0f * D_0045B080[0];
        g->f30 = -1;
        g->f32 = -1;
        g->f34 = -1;
        g->f36 = -1;
        g->f38 = 0;
        g->f3C = 0;
        nd = g->f20;
        {
            f32 v4[4] __attribute__((aligned(16))) = {0};
            v4[0] = cx;
            v4[1] = hz;
            v4[2] = cy;
            NodeSetTranslation_1866b0(nd, v4);
        }

        rot = factory_FactoryGridDirToAngle_4ff990(kind);
        nd = g->f20;
        {
            f32 v5[4] __attribute__((aligned(16))) = {0};
            v5[0] = 0.0f;
            v5[1] = rot;
            v5[2] = 0.0f;
            NodeSetRotation_186620(nd, v5);
        }

        nd = g->f20;
        {
            f32 v6[4] __attribute__((aligned(16))) = {0};
            v6[0] = 1.0f;
            v6[1] = 1.0f;
            v6[2] = 1.0f;
            NodeSetScale_1865b0(nd, v6);
        }
        g->f25 = 1;
    }
    return 1;
}
