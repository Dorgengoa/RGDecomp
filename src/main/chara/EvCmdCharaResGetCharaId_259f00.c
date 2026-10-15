#include "types.h"

typedef struct E8 { s32 a; s32 b; } E8;

struct Obj0 {
    u8 pad000[0x2];
    s16 m02;
};

extern s32 GetCharaResMgr_1fdb60(void);
extern s32 ScriptGetInt_26a2a0(E8 *);
extern struct Obj0 *CharaResFindById_1f0530(s32, s32);
extern void ScriptSetRefInt_26a1e0(E8 *, s32);

s32 EvCmdCharaResGetCharaId_259f00(E8 *p0)
{
    s32 r0;
    s32 r1;
    struct Obj0 *r2;
    s16 t0;

    r0 = GetCharaResMgr_1fdb60();
    r1 = ScriptGetInt_26a2a0(p0++);
    r2 = CharaResFindById_1f0530(r0, r1);
    if (r2 != 0) {
        t0 = r2->m02;
        ScriptSetRefInt_26a1e0(p0, t0);
    } else {
        ScriptSetRefInt_26a1e0(p0, -1);
    }
    return 1;
}
