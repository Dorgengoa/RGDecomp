/* rgp:protos */
#define RGP_SELF_DListGetCountPow2_42ea70 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Read the u16 at +0xA. */

typedef struct Obj_FUN_0042ea70 {
    u8 pad000[0xA];
    u16 field;         /* +0xA */
} Obj_FUN_0042ea70;

u16 DListGetCountPow2_42ea70(Obj_FUN_0042ea70 *o)
{
    return o->field;
}
