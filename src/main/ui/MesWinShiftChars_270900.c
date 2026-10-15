#include "types.h"

typedef struct Obj {
    u8 pad0[0x5C];
    s16 hist[16];       /* 0x5C */
    u8 pad7C[0x18C4 - 0x7C];
    s16 slot[16];       /* 0x18C4 */
    s32 val[16];        /* 0x18E4 */
    s16 cnt;            /* 0x1924 */
    u8 pad1926[0x193C - 0x1926];
    s32 sum;            /* 0x193C */
} Obj;

extern void MesWinAddCharCount_274c60(Obj *, s32);
extern f32 MesWinGetTypeCursor_272b00(Obj *);
extern void MesWinSetTypeCursor_272b10(Obj *, f32);
extern void MesWinAddShownEnd_271670(Obj *, s32);
extern s32 MesWinGetShownStart_2716a0(Obj *);
extern void MesWinSetShownStart_2716b0(Obj *, s32);
extern s32 MesWinGetCharCode_274dd0(Obj *, s32);
extern void MesWinSetCharCode_274de0(Obj *, s32, s32);
extern s32 MesWinGetCharX_274d90(Obj *, s32);
extern void MesWinSetCharX_274da0(Obj *, s32, s32);
extern s32 MesWinGetCharY_274d50(Obj *, s32);
extern void MesWinSetCharY_274d60(Obj *, s32, s32);
extern s32 MesWinGetCharColor_274cd0(Obj *, s32);
extern void MesWinSetCharColor_274ce0(Obj *, s32, s32);
extern s32 MesWinGetCharAge_274c90(Obj *, s32);
extern void MesWinSetCharAge_274ca0(Obj *, s32, s32);
extern void MesWinAddCharY_274d10(Obj *, s32, s16);
extern void MesWinAddPenY_272ab0(Obj *, s32);
extern void MesWinAddScrollY_2716f0(Obj *, s32);
extern void MesWinAddScrollTarget_2716c0(Obj *, s32);
extern void MesWinAddPage_272210(Obj *, s32);

void MesWinShiftChars_270900(Obj *o, s32 n)
{
    s32 neg;
    s32 j;
    s32 i;
    s16 v;
    s32 w;
    s32 first;
    s32 m;
    s16 *p;

    neg = -n;
    MesWinAddCharCount_274c60(o, neg);
    MesWinSetTypeCursor_272b10(o, MesWinGetTypeCursor_272b00(o) - (f32)n);
    MesWinAddShownEnd_271670(o, neg);
    MesWinSetShownStart_2716b0(o, MesWinGetShownStart_2716a0(o) - n);
    for (j = n, i = 0; j < 0x300; j++, i++) {
        MesWinSetCharCode_274de0(o, i, MesWinGetCharCode_274dd0(o, j));
        MesWinSetCharX_274da0(o, i, MesWinGetCharX_274d90(o, j));
        MesWinSetCharY_274d60(o, i, MesWinGetCharY_274d50(o, j));
        MesWinSetCharColor_274ce0(o, i, MesWinGetCharColor_274cd0(o, j));
        MesWinSetCharAge_274ca0(o, i, MesWinGetCharAge_274c90(o, j));
    }
    for (; i < 0x300; i++) {
        MesWinSetCharCode_274de0(o, i, 0);
        MesWinSetCharX_274da0(o, i, 0);
        MesWinSetCharY_274d60(o, i, 0);
        MesWinSetCharColor_274ce0(o, i, 0);
        MesWinSetCharAge_274ca0(o, i, 0);
    }
    i = 0;
    do {
        p = &o->slot[i];
        if (n <= *p) {
            *p -= (s16)n;
        } else {
            *p = -1;
            o->val[i] = 0;
        }
        i++;
    } while (i < 16);
    first = -1;
    for (i = 0; i < 16; i++) {
        if (o->slot[i] == -1) {
            continue;
        }
        if (o->val[i] > 0) {
            first = i;
            break;
        }
    }
    if (first > 0) {
        for (m = 0; m < 16 - first; m++) {
            o->slot[m] = o->slot[first + m];
            o->val[m] = o->val[first + m];
        }
    }
    for (m = 16 - first; m < 16; m++) {
        o->slot[m] = -1;
        o->val[m] = 0;
    }
    o->cnt = 0;
    for (i = 0; i < 16; i++) {
        if (o->slot[i] == -1) {
            o->cnt = i;
            break;
        }
    }
    if (MesWinGetCharY_274d50(o, 0) != 0) {
        j = (s16)MesWinGetCharY_274d50(o, 0);
        n = -j;
        for (i = 0; i < 0x300; i++) {
            MesWinAddCharY_274d10(o, i, n);
        }
        MesWinAddPenY_272ab0(o, n);
        MesWinAddScrollY_2716f0(o, j);
        MesWinAddScrollTarget_2716c0(o, j);
        MesWinAddPage_272210(o, -1);
        o->sum -= o->hist[0];
        i = 0;
        do {
            o->hist[i] = o->hist[i + 1];
            i++;
        } while (i < 15);
        o->hist[15] = 0;
    }
}
