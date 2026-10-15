#include "types.h"

extern void MesFontGetPakPath_2704b0(s32, void *);
extern s32 ResidentFileReadLocalizedMaybe_1c2860(void *, s32, void *);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

s32 MesFontPakRead_2703f0(s32 p0, s32 p1)
{
    s32 vAC;
    s32 v20[35];
    s32 rv2;
    s32 r1;
    s32 t0;

    if (p1 == 0) {
        rv2 = 0;
    } else {
        vAC = 0;
        MesFontGetPakPath_2704b0(p0, v20);
        r1 = ResidentFileReadLocalizedMaybe_1c2860(v20, p1, &vAC);
        t0 = vAC;
        rv2 = (t0 > 0);
    }
    return rv2;
}
