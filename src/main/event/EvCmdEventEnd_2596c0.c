#include "types.h"

extern s32 ScriptArgInitInt_26a1b0(void *, s32);
extern s32 EvCmdEventPlayerEnd_260f30(void *, s32);
extern s32 EvCmdMesWinLoadFile_265c00(void *, s32);
extern s32 EvCmdEventStackPop_25d140(void *, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

s32 EvCmdEventEnd_2596c0(s32 p0, s32 p1)
{
    s64 v28;
    s64 v20;
    s64 v18;
    s64 v10;
    s32 rv9;
    s32 r0;
    s32 r1;
    s32 rv8;
    s32 r2;
    s32 r3;
    s32 r4;
    s32 rv7;
    s32 r5;
    s32 r6;

    if (p1 != 0) {
        rv9 = 0;
    } else {
        r0 = ScriptArgInitInt_26a1b0(&v28, -1);
        r1 = EvCmdEventPlayerEnd_260f30(&v28, 1);
        if (r1 == 0) {
            rv8 = 0;
        } else {
            r2 = ScriptArgInitInt_26a1b0(&v10, 6);
            r3 = ScriptArgInitInt_26a1b0(&v18, -1);
            r4 = EvCmdMesWinLoadFile_265c00(&v10, 2);
            if (r4 == 0) {
                rv7 = 0;
            } else {
                r5 = ScriptArgInitInt_26a1b0(&v20, 4);
                r6 = EvCmdEventStackPop_25d140(&v20, 1);
                rv7 = (r6 != 0);
            }
            rv8 = rv7;
        }
        rv9 = rv8;
    }
    return rv9;
}
