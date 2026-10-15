#include "types.h"

typedef struct E8 { s32 a; s32 b; } E8;

extern s32 ScriptSlotGetInt_2cc9c0(E8 *);
extern f32 ScriptSlotGetFloat_2cc9a0(E8 *);
extern s32 GetActionMgr_1fdb50(void);
extern s32 ActionMgrFindById_233b50(s32, s32);
extern void CharaAddReqMove_238730(s32, f32 *);

extern const s32 D_004DB928;

s32 AiCmdCharaAddReqMove_2c8350(E8 *p0, s32 p1)
{
    f32 v[3];
    s32 h;
    s32 r;
    s32 x;

    h = D_004DB928;
    if (p1 == 4) {
        h = ScriptSlotGetInt_2cc9c0(p0++);
    }
    v[0] = ScriptSlotGetFloat_2cc9a0(p0++);
    v[1] = ScriptSlotGetFloat_2cc9a0(p0++);
    v[2] = ScriptSlotGetFloat_2cc9a0(p0++);
    r = GetActionMgr_1fdb50();
    x = ActionMgrFindById_233b50(r, h);
    if (x != 0) {
        CharaAddReqMove_238730(x, v);
    }
    return 1;
}
