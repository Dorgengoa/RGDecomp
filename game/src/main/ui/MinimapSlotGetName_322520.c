/* rgp:protos */
#define RGP_SELF_MinimapSlotGetName_322520 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Address of the sub-object at +0x180. */

typedef struct Obj_FUN_00322520 {
    u8 pad000[0x180];
    u8 sub[1];         /* +0x180 */
} Obj_FUN_00322520;

void *MinimapSlotGetName_322520(Obj_FUN_00322520 *o)
{
    return o->sub;
}
