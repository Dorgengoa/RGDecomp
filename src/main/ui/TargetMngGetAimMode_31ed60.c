#include "types.h"

/* Read the s32 at +0x140. */

typedef struct Obj_FUN_0031ed60 {
    u8 pad000[0x140];
    s32 field;         /* +0x140 */
} Obj_FUN_0031ed60;

s32 TargetMngGetAimMode_31ed60(Obj_FUN_0031ed60 *o)
{
    return o->field;
}
