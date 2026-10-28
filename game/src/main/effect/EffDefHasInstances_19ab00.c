/* rgp:protos */
#define RGP_SELF_EffDefHasInstances_19ab00 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Is the s32 at +0x5C non-zero? */

typedef struct Obj_FUN_0019ab00 {
    u8 pad000[0x5C];
    s32 field;         /* +0x5C */
} Obj_FUN_0019ab00;

u8 EffDefHasInstances_19ab00(Obj_FUN_0019ab00 *o)
{
    u8 set;

    set = o->field != 0;
    return set;
}
