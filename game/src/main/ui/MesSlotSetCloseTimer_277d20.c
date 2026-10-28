/* rgp:protos */
#define RGP_SELF_MesSlotSetCloseTimer_277d20 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Write the s32 at +0x54. */

typedef struct Obj_FUN_00277d20 {
    u8 pad000[0x54];
    s32 field;         /* +0x54 */
} Obj_FUN_00277d20;

void MesSlotSetCloseTimer_277d20(Obj_FUN_00277d20 *o, s32 value)
{
    o->field = value;
}
