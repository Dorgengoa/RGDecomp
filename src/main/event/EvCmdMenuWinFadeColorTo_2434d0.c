#include "types.h"

typedef struct E8 { s32 a; s32 b; } E8;

extern s32 ScriptGetInt_2490f0(E8 *q);
extern f32 TaggedGetFloat_2490d0(E8 *q);
extern void *MenuWinGet_2653e0(s32 id);
extern void MenuWinFadeColorTo_26c210(void *o, f32 *m, s32 n);

s32 EvCmdMenuWinFadeColorTo_2434d0(E8 *q)
{
    f32 m[4];
    void *o;
    s32 t;

    o = MenuWinGet_2653e0(ScriptGetInt_2490f0(q++));
    if (o == 0) {
        return 0;
    }
    t = q->a;
    switch (t) {
    case 0:
        m[0] = (f32)ScriptGetInt_2490f0(q++);
        m[1] = (f32)ScriptGetInt_2490f0(q++);
        m[2] = (f32)ScriptGetInt_2490f0(q++);
        m[3] = (f32)ScriptGetInt_2490f0(q++);
        break;
    case 1:
        m[0] = TaggedGetFloat_2490d0(q++);
        m[1] = TaggedGetFloat_2490d0(q++);
        m[2] = TaggedGetFloat_2490d0(q++);
        m[3] = TaggedGetFloat_2490d0(q++);
        break;
    }
    MenuWinFadeColorTo_26c210(o, m, ScriptGetInt_2490f0(q));
    return 1;
}
