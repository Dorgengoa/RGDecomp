#include "types.h"

extern void *GetGameData_1fede0(void);
extern void ScriptSlotStoreFloatRef_2cc8e0(void *, f32);

s32 AiCmdGetBattleRadius_2c2c30(void *q)
{
    void *r;
    void *a;
    void *b;
    void *t;
    f32 v;

    r = GetGameData_1fede0();
    a = *(void **)((s32)r + 0x20);
    v = 600.0f;
    t = *(void **)((s32)a + 0x238);
    if (t != 0) {
        b = *(void **)((s32)t + 0x18);
    } else {
        b = 0;
    }
    if (b != 0) {
        v = *(f32 *)((s32)b + 0x20);
        if (v <= 0.0f) {
            v = -1.0f;
        }
    }
    ScriptSlotStoreFloatRef_2cc8e0(q, v);
    return 1;
}
