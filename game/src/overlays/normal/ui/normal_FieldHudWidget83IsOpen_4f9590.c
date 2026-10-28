/* rgp:protos */
#define RGP_SELF_normal_FieldHudWidget83IsOpen_4f9590 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* normal 0x004F9590 -- `lh $3,0x49E($4) / beqz $3,L / daddu $2,$0,$0 /
 * daddiu $2,$0,0x1 / L: jr / nop`.
 *
 * Two things have to be right together and each is one word:
 *  1. `return p->f49E != 0;` and every if/else spelling of it FOLD to
 *     `sltu $2,$0,$2` -- three words.  Only `r = 0; if (x != 0) { r = 1; }`
 *     keeps retail's branch, with the zero in the delay slot.
 *  2. the constant is `daddiu`, not `addiu`, which is the recorded UNSIGNED
 *     NARROW TYPE tell -- so `r` is `u16`.  And the RETURN TYPE has to be
 *     `u16` as well: with an `s32` return the u16->int promotion adds
 *     `andi $2,$3,0xFFFF` in the `jr`'s delay slot, one word long.
 * 32 spellings across three probe builds; this is the only exact one.  Same
 * class as title's `004EA000` (where the fix was the CALLEE's parameter type)
 * and insmenu's `004F82E0` (where the consumer is a compare and it is open):
 * ⇒ when the value flows into a RETURN, the return type is the other half.
 * One of the 55 unnamed functions; see scripts/n_unnamed.py. */
typedef struct Obj {
    u8  pad000[0x49E];
    s16 f49E;
} Obj;

u16 normal_FieldHudWidget83IsOpen_4f9590(Obj *p)
{
    u16 r;

    r = 0;
    if (p->f49E != 0) {
        r = 1;
    }
    return r;
}
