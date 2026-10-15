#include "types.h"
typedef struct { s32 a, b; } E8_25bac0;
struct O25bac0 { u8 pad000[0x18]; s32 m18; };
extern struct O25bac0 * GetGameData_1fede0(void);
extern s32 ScriptGetInt_26a2a0(E8_25bac0 *);
extern s32 InvCountById_3c78d0(s32, s32, s32, s32);
extern void ScriptSetRefInt_26a1e0(E8_25bac0 *, s32);

s32 EvCmdInvCountItem_25bac0(E8_25bac0 *p0, s32 p1)
{
    struct O25bac0 *o;
    s32 a;
    s32 b;
    s32 r;

    o = GetGameData_1fede0();
    a = ScriptGetInt_26a2a0(p0++);
    b = 0;
    if (p1 >= 3) {
        b = ScriptGetInt_26a2a0(p0++);
    }
    r = InvCountById_3c78d0(o->m18, a, b, 0);
    ScriptSetRefInt_26a1e0(p0, r);
    return 1;
}
