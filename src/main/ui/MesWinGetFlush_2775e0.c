#include "types.h"

/* Read the s8 at +0xB6. */

typedef struct Obj_FUN_002775e0 {
    u8 pad000[0xB6];
    s8 field;         /* +0xB6 */
} Obj_FUN_002775e0;

s8 MesWinGetFlush_2775e0(Obj_FUN_002775e0 *o)
{
    return o->field;
}
