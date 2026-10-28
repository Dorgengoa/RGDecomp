/* rgp:protos */
#define RGP_SELF_LoaderUseSyncRead_1cd890 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0xC];
    u8 m0C;
};

u8 LoaderUseSyncRead_1cd890(struct Obj0 *p0)
{
    s32 r0;
    u8 t0;

    r0 = GetKeyCapModeMaybe_1c3540();
    if (r0 != 0) {
        return 1;
    }
    t0 = p0->m0C;
    return t0;
}
