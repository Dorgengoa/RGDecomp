/* rgp:protos */
#define RGP_SELF_EvTargetSetPointCount_352940 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Write the s32 at +0x130. */

typedef struct Obj_FUN_00352940 {
    u8 pad000[0x130];
    s32 field;         /* +0x130 */
} Obj_FUN_00352940;

void EvTargetSetPointCount_352940(Obj_FUN_00352940 *o, s32 value)
{
    o->field = value;
}
