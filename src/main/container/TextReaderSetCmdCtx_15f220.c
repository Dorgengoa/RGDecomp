#include "types.h"

/* Write the s32 at +0x30. */

typedef struct Obj_FUN_0015f220 {
    u8 pad000[0x30];
    s32 field;         /* +0x30 */
} Obj_FUN_0015f220;

void TextReaderSetCmdCtx_15f220(Obj_FUN_0015f220 *o, s32 value)
{
    o->field = value;
}
