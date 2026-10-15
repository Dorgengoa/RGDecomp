#include "types.h"

extern s32 GetGameMode_1f59c0(void);
extern void ScriptSetRefInt_26a1e0(void *o, s32 value);
extern s32 func_5219B0(void);

s32 EvCmdMenuThinkIsSelecting_25fb20(void *arg0)
{
    s32 t;

    t = GetGameMode_1f59c0() != 3;
    if (t) {
        t = func_5219B0() != 0;
    }
    ScriptSetRefInt_26a1e0(arg0, t & 0xFF);
    return 1;
}
