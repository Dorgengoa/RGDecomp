#include "types.h"

struct S8 { s32 a; s32 b; };

extern s32 ScriptGetInt_2490f0(struct S8 *);
extern s32 MenuWinGet_2653e0(s32);
extern void MenuWinSetBlink_26c1a0(s32, s32, s32);

s32 EvCmdMenuWinSetBlink_242ff0(struct S8 *p0, s32 p1)
{
    s32 r0;
    s32 r1;
    s32 r2;
    s32 r3;

    r0 = ScriptGetInt_2490f0(p0++);
    r1 = MenuWinGet_2653e0(r0);
    if (r1 == 0) {
        return 0;
    }
    r2 = ScriptGetInt_2490f0(p0++);
    if (p1 == 3) {
        r3 = ScriptGetInt_2490f0(p0);
        MenuWinSetBlink_26c1a0(r1, r2, r3);
    } else {
        MenuWinSetBlink_26c1a0(r1, r2, 0x1E);
    }
    return 1;
}
