/* rgp:protos */
#define RGP_SELF_EffectEntryGetName_2d9540 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Address of the sub-object at +0xBC. */

typedef struct Obj_FUN_002d9540 {
    u8 pad000[0xBC];
    u8 sub[1];         /* +0xBC */
} Obj_FUN_002d9540;

void *EffectEntryGetName_2d9540(Obj_FUN_002d9540 *o)
{
    return o->sub;
}
