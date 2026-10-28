/* rgp:protos */
#define RGP_SELF_InsectCageMenuDialogTwoButtonLayout_38c740 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct Desc {
    void *m0;
    s32 m4;
    s32 m8;
    s32 mC;
    s32 m10;
    s32 m14;
    s32 m18;
    s32 m1C;
    s32 m20;
    s32 m24;
    s32 m28;
    s32 m2C;
    s16 m30;
    s16 m32;
} Desc;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern void *memset(void *, s32, u32);
extern s8 D_00463E50[0x400];
extern s32 D_00483308;

void InsectCageMenuDialogTwoButtonLayout_38c740(void)
{
    s32 id;
    s32 y;
    Desc d __attribute__((aligned(16)));
    s32 t;
    s32 i;
    s32 x;
    void *p;
    s32 w;
    s32 h;

    id = D_00483308;
    UiSetWidgetPos_290f60(id, 0x75E4, 0, 0);
    UiSetWidgetPos_290f60(id, 0x75EE, 0, 0);
    memset(&d, 0, sizeof(d));
    p = UiGetWidgetSprite_28fe10(id, 0x75E4, 0);
    d.m0 = p;
    d.m4 = ((s32)UiGetWidgetText_28f620(id, 0x75E4, 0));
    d.m10 = 0x24;
    d.m14 = 0x46;
    d.m8 = 0;
    d.m18 = 0x12;
    d.mC = 0;
    d.m1C = 0xE;
    d.m20 = 0;
    d.m28 = 0x200;
    d.m24 = 0;
    d.m2C = 0x1C0;
    d.m30 = 4;
    UiWindowFitToText_28d0c0(&d, 0, 0, 0);
    UiGetWidgetTextSize_28f430(id, 0x75E4, &w, &h, 0);
    y = (h >> 1) + 0xDC;
    for (i = 0; i < 2; i++) {
        x = i * 0x50 + 0xBA;
        UiSetSpritePos_28fd10(id, 0x75EE, x, y, i);
        UiSetTextPos_28f5d0(id, 0x75EE, x + D_00463E50[i], y + 4, i + 1);
    }
    UiSetWidgetPos_290f60(id, 0x75F8, 0, *(s16 *)((u8 *)p + 2) + h + 0x12);
    p = UiGetWidgetSprite_28fe10(id, 0x75F8, 0);
    t = w + d.m10 - 0xC;
    InsectCageMenuDialogFrameLayoutMaybe_3908c0(p, t - 5, (long long)(0x100 - (t >> 1)), (long long)(0));
}
