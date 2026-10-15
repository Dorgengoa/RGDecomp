#include "types.h"

/* Read the s32 at +0x0. */

typedef struct Obj_FUN_0018e080 {
    s32 field;         /* +0x00 */
} Obj_FUN_0018e080;

s32 ListGetHead_18e080(Obj_FUN_0018e080 *o)
{
    return o->field;
}
