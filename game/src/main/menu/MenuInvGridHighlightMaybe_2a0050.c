/* rgp:protos */
#define RGP_SELF_MenuInvGridHighlightMaybe_2a0050 1
#include "port/game_protos.h"
#line 1
#pragma opt_dead_assignments off
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern s32 D_004659F0[0x10];
extern s32 D_004659F8[0x10];
extern f32 D_0047D40C;
extern f32 D_0047D488;

s32 MenuInvGridHighlightMaybe_2a0050(u8 *arg0, s32 arg1)
{
    s32 y;
    s32 h;
    s32 v;
    s32 w;
    s32 x;
    s32 idx;
    s32 i;
    u8 *g;

    g = ((u8 *)GetGameData_1fede0());
    y = 0;
    w = D_004659F0[0];
    h = D_004659F8[0];
    for (; y < h; y++) {
        for (x = 0; x < w; x++) {
            idx = x + y * w;
            UiSetSpriteFlags_290bd0(*(s32 *)arg0, 0x76, (long long)(0x238), -1, idx, 0);
            UiSetSpriteFlags_290bd0(*(s32 *)arg0, 0x74, (long long)(8), -1, idx, 0);
            if (arg1 != 0) {
                v = ((s32)InvFindByCategoryIndex_3c86e0(*(s32 *)(g + 0x18), 0, *(s8 *)(arg0 + 0x11), x, y, 0));
                if (v != 0 && ((unsigned char)ItemIsInsectFood_3d45b0(v)) != 0) {
                    UiSetSpriteFlags_290bd0(*(s32 *)arg0, 0x76, (long long)(8), 1, idx, 0);
                    UiSetSpriteFlags_290bd0(*(s32 *)arg0, 0x74, (long long)(8), 1, idx, 0);
                }
            }
        }
    }
    if (arg1 != 0) {
        UiSetWidgetColor_2905b0(*(s32 *)arg0, 0x75, D_0047D40C, D_0047D40C, D_0047D40C, 1.0f);
        { f32 o = 1.0f; UiSetWidgetColor_2905b0(*(s32 *)arg0, 0x74, D_0047D488, D_0047D488, D_0047D488, o); }
    } else {
        UiSetWidgetColor_2905b0(*(s32 *)arg0, 0x75, 1.0f, 1.0f, 1.0f, 1.0f);
        UiSetWidgetColor_2905b0(*(s32 *)arg0, 0x74, 1.0f, 1.0f, 1.0f, 1.0f);
        for (i = 0; i < w * h; i++) {
            UiSetSpriteFlags_290bd0(*(s32 *)arg0, 0x76, (long long)(0x20), 1, i, 0);
        }
    }
    return 1;
}
