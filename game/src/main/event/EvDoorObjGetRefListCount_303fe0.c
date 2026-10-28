/* rgp:protos */
#define RGP_SELF_EvDoorObjGetRefListCount_303fe0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Read the s16 at +0x188. */

typedef struct Obj_FUN_00303fe0 {
    u8 pad000[0x188];
    s16 field;         /* +0x188 */
} Obj_FUN_00303fe0;

s16 EvDoorObjGetRefListCount_303fe0(Obj_FUN_00303fe0 *o)
{
    return o->field;
}
