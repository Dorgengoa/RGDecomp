#include "types.h"

/* Spin until D_004810C4 has advanced `b` past `a`, signalling the IOP each
   time round. */

extern s32 D_004810C4;
extern s32 D_004810C0;
extern s32 D_0047DF18;
extern s32 DisableIntr_120660(void);
extern void EnableIntr_1206b0(void);
extern s32 WaitSema(s32 sema);

void WaitVsyncCount_15de90(s32 a, s32 b)
{
    s32 t;

    for (;;) {
        if (D_004810C4 - a >= b) {
            break;
        }
        t = DisableIntr_120660();
        D_004810C0 = 1;
        if (t != 0) {
            EnableIntr_1206b0();
        }
        WaitSema(D_0047DF18);
    }
}
