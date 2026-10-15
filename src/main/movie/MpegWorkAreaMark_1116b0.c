#include "types.h"

/* Copy the s32 at +0x8 to +0xC. */

/* NOT void: retail routes the copied word through $2, which is the return
   register -- the value is handed back.  Written `void` it comes out in $3. */

typedef struct Obj_FUN_001116b0 {
    u8 pad000[0x8];
    s32 src;         /* +0x8 */
    s32 dst;         /* +0xC */
} Obj_FUN_001116b0;

s32 MpegWorkAreaMark_1116b0(Obj_FUN_001116b0 *o)
{
    s32 v;

    v = o->src;
    o->dst = v;
    return v;
}
