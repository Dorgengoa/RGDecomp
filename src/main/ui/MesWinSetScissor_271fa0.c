#include "types.h"

typedef struct Obj {
    u8 pad0[0x40];
    s32 x;
    s32 y;
    u8 pad48[8];
    s16 minY;
    s16 maxY;
    s16 defW;
    s16 defH;
    u8 pad58[0xA8 - 0x58];
    s32 w;
    s32 h;
    u8 padB0[0x1C4C - 0xB0];
    s32 rx;
    s32 ry;
    s32 rw;
    s32 rh;
} Obj;

extern void GsPktWriteAD_13ec80(s32, s32, s64);
extern s32 DrawEnvGetHeight_1451d0(void *);
extern s32 DrawEnvGetWidth_1451e0(void *);
extern void *GetDrawCtx_15de80(void);
extern s32 MesWinGetClipMode_2721d0(Obj *);
extern s32 MesWinGetLineFixedPos_272440(Obj *, s32);

void MesWinSetScissor_271fa0(Obj *obj, s32 arg1, s32 arg2)
{
    void *g;
    s32 sw;
    s32 sh;
    s32 x0;
    s32 x1;
    s32 y0;
    s32 y1;

    g = GetDrawCtx_15de80();
    sw = DrawEnvGetWidth_1451e0(g);
    sh = DrawEnvGetHeight_1451d0(g);
    if (!(MesWinGetClipMode_2721d0(obj) & 0xFF)) {
        GsPktWriteAD_13ec80(arg1, 0x40, ((s64)obj->maxY << 48) | (((s64)(sw - 1) << 16) | ((s64)obj->minY << 32)));
        return;
    }
    if (MesWinGetLineFixedPos_272440(obj, arg2) != 0) {
        return;
    }
    if ((MesWinGetClipMode_2721d0(obj) & 0xFF) == 1) {
        obj->rx = obj->x;
        obj->ry = obj->y - 1;
        if (obj->w > 0) {
            obj->rw = obj->w;
        } else {
            obj->rw = obj->defW;
        }
        if (obj->h > 0) {
            obj->rh = obj->h;
        } else {
            obj->rh = obj->defH;
        }
    }
    x0 = obj->rx;
    y0 = obj->ry;
    x1 = x0 + obj->rw;
    y1 = y0 + obj->rh;
    if (x0 < 0) {
        x0 = 0;
    }
    if (x1 < 0) {
        x1 = 0;
    }
    if (sw - 1 < x0) {
        x0 = sw - 1;
    }
    if (sw - 1 < x1) {
        x1 = sw - 1;
    }
    if (y0 < 0) {
        y0 = 0;
    }
    if (y1 < 0) {
        y1 = 0;
    }
    if (sh - 1 < y0) {
        y0 = sh - 1;
    }
    if (sh - 1 < y1) {
        y1 = sh - 1;
    }
    if (y0 < obj->minY) {
        y0 = obj->minY;
    }
    if (obj->maxY < y1) {
        y1 = obj->maxY;
    }
    GsPktWriteAD_13ec80(arg1, 0x40, ((s64)y1 << 48) | (((s64)y0 << 32) | ((s64)x0 | ((s64)x1 << 16))));
}
