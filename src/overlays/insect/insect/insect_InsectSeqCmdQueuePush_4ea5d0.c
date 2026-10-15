#include "types.h"
/* insect 0x004EA5D0 -- 68 bytes, 17 instructions, a leaf with no frame.
 * The s32[0x40] slot table at +0x5C runs exactly up to the count at +0x15C.
 * Retail forms `o + i*4`, then `+0x5C` as a separate pointer, and LOADS
 * through the intermediate while STORING through the pointer -- the
 * [[ixa07 pointer-associativity]] shape, one named pointer local.
 */

typedef struct Obj {
    u8  pad00[0x5C];
    s32 m5C[0x40];                  /* +0x5C */
    s32 m15C;                       /* +0x15C */
} Obj;

void insect_InsectSeqCmdQueuePush_4ea5d0(Obj *o, s32 v)
{
    s32 i;
    s32 *p;

    for (i = 0; i < 0x40; i++) {
        p = &o->m5C[i];
        if (*p == 0) {
            *p = v;
            o->m15C = o->m15C + 1;
            return;
        }
    }
}
