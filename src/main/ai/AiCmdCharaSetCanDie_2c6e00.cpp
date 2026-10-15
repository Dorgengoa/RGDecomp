#include "types.h"

struct E8 { u8 b[8]; };
struct Obj0 { u8 pad000[0xA44]; s32 mA44; };

extern "C" s32 ScriptSlotGetInt_2cc9c0(struct E8 *);
extern "C" s32 GetActionMgr_1fdb50(void);
extern "C" void *ActionMgrFindById_233b50(s32, s32);

extern "C" s32 AiCmdCharaSetCanDie_2c6e00(struct E8 *p0, s32 p1)
{
    struct E8 *q;
    s32 r0;
    bool r1;
    struct Obj0 *r3;
    s32 t0;

    q = p0;
    if (p1 != 2) {
        return 0;
    }
    r0 = ScriptSlotGetInt_2cc9c0(q++);
    r1 = ScriptSlotGetInt_2cc9c0(q);
    if (r1) {
        r3 = (struct Obj0 *)ActionMgrFindById_233b50(GetActionMgr_1fdb50(), r0);
        t0 = r3->mA44;
        r3->mA44 = (t0 & 0xFFDFFFFF);
    } else {
        r3 = (struct Obj0 *)ActionMgrFindById_233b50(GetActionMgr_1fdb50(), r0);
        t0 = r3->mA44;
        r3->mA44 = (t0 | 0x200000);
    }
    return 1;
}
