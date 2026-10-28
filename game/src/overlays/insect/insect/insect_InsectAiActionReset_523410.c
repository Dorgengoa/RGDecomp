/* rgp:protos */
#define RGP_SELF_insect_InsectAiActionReset_523410 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* insect 0x00523410 -- 72 B / 18 words.  Branch-free zero/-1 init.
 *
 * The `dsll32 $3,$0,16 / dsra32 $3,$3,16` pair is a 16-bit SIGN EXTENSION of a
 * value mwcc will not constant-fold because it never sees it as a constant:
 * it is the RESULT VALUE of the inner assignment in a CHAIN,
 *
 *     o->f1A = o->f18 = 0;
 *
 * whose type is s16 (`sh`), narrowed again by the s8 store at 0x1A.  That is
 * why 0x18 is written TWICE (once plainly, once as the chain's inner store) --
 * mwcc does not dead-store-eliminate a repeated store through a struct pointer.
 *
 * -1 is materialised once in $5 (a byte store of -1 needs a register) and the
 * two shifts are hoisted into the store stream by the list scheduler; the
 * STORES themselves are in source order, which is not ascending offset here
 * (0x11 before 0x10, 0x0C after 0x1C, 0x12/0x13 last). */
typedef struct Rec {
    s32 f00;
    s32 f04;
    s32 f08;
    s32 f0C;
    s8  f10, f11, f12, f13, f14;
    u8  pad15[1];
    s16 f16;
    s16 f18;
    s8  f1A;
    u8  pad1B[1];
    s8  f1C;
} Rec;

void insect_InsectAiActionReset_523410(Rec *o)
{
    o->f00 = 0;
    o->f04 = 0;
    o->f08 = 0;
    o->f11 = -1;
    o->f10 = -1;
    o->f14 = -1;
    o->f18 = 0;
    o->f16 = 0;
    o->f1A = o->f18 = 0;
    o->f1C = 0;
    o->f0C = 0;
    o->f12 = -1;
    o->f13 = -1;
}
