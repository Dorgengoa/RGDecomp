/* rgp:protos */
#define RGP_SELF_insect_InsectTeamSlotSetName_5140f0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* insect 0x005140F0 -- a 3-instruction leaf setter.  Both parameters are USED in
 * the body, so the arity needs no caller evidence: a store of $5 through $4
 * cannot be a pass-through. */
typedef struct Ent {
    u8 pad00[0x1C];
    s32 f1C;
} Ent;

void insect_InsectTeamSlotSetName_5140f0(Ent *p, s32 v)
{
    p->f1C = v;
}
