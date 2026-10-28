/* rgp:protos */
#define RGP_SELF_MemZero 1
#define RGP_SELF_MenuItemModelPopInState_2a8030 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct V4 {
    f32 x;
    f32 y;
    f32 z;
    f32 w;
} V4;

typedef struct Desc {
    u8 pad0[0xC];
    s32 fC;
    u8 pad10[0xA0];
} Desc;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern f32 D_0047D278 __attribute__((section(".sdata")));
extern f32 D_0047D578 __attribute__((section(".sdata")));
extern f32 D_0047D5A4;
extern f32 D_0047D5A8;
extern void *D_0048235C;
extern s32 D_00482360;
extern void *D_00482364;
extern u8 *D_00482374;
extern void *D_004823D8;
extern s16 D_00482488;
extern u8 *D_004824BC;
extern f32 D_004824E0;
extern f32 D_004824E4;
extern u8 D_004DB6F0[0x100];

static inline void MemZero(u8 *q, u32 n)
{
    if (q != 0) {
        do {
            *q = 0;
            n--;
            q++;
        } while (n != 0);
    }
}

s32 MenuItemModelPopInState_2a8030(void)
{
    Desc d __attribute__((aligned(16)));
    V4 v __attribute__((aligned(16)));
    s16 n;
    f32 f;

    n = 0;
    f = D_004824E0 + D_0047D578;
    D_004824E0 = f;
    {
        f32 lim = D_0047D278;
        if (!(f < lim)) {
            n++;
            D_004824E0 = lim;
        }
    }
    f = D_004824E4 + D_0047D5A4;
    D_004824E4 = f;
    if (!(f < 1.0f)) {
        n++;
        D_004824E4 = 1.0f;
    }
    {
        f32 e = D_004824E0;
        u8 *o = D_004824BC;
        MemZero((u8 *)&v, 16);
        v.x = e;
        v.y = e;
        v.z = e;
        ModelSetScale_150ff0(o, &v);
    }
    *(f32 *)(D_004824BC + 0x170) = D_004824E4;
    if (n >= 2) {
        D_00482488 = 1;
        UiSetWidgetPos_290f60(D_00482360, 0x140, -0x46, 0xEA);
        UiFadeWidgetAlpha_290690(D_00482360, 0x140, 1.0f, D_0047D5A8, -1.0f);
        MenuInvGridHighlightMaybe_2a0050(D_00482374, 1);
        UiSetWidgetsVisibleById_291110(D_00482360, 0x36, 1, 1);
        UiSetWidgetPos_290f60(D_00482360, 0x36, 0x50, -0x26);
        MsgFormatParamsCtor_28aa00(&d);
        d.fC = *(s32 *)(D_00482374 + 0x6C);
        MsgFormat_28a9a0(D_004DB6F0, MsgTableLookup_28aa30(D_004823D8, 0x3EC), &d, 1);
        UiSetTextString_28f510(D_00482360, 0x36, D_004DB6F0, 0);
        UiSetTextCenteredX_28f300(D_00482360, 0x36, 0xE8, 0);
        UiEntryListSelectByTag_28ea90(D_00482364, 3, 0);
        UiFadeWidgetAlpha_290690(D_00482360, 0x227, 1.0f, D_0047D5A4, -1.0f);
        UiFadeWidgetAlpha_290690(D_00482360, 0x78, 1.0f, D_0047D5A4, -1.0f);
        StateMachineSetState_28ede0(D_0048235C, 9, 0);
    }
    return 1;
}
