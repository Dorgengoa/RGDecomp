#include "types.h"

/* Read the u8 at +0x32. */

typedef struct Obj_FUN_00323790 {
    u8 pad000[0x32];
    u8 field;         /* +0x32 */
} Obj_FUN_00323790;

u8 EntryListGetChildCount_323790(Obj_FUN_00323790 *o)
{
    return o->field;
}
