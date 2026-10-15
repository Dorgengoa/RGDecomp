#include "types.h"

/* Read the s32 at +0x1954. */

typedef struct Obj_FUN_00274e40 {
    u8 pad000[0x1954];
    s32 field;         /* +0x1954 */
} Obj_FUN_00274e40;

s32 MesWinGetTextFile_274e40(Obj_FUN_00274e40 *o)
{
    return o->field;
}
