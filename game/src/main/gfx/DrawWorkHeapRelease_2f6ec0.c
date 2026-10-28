/* rgp:protos */
#define RGP_SELF_DrawWorkHeapRelease_2f6ec0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern u8 D_004E6420[];
extern s32 D_004E6434;

struct Obj0;

struct Obj0 {
    u8 pad000[0x180C];
    s32 m180C;
};

s32 DrawWorkHeapRelease_2f6ec0(void)
{
    s32 r0;
    s32 r1;
    struct Obj0 *r2;
    s32 t0;
    s32 t1;
    s32 r3;
    s32 r4;

    r0 = GetDrawCtx_15de80();
    r1 = (DrawListFlushAndFree_1404b0(r0), (s32)0);
    r2 = GetCurrentScene_1f5be0();
    t0 = r2->m180C;
    if (t0 != 0) {
        t1 = D_004E6434;
        r3 = (MemStackHeapFree_14dcb0(t0, t1), (s32)0);
    }
    r4 = (MemStackHeapReinit_14de90(D_004E6420), (s32)0);
    return r4;
}
