/* rgp:protos */
#define RGP_SELF_CharaInteractSetupMaybe_3eb790 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/

/* Seven parameters ($4..$10).  There is NO local for the sub-object: retail
   addresses every field as an offset off $21 (the first parameter) and
   materialises `$21+0x34` only where a pointer is actually passed.  Naming it
   costs the seventh parameter its callee-saved slot. */

typedef struct {
    u8 pad00[0x34];
    s16 m34;
    s16 m36;
    u8 pad38[0x6];
    u8 b0 : 1;
    u8 b1 : 1;
    u8 b2 : 1;
} SB790;

unsigned char CharaInteractSetupMaybe_3eb790(SB790 *p, s32 p1, s16 p2, s16 p3, s32 p4, s32 p5, s32 p6)
{
    f32 tmp[12] __attribute__((aligned(16)));

    InteractRecResetMaybe_3ee600(&p->m34);
    p->m34 = p2;
    p->m36 = p3;
    p->b0 = p4;
    p->b1 = p5;
    p->b2 = p6;
    ActionPacketReset_3e3d00(tmp);
    return InteractFindRowMaybe_3e1c30(tmp, p1, &p->m34);
}
