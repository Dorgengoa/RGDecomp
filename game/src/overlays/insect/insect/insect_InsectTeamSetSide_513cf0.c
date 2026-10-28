/* rgp:protos */
#define RGP_SELF_insect_InsectTeamSetSide_513cf0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* insect 0x513CF0 -- 8 B / 2 words.  `jr $31 / sb $5, 0x98E($4)`:
 * a single-byte setter, the value handed straight through from $5. */

typedef struct Obj {
    u8 pad00[0x98E];
    u8 m98E;                  /* +0x98E */
} Obj;

void insect_InsectTeamSetSide_513cf0(Obj *o, u8 v)
{
    o->m98E = v;
}
