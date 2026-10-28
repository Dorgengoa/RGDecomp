/* rgp:protos */
#define RGP_SELF_insect_InsectAiGetAction_522300 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* insect 0x522300 -- 8 B / 2 words.  `jr $31 / lw $2, 0x8CC($4)`:
 * a bare word accessor.  The load WIDTH (lw) fixes the member at s32. */

typedef struct Obj {
    u8  pad00[0x8CC];
    s32 m8CC;                 /* +0x8CC */
} Obj;

s32 insect_InsectAiGetAction_522300(Obj *o)
{
    return o->m8CC;
}
