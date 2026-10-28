/* rgp:protos */
#define RGP_SELF_EvCmdEventMesWinAdvance_245890 1
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
struct Obj1;

struct Obj0 {
    u8 pad000[0x4];
    struct Obj1 *m04;
};

struct Obj1 {
    u8 pad000[0x42C];
    s32 m42C;
};

s32 EvCmdEventMesWinAdvance_245890(void)
{
    s32 t2;

    t2 = gEventContext->m04->m42C;
    if (t2 != 0) {
        MesWinAdvance_2768f0(t2);
    }
    return 1;
}
