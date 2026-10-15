#include "types.h"

/* Read the u8 at +0x140. */

typedef struct Obj_FUN_002ed820 {
    u8 pad000[0x140];
    u8 field;         /* +0x140 */
} Obj_FUN_002ed820;

u8 LensFlareIsEnabled_2ed820(Obj_FUN_002ed820 *o)
{
    return o->field;
}
