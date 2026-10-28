/* rgp:protos */
#define RGP_SELF_StreamChanPlay_1d6c30 1
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

void StreamChanPlay_1d6c30(struct Obj0 *p0, f32 fa0)
{
    s16 t0;
    s32 r0;
    s32 rv2;
    s32 r1;
    s32 r3;
    s32 r4;

    t0 = p0->m80;
    if (t0 >= 0) {
        r0 = ((unsigned char)StreamChanIsPlaying_1d71f0(p0));
        rv2 = r0;
        if (r0 != 0) {
            r1 = (StreamChanSetPauseReq_1d7140(p0, 1), (s32)0);
            rv2 = r1;
        }
        r3 = (StreamChanSetResumeReq_1d7170(p0, 1), (s32)0);
        r4 = (StreamChanSetVolume_1d7010(p0, fa0), (s32)0);
        return;
    }
}
