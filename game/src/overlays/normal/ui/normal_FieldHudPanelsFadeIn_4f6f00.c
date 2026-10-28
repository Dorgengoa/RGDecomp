/* rgp:protos */
#define RGP_SELF_normal_FieldHudPanelsFadeIn_4f6f00 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* normal 0x004F6F00 -- the long sibling of normal_FieldHudPanelsFadeOut_4f6ed0: one guard around a
 * thirteen-store reset, written in retail's EMISSION order.
 * One of the 55 unnamed functions. */
typedef struct Obj {
    u8  pad000[0x2B0];
    s16 f2B0;
    s16 f2B2;
    u8  pad2B4[0x378 - 0x2B4];
    s16 f378;
    u8  pad37A[0x37E - 0x37A];
    s16 f37E;
    u8  pad380[0x386 - 0x380];
    s16 f386;
    u8  pad388[0x3D4 - 0x388];
    s32 f3D4;

    s16 f3D8;
    s16 f3DA;
    u8  pad3DC[0x49C - 0x3DC];
    s16 f49C;
    s16 f49E;
    s16 f4A0;
    s16 f4A2;
    s16 f4A4;
    s16 f4A6;
} Obj;

void normal_FieldHudPanelsFadeIn_4f6f00(Obj *p)
{
    if (p->f378 != 0) {
        p->f386 = 0;
        p->f3D4 = -1;
        p->f2B0 = 1;
        p->f2B2 = 0;
        p->f49C = 0;
        p->f4A4 = 0;
        p->f49E = 0;
        p->f4A0 = 0;
        p->f3D8 = 0;
        p->f3DA = 0;
        p->f4A2 = 0;
        p->f37E = 0;
        p->f4A6 = 0;
    }
}
