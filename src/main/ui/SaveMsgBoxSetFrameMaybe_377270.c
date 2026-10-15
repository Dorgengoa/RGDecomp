#include "types.h"

extern void UiSetSpriteUvW_28f850(s32, u16, s32, s32);
extern void UiSetSpriteW_28fbf0(s32, u16, s32, s32);
extern void UiSetSpritePos_28fd10(s32, u16, s32, s32, s32);
extern s8 D_00463B18[];
extern u16 D_0047FB04;
extern f32 D_0047FB08;
extern f32 D_0047FB0C;
extern f32 D_0047FB10;

void SaveMsgBoxSetFrameMaybe_377270(s32 arg0, s32 arg1, s32 arg2, s32 arg3)
{
    f32 w[3];
    s32 v;
    s32 *ip;
    s32 pos;
    s32 i;

    if (arg0 == 0) {
        return;
    }
    if (arg2 < 0) {
        for (i = 0; i < 3; i++) {
            UiSetSpriteW_28fbf0(arg0, D_0047FB04, 0, i + 11);
            UiSetSpriteUvW_28f850(arg0, D_0047FB04, 0, i + 11);
        }
        return;
    }
    v = arg3 - 20;
    w[0] = D_0047FB08;
    w[1] = D_0047FB0C;
    w[2] = D_0047FB10;
    ip = (s32 *)&w[1];
    *ip = v;
    if (v < 0) {
        *ip = 0;
    }
    pos = arg1;
    for (i = 0; i < 3; i++) {
        UiSetSpritePos_28fd10(arg0, D_0047FB04, pos, arg2, i + 11);
        UiSetSpriteW_28fbf0(arg0, D_0047FB04, ((s32 *)w)[i], i + 11);
        UiSetSpriteUvW_28f850(arg0, D_0047FB04, D_00463B18[i], i + 11);
        pos += ((s32 *)w)[i];
    }
}
