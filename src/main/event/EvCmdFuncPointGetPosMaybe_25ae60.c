#include "types.h"

typedef struct { s32 a, b; } T_0025ae60;
typedef struct { u8 pad[0x20]; f32 f20, f24, f28; } S_0025ae60;

extern s32 FuncPointGetActiveId_201a00(T_0025ae60 *);
extern void *GetGameData_1fede0(void);
extern S_0025ae60 *GroupGetRecordById_425590(void *, s32);
extern void ScriptSetRefFloat_26a1c0(T_0025ae60 *, f32);

s32 EvCmdFuncPointGetPosMaybe_25ae60(T_0025ae60 *q)
{
    s32 id;
    void *g;
    void *x;
    S_0025ae60 *r;

    id = FuncPointGetActiveId_201a00(q);
    g = GetGameData_1fede0();
    x = *(void **)((s32)g + 8);
    r = GroupGetRecordById_425590(*(void **)((s32)x + 0x74), (s16)id);
    if (r != 0) {
        ScriptSetRefFloat_26a1c0(q++, r->f20);
        ScriptSetRefFloat_26a1c0(q++, r->f24);
        ScriptSetRefFloat_26a1c0(q, r->f28);
    }
    return 1;
}
