/* rgp:protos */
#define RGP_SELF_EventParamRecGetDamping_2e3b00 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Read the f32 at +0x14. */

typedef struct Obj_FUN_002e3b00 {
    u8 pad000[0x14];
    f32 field;         /* +0x14 */
} Obj_FUN_002e3b00;

f32 EventParamRecGetDamping_2e3b00(Obj_FUN_002e3b00 *o)
{
    return o->field;
}
