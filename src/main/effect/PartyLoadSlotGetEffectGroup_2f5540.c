#include "types.h"

/* Read the s16 at +0x2. */

typedef struct Obj_FUN_002f5540 {
    u8 pad000[0x2];
    s16 field;         /* +0x2 */
} Obj_FUN_002f5540;

s16 PartyLoadSlotGetEffectGroup_2f5540(Obj_FUN_002f5540 *o)
{
    return o->field;
}
