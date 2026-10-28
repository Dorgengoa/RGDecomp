/* rgp:protos */
#define RGP_SELF_NavNodeSetPrev_311860 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Write the s16 at +0x1E. */

typedef struct Obj_FUN_00311860 {
    u8 pad000[0x1E];
    s16 field;         /* +0x1E */
} Obj_FUN_00311860;

void NavNodeSetPrev_311860(Obj_FUN_00311860 *o, s16 value)
{
    o->field = value;
}
