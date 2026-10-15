#include "types.h"
typedef struct { s32 a, b; } E8_243900;
extern s32 ScriptGetInt_2490f0(E8_243900 *);
extern s32 MenuWinGet_2653e0(s32);
extern void MenuWinSetActive_26c3f0(s32, s32);
extern void MenuWinSetDrawLayer_26c3d0(s32, s32);

s32 EvCmdMenuWinSetActive_243900(E8_243900 *p0, s32 p1)
{
    s32 r0;
    s32 r1;
    s32 r2;
    s32 r4;

    r0 = ScriptGetInt_2490f0(p0++);
    r1 = MenuWinGet_2653e0(r0);
    if (r1 == 0) {
        return 0;
    }
    r2 = ScriptGetInt_2490f0(p0++);
    MenuWinSetActive_26c3f0(r1, r2);
    if (p1 >= 3) {
        r4 = ScriptGetInt_2490f0(p0);
        MenuWinSetDrawLayer_26c3d0(r1, r4);
    }
    return 1;
}
