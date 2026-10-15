#include "types.h"

/* Read the s32 at +0x10. */

typedef struct Obj_FUN_0018a370 {
    u8 pad000[0x10];
    s32 field;         /* +0x10 */
} Obj_FUN_0018a370;

s32 ListNodeGetData_18a370(Obj_FUN_0018a370 *o)
{
    return o->field;
}
