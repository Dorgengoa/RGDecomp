/* rgp:protos */
#define RGP_SELF_factory_FactoryBlueprintCursorBob_4fb0f0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct Sub {
    s16 f00;
    s16 f02;
    s16 f04;
    s16 f06;
    u8  pad08[0x8];
    s16 f10;
    s16 f12;
} Sub;

typedef struct Hdr {
    u8  pad00[0x4];
    Sub f04;
} Hdr;

typedef struct Scr {
    u8    pad00[0x64];
    f32   f64;
    u8    pad68[0x14];
    u8    f7C;
    u8    pad7D[0x3];
    void *f80;
    void *f84;
    u8    pad88[0x10];
    u8    f98[0x4];
} Scr;

extern f32   D_0047D3D0;                        /* _gp - 0x7DA0 */
extern f32   D_0047D3EC;                        /* _gp - 0x7D84 */
extern void *D_004807EC;                        /* _gp - 0x4984 */

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

void factory_FactoryBlueprintCursorBob_4fb0f0(Scr *o, s32 flag)
{
    Hdr *h;
    Sub *m;
    f32  s;
    s32  x;
    s32  y;

    o->f64 = 0.15707964f + o->f64;
    if (o->f64 > 0.0f) {
        o->f64 = -3.1415927f;
    }
    s = 6.0f * Sinf_128fd0(o->f64);
    switch (o->f7C) {
    case 0:
        h = ((Hdr *)UiEntryListFindByTag_28ea40(o->f84, 0x88CC));
        m = &h->f04;
        x = (s32)(s + (f32)(m->f00 + m->f10 * m->f04));
        y = (s32)(s + (f32)(m->f02 + m->f12 * m->f06));
        if (flag != 0) {
            UiSetWidgetPos_290f60(o->f80, 0x40, x, y);
        } else {
            UiMoveWidgetUniform_290f50(o->f80, 0x40, x, y, 0.5f, 0);
        }
        UiSelFrameSetPos_28daa0(o->f98, 0x26, m->f10 * m->f04 + 0x1A, m->f12 * m->f06 + 0x1A);
        UiSelFrameAnimStep_28d820(o->f98, 0x26);
        break;
    case 1:
        h = ((Hdr *)UiEntryListFindByTag_28ea40(o->f84, 0x88D6));
        m = &h->f04;
        x = (s32)(s + (f32)(m->f00 + 0x37 + m->f10 * m->f04));
        y = m->f02 + 0x36;
        if (flag != 0) {
            UiSetWidgetPos_290f60(D_004807EC, 0x97, x, y);
        } else {
            UiMoveWidgetUniform_290f50(D_004807EC, 0x97, x, y, 0.5f, 0);
        }
        break;
    case 2:
        h = ((Hdr *)UiEntryListFindByTag_28ea40(o->f84, 0x88E0));
        m = &h->f04;
        x = (s32)(s + (f32)(m->f00 + 0x37 + m->f10 * m->f04));
        y = m->f02 + 0x36;
        if (flag != 0) {
            UiSetWidgetPos_290f60(D_004807EC, 0x97, x, y);
        } else {
            UiMoveWidgetUniform_290f50(D_004807EC, 0x97, x, y, 0.5f, 0);
        }
        break;
    case 3:
    case 4:
    case 6:
    case 9:
        h = ((Hdr *)UiEntryListFindByTag_28ea40(o->f84, 0x88EA));
        m = &h->f04;
        x = (s32)(s + (f32)(m->f00 + m->f10 * m->f04));
        y = m->f02;
        if (flag != 0) {
            UiSetWidgetPos_290f60(D_004807EC, 0x97, x, y);
        } else {
            UiMoveWidgetUniform_290f50(D_004807EC, 0x97, x, y, 0.5f, 0);
        }
        break;
    }
}
