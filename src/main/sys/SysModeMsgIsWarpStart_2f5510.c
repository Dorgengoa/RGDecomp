#include "types.h"

extern void * SysGetModeMsg_1c39b0(void);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    s16 m00;
};

s32 SysModeMsgIsWarpStart_2f5510(void)
{
    struct Obj0 *r0;
    s16 t0;

    r0 = SysGetModeMsg_1c39b0();
    if (r0 != 0) {
        t0 = r0->m00;
        return (t0 == 6);
    }
    return 0;
}
