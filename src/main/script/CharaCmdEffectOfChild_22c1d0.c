#include "types.h"

extern s32 GetActionMgr_1fdb50(void);
extern s32 ActionMgrFindById_233b50(s32, s32);
extern s32 ScriptArgGetInt_302d70(s32);
extern s32 CharaGetActAbortCodeMaybe_2149b0(s32);
extern s32 CharaGetActionTable_214cd0(s32);
extern s32 ScriptArgGetStr_302cb0(s32);
extern void CharaPlayEffectByName_21f800(s32, s32, s32);

struct Obj0;

struct Obj0 {
    s32 m00;
};

s32 CharaCmdEffectOfChild_22c1d0(struct Obj0 *p0, s32 p1, s32 p2)
{
    s32 r0;
    s32 t0;
    s32 r1;
    s32 ok;
    s32 r2;
    s32 r4;
    s32 r6;
    s32 r7;
    s32 r8;

    if (p2 == 2) goto go;
    if (p2 == 3) goto go;
    return 0;
go:
    r0 = GetActionMgr_1fdb50();
    t0 = p0->m00;
    r1 = ActionMgrFindById_233b50(r0, t0);
    if (r1 == 0) {
        return 1;
    }
    ok = 0;
    if (2 < p2) {
        r2 = ScriptArgGetInt_302d70((p1 + 0xA));
        ok = (r2 != 0);
    }
    if (ok != 0) {
        r4 = CharaGetActAbortCodeMaybe_2149b0(r1);
        if (r4 != 0) {
            return 1;
        }
    }
    r6 = CharaGetActionTable_214cd0(r1);
    if (r6 == 0) {
        return 1;
    }
    r7 = ScriptArgGetInt_302d70((p1 + 5));
    r8 = ScriptArgGetStr_302cb0(p1);
    CharaPlayEffectByName_21f800(r6, r7, r8);
    return 1;
}
