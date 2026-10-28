/* rgp:protos */
#define RGP_SELF_EvObjGetXform_2f9c90 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Address of the sub-object at +0x10. */

typedef struct Obj_FUN_002f9c90 {
    u8 pad000[0x10];
    u8 sub[1];         /* +0x10 */
} Obj_FUN_002f9c90;

void *EvObjGetXform_2f9c90(Obj_FUN_002f9c90 *o)
{
    return o->sub;
}
