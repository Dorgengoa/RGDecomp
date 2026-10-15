#include "types.h"
#pragma no_branch_likely off
typedef struct M { u8 pad[0x9C4]; s32 a; s32 b; } M;
typedef struct O { s32 x0; s8 x4; s8 x5; } O;
extern "C" void SoundStopEntry_1b8bc0(s32 arg0, s32 arg1, s32 arg2);
extern "C" void InsectCageSePlay_3844b0(O *, s32);
extern M *D_004E94A0[5];
static inline s32 isA(M *m) { return m->a != 0; }
static inline s32 isB(M *m) { return m->b != 0; }
extern "C" void MenuObjLoopSoundUpdate_3843d0(O *arg0)
{
    s32 na;
    s32 i;
    s32 nb;
    M *m;

    na = 0;
    nb = 0;
    for (i = 0; i < 5; i++) {
        m = D_004E94A0[i];
        if (m != 0) {
            if (isA(m)) {
                na++;
            }
            if (isB(m)) {
                nb++;
            }
        }
    }
    if (na != 0) {
        InsectCageSePlay_3844b0(arg0, 0);
    } else {
        arg0->x4 = 0;
        SoundStopEntry_1b8bc0(arg0->x0, 0, 0);
    }
    if (nb != 0) {
        InsectCageSePlay_3844b0(arg0, 2);
    } else {
        arg0->x5 = 0;
        SoundStopEntry_1b8bc0(arg0->x0, 2, 0);
    }
}
