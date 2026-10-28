/* rgp:protos */
#define RGP_SELF_CaptionCfgInit_340240 1
#include "port/game_protos.h"
#line 1
#include "types.h"

extern void memset(void *, s32, s32);
/*rgp*/
/*rgp*/
/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    s32 m00;
    u8 pad004[0x14];
    s32 m18;
    u8 pad01C[0x34];
    s32 m50;
};

void CaptionCfgInit_340240(struct Obj0 *p0, s32 p1)
{
    s32 l0;

    p0->m00 = p1;
    l0 = 0;
    do {
        *(s16 *)((u8 *)p0 + (l0 << 1) + 0x4) = 0;
        *(s16 *)((u8 *)p0 + (l0 << 1) + 0xC) = 0;
        l0 = (l0 + 1);
    } while (l0 < 2);
    p0->m50 = 0;
    memset((struct Obj0 *)((u8 *)p0 + 0x1C), 0, 0x10);
    memset((struct Obj0 *)((u8 *)p0 + 0x2C), 0, 0x10);
    memset((struct Obj0 *)((u8 *)p0 + 0x3C), 0, 0x10);
    p0->m18 = 0;
    CaptionCfgSetGlyphBase_33fe70(p0, 0);
    CaptionCfgSetAltGlyphBase_33fe50(p0, 0);
    CaptionCfgSetImageMode_33fe30(p0, 0);
}
