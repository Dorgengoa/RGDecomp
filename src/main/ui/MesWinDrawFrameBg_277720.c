#include "types.h"

typedef struct {
    s32 x;
    s32 y;
    s32 w;
    s32 h;
} Rect;

extern void GsPktSetRGBAQ_13ee40(s32, s32, s32, s32, s32);
extern void GsPktSetXYZPixel_13f110(s32, s32, s32, s32);
extern void GsPktClose_13f5b0(s32);
extern void GsPktOpenPrim_13f730(s32, s32);
extern void FontPktSetFlatState_26fd20(void);

void MesWinDrawFrameBg_277720(s32 arg0, Rect *rp, s32 arg2, s32 arg3, s32 arg4, s32 arg5) {
    Rect r;
    s32 y1;
    s32 y;
    s32 a;
    s32 y3;
    s32 y2;
    s32 x3;
    s32 b;
    s32 i;
    s32 x2;

    r = *rp;
    if (arg0 == 0) {
        return;
    }
    FontPktSetFlatState_26fd20();
    y = r.y;
    i = 0;
    y1 = y + 4;
    y2 = y + r.h;
    y3 = y2 - 4;
    x2 = r.x + *(volatile s32 *)&r.w;
    x3 = x2 - 0x30;
    do {
        GsPktOpenPrim_13f730(arg0, 4);
        if (i == 0) {
            b = y1;
            a = y;
        } else if (i == 1) {
            a = y1;
            b = y3;
        } else {
            a = y3;
            b = y2;
        }
        GsPktSetRGBAQ_13ee40(arg0, arg2, arg3, arg4, 0);
        GsPktSetXYZPixel_13f110(arg0, r.x, a, 0);
        GsPktSetXYZPixel_13f110(arg0, r.x, b, 0);
        if (i != 0) {
            GsPktSetRGBAQ_13ee40(arg0, arg2, arg3, arg4, arg5);
        }
        GsPktSetXYZPixel_13f110(arg0, r.x + 0x30, a, 0);
        if (i == 0) {
            GsPktSetRGBAQ_13ee40(arg0, arg2, arg3, arg4, arg5);
        }
        if (i == 2) {
            GsPktSetRGBAQ_13ee40(arg0, arg2, arg3, arg4, 0);
        }
        GsPktSetXYZPixel_13f110(arg0, r.x + 0x30, b, 0);
        if (i == 0) {
            GsPktSetRGBAQ_13ee40(arg0, arg2, arg3, arg4, 0);
        }
        if (i == 2) {
            GsPktSetRGBAQ_13ee40(arg0, arg2, arg3, arg4, arg5);
        }
        GsPktSetXYZPixel_13f110(arg0, x3, a, 0);
        if (i == 0) {
            GsPktSetRGBAQ_13ee40(arg0, arg2, arg3, arg4, arg5);
        }
        if (i == 2) {
            GsPktSetRGBAQ_13ee40(arg0, arg2, arg3, arg4, 0);
        }
        GsPktSetXYZPixel_13f110(arg0, x3, b, 0);
        if (i != 2) {
            GsPktSetRGBAQ_13ee40(arg0, arg2, arg3, arg4, 0);
        }
        GsPktSetXYZPixel_13f110(arg0, x2, a, 0);
        GsPktSetXYZPixel_13f110(arg0, x2, b, 0);
        GsPktClose_13f5b0(arg0);
        i++;
    } while (i < 3);
}
