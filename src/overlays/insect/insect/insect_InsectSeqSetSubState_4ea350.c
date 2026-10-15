#include "types.h"
/* insect 0x004EA350 -- 100 bytes, 25 instructions.  Push v into the first free
 * slot of the four-entry ring at +0x14; if the ring is full, shift it down and
 * write the newest at the end. */

typedef struct Ring {
    u8  pad00[0x14];
    s32 f14[4];                     /* +0x14 .. +0x20 */
    s32 f24;                        /* +0x24 */
    s32 f28;                        /* +0x28 */
} Ring;

void insect_InsectSeqSetSubState_4ea350(Ring *r, s32 v)
{
    s32 i;
    s32 *p;

    r->f28 = v;
    for (i = 0; i < 4; i++) {
        p = &r->f14[i];
        if (*p == -1) {
            *p = v;
            return;
        }
    }
    for (i = 0; i < 3; i++) {
        r->f14[i] = r->f14[i + 1];
    }
    r->f14[3] = v;
}
