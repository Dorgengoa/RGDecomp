/* rgp:protos */
#define RGP_SELF_Character2ResetMaybe_1aef80 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0x5A0];
    s32 m5A0;
    s32 m5A4;
    s32 m5A8;
    s32 m5AC;
    s32 m5B0;
    s32 m5B4;
    s32 m5B8;
    s32 m5BC;
    u8 pad5C0[0x10];
    s32 m5D0;
    s32 m5D4;
    s32 m5D8;
    s32 m5DC;
    s32 m5E0;
    s32 m5E4;
    s32 m5E8;
    s32 m5EC;
    u8 pad5F0[0x4C];
    s32 m63C;
    u8 pad640[0x130];
    s32 m770;
    s32 m774;
    s32 m778;
    s32 m77C;
    s32 m780;
    u8 pad784[0x4];
    s32 m788;
};

void Character2ResetMaybe_1aef80(struct Obj0 *p0)
{
    p0->m774 = 0;
    p0->m770 = 0;
    p0->m778 = 0;
    p0->m5A0 = 0x43000000;
    p0->m5A4 = 0x43000000;
    p0->m5A8 = 0x43000000;
    p0->m5AC = 0x43000000;
    p0->m5B0 = 0;
    p0->m5B4 = 0;
    p0->m5B8 = 0;
    p0->m5BC = 0;
    p0->m5D0 = 0x43000000;
    p0->m5D4 = 0x43000000;
    p0->m5D8 = 0x43000000;
    p0->m5DC = 0x43000000;
    p0->m5E0 = 0;
    p0->m5E4 = 0;
    p0->m5E8 = 0;
    p0->m5EC = 0;
    p0->m63C = 0xBF800000;
    p0->m77C = 0x41700000;
    p0->m780 = 0;
    p0->m788 = 0;
    ModelObjExInit_1b0bf0(p0);
}
