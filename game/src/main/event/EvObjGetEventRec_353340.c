/* rgp:protos */
#define RGP_SELF_EvObjGetEventRec_353340 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Address of the sub-object at +0xE0. */

typedef struct Obj_FUN_00353340 {
    u8 pad000[0xE0];
    u8 sub[1];         /* +0xE0 */
} Obj_FUN_00353340;

void *EvObjGetEventRec_353340(Obj_FUN_00353340 *o)
{
    return o->sub;
}
