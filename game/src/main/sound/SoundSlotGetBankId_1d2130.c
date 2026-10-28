/* rgp:protos */
#define RGP_SELF_SoundSlotGetBankId_1d2130 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Read the s32 at +0x14. */

typedef struct Obj_FUN_001d2130 {
    u8 pad000[0x14];
    s32 field;         /* +0x14 */
} Obj_FUN_001d2130;

s32 SoundSlotGetBankId_1d2130(Obj_FUN_001d2130 *o)
{
    return o->field;
}
