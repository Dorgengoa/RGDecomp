#include "types.h"

extern s32 GetActionMgr_1fdb50(void);
extern s32 ActionMgrFindById_233b50(s32, s32);
extern void CharaGetPos_2388a0(s32, void *);
extern void CharaGetHomePos_214350(s32, void *);
extern void VecSub_1cbd00(void *, void *, void *);
extern s32 CharaGetMoveReq_2149e0(s32);
extern s32 ScriptArgGetInt_302d70(s32);
extern void CharaMoveReqSet_219310(s32, void *, s32, s32);

struct Obj0 {
    s32 m00;
};

struct Buf10 {
    u8 b[0x10];
};

s32 CharaCmdReturnToHomePos_22d5d0(struct Obj0 *p0, s32 p1, s32 argc)
{
    struct Buf10 sp50;
    struct Buf10 sp40;
    struct Buf10 sp30;
    s32 r0;
    s32 o;
    s32 q;
    s32 r;

    if (argc != 1) {
        return 0;
    }
    r0 = GetActionMgr_1fdb50();
    o = ActionMgrFindById_233b50(r0, p0->m00);
    if (o == 0) {
        return 1;
    }
    CharaGetPos_2388a0(o, &sp50);
    CharaGetHomePos_214350(o, &sp40);
    VecSub_1cbd00(&sp30, &sp40, &sp50);
    q = CharaGetMoveReq_2149e0(o);
    r = ScriptArgGetInt_302d70(p1);
    CharaMoveReqSet_219310(q, &sp30, r, 2);
    return 1;
}
