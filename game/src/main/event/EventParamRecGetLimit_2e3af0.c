/* rgp:protos */
#define RGP_SELF_EventParamRecGetLimit_2e3af0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Read the f32 at +0x18. */

typedef struct Obj_FUN_002e3af0 {
    u8 pad000[0x18];
    f32 field;         /* +0x18 */
} Obj_FUN_002e3af0;

f32 EventParamRecGetLimit_2e3af0(Obj_FUN_002e3af0 *o)
{
    return o->field;
}
