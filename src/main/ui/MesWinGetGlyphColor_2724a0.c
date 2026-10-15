#include "types.h"

#pragma divbyzerocheck on

typedef struct {
    u8 b[8];
} ColorS;

typedef union {
    s64 v;
    u8 b[8];
} Color;

typedef struct {
    s64 e[0x195C / 8];
    u8 pad[4];
    u8 alpha;
    u8 pad195D[0x1CFC - 0x195D];
    s32 ids[0x28];
    s16 w[8];
} Big;

extern Color PackRgba_26ffb0(s32);
extern s32 MesWinGetChoiceLineState_272360(Big *, s32);
extern s32 MesWinCharColorLookupMaybe_272690(u8);
extern s16 MesWinGetCharY_274d50(Big *, s32);
extern s32 D_0045F208[];

void MesWinGetGlyphColor_2724a0(Color *out, Big *arg1, s32 arg2)
{
    s32 i;
    s32 id;
    Color c;
    Color t;
    Color t2;
    Color d;
    s16 w;
    s16 k;
    s16 n;

    k = MesWinGetCharY_274d50(arg1, arg2);
    n = D_0045F208[0] + 4;
    i = k / n;
    id = arg1->ids[i];
    if (id != 0) {
        t = PackRgba_26ffb0(id);
        c = t;
        c.b[3] = (arg1->alpha * c.b[3]) / 128;
        *out = c;
        return;
    }
    t2 = PackRgba_26ffb0(MesWinCharColorLookupMaybe_272690(*(u8 *)((arg2 << 3) + (s32)arg1 + 0xCB)));
    d = t2;
    w = arg1->w[i];
    if (w >= 0) {
        d.b[3] = (w * d.b[3]) / 128;
    } else {
        d.b[3] = (arg1->alpha * d.b[3]) / 128;
    }
    switch (MesWinGetChoiceLineState_272360(arg1, i)) {
    case 1:
        d.b[0] >>= 1;
        d.b[1] >>= 1;
        d.b[2] >>= 1;
        break;
    case 2:
        d.b[3] = (arg1->alpha * 255) / 128;
        break;
    case 3:
        d.b[0] = 0;
        d.b[1] = 0;
        d.b[2] = 0;
        d.b[3] = (arg1->alpha << 6) / 128;
        break;
    case 4:
        d.b[3] = 0;
        break;
    }
    *out = d;
}
