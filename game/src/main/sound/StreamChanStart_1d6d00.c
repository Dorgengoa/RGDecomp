/* rgp:protos */
#define RGP_SELF_StreamChanStart_1d6d00 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
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
    u8 m00;
    u8 pad001[0x7F];
    s16 m80;
};

void StreamChanStart_1d6d00(struct Obj0 *p0, s32 p1, s32 p2)
{
    s16 t0;
    s32 r0;
    s32 rv2;
    s32 r1;
    s32 r3;
    s32 rv5;
    s32 r4;
    s32 r6;
    s32 r7;
    s32 r8;
    s32 r9;

    t0 = p0->m80;
    if (t0 >= 0) {
        if (p1 == 0) {
            return;
        }
        p0->m00 = 0;
        r0 = ((unsigned char)StreamChanIsPlaying_1d71f0(p0));
        rv2 = r0;
        if (r0 != 0) {
            r1 = (StreamChanSetPauseReq_1d7140(p0, 1), (s32)0);
            rv2 = r1;
        }
        r3 = ((unsigned char)StreamChanIsActive_1d7210(p0));
        rv5 = r3;
        if (r3 != 0) {
            r4 = (StreamChanSetStopReq_1d7110(p0, 1), (s32)0);
            rv5 = r4;
        }
        r6 = (StreamChanSetOpenReq_1d71a0(p0, 1), (s32)0);
        r7 = (StreamChanSetResumeReq_1d7170(p0, 0), (s32)0);
        r8 = (StreamChanSetLoop_1d70e0(p0, (p2 != 0)), (s32)0);
        r9 = ((s32)FileMakeDevicePath_181980(p1, p0));
        return;
    }
}
