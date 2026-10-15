#include "types.h"

/* Read the s32 at +0xD8. */

typedef struct Obj_FUN_002f9c80 {
    u8 pad000[0xD8];
    s32 field;         /* +0xD8 */
} Obj_FUN_002f9c80;

s32 EvObjGetScriptList_2f9c80(Obj_FUN_002f9c80 *o)
{
    return o->field;
}
