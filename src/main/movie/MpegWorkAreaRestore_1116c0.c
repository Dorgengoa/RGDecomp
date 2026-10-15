#include "types.h"

/* Copy the s32 at +0xC to +0x8. */

/* NOT void: retail routes the copied word through $2, which is the return
   register -- the value is handed back.  Written `void` it comes out in $3. */

typedef struct Obj_FUN_001116c0 {
    u8 pad000[0x8];
    s32 dst;         /* +0x8 */
    s32 src;         /* +0xC */
} Obj_FUN_001116c0;

s32 MpegWorkAreaRestore_1116c0(Obj_FUN_001116c0 *o)
{
    s32 v;

    v = o->src;
    o->dst = v;
    return v;
}
