/* rgp:protos */
#define RGP_SELF_EvDoorObjReset_304440 1
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
    u8 pad000[0x170];
    s32 m170;
    s32 m174;
    s32 m178;
    s32 m17C;
    s32 m180;
    s32 m184;
    s16 m188;
    s16 m18A;
    u8 m18C;
    u8 pad18D[0xF];
    s16 m19C;
    s16 m19E;
    u8 m1A0;
    u8 m1A1;
    u8 m1A2;
};

void EvDoorObjReset_304440(struct Obj0 *p0)
{
    EvObjReset_2f9eb0(p0);
    DoorCursorClear_305630((struct Obj0 *)((u8 *)p0 + 0xE0));
    p0->m170 = 0;
    p0->m174 = 0;
    p0->m178 = 0;
    p0->m17C = 0;
    p0->m180 = 0;
    p0->m184 = 0;
    p0->m188 = 0;
    p0->m18A = 0;
    p0->m19C = 0;
    p0->m18C = 0;
    p0->m19E = 0;
    p0->m1A0 = 0;
    p0->m1A2 = 0;
    p0->m1A1 = 0;
}
