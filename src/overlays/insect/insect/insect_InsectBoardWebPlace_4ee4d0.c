#include "types.h"
/* insect 0x004EE4D0 -- 208 bytes, 52 instructions, 10 calls, 2 conditional
 * branches, br/ins 0.038.  From x_band.py's branch-light band.
 *
 * A 3x3 neighbourhood sweep.  Both loops run -1..1 and both are ROTATED (the
 * bottom test is a `bnel` with the next iteration's argument in the delay
 * slot), so both are plain `for`s whose first iteration mwcc can prove taken.
 * `y + i` is computed in the OUTER loop and `x + j` in the inner, which is
 * what the two nested `for`s give without any hoisting in the source.
 *
 * Both latches compare into `$at`, so both are spelled `<= 1` and not `< 2`
 * (at-compare-class: a latch that is a bare `<` gives a GPR, anything else
 * gives $at -- the two predicates are identical and the token decides).
 *
 * The grid stride is 5: `sll 2 / addu / addu` is `y * 5`, written out, and the
 * ASSOCIATION is `x + (y * 5 + o)` -- retail adds the base into the scaled
 * index and then adds x, which `o + y * 5 + x` gets backwards in both addus.
 * The base has to be an INTEGER there: `y * 5 + (u8 *)o` is pointer arithmetic
 * and mwcc normalises the pointer to `rs`, giving `addu $3, $18, $3`; casting
 * the base to `s32` keeps the source's own operand order in the outer add.
 * The INNER one needs the product NAMED -- `t = y * 5;` then `t + (s32)o` --
 * because an unnamed product is mwcc's own temporary and it canonicalises the
 * commutative `addu` with the VARIABLE in `rs`.  Same family as
 * normal-named-product-local, on an integer.  Nine spellings measured; five of
 * them are one inert object.
 */

typedef struct Ins {
    u8 pad000[0x13B];
    u8 f13B;                        /* +0x013B */
} Ins;

extern void insect_InsectBoardTimerSet_4ee320(Ins *o, s32 a, s32 x, s32 y, s32 b, s32 c);

void insect_InsectBoardWebPlace_4ee4d0(Ins *o, s32 x, s32 y)
{
    s32  i;
    s32  j;
    s32  t;
    Ins *p;

    for (i = -1; i <= 1; i++) {
        for (j = -1; j <= 1; j++) {
            insect_InsectBoardTimerSet_4ee320(o, 0, x + j, y + i, 6, 1);
        }
    }
    insect_InsectBoardTimerSet_4ee320(o, 1, x, y, 6, 1);
    t = y * 5;
    p = (Ins *)(x + (t + (s32)o));
    p->f13B |= 0x10;
}
