#include "types.h"

typedef struct Ent {
    s16 x;
    s16 y;
    u8 pad[0x1C];
} Ent;

extern void GsPktSetTexFilter_13e3d0(s32, s32);
extern void GsPktSetTextured_13e400(s32, s32);
extern void GsPktSetRGBAQ_13ee40(s32, s32, s32, s32, s32);
extern void GsPktSetXYZf_13f060(s32, f32, f32, f32);
extern void GsPktSetXYZPixel_13f110(s32, s32, s32, s32);
extern void GsPktClose_13f5b0(s32);
extern void GsPktOpenPrim_13f730(s32, s32);
extern void GsPktSetupUiDrawState_2932b0(void);
extern s32 SaveMenuIconBitTestMaybe_37b390(s32, s32);
extern s32 SaveMenuIconCellLookupMaybe_37b3d0(Ent *);
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
    GsPktSetupUiDrawState_2932b0();
    GsPktSetTextured_13e400(arg0, 0);
    GsPktSetTexFilter_13e3d0(arg0, 0);
    for (i = 0; i < 8; i++, p++) {
        if (p->x == -1) {
            return;
        }
        r = SaveMenuIconCellLookupMaybe_37b3d0(p);
        if (r < 0) continue;
        if (SaveMenuIconBitTestMaybe_37b390(r, arg1) <= 0) continue;
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
