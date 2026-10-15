#include "types.h"

/* Write the s32 at +0x14. */

typedef struct Obj_FUN_001d2100 {
    u8 pad000[0x14];
    s32 field;         /* +0x14 */
} Obj_FUN_001d2100;

void SoundSlotSetBankId_1d2100(Obj_FUN_001d2100 *o, s32 value)
{
    o->field = value;
}
