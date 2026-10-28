/* rgp:protos */
#define RGP_SELF_EvSubMachineSetCastSlot_251f50 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Write the s32 at +0x60. */

typedef struct Obj_FUN_00251f50 {
    u8 pad000[0x60];
    s32 field;         /* +0x60 */
} Obj_FUN_00251f50;

void EvSubMachineSetCastSlot_251f50(Obj_FUN_00251f50 *o, s32 value)
{
    o->field = value;
}
