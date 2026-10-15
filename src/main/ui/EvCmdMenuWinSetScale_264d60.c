#include "types.h"

typedef struct Cmd { s32 a, b; } Cmd;

extern s32 ScriptGetInt_26a2a0(s32);
extern f32 TaggedGetFloat_26a280(s32);
extern void *MenuWinGet_2653e0(s32);
extern void MenuWinSetScale_26c2f0(void *, f32, f32);

s32 EvCmdMenuWinSetScale_264d60(Cmd *p0)
{
    s32 id;
    f32 x, y;
    void *h;

    id = ScriptGetInt_26a2a0((s32)p0++);
    x = TaggedGetFloat_26a280((s32)p0++);
    y = TaggedGetFloat_26a280((s32)p0);
    h = MenuWinGet_2653e0(id);
    if (h == 0) {
        return 0;
    }
    MenuWinSetScale_26c2f0(h, x, y);
    return 1;
}
