/* rgp:protos */
#define RGP_SELF_HpGaugeSetMode_31e2d0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Write the u8 at +0x240. */

typedef struct Obj_FUN_0031e2d0 {
    u8 pad000[0x240];
    u8 field;         /* +0x240 */
} Obj_FUN_0031e2d0;

void HpGaugeSetMode_31e2d0(Obj_FUN_0031e2d0 *o, u8 value)
{
    o->field = value;
}
