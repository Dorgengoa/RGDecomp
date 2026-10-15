#include "types.h"

typedef struct { s32 a, b; } E_0025a620;

extern void *GetActionMgr_1fdb50(void);
extern void *ScriptGetInt_26a2a0(E_0025a620 *);
extern void *ActionMgrFindById_233b50(void *, void *);
extern void CharaGetHoldDir_2143b0(void *, f32 *);
extern void ScriptSetRefFloat_26a1c0(E_0025a620 *, f32);

s32 EvCmdCharaGetHoldDir_25a620(E_0025a620 *p)
{
    f32 v[4];
    void *r;
    void *s;
    void *t;

    r = GetActionMgr_1fdb50();
    s = ScriptGetInt_26a2a0(p++);
    t = ActionMgrFindById_233b50(r, s);
    if (t != 0) {
        CharaGetHoldDir_2143b0(t, v);
        ScriptSetRefFloat_26a1c0(p++, v[0]);
        ScriptSetRefFloat_26a1c0(p++, v[1]);
        ScriptSetRefFloat_26a1c0(p, v[2]);
    }
    return 1;
}
