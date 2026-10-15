#include "types.h"

/* Read the s8 at +0xB7. */

typedef struct Obj_FUN_002721f0 {
    u8 pad000[0xB7];
    s8 field;         /* +0xB7 */
} Obj_FUN_002721f0;

s8 MesWinIsPageWait_2721f0(Obj_FUN_002721f0 *o)
{
    return o->field;
}
