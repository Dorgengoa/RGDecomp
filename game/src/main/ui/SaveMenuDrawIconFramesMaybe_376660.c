/* rgp:protos */
#define RGP_SELF_SaveMenuDrawIconFramesMaybe_376660 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct Ent {
    s16 x;
    s16 y;
    u8 pad[0x1C];
} Ent;

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
extern s8 D_00454030[][2];

void SaveMenuDrawIconFramesMaybe_376660(s32 arg0, s32 arg1, Ent *arg2, s32 arg3, s32 arg4, f32 alpha)
{
    s32 y;
    s32 by;
    s32 x;
    s32 a;
    s32 r;
    Ent *p;
    s32 bx;
    s32 i;
    s32 j;

    if (arg0 == 0 || arg2 == NULL) {
        return;
    }
    bx = arg3 - arg2->x - 4;
    a = 128.0f * alpha;
    by = arg4 - arg2->y - 4;
    p = arg2;
    GsPktSetupUiDrawState_2932b0((int)arg0);
    GsPktSetTextured_13e400(arg0, 0);
    GsPktSetTexFilter_13e3d0(arg0, 0);
    for (i = 0; i < 8; i++, p++) {
        if (p->x == -1) {
            return;
        }
        r = ((signed char)SaveMenuIconCellLookupMaybe_37b3d0(p));
        if (r < 0) continue;
        if (((unsigned char)SaveMenuIconBitTestMaybe_37b390(r, arg1)) <= 0) continue;
        x = bx + p->x;
        y = by + p->y;
        GsPktOpenPrim_13f730(arg0, 2);
        GsPktSetRGBAQ_13ee40(arg0, 0xD2, 0xD2, 0xD2, a);
        for (j = 0; j < 10; j++) {
            GsPktSetXYZPixel_13f110(arg0, x + D_00454030[j][0], y + D_00454030[j][1], 0);
            if (j == 4) {
                GsPktClose_13f5b0(arg0);
                GsPktOpenPrim_13f730(arg0, 2);
            }
        }
        GsPktClose_13f5b0(arg0);
        GsPktSetTexFilter_13e3d0(arg0, 1);
        GsPktOpenPrim_13f730(arg0, 2);
        GsPktSetRGBAQ_13ee40(arg0, 0xA, 0xA, 0xA, a);
        for (j = 10; j < 15; j++) {
            GsPktSetXYZf_13f060(arg0, ((f32)x + (f32)D_00454030[j][0]) - 0.5f, ((f32)y + (f32)D_00454030[j][1]) - 0.5f, 0.0f);
        }
        GsPktClose_13f5b0(arg0);
    }
}
