#include "types.h"

/* Write the s16 at +0x220. */

typedef struct Obj_FUN_0031e300 {
    u8 pad000[0x220];
    s16 field;         /* +0x220 */
} Obj_FUN_0031e300;

void HpGaugeSetBarWidth_31e300(Obj_FUN_0031e300 *o, s16 value)
{
    o->field = value;
}
