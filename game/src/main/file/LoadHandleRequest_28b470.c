/* rgp:protos */
#define RGP_SELF_LoadHandleRequest_28b470 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
extern s32 strcpy(void *, s32);
/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    s32 m00;
    s32 m04;
};

s32 LoadHandleRequest_28b470(struct Obj0 *p0, s32 p1, s32 p2, s32 p3, s32 p4, s32 p5)
{
    s32 r0;
    s32 r2;
    s32 rv5;
    s32 r3;
    s32 t0;

    r0 = ((s32)GetLoaderMgr_1f59d0());
    if (r0 == 0) {
        return -1;
    }
    LoadHandleInit_28b610(p0);
    r2 = ((short)LoaderRequestFileEx_1cd6c0(r0, p1, p3, p4));
    p0->m00 = r2;
    if (r2 < 0) {
        p0->m04 = -1;
        rv5 = -1;
    } else {
        r3 = ((s32)strcpy((struct Obj0 *)((u8 *)p0 + 8), p1));
        p0->m04 = 0;
        if (p2 == 1) {
            LoaderQueueAppendSeparator_1cd670(r0);
        }
        t0 = p0->m00;
        rv5 = t0;
    }
    return rv5;
}
