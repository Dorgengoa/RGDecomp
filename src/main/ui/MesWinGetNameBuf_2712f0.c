#include "types.h"

/* Address of the sub-object at +0x1DC6. */

typedef struct Obj_FUN_002712f0 {
    u8 pad000[0x1DC6];
    u8 sub[1];         /* +0x1DC6 */
} Obj_FUN_002712f0;

void *MesWinGetNameBuf_2712f0(Obj_FUN_002712f0 *o)
{
    return o->sub;
}
