/* rgp:protos */
#define RGP_SELF_LoaderClear_1ce040 1
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
    s32 m00;
    s32 m04;
    s32 m08;
    u8 m0C;
    u8 m0D;
    u8 pad00E[0x2];
    s32 m10;
    s32 m14;
    s32 m18;
    s32 m1C;
};

void LoaderClear_1ce040(struct Obj0 *p0)
{
    p0->m10 = 0;
    p0->m14 = 0;
    p0->m18 = 0;
    p0->m1C = 0;
    S16ArrayReset_1ce240((struct Obj0 *)((u8 *)p0 + 0x20));
    S16ArrayReset_1ce240((struct Obj0 *)((u8 *)p0 + 0x28));
    S16ArrayReset_1ce240((struct Obj0 *)((u8 *)p0 + 0x30));
    p0->m00 = 0;
    p0->m04 = 0;
    p0->m08 = 0;
    p0->m0C = 0;
    p0->m0D = 0;
    FileReqReset_182a00();
}
