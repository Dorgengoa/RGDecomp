/* rgp:protos */
#define RGP_SELF_MapIdIndexHasIds_1ddbd0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Is the s32 at +0x0 non-zero? */

typedef struct Obj_FUN_001ddbd0 {
    s32 field;         /* +0x0 */
} Obj_FUN_001ddbd0;

u8 MapIdIndexHasIds_1ddbd0(Obj_FUN_001ddbd0 *o)
{
    u8 set;

    set = o->field != 0;
    return set;
}
