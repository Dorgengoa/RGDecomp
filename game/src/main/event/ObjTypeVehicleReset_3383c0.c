/* rgp:protos */
#define RGP_SELF_ObjTypeVehicleReset_3383c0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0x110];
    s32 m110;
    s16 m114;
    u8 pad116[0x2];
    s32 m118;
    s32 m11C;
    u8 m120;
    u8 pad121[0xF];
    s16 m130;
    s16 m132;
};

void ObjTypeVehicleReset_3383c0(struct Obj0 *p0)
{
    EvObjReset_2f9eb0(p0);
    TargetRefClear_2e71d0((struct Obj0 *)((u8 *)p0 + 0xE0));
    p0->m118 = 0;
    p0->m11C = 0;
    p0->m110 = 0;
    p0->m114 = 0;
    p0->m130 = 0;
    p0->m120 = 0;
    p0->m132 = 0;
}
