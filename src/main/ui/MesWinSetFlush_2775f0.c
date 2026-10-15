#include "types.h"

/* Write the u8 at +0xB6. */

typedef struct Obj_FUN_002775f0 {
    u8 pad000[0xB6];
    u8 field;         /* +0xB6 */
} Obj_FUN_002775f0;

void MesWinSetFlush_2775f0(Obj_FUN_002775f0 *o, u8 value)
{
    o->field = value;
}
