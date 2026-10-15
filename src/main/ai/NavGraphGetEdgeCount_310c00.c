#include "types.h"

/* Read the u16 at +0xB8. */

typedef struct Obj_FUN_00310c00 {
    u8 pad000[0xB8];
    u16 field;         /* +0xB8 */
} Obj_FUN_00310c00;

u16 NavGraphGetEdgeCount_310c00(Obj_FUN_00310c00 *o)
{
    return o->field;
}
