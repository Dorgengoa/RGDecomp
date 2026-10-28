#include "types.h"
#pragma opt_propagation off

class Obj {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 f4C0() { return VCM0(s32, 0x4C0); }
    
    
    s32 f4CC() { return VCM0(s32, 0x4CC); }
    s32 f4D0() { return VCM0(s32, 0x4D0); }
};

struct ObjData {
    void *vt;
    u8 pad4[0x8];
    s32 unkC;
};

typedef struct {
    u8 pad0[0x14];
    s32 unk14;
    u8 pad18[0x20 - 0x18];
    s32 unk20;
} Obj001fede0;

extern "C" {
Obj001fede0 *GetGameData_1fede0(void);
void ScriptSlotStoreIntRef_3347f0(s32, s32);
s32 ScriptSlotGetInt_3348b0(s32);
void CharaSysEventLogRecordOpenHud_3a3260(s32, s32, s32, s32, s32);
Obj *CharaMgrPoolFindById_3a8c60(s32, s32);
}

extern "C" s32 ScriptCmdCharaGaugeNotFull_32cc70(s32 arg0, s32 arg1)
{
    Obj001fede0 *g;
    Obj *o;
    bool ok;

    if (arg1 < 2) {
        return 1;
    }
    g = GetGameData_1fede0();
    o = CharaMgrPoolFindById_3a8c60(g->unk14, ScriptSlotGetInt_3348b0(arg0));
    ok = 0;
    if (o != NULL) {
        ok = o->f4C0() != 0 && o->f4CC() < o->f4D0();
    }
    ScriptSlotStoreIntRef_3347f0(arg0 + 8, ok);
    if (!ok) {
        s32 c = ((ObjData *)o)->unkC;
        CharaSysEventLogRecordOpenHud_3a3260(g->unk20, 0x7FF9, c, 0x82, 1);
    }
    return 1;
}
