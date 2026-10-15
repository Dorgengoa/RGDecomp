#include "types.h"
/* insect 0x0051D370 -- 40 B / 10 words.  A constructor wrapper: forward the
 * `this` pointer to the field-reset insect_InsectAbilityReset_51d280 and RETURN it.  $16
 * holds `this` across the call and `daddu $2,$16,$0` is the return, so the
 * result is the parameter and not the callee's value (the callee is void).
 * One of three identical members (005233E0, 00523460) differing only in the
 * callee. */
typedef struct Ent Ent;

extern void insect_InsectAbilityReset_51d280(Ent *o);

Ent *insect_InsectAbilityCtor_51d370(Ent *o)
{
    insect_InsectAbilityReset_51d280(o);
    return o;
}
