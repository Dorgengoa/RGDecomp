#include "types.h"

/* Copy the s16 at +0x222 to +0x220. */

typedef struct Obj_FUN_002fb2b0 {
    u8 pad000[0x220];
    s16 dst;         /* +0x220 */
    s16 src;         /* +0x222 */
} Obj_FUN_002fb2b0;

void NpcObjTableRestoreFlags_2fb2b0(Obj_FUN_002fb2b0 *o)
{
    o->dst = o->src;
}
