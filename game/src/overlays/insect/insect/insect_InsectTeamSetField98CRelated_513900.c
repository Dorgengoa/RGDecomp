/* rgp:protos */
#define RGP_SELF_insect_InsectTeamSetField98CRelated_513900 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* insect 0x513900 -- 8 B / 2 words.  `jr $31 / sb $5, 0x98C($4)`:
 * a single-byte setter, the value handed straight through from $5. */

typedef struct Obj {
    u8 pad00[0x98C];
    u8 m98C;                  /* +0x98C */
} Obj;

void insect_InsectTeamSetField98CRelated_513900(Obj *o, u8 v)
{
    o->m98C = v;
}
