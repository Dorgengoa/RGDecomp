/* rgp:protos */
#define RGP_SELF_EvCmdEventMesWinClose_245ba0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern struct Obj0 * gEventContext;

struct Obj0;

struct Obj0 {
    u8 pad000[0x4];
    s32 m04;
};

s32 EvCmdEventMesWinClose_245ba0(void)
{
    s32 r;

    r = MesWinOwnerClose_24eab0((gEventContext->m04 + 0x420));
    return 1;
}
