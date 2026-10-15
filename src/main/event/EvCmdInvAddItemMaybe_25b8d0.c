#include "types.h"
typedef struct { s32 a, b; } E8_25b8d0;
struct O25b8d0 { u8 pad000[0x18]; s32 m18; };
extern struct O25b8d0 * GetGameData_1fede0(void);
extern s32 ScriptGetInt_26a2a0(E8_25b8d0 *);
extern s32 InvAddItemCheckedMaybe_3c6460(s32, s32, s32, s32, s32);
extern void ScriptSetRefInt_26a1e0(E8_25b8d0 *, u8);

s32 EvCmdInvAddItemMaybe_25b8d0(E8_25b8d0 *p0, s32 p1)
{
    struct O25b8d0 *o;
    s32 a;
    s32 b;
    s32 r;

    o = GetGameData_1fede0();
    a = ScriptGetInt_26a2a0(p0++);
    b = 1;
    if (p1 >= 3) {
        b = ScriptGetInt_26a2a0(p0++);
    }
    r = InvAddItemCheckedMaybe_3c6460(o->m18, a, b, 0, 0);
    ScriptSetRefInt_26a1e0(p0, r);
    return 1;
}
