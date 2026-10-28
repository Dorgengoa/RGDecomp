/* rgp:protos */
#define RGP_SELF_insect_InsectTeamSetFormation_5138f0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* insect 0x5138F0 -- 8 B / 2 words.  `jr $31 / sb $5, 0x98D($4)`:
 * a single-byte setter, the value handed straight through from $5. */

typedef struct Obj {
    u8 pad00[0x98D];
    u8 m98D;                  /* +0x98D */
} Obj;

void insect_InsectTeamSetFormation_5138f0(Obj *o, u8 v)
{
    o->m98D = v;
}
