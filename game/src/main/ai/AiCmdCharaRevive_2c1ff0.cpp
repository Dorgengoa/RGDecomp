/* rgp:protos */
#line 1
#pragma divbyzerocheck on
#include "types.h"
extern "C" {

extern void ObjRecClearFlags_1c3dc0(s32, s32, s32, s32);
extern s32 GetActionMgr_1fdb50(void);
extern s32 GetGameData_1fede0(void);
extern void CharaAddFlags_212460(void *, s64);
extern u8 *ActionMgrFindById_233b50(s32, s32);
extern s32 ScriptSlotGetInt_2cc9c0(void *);
extern s32 D_004DB920[4];
extern s32 D_004DB928[4];

class VC_0 {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    void f(s32 x0, f32 x1) { VCM(void, (void *, s32, f32), 0x2BC, x0, x1); }
};
extern VC_0 *ActorFindById_3eb870(s32, s32);

s32 AiCmdCharaRevive_2c1ff0(void *rgp_a0)
{
    s32 id;
    VC_0 *v;
    u8 *p;
    s32 t;

    id = ScriptSlotGetInt_2cc9c0((void *)rgp_a0);
    if (id < 0) {
        id = D_004DB928[0];
    }
    v = ActorFindById_3eb870(GetGameData_1fede0(), id);
    if (v != 0) {
        v->f(0, 100.0f);
    }
    p = ActionMgrFindById_233b50(GetActionMgr_1fdb50(), id);
    if (p != 0) {
        t = *(s32 *)(p + 0xA44) | 0x01000000;
        *(s32 *)(p + 0xA44) = t;
        *(s32 *)(p + 0xA44) = t & 0xFF7FFFFF;
        CharaAddFlags_212460(p, (s64)0x1000 << 32);
    }
    ObjRecClearFlags_1c3dc0(D_004DB920[0], 1, id, 0x10);
    ObjRecClearFlags_1c3dc0(D_004DB920[0], 1, id, 8);
    ObjRecClearFlags_1c3dc0(D_004DB920[0], 1, id, 0x20000);
    return 1;
}

}
