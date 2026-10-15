#include "types.h"
struct Obj1 { u8 pad000[0x160]; s64 m160; };
struct Obj0 { u8 pad000[0x18]; struct Obj1 *m18; };
typedef struct { s32 a, b; } E8_0025ad50;
extern struct Obj0 * GetGameData_1fede0(void);
extern s32 ScriptGetInt_26a2a0(E8_0025ad50 *);
extern void ScriptSetRefInt_26a1e0(E8_0025ad50 *, s32);

s32 EvCmdMoneyCheck_25ad50(E8_0025ad50 *p0)
{
    struct Obj0 *r0;
    s64 t1;
    s32 r1;

    r0 = GetGameData_1fede0();
    t1 = r0->m18->m160;
    r1 = ScriptGetInt_26a2a0(p0++);
    if ((s64)r1 <= t1) {
        ScriptSetRefInt_26a1e0(p0, 1);
    } else {
        ScriptSetRefInt_26a1e0(p0, 0);
    }
    return 1;
}
