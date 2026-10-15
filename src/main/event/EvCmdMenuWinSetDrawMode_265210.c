#include "types.h"

typedef struct Cmd { s32 a, b; } Cmd;

extern s32 ScriptGetInt_26a2a0(s32);
extern void *MenuWinGet_2653e0(s32);
extern void MenuWinSetDrawMode_26c3e0(void *, s32);

s32 EvCmdMenuWinSetDrawMode_265210(Cmd *p0)
{
    s32 id, v;
    void *h;

    id = ScriptGetInt_26a2a0((s32)p0++);
    v = ScriptGetInt_26a2a0((s32)p0);
    h = MenuWinGet_2653e0(id);
    if (h == 0) {
        return 0;
    }
    MenuWinSetDrawMode_26c3e0(h, v);
    return 1;
}
