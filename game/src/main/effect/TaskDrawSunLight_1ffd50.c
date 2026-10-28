/* rgp:protos */
#define RGP_SELF_TaskDrawSunLight_1ffd50 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0x4344];
    s32 m4344;
};

void TaskDrawSunLight_1ffd50(void)
{
    struct Obj0 *r0;
    s32 t0;
    s32 r1;
    s32 r2;

    r0 = GetCurrentScene_1f5be0();
    t0 = r0->m4344;
    r1 = ((s32)ObjRecGetLiveObject_1c3bc0(r0, t0));
    r2 = ((s32)GetMapSunLight_201a30());
    SunLightDraw_293410(r2, r1);
}
