/* rgp:protos */
#define RGP_SELF_RevelationBoardStateInit_34da10 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
extern s32 memset(void *, s32, s32);
/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    s32 m00;
    s32 m04;
    s32 m08;
    u8 pad00C[0x4];
    s16 m10;
    s16 m12;
    u8 pad014[0x4];
    s16 m18;
    u8 pad01A[0x752];
    s16 m76C;
    s16 m76E;
    s16 m770;
    s16 m772;
    s32 m774;
    u8 pad778[0x4];
    s32 m77C;
    u8 pad780[0x20];
    s16 m7A0;
    u8 m7A2;
};

s32 RevelationBoardStateInit_34da10(struct Obj0 *p0, s32 p1)
{
    s32 r0;
    s32 r1;
    s32 t0;
    s32 r2;

    p0->m00 = 0;
    if (p1 != 0) {
        p0->m00 = p1;
    }
    r0 = SceneSoundGetSlot0HandleCur_207df0();
    p0->m08 = r0;
    p0->m774 = 0;
    p0->m10 = 0;
    p0->m12 = 0;
    p0->m18 = 0;
    r1 = ((s32)memset((struct Obj0 *)((u8 *)p0 + 0x1C), 0, 0x750));
    p0->m76C = -1;
    p0->m76E = 0;
    p0->m770 = 0;
    p0->m772 = 0;
    p0->m04 = 0;
    p0->m7A0 = 0;
    t0 = p0->m00;
    r2 = UiGetWidgetColor_2904b0(t0, 0x47);
    p0->m77C = r2;
    p0->m7A2 = 0;
    return r2;
}
