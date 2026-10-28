/* rgp:protos */
#define RGP_SELF_EvObjLiftSetTargetSetCount_336010 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Write the s16 at +0xEA. */

typedef struct Obj_FUN_00336010 {
    u8 pad000[0xEA];
    s16 field;         /* +0xEA */
} Obj_FUN_00336010;

void EvObjLiftSetTargetSetCount_336010(Obj_FUN_00336010 *o, s16 value)
{
    o->field = value;
}
