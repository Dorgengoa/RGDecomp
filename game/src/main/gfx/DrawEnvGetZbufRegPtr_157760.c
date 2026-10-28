/* rgp:protos */
#define RGP_SELF_DrawEnvGetZbufRegPtr_157760 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Address of the sub-object at +0x90. */

typedef struct Obj_FUN_00157760 {
    u8 pad000[0x90];
    u8 sub[1];         /* +0x90 */
} Obj_FUN_00157760;

void *DrawEnvGetZbufRegPtr_157760(Obj_FUN_00157760 *o)
{
    return o->sub;
}
