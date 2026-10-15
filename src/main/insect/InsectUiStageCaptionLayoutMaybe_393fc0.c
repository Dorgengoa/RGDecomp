#include "types.h"
#pragma divbyzerocheck on
typedef struct E {
    s16 x0;
    s16 x2;
    s16 x4;
    s16 x6;
    s16 x8;
    s16 xA;
    s16 xC;
    s16 xE;
    s32 x10;
    s32 x14;
    s16 x18;
    s16 x1A;
    s16 x1C;
    s16 x1E;
} E;

typedef struct A {
    u8 pad0[0x20];
    E *p20;
} A;

void InsectUiStageCaptionLayoutMaybe_393fc0(s32 pad0, A *arg1, s32 arg2)
{
    E *t;
    E *e;
    s32 i;
    s32 n;

    if (arg1 == NULL) {
        return;
    }
    e = arg1->p20;
    if (e == NULL) {
        return;
    }
    {
        t = e;
        i = 0;
        do {
            e->x2 = -1;
            i++;
            e->x0 = -1;
            e->xE = 0;
            e->x6 = 0;
            e->xC = 0;
            e->x4 = 0;
            e->xA = 0;
            e->x8 = 0;
            e->x14 = 0;
            e->x10 = 0;
            e->x1A = 0;
            e->x18 = 0;
            e->x1C = 0;
            e++;
        } while (i < 5);
        if (arg2 != 4) {
            arg2 = arg2 + 1;
            t[0].x0 = 0;
            t[0].x2 = 0;
            t[0].xC = 0x2C;
            t[0].x4 = 0x2C;
            t[0].xE = 0x2E;
            t[0].x6 = 0x2E;
            t[0].x8 = 0xF6;
            t[0].xA = 0x40;
            t[1].x0 = 0x2C;
            t[1].x2 = 0;
            t[1].xC = 0x2C;
            t[1].x4 = 0x2C;
            t[1].xE = 0x2E;
            t[1].x6 = 0x2E;
            t[1].x8 = arg2 % 3 * t[1].xC + 0xF6;
            t[1].xA = arg2 / 3 * t[1].xE + 0x40;
            t[2].x0 = 0x58;
            t[2].x2 = 0;
            t[2].xC = 0x2C;
            t[2].x4 = 0x2C;
            t[2].xE = 0x2E;
            t[2].x6 = 0x2E;
            t[2].x8 = 0x14E;
            t[2].xA = 0x6E;
            t[3].x0 = 0x84;
            t[3].x2 = 0;
            t[3].xC = 0x2C;
            t[3].x4 = 0x2C;
            t[3].xE = 0x2E;
            t[3].x6 = 0x2E;
            t[3].x8 = 0x14E;
            t[3].xA = 0x9C;
        } else {
            t[0].x0 = 0;
            t[0].x2 = 0;
            t[0].xC = 0x84;
            t[0].x4 = 0x84;
            t[0].xE = 0x2E;
            t[0].x6 = 0x2E;
            t[0].x8 = 0xF6;
            t[0].xA = 0x9C;
        }
    }
}
