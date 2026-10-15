#include "types.h"

/* Two guards; the 0xFE00/0xFF00 window is an && (both tests skip to the
   shared tail).  The tail writes an 8-byte record at +0xC4 indexed by the
   count read back from MesWinGetCharCount_274c70. */

typedef struct Rec {
    s16 m0;
    s16 m2;
    s16 m4;
    s8  m6;
    s8  m7;
} Rec;

extern s32  MesWinGetCharCount_274c70(void *o);
extern void MesWinPushPause_275d60(void *o, s32 a, s32 b);
extern s32  MesWinGetPenX_272ad0(void *o);
extern s32  MesWinGetPenY_272aa0(void *o);
extern void MesWinAddCharCount_274c60(void *o, s32 v);

s32 MesWinPushChar_2743c0(void *o, s32 v)
{
    Rec *e;

    if (MesWinGetCharCount_274c70(o) >= 0x300) {
        return 0;
    }
    if (v >= 0xFE00 && v < 0xFF00) {
        if (MesWinGetCharCount_274c70(o) > 0) {
            MesWinPushPause_275d60(o, MesWinGetCharCount_274c70(o) - 1, v - 0xFE00);
        }
        return 0;
    }
    e = (Rec *)((u8 *)o + MesWinGetCharCount_274c70(o) * 8 + 0xC4);
    e->m0 = v;
    e->m2 = MesWinGetPenX_272ad0(o);
    e->m4 = MesWinGetPenY_272aa0(o);
    e->m7 = *(u8 *)((u8 *)o + 0x1945);
    e->m6 = 0;
    MesWinAddCharCount_274c60(o, 1);
    return 1;
}
