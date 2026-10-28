/* rgp:protos */
#define RGP_SELF_EvObjLiftGetPlayState_336120 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Read the s16 at +0x108. */

typedef struct Obj_FUN_00336120 {
    u8 pad000[0x108];
    s16 field;         /* +0x108 */
} Obj_FUN_00336120;

s16 EvObjLiftGetPlayState_336120(Obj_FUN_00336120 *o)
{
    return o->field;
}
