#include "types.h"
/* insect 0x005151A0 -- 26 instructions.  The 0x3C stack slot is written with a
 * single `sh` and read back with two `lbu`s, so it is a two-byte union and not
 * two independent locals.  D_00481028 is `-0x4148($28)`, i.e. _gp 0x00485170
 * relative, so it must stay a plain (non-const) extern to keep %gp_rel.
 *
 * The `else` arm is a TWO-BYTE STRUCT COPY THROUGH A CAST, not two scalar
 * assignments.  Written as two named locals mwcc emits the two `lbu`s in the
 * REVERSE of the two `sb`s' source order (28 arms in
 * build/ix17/parked/insect_InsectPieceGetMoveKind_5151a0.md prove it in both directions);
 * `*(P2 *)t = *(P2 *)&s->m6E;` gives retail's ascending 0x6E/0x6F loads AND
 * ascending t[0]/t[1] stores.  A P2 LOCAL copied member-wise is 4 words LONG,
 * a Pair (union) local 2 words long, and the whole 166-cell knob sweep is
 * INERT. */

typedef struct Obj {
    u8 pad000[0x6E];
    u8 m6E;                         /* +0x6E */
    u8 m6F;                         /* +0x6F */
} Obj;

typedef union Pair {
    s16 h;
    u8  b[2];
} Pair;

typedef struct P2 {
    u8 a;
    u8 b;
} P2;

extern s16 D_00481028;

extern s32 insect_InsectPieceTestStatus_513280(Obj *p, s32 k);

void insect_InsectPieceGetMoveKind_5151a0(u8 *t, Obj *s)
{
    Pair w;
    u8   c0;
    u8   c1;

    if (insect_InsectPieceTestStatus_513280(s, 0x1A) != 0) {
        w.h = D_00481028;
        t[0] = w.b[0];
        t[1] = w.b[1];
    } else {
        *(P2 *)t = *(P2 *)&s->m6E;
    }
}
