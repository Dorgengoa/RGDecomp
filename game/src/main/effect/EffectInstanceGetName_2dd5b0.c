/* rgp:protos */
#define RGP_SELF_EffectInstanceGetName_2dd5b0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Address of the sub-object at +0x170. */

typedef struct Obj_FUN_002dd5b0 {
    u8 pad000[0x170];
    u8 sub[1];         /* +0x170 */
} Obj_FUN_002dd5b0;

void *EffectInstanceGetName_2dd5b0(Obj_FUN_002dd5b0 *o)
{
    return o->sub;
}
