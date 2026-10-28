/* rgp:protos */
#define RGP_SELF_MenuChoiceCursorSet_29c180 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct {
    u16 x0;
    u16 x2;
    u16 x4;
} E;

typedef struct {
    u8 pad0[0x4C4];
    s32 h;
} Obj;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern f32 D_0047D288;
extern u16 D_0047EC18[] __attribute__((section(".sdata")));

s32 MenuChoiceCursorSet_29c180(Obj *o, s16 sel, s32 flag) {
    s32 i;
    E *e;

    i = 0;
    do {
        if (i == sel) {
            UiSetSpriteSizeUvSize_28f670(o->h, 0x12F, 0, 0, 0, 0, i);
        } else {
            UiSetSpriteSizeUvSize_28f670(o->h, 0x12F, 0x84, 0x1D, 4, 4, i);
        }
        UiSetWidgetColor_2905b0(o->h, D_0047EC18[i], 1.0f, 1.0f, 1.0f, 1.0f);
        i++;
    } while (i < 2);
    e = ((E *)UiGetWidgetSprite_28fe10(o->h, 0x118, 0));
    if (e == NULL) {
        return 0;
    }
    e->x0 = 5;
    e->x2 = sel * 28 + 9;
    e->x4 = 0x84;
    UiSetWidgetsVisibleById_291110(o->h, 0x118, 1, 1);
    if ((s16)flag < 0) {
        { s32 k_ = sel * 2; k_ = *(u16 *)((s32)D_0047EC18 + k_); UiSetWidgetColor_2905b0(o->h, k_, D_0047D288, D_0047D288, D_0047D288, 1.0f); }
    }
    return 1;
}
