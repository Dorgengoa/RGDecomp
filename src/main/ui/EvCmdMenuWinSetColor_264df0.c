#include "vec.h"

typedef struct Cmd { s32 a, b; } Cmd;

extern s32 ScriptGetInt_26a2a0(s32);
extern f32 TaggedGetFloat_26a280(s32);
extern void *MenuWinGet_2653e0(s32);
extern void MenuWinSetColor_26c380(void *, Vec4 *);

/* all four components come from the operand stream -- no `sq zero` init and
   no 1.0f w. */
s32 EvCmdMenuWinSetColor_264df0(Cmd *p0)
{
    s32 id;
    Vec4 v;
    void *h;

    id = ScriptGetInt_26a2a0((s32)p0++);
    v.x = TaggedGetFloat_26a280((s32)p0++);
    v.y = TaggedGetFloat_26a280((s32)p0++);
    v.z = TaggedGetFloat_26a280((s32)p0++);
    v.w = TaggedGetFloat_26a280((s32)p0);
    h = MenuWinGet_2653e0(id);
    if (h == 0) {
        return 0;
    }
    MenuWinSetColor_26c380(h, &v);
    return 1;
}
