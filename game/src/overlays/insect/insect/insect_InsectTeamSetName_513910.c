/* rgp:protos */
#define RGP_SELF_insect_InsectTeamSetName_513910 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* insect 0x00513910 -- a 3-instruction leaf setter.  Both parameters are USED in
 * the body, so the arity needs no caller evidence: a store of $5 through $4
 * cannot be a pass-through. */
typedef struct Ent {
    u8 pad00[0x988];
    s32 f988;
} Ent;

void insect_InsectTeamSetName_513910(Ent *p, s32 v)
{
    p->f988 = v;
}
