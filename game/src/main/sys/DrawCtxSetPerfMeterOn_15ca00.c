/* rgp:protos */
#define RGP_SELF_DrawCtxSetPerfMeterOn_15ca00 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern struct Obj0 * D_004810A4;

struct Obj0;

struct Obj0 {
    u8 pad000[0x3CC8];
    s32 m3CC8;
};

void DrawCtxSetPerfMeterOn_15ca00(s32 p0)
{
    D_004810A4->m3CC8 = p0;
}
