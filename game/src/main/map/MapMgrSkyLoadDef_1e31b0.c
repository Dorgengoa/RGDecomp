/* rgp:protos */
#define RGP_SELF_MapMgrSkyLoadDef_1e31b0 1
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
    s16 m00;
    u8 pad002[0x6];
    s32 m08;
};

s32 MapMgrSkyLoadDef_1e31b0(s32 p0, struct Obj0 *p1)
{
    s16 t0;
    s32 t1;

    if (p1 != 0) {
        t0 = p1->m00;
        t1 = p1->m08;
        return (s32)MapSkyLoad_1e6250((p0 + 0xE0), t0, t1);
        
    }
    return 0;
}
