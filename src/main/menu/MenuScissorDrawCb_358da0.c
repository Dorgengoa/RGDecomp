#include "types.h"

typedef struct P {
    u8 pad0[0x138];
    s32 handle;
    u8 pad13c[0x154-0x13C];
    s32 x1E8;
    s32 x1EC;
    s32 x1F0;
    s32 x1F4;
} P;

extern void *UiEntryListGetCurrentData_28ec60(s32);
extern void GsPktWriteAD_13ec80(s32, s32, s64);
extern void GsPktClose_13f5b0(s32);
extern void GsPktOpenPrim_13f730(s32, s32);
extern s32 DrawEnvGetHeight_1451d0(s32);
extern s32 DrawEnvGetWidth_1451e0(s32);
extern s32 GetDrawCtx_15de80(void);
extern P * D_00482380;

s32 MenuScissorDrawCb_358da0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4)
{
    s32 x;
    s32 y;
    s32 x2;
    s32 y2;
    s32 t;
    s32 w;
    s32 h;
    P *p;
    s64 z;
    u8 *item;

    if (arg4 != 0) {
        if (arg0 == 0) {
            return 1;
        }
        GsPktOpenPrim_13f730(arg0, 6);
        item=UiEntryListGetCurrentData_28ec60(D_00482380->handle);
        x = D_00482380->x1E8 + 0x77;
        y = D_00482380->x1EC + 0x4E + *(s16 *)(item+0x12) * *(s16 *)(item+6);
        x2 = x + (D_00482380->x1F0 + 1);
        y2 = y + (D_00482380->x1F4 + 1);
        z = (s64)x|((s64)x2 << 16)|((s64)y << 32);
        GsPktWriteAD_13ec80(arg0, 0x40, z | ((s64)y2 << 48));
        GsPktClose_13f5b0(arg0);
        return 1;
    }
    if (arg0 == 0) {
        return 1;
    }
    t = GetDrawCtx_15de80();
    w = DrawEnvGetWidth_1451e0(t);
    h = DrawEnvGetHeight_1451d0(t);
    GsPktOpenPrim_13f730(arg0, 6);
    GsPktWriteAD_13ec80(arg0, 0x40, ((s64)(w - 1) << 16) | ((s64)(h - 1) << 48));
    GsPktClose_13f5b0(arg0);
    return 1;
}
