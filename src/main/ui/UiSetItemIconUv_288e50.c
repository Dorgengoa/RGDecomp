#include "types.h"
#pragma divbyzerocheck on

typedef struct {
    u8 pad0[0x4];
    s16 unk4;
    s16 unk6;
    s16 unk8;
    s16 unkA;
    s16 unkC;
    s16 unkE;
    u8 pad10[0xc];
    u16 unk1C;
} T288e50_arg0;

extern void UiIconGetSheetPos_288720(s32, s32, s16 *, s16 *);

s32 UiSetItemIconUv_288e50(T288e50_arg0 *arg0, s32 id, s32 x0, s32 y0) {
    s32 idx;
    s32 w;
    s32 h;
    s16 x;
    s16 y;
    f32 cx;
    f32 cy;
    f32 fx;
    s16 px;
    s16 py;

    if (arg0 == NULL) {
        return 0;
    }
    x = x0;
    y = y0;
    if (id >= 0) {
        idx = (id % 100) - 1;
        UiIconGetSheetPos_288720(id / 1000, (id % 1000) / 100, &px, &py);
        if (idx < 0 || idx > 0x40) {
            idx = 0;
        }
        h = 0x20;
        w = h;
        if (id == 0x8FD) {
            h = 0x28;
            w = h;
        }
        cx = (f32)(idx % 8);
        cy = (f32)((idx / 8) % 8);
        if (x == -1) {
            x = w;
        }
        if (y == -1) {
            y = h;
        }
        fx = cx * (f32)w;
        arg0->unk8 = (f32)px + fx;
        arg0->unkA = (f32)py + cy * (f32)h;
        if (!((f32)px + fx < 992.0f)) {
            w -= 1;
        }
        arg0->unkC = w;
        arg0->unkE = h;
        arg0->unk4 = x;
        arg0->unk6 = y;
        arg0->unk1C |= 2;
    } else {
        arg0->unkA = 0;
        arg0->unk8 = 0;
        arg0->unkE = 0;
        arg0->unkC = 0;
        arg0->unk6 = 0;
        arg0->unk4 = 0;
        arg0->unk1C |= 2;
    }
    return 1;
}
