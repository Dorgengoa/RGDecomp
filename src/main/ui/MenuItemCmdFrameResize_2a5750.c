#include "types.h"

typedef struct {
    u8 pad0[0xC4];
    s16 xC4;
    u8 padC6[0x1E];
    s16 xE4;
    u8 padE6[0x1A];
    s16 x100;
    u8 pad102[0x20];
    s16 x122;
    u8 pad124[2];
    s16 x126;
    u8 pad128[0x18];
    s16 x140;
    u8 pad142[4];
    s16 x146;
    u8 pad148[0x1A];
    s16 x162;
    u8 pad164[0x1E];
    s16 x182;
    s16 x184;
    u8 pad186[0x1A];
    s16 x1A0;
    s16 x1A2;
} Obj;

extern void UiSetSpriteSizeUvSize_28f670(s32, s32, s32, s32, s32, s32, s32);
extern Obj *UiGetWidgetSprite_28fe10(s32, s32, s32);
extern s16 D_00450DD0[];
extern s16 D_00450DD2[];

s32 MenuItemCmdFrameResize_2a5750(s32 *arg0, s32 arg1, s32 arg2)
{
    Obj *o;
    s16 *t;
    s32 i;
    s16 v;

    o = UiGetWidgetSprite_28fe10(*arg0, arg1, 0);
    if (o == NULL) {
        return 0;
    }
    v = *(s16 *)((u8 *)D_00450DD2 + arg2 * 4) - 0xE;
    t = (s16 *)((u8 *)D_00450DD0 + arg2 * 4);
    i = 0;
    o->x184 = v;
    o->xE4 = v;
    v = t[0] * 0x1B - 8;
    o->x146 = v;
    o->x126 = v;
    do {
        if (i < t[0]) {
            UiSetSpriteSizeUvSize_28f670(*arg0, arg1, t[1], 0x1B, 4, 4, i);
            if (i > 0) {
                UiSetSpriteSizeUvSize_28f670(*arg0, arg1, o->xE4 + 0xC, 4, 6, 4, i + 0xD);
            }
        } else {
            UiSetSpriteSizeUvSize_28f670(*arg0, arg1, 0, 0, 0, 0, i);
            if (i > 0) {
                UiSetSpriteSizeUvSize_28f670(*arg0, arg1, 0, 0, 0, 0, i + 0xD);
            }
        }
        i++;
    } while (i < 6);
    v = o->xC4 + o->xE4;
    o->x1A0 = v;
    o->x100 = v;
    v = o->x122 + o->x126;
    o->x1A2 = v;
    o->x182 = v;
    o->x162 = v;
    o->x140 = o->xE4 + 0x11;
    return 1;
}
