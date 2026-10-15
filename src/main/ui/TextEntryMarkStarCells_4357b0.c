#include "types.h"

typedef struct {
    u8 pad0[0x1C];
    s16 x1C;
    u8 pad1E[2];
} P;

typedef struct {
    u8 pad0[0x20];
    P *p;
    P *q;
} E;

extern E *UiFindWidget_290460(s32, s32);

s32 TextEntryMarkStarCells_4357b0(s8 *o, s16 x, s32 y)
{
    E *e;
    P *p;
    P *q;
    s32 r;
    s32 c;
    s16 k;

    if (x < 0 || (s16)(u32)y < 0) {
        e = UiFindWidget_290460(*(s32 *)o, 0xE);
        if (e == NULL) {
            return 1;
        }
        p = e->p;
        if (p == NULL) {
            return 2;
        }
        for (r = 0; r < 6; r++) {
            for (c = 0; c < 29; c++, p++) {
                if ((o + (s16)r)[(s16)(c + r * 29) + 0x30] == '*') {
                    p->x1C = 8;
                } else {
                    p->x1C = 0;
                }
            }
        }
        return 0;
    }
    e = UiFindWidget_290460(*(s32 *)o, 0xE);
    if (e == NULL) {
        return 1;
    }
    p = e->p;
    if (p == NULL) {
        return 2;
    }
    k = x + (s16)y * 29;
    q = &p[k];
    if (((s16)y + (k + o))[0x30] == '*') {
        q->x1C = 8;
    } else {
        q->x1C = 0;
    }
    return 0;
}
