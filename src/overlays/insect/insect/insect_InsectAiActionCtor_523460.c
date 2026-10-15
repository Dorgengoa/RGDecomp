#include "types.h"
/* insect 0x00523460 -- 40 B / 10 words.  Same constructor wrapper as
 * insect_InsectAbilityCtor_51d370, against insect_InsectAiActionReset_523410. */
typedef struct Ent Ent;

extern void insect_InsectAiActionReset_523410(Ent *o);

Ent *insect_InsectAiActionCtor_523460(Ent *o)
{
    insect_InsectAiActionReset_523410(o);
    return o;
}
