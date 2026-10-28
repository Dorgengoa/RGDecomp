/* rgp:protos */
#define RGP_SELF_CompleteCheckCategoryMsgState_39e0b0 1
#include "port/game_protos.h"
#line 1
#pragma opt_propagation off
#pragma opt_loop_invariants off
#include "types.h"

typedef struct Desc {
    s32 a;
    void *b;
    u8 pad08[0x8];
    s32 x10;
    s32 x14;
    s32 x18;
    s32 x1C;
    u8 pad20[0x14];
} Desc;

typedef struct Item {
    u8 pad00[0xC];
    u32 color;
} Item;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern void *memset(void *, s32, u32);
extern f32 D_0047D288;
extern u8 D_00483690;
extern u8 D_004B2570[0x400];
extern u8 D_004E96B0[0x400];
extern u8 D_004E96D0[0x400];

s32 CompleteCheckCategoryMsgState_39e0b0(s32 unused, s32 flag) {
    Desc d __attribute__((aligned(16)));
    s32 i;
    Item *p;

    if (flag != 0) {
        memset(&d, 0, sizeof(Desc));
        d.a = ((s32)UiGetWidgetSprite_28fe10(D_004E96B0, 8, 0));
        d.b = ((Item *)UiGetWidgetText_28f620(D_004E96B0, 8, 0));
        d.x10 = 0x3C;
        d.x18 = 0x1C;
        d.x14 = 0xC;
        d.x1C = 8;
        UiWindowFitToText_28d0c0(&d, 0, 0, 0);
        UiSetWidgetsVisibleById_291110(D_004E96B0, 8, 1, 1);
        UiEntryListSelectByTag_28ea90(D_004E96D0, 0x7532, 0);
        { f32 one = 1.0f; UiSetWidgetColor_2905b0(D_004E96B0, 1, D_0047D288, D_0047D288, D_0047D288, one); }
        i = 0;
        do {
            p = ((Item *)UiGetWidgetText_28f620(D_004E96B0, 6, i));
            if (p->color == 0xFF004040) {
                p->color = 0xFF002020;
            } else {
                p->color = 0xFF202020;
            }
        } while (++i < 17);
    } else {
        i = MenuGridCursorInput_28e170(D_004E96D0, D_004B2570, 0, 0);
        if ((u32)(i - 1) < 2) {
            UiSetWidgetColor_2905b0(D_004E96B0, 1, 1.0f, 1.0f, 1.0f, 1.0f);
            i = 0;
            do {
                p = ((Item *)UiGetWidgetText_28f620(D_004E96B0, 6, i));
                if (p->color == 0xFF002020) {
                    p->color = 0xFF004040;
                } else {
                    p->color = 0xFF303030;
                }
            } while (++i < 17);
            UiSetWidgetsVisibleById_291110(D_004E96B0, 8, 0, 1);
            StateMachineSetState_28ede0(&D_00483690, 0x7532, 0);
        }
    }
    return 1;
}
