/* rgp:protos */
#define RGP_SELF_StreamChanStop_1d6ca0 1
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
    u8 pad000[0x80];
    s16 m80;
};

void StreamChanStop_1d6ca0(struct Obj0 *p0)
{
    s16 t0;
    s32 r0;
    s32 rv3;
    s32 r1;
    s32 r2;
    s32 r4;

    t0 = p0->m80;
    if (t0 >= 0) {
        r0 = ((unsigned char)StreamChanIsActive_1d7210(p0));
        rv3 = r0;
        if (r0 != 0) {
            r1 = (StreamChanSetPauseReq_1d7140(p0, 1), (s32)0);
            r2 = (StreamChanSetStopReq_1d7110(p0, 1), (s32)0);
            rv3 = r2;
        }
        r4 = (StreamChanSetResumeReq_1d7170(p0, 1), (s32)0);
        return;
    }
}
