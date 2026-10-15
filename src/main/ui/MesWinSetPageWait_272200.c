#include "types.h"

/* Write the u8 at +0xB7. */

typedef struct Obj_FUN_00272200 {
    u8 pad000[0xB7];
    u8 field;         /* +0xB7 */
} Obj_FUN_00272200;

void MesWinSetPageWait_272200(Obj_FUN_00272200 *o, u8 value)
{
    o->field = value;
}
