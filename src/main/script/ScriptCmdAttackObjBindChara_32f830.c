#include "types.h"

typedef struct { s32 a; s32 b; } Arg;

typedef struct {
    u8  pad00[0x86];
    s16 f86;
    s16 f88;
    s16 f8A;
} Obj;

extern s32 IsInBattle_288420(void);
extern s32 GetObjRefTable_313de0(void);
extern s32 ScriptSlotGetInt_3348b0(void *);
extern s32 ScriptSlotGetCodeAddr_334870(void *);
extern Obj *HandleRegistryLookup_314aa0(s32, s32);
extern void ExecInfoInitFromChara_3a7830(void *, s32, s32, s32, s32);
extern void JudgeObjectSyncOwner_314440(Obj *);

s32 ScriptCmdAttackObjBindChara_32f830(u8 *p, s32 kind)
{
    Obj *o;
    s32 h;
    s32 r;
    u8 *q;
    s32 v;
    s32 w;

    if (kind != 3 && kind != 4) {
        return 0;
    }
    if (IsInBattle_288420() == 0) {
        return 1;
    }
    h = GetObjRefTable_313de0();
    o = HandleRegistryLookup_314aa0(h, ScriptSlotGetInt_3348b0(p));
    if (o == 0) {
        return 1;
    }
    if (o->f8A != 1) {
        return 1;
    }
    q = (u8 *)o + 0x10;
    r = 0;
    if (kind == 4) {
        r = ScriptSlotGetInt_3348b0(p + 0x18);
    }
    v = o->f86;
    w = ScriptSlotGetInt_3348b0(p + 0x10);
    ExecInfoInitFromChara_3a7830(q, v, w, r != 0, ScriptSlotGetCodeAddr_334870(p + 8));
    JudgeObjectSyncOwner_314440(o);
    return 1;
}
