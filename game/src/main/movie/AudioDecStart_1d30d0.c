/* rgp:protos */
#define RGP_SELF_AudioDecStart_1d30d0 1
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
    u8 pad004[0x40];
    s32 m44;
    s32 m48;
    u8 pad04C[0x4];
    s32 m50;
};

s32 AudioDecStart_1d30d0(struct Obj0 *p0)
{
    s32 t0;
    s32 t1;
    s32 rv0;
    s32 t2;

    t0 = p0->m48;
    t1 = p0->m44;
    rv0 = t0 / 1024;
    t2 = p0->m50;
    SoundSendCmd_1b6cc0(0x26, 6, 0x80E0, 0, 0x13, t1, (rv0 * 1024), (t1 + t2));
    p0->m00 = 2;
    AudioDecSetInputVolume_1d2b90(0x7FFF);
    return 0;
}
