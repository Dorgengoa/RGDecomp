#include "types.h"

class VG {
public:
    u8 pad[0x190];
    VC_VPTR_MEMBER;
    
    
    
    s32 v4() { return VCM0(s32, 0x18); }
};

extern "C" {
s32 ModelGetFrame_1511f0(s32, s32);
s32 ModelFindFrameIndexByName_151220(s32, s32);
s32 *ObjFindNthAttachPoint_1addc0(s32, s32, s32);
s32 ObjRecGetLiveObject_1c4a90(s32, s32);
s32 GetCurrentScene_1f5be0(void);
s32 GetEffectMgr_2d9040(void);
void EffectCopyHandle_2dd3b0(void *, void *);
void EffectAttachToNode_2e0790(s32, void *, s32);
s32 ScriptSlotGetCodeAddr_334870(void *);
s32 ScriptSlotGetInt_3348b0(void *);
extern VG *D_004826E0;
}

extern "C" s32 ScriptCmdEffectAttachNode_32d740(u8 *arg0, s32 arg1) {
    u8 sp60[0x20] __attribute__((aligned(16)));
    s32 m;
    s32 g;
    s32 i;
    s32 o;
    s32 k;
    s32 *p;
    s32 r;

    if (arg1 != 2 && arg1 != 3) return 0;
    if (D_004826E0 == 0) return 0;
    m = GetEffectMgr_2d9040();
    g = GetCurrentScene_1f5be0();
    i = ScriptSlotGetInt_3348b0(arg0);
    if (i < 0) {
        o = D_004826E0->v4();
    } else {
        o = ObjRecGetLiveObject_1c4a90(g, i);
    }
    if (o == 0) return 1;
    if (*(s32 *)(arg0 + 8) == 2) {
        r = ModelGetFrame_1511f0(o, ModelFindFrameIndexByName_151220(o, ScriptSlotGetCodeAddr_334870(arg0 + 8)));
    } else {
        k = 0;
        if (arg1 == 3) k = ScriptSlotGetInt_3348b0(arg0 + 0x10);
        p = ObjFindNthAttachPoint_1addc0(o, ScriptSlotGetInt_3348b0(arg0 + 8), k);
        if (p == 0) return 1;
        r = ModelGetFrame_1511f0(o, *p);
    }
    if (r == 0) return 1;
    EffectCopyHandle_2dd3b0(sp60, D_004826E0);
    EffectAttachToNode_2e0790(m, sp60, r);
    return 1;
}
