/* rgp:protos */
#define RGP_SELF_insect_InsectAiActionListCtor_5233e0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* insect 0x005233E0 -- 40 B / 10 words.  Same constructor wrapper as
 * insect_InsectAbilityCtor_51d370, against insect_InsectAiActionListInit_5233b0 (the 0x200-word table
 * clear). */
typedef struct Ent Ent;

/*rgp*/

Ent *insect_InsectAiActionListCtor_5233e0(Ent *o)
{
    insect_InsectAiActionListInit_5233b0(o);
    return o;
}
