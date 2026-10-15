#include "types.h"

#pragma divbyzerocheck on

typedef struct {
    s16 v[5];
} S5_434690;

typedef struct {
    u8 pad0[0x4];
    s16 m4;
    s16 m6;
    s16 m8;
    s16 mA;
    u8 padC[0x8];
    s16 m14;
    s16 m16;
} Cur434690;

typedef struct {
    s32 h;
    u8 pad4[0xE0 - 4];
    s16 mE0;
} Obj434690;

extern "C" {
s16 TextEntryGridFindValidCellMaybe_433e90(void *, s8 *, s16, s16, s16);
void UiGetWidgetPos_2910a0(s32, s32, s32 *, s32 *);
void UiSetWidgetPos_290f60(s32, s32, s32, s32);
extern s16 D_00480360;
extern s16 D_00480370;
}

extern "C" bool TextEntryNameCursorAdvance_434690(Obj434690 *arg0, Cur434690 *arg1)
{
    S5_434690 hi;
    S5_434690 lo;
    s32 x;
    s32 y;
    bool r;
    s16 p;
    s16 l;

    {
        s16 *sp_ = &D_00480360;
        s16 *dp_ = hi.v;
        s32 n_ = 5;
        do {
            n_--;
            *dp_ = *sp_;
            sp_++;
            dp_++;
        } while (n_ > 0);
    }
    {
        s16 *sp_ = &D_00480370;
        s16 *dp_ = lo.v;
        s32 n_ = 5;
        do {
            n_--;
            *dp_ = *sp_;
            sp_++;
            dp_++;
        } while (n_ > 0);
    }
    arg1->m14++;
    r = false;
    if (arg1->m16 >= hi.v[arg0->mE0]) {
        l = *(s16 *)((u32)&lo.v[arg0->mE0]);
        if (arg1->m14 >= l) {
            if (l < arg1->m14) {
                r = true;
            }
            arg1->m14 = l;
        } else {
            p = TextEntryGridFindValidCellMaybe_433e90(arg0, (s8 *)arg0 + 0x197, arg1->m14 + arg1->m16 * 29, 0, 1);
            arg1->m14 = p % 29;
            arg1->m16 = p / 29;
        }
    } else if (arg1->m14 > 28) {
        arg1->m14 = 0;
        arg1->m16++;
    } else {
        p = TextEntryGridFindValidCellMaybe_433e90(arg0, (s8 *)arg0 + 0x197, arg1->m14 + arg1->m16 * 29, 0, 1);
        arg1->m14 = p % 29;
        arg1->m16 = p / 29;
    }
    UiGetWidgetPos_2910a0(arg0->h, 2, &x, &y);
    UiSetWidgetPos_290f60(arg0->h, 7, x + (arg1->m4 + arg1->m14 * arg1->m8), y + (arg1->m6 + arg1->m16 * arg1->mA));
    return r;
}
