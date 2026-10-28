/* rgp:protos */
#define RGP_SELF_insect_InsectAiActionCtor_523460 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* insect 0x00523460 -- 40 B / 10 words.  Same constructor wrapper as
 * insect_InsectAbilityCtor_51d370, against insect_InsectAiActionReset_523410. */
typedef struct Ent Ent;

/*rgp*/

Ent *insect_InsectAiActionCtor_523460(Ent *o)
{
    insect_InsectAiActionReset_523410(o);
    return o;
}
