/* rgp:protos */
#define RGP_SELF_factory_FactoryFloorBuild_503910 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* factory.bin overlay, 0x00503910 -- allocate and clear the two blueprint
 * grids for a newly selected recipe, then build its part list.  748 bytes,
 * 188 instructions, 8 conditional branches, 8 calls (br/ins 0.043).
 *
 * ⚠⚠ PARKED, session 8 -- RIGHT LENGTH (187 words), 7 bad, and NOT in
 * config/ocunits/factory.txt.  Everything else is byte-identical; the residue
 * is the CALLER-SAVED scratch register in the third loop's body:
 *     retail  lw $4, 0x234($18)  in the latch's delay slot, index in $3
 *     ours    sll $2, $16, 1     in the slot, o->f234 read later into $2
 * The two bodies compute the same seven values in a different order and the
 * whole rest of the function agrees.
 * Measured and NOT the answer, SIXTEEN spellings over two probe builds: named
 * locals for the header, for the element address, for the halfword argument
 * and for all three; `o->f2AC + i` instead of `&o->f2AC[i]`; `!f(...)` instead
 * of `f(...) == 0`; an explicit `(s16)` on the argument; `while`, `do/while`
 * and a `break`-then-return form; and `o->f238` spelled out at the call.  The
 * two variants that spell `o->f238` at every call are two words SHORT, so the
 * named `heap` local is settled independently.
 * ⇒ [[factory-unused-first-parameter]]'s rule -- a caller-saved residue is
 * about which value keeps a register alive, not about spelling -- holds here
 * as a bounded negative: no source-level ordering reaches mwcc's choice of
 * scratch register for a value that dies inside one basic block.
 *
 * ★ Two structurally identical nested loops -- the recipe grid at f2A0 and the
 * expanded pixel grid at f294 -- over a 6-byte cell, then a third loop over
 * the 12-byte part list at f2AC.  Each loop's counter is its own source
 * variable ([[overlay-normal]]); the `mult` in the inner latch's delay slot is
 * the likely-branch duplication of `row * width`, recomputed per iteration
 * because the index expression is written out in full.
 *
 * ★ `o->f238` is a SUB-OBJECT address with four uses, so mwcc materialises
 * `addiu $17, $18, 0x238` once ([[factory-subobject-use-count]]).
 *
 * ★ D_0045B080 is a MAIN-image float at 0x0045B080, far outside the gp window
 * (_gp 0x00485170 +/- 0x8000), so it is `const` and takes %hi/%lo.
 */

typedef struct Cell {
    s16 f00;
    s16 f02;
    s16 f04;
} Cell;                                         /* 6 */

typedef struct Part {
    u8 pad00[0xC];
} Part;                                         /* 12 */

typedef struct Hdr {
    s16 f00;
    s8  f02;
    s8  f03;
    s16 f04;
    s16 f06;
    u8  pad08[0xC];
    s32 f14;
} Hdr;

typedef struct Obj {
    u8    pad000[0x234];
    Hdr  *f234;
    u8    f238[0x5C];
    Cell *f294;
    s16   f298;
    s16   f29A;
    f32   f29C;
    Cell *f2A0;
    s16   f2A4;
    s16   f2A6;
    f32   f2A8;
    Part *f2AC;
    s16   f2B0;
    u8    pad2B2[0x2];
    s32   f2B4;
    f32   f2B8;
    f32   f2BC;
    f32   f2C0;
    f32   f2C4;
    u8    pad2C8[0x14];
    s32   f2DC;
    s32   f2E0;
} Obj;

extern f32 D_0045B080;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

void factory_FactoryFloorBuild_503910(Obj *o, s32 a)
{
    Cell *q;
    void *heap;
    f32   k;
    f32   lo;
    f32   hi;
    s32   y;
    s32   x;
    s32   i;
    Hdr  *hd;

    factory_FactoryFloorRelease_503c10(o);
    o->f234 = ((Hdr *)factory_FactoryFloorFindById_504120(o, a));
    if (o->f234 == 0) {
        return;
    }
    heap = o->f238;
    o->f2B4 = o->f234->f04;
    k = D_0045B080;
    o->f2A4 = o->f234->f02;
    o->f2A6 = o->f234->f03;
    o->f2A8 = o->f2B4 * k;
    o->f2A0 = (Cell *)MemStackNew_14e1b0(o->f2A4 * o->f2A6 * 6, heap);
    for (y = 0; y < o->f2A6; y++) {
        for (x = 0; x < o->f2A4; x++) {
            q = &o->f2A0[y * o->f2A4] + x;
            q->f00 = -1;
            q->f02 = -1;
            q->f04 = 0;
        }
    }
    o->f298 = o->f2A4 * o->f2B4;
    o->f29A = o->f2A6 * o->f2B4;
    o->f29C = k;
    o->f294 = (Cell *)MemStackNew_14e1b0(o->f298 * o->f29A * 6, heap);
    for (y = 0; y < o->f29A; y++) {
        for (x = 0; x < o->f298; x++) {
            q = &o->f294[y * o->f298] + x;
            q->f00 = -1;
            q->f02 = -1;
            q->f04 = 0;
        }
    }
    o->f2AC = (Part *)MemStackNew_14e1b0(o->f234->f14 * 12, heap);
    if (o->f2AC != 0) {
        o->f2B0 = o->f234->f14;
        for (i = 0; i < o->f2B0; i++) {
            hd = *(Hdr *volatile *)&o->f234;
            if (factory_FactoryBeltAlloc_504d30(&o->f2AC[i], hd->f06, heap) == 0) {
                return;
            }
        }
    }
    lo = -0.5f * D_0045B080;
    o->f2B8 = o->f298 * lo;
    hi = 0.5f * D_0045B080;
    o->f2BC = o->f298 * hi;
    o->f2C0 = o->f29A * lo;
    o->f2C4 = o->f29A * hi;
    o->f2E0 = 0;
    o->f2DC = 0;
    MapBlockIdListAdd_1e3320(GetMapMgr_201a90(), o->f234->f00);
}
