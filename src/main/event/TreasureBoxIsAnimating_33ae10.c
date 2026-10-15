#include "types.h"

/* Is the s16 at +0x26 non-zero? */

typedef struct Obj_FUN_0033ae10 {
    u8 pad000[0x26];
    s16 field;         /* +0x26 */
} Obj_FUN_0033ae10;

u8 TreasureBoxIsAnimating_33ae10(Obj_FUN_0033ae10 *o)
{
    u8 set;

    set = o->field != 0;
    return set;
}
