#include "types.h"

/* Same guard shape as CharaCmdFadeIn_22bb10 but on argc 3/4.
   `dsll32/dsra32 ..,16` on the -1 / call result is an explicit (s16) cast. */

extern s32 ScriptArgGetInt_302d70(s32);
extern s32 ScriptArgGetStr_302cb0(s32);
extern s32 GetEffectMgr_2d9040(void);
extern void EffectCreateByName_2e1020(void *, s32, s32, s16);
extern void EffectSetId_2e0100(s32, void *, s32);
extern s32 GetObjNodeByName_1ce3a0(s32, s32, s32);
extern void EffectAttachToNode_2e0790(s32, void *, s32);

struct Obj0 {
    s32 m00;
};

struct Buf20 {
    u8 b[0x20];
};

s32 CharaCmdEffRef_22bc20(struct Obj0 *p0, s32 p1, s32 argc)
{
    struct Buf20 sp50;
    s32 a;
    s32 m;
    s32 v;
    s32 w;
    s32 u;

    if (argc != 3 && argc != 4) {
        return 0;
    }
    a = -1;
    if (argc > 3) {
        a = ScriptArgGetInt_302d70(p1 + 0xF);
    }
    m = GetEffectMgr_2d9040();
    v = ScriptArgGetStr_302cb0(p1);
    EffectCreateByName_2e1020(&sp50, m, v, (s16)a);
    EffectSetId_2e0100(m, &sp50, p0->m00);
    w = ScriptArgGetInt_302d70(p1 + 5);
    u = ScriptArgGetStr_302cb0(p1 + 0xA);
    EffectAttachToNode_2e0790(m, &sp50, GetObjNodeByName_1ce3a0(p0->m00, w, u));
    return 1;
}
