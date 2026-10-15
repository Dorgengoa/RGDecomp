#include "types.h"

typedef struct S8_0025e9f0 {
    s32 a;
    s32 b;
} S8_0025e9f0;

typedef struct Obj_0025e9f0 {
    u8 pad000[0xA44];
    s32 fA44;
} Obj_0025e9f0;

extern s32 ScriptGetInt_26a2a0(S8_0025e9f0 *p);
extern void *GetActionMgr_1fdb50(void);
extern Obj_0025e9f0 *ActionMgrFindById_233b50(void *a, s32 b);

s32 EvCmdCharaSetSkipMoveMaybe_25e9f0(S8_0025e9f0 *a0)
{
    S8_0025e9f0 *p;
    s32 id;
    s32 flag;
    Obj_0025e9f0 *r;
    s32 t;

    p = a0;
    id = ScriptGetInt_26a2a0(p++);
    flag = ScriptGetInt_26a2a0(p);
    r = ActionMgrFindById_233b50(GetActionMgr_1fdb50(), id);
    if (r != 0) {
        if (flag != 0) {
            t = r->fA44 | 0x8000000;
        } else {
            t = r->fA44 & ~0x8000000;
        }
        r->fA44 = t;
    }
    return 1;
}
