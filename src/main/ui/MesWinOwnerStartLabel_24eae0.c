#include "types.h"

extern s32 MesWinClose_2774f0(s32);
extern s32 MesWinGetTextFile_274e40(s32);
extern s32 MesWinGetTextFileSize_274e30(s32);
extern s32 TextFindAtLabelLine_2772f0(s32, s32, s32);
extern s32 MesWinSetLabelText_274e20(s32, s32);
extern s32 MesWinGetLabelText_274e10(s32);
extern s32 MesWinSetText_2727b0(s32, s32, s32, s32);
extern s32 EventVoiceStopSetWait_24e8c0(void *, s32, s32, s32);
extern s32 MesWinOwnerCalcPageWait_24e860(void *);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0xC];
    s32 m0C;
    s32 m10;
    s32 m14;
    s32 m18;
    s32 m1C;
    s32 m20;
};

s32 MesWinOwnerStartLabel_24eae0(struct Obj0 *p0, s32 p1, s32 p2)
{
    s32 t0;
    s32 r0;
    s32 t1;
    s32 r1;
    s32 t2;
    s32 r2;
    s32 rv15;
    s32 rv13;
    s32 rv14;
    s32 r3;
    s32 rv11;
    s32 rv12;
    s32 t3;
    s32 r4;
    s32 t4;
    s32 r5;
    s32 t5;
    s32 r6;
    s32 rv9;
    s32 rv10;
    s32 r7;
    s32 r8;

    t0 = p0->m0C;
    if (t0 == 0) {
        return -1;
    }
    r0 = MesWinClose_2774f0(t0);
    p0->m10 = -1;
    p0->m18 = -1;
    t1 = p0->m0C;
    r1 = MesWinGetTextFile_274e40(t1);
    t2 = p0->m0C;
    r2 = MesWinGetTextFileSize_274e30(t2);
    rv15 = p2;
    if (r1 != 0) {
        rv13 = r2;
        rv14 = p2;
        if (r2 >= 0) {
            r3 = TextFindAtLabelLine_2772f0(r1, r2, p1);
            rv11 = 0;
            rv12 = p2;
            if (r3 != 0) {
                t3 = p0->m0C;
                r4 = MesWinSetLabelText_274e20(t3, r3);
                t4 = p0->m0C;
                r5 = MesWinGetLabelText_274e10(t4);
                t5 = p0->m0C;
                r6 = MesWinSetText_2727b0(t5, r5, 0, 0);
                p0->m1C = 0;
                rv9 = r6;
                rv10 = 0;
                if (p2 != 0) {
                    r7 = EventVoiceStopSetWait_24e8c0(p0, -1, 0, 0);
                    p0->m14 = 0;
                    r8 = MesWinOwnerCalcPageWait_24e860(p0);
                    p0->m20 = 1;
                    rv9 = 1;
                    rv10 = p2;
                } else {
                    p0->m20 = 0;
                    rv9 = r6;
                    rv10 = 0;
                }
                rv11 = rv9;
                rv12 = rv10;
            }
            rv13 = rv11;
            rv14 = rv12;
        }
        rv15 = rv14;
    }
    return -1;
}
