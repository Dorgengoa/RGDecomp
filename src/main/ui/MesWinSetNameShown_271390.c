#include "types.h"

/* Write the s16 at +0x1DC4. */

typedef struct Obj_FUN_00271390 {
    u8 pad000[0x1DC4];
    s16 field;         /* +0x1DC4 */
} Obj_FUN_00271390;

void MesWinSetNameShown_271390(Obj_FUN_00271390 *o, s16 value)
{
    o->field = value;
}
