#include "types.h"

/* Read the s32 at +0x0. */

typedef struct Obj_FUN_0032ae80 {
    s32 field;         /* +0x00 */
} Obj_FUN_0032ae80;

s32 MinimapSubGetArray_32ae80(Obj_FUN_0032ae80 *o)
{
    return o->field;
}
