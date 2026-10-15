#include "types.h"
/* insect 0x004ED180 -- 792 bytes, 200 instructions, 10 calls, 22 conditional
 * branches.  Builds the 5x7 highlight mask at o->f118 for one entity and
 * returns it (0 when there is no entity).
 *
 * The dispatch on `kind` is a `beql` CHAIN, so it is a switch whose compare
 * order is REVERSED: the blocks run 0, 1, 2, 3 forwards (4ED384, 4ED410,
 * 4ED428, 4ED440) while the chain tests 3, 2, 1, 0.
 *
 * `t` (0xB8) is the u8 out-buffer insect_InsectPieceGetMoveKind_5151a0 fills; `u` (0xBC) is a
 * SIGNED copy of it.  `rng = u[1]` is not reloaded -- mwcc forwards the u8
 * value it just stored and sign-extends it with `dsll32/dsra32 ..,24`, which
 * is what proves u is s8[2] and t is u8[2].  u sits ABOVE t, so u is declared
 * FIRST (mwcc gives LATER declarations LOWER addresses).
 *
 * insect_InsectBoardGetPiece_4ee9a0's coordinate parameters are s16 here -- the
 * `dsll32/dsra32 ..,16` pair is the narrowing of the s32 loop counters; the
 * s8 call sites elsewhere need no narrowing and so cannot see it.
 *
 * The 0xA0 `sq`/`lq` pair in case 0 is an mwcc SPILL of the row base
 * `(u8 *)o + ty*5`, not a source local.
 */

typedef struct Ent { u8 pad00[0x71]; s8 f71; } Ent;
typedef struct P2 { s8 a; s8 b; } P2;

typedef struct Obj {
    u8 pad000[0x118];
    u8 f118[35];                    /* +0x118 -- 7 rows of 5 */
} Obj;

extern s32  insect_InsectBoardIsHole_4ee7e0(Obj *o, s32 x, s32 y);
extern Ent *insect_InsectBoardGetPiece_4ee9a0(Obj *o, s16 x, s16 y);
extern s32  insect_InsectBoardInBounds_4efac0(Obj *o, s32 x, s32 y);
extern void insect_InsectBoardMoveRangeDiagonal_4ed4d0(Obj *o, s32 x, s32 y, s32 r);
extern void insect_InsectBoardMoveRangeOrthogonal_4ed6f0(Obj *o, s32 x, s32 y, s32 r);
extern s32  insect_InsectPieceTestStatus_513280(Ent *e, s32 k);
extern s32  insect_InsectPieceIsKing_514b00(Ent *e);
extern void insect_InsectPieceGetMoveKind_5151a0(u8 *t, Ent *e);

u8 *insect_InsectBoardCalcMoveRange_4ed180(Obj *o, Ent *e)
{
    P2   u;
    u8   t[2];
    Ent *p;
    s32  y;
    s32  x;
    s32  bx;
    s32  by;
    s32  tx;
    s32  dx;
    s32  dy;
    s32  ty;
    s32  kind;
    s32  rng;
    s8   t71;
    u8   c;

    bx = 0;
    by = 0;
    for (y = 0; y < 7; y++) {
        for (x = 0; x < 5; x++) {
            o->f118[y * 5 + x] = 0;
        }
    }
    if (e == 0) {
        return 0;
    }
    t71 = e->f71;
    for (y = 0; y < 7; y++) {
        for (x = 0; x < 5; x++) {
            if (insect_InsectBoardIsHole_4ee7e0(o, x, y) != 0) {
                o->f118[y * 5 + x] |= 0xC;
            } else {
                p = insect_InsectBoardGetPiece_4ee9a0(o, (s16)x, (s16)y);
                if (p != 0) {
                    if (p != e) {
                        o->f118[y * 5 + x] |= 4;
                        if (t71 != p->f71) {
                            o->f118[y * 5 + x] |= 8;
                        } else {
                            o->f118[y * 5 + x] |= 0x10;
                        }
                        if (insect_InsectPieceIsKing_514b00(p) != 0) {
                            o->f118[y * 5 + x] |= 0x20;
                        }
                    } else {
                        bx = x;
                        by = y;
                        o->f118[y * 5 + x] |= 1;
                    }
                }
            }
        }
    }
    insect_InsectPieceGetMoveKind_5151a0(t, e);
    u = *(P2 *)t;
    kind = u.a;
    rng = u.b;
    if (insect_InsectPieceTestStatus_513280(e, 6) != 0) {
        rng = 1;
        if (kind == 0 || kind == 3) {
            kind = 1;
        }
    }
    switch (kind) {
    case 0:
        for (dy = -rng; dy <= rng; dy++) {
            for (dx = -rng; dx <= rng; dx++) {
                ty = by + dy;
                tx = bx + dx;
                if (insect_InsectBoardInBounds_4efac0(o, tx, ty) != 0) {
                    c = o->f118[ty * 5 + tx];
                    if ((c & 4) == 0) {
                        o->f118[ty * 5 + tx] = c | 2;
                    }
                }
            }
        }
        break;
    case 1:
        insect_InsectBoardMoveRangeOrthogonal_4ed6f0(o, bx, by, rng);
        break;
    case 2:
        insect_InsectBoardMoveRangeDiagonal_4ed4d0(o, bx, by, rng);
        break;
    case 3:
        insect_InsectBoardMoveRangeOrthogonal_4ed6f0(o, bx, by, rng);
        insect_InsectBoardMoveRangeDiagonal_4ed4d0(o, bx, by, rng);
        break;
    }
    return o->f118;
}
