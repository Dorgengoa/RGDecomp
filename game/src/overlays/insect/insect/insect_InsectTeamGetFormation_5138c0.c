/* rgp:protos */
#define RGP_SELF_insect_InsectTeamGetFormation_5138c0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* insect 0x005138C0 -- 8 bytes, 2 instructions.  A leaf accessor: the whole
 * body is `lb $2, 0x98D($4)` in the `jr $31` delay slot. */

typedef struct Obj {
    u8 pad000[0x98D];
    s8 m98D;                        /* +0x98D */
} Obj;

s8 insect_InsectTeamGetFormation_5138c0(Obj *o)
{
    return o->m98D;
}
