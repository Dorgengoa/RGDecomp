#include "types.h"

/* MAIN VoBufIncCount_1d4a10 -- ring-buffer push.  divbyzerocheck supplies the
   `bnez $2 / div / break 0,7` around `% r->m14`.  r->m0C is RE-READ after
   the store through r->m08 (mwcc cannot prove no alias). */

/* THE LAST WORD WAS opt_propagation.  Retail materialises the stored value 2
   ONCE into $5 at 0x001D4A28 and still has it in $5 for the second argument
   of EnableIntr_1206b0 fourteen instructions later; mwcc re-materialises it with a
   second `addiu $5,$0,2` in front of the jal, so the draft is exactly one
   word LONG.  EIGHT source spellings are ONE object 6bdd62e1 and measured
   nothing -- the literal 2 in both places, declaration order swapped, an
   element pointer local, an s16 second parameter, hoisting `st = 2` above the
   first call, `u32` for the stored member, and giving DisableIntr_120660 an
   argument.  Seven other knobs are inert on the same object.
   `opt_propagation off` stops the re-materialisation and closes it.  */

#pragma divbyzerocheck on
#pragma opt_propagation off

typedef struct El1D4A10 {
    s32 m00;
    u8 pad04[0x44];
} El1D4A10;

typedef struct Ring1D4A10 {
    u8 pad00[0x8];
    El1D4A10 *m08;
    s32 m0C;
    s32 m10;
    s32 m14;
} Ring1D4A10;

extern void DisableIntr_120660(void);
extern void EnableIntr_1206b0(s32, s32);

void VoBufIncCount_1d4a10(Ring1D4A10 *r)
{
    s32 i;
    s32 st;

    DisableIntr_120660();
    i = r->m0C;
    st = 2;
    r->m08[i].m00 = st;
    r->m10 = r->m10 + 1;
    r->m0C = (r->m0C + 1) % r->m14;
    EnableIntr_1206b0(i, st);
}
