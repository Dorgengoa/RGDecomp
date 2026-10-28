/* rgp:protos */
#define RGP_SELF_normal_LeaderHudReset_506ef0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* normal 0x00506EF0 -- reset of the same object normal_FUN_005062F0 resets,
 * one layer up.  `lui 0x3F800000 / sw` is mwcc storing the f32 constant 1.0f
 * through an INTEGER register, not an s32 store. */
typedef struct Obj {
    u8   pad000[0x5C];
    s8   f05C;
    u8   pad05D[0x94 - 0x5D];
    void *f094;
    s16  f098;
    u8   pad09A[2];
    f32  f09C;
    f32  f0A0;
    s8   f0A4;
    u8   pad0A5[1];
    s16  f0A6;
    u8   pad0A8[0xB0 - 0xA8];
    f32  f0B0;
    f32  f0B4;
    f32  f0B8;
    f32  f0BC;
} Obj;

extern f32   D_0047DADC;
extern f32   D_0047D278;
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 normal_LeaderHudReset_506ef0(Obj *p)
{
    f32 a;
    f32 b;

    UiPageClearMemStack_289c50(p);
    normal_LeaderHudSetField70Related_506b40(p, -1);
    normal_LeaderHudSetField74Related_506b60(p, 0);
    normal_LeaderHudSetBannerBlinking_506af0(p, 0);
    normal_LeaderHudSetBannerCountdown_506ab0(p, 0x1E);
    normal_LeaderHudSetField78Related_506960(p, 0, 0.0f, 0.0f, 0.0f);
    normal_LeaderHudSetField85Related_506950(p, -1);
    normal_LeaderHudSetField90Related_506940(p, 0);
    p->f0B0 = 1.0f;
    a = D_0047DADC;
    p->f0B8 = 0.0f;
    b = D_0047D278;
    p->f0B4 = 0.0f;
    p->f0BC = 0.0f;
    p->f098 = 0;
    p->f09C = a;
    p->f0A0 = b;
    p->f0A4 = 0;
    p->f0A6 = 0;
    p->f094 = SceneSoundGetSlot0HandleCur_207df0();
    p->f05C = 0;
    return 1;
}
