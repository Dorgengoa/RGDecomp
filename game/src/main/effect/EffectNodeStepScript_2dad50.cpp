/* rgp:protos */
#line 1
#include "types.h"

class Obj {
    u8 pad[0x190];
public:
    VC_VPTR_MEMBER;
    
    
    
    
    u8 * v1C() { return VCM0(u8 *, 0x1C); }
    
    
    
    s32 v2C() { return VCM0(s32, 0x2C); }
    
    
    void v38(s16 a0) { VCM(void, (void *, s16), 0x38, a0); }
    void v3C(s32 a0) { VCM(void, (void *, s32), 0x3C, a0); }
    s16 v40() { return VCM0(s16, 0x40); }
    s16 v44() { return VCM0(s16, 0x44); }
};

extern "C" {
s32 ScriptVmHasLabel_1768f0(u8 *, s32);
void ScriptVmRunEntry_176940(u8 *, s32);
void ScriptVmResume_176ab0(u8 *);
void EffectSetCurrentNode_2d9530(Obj *);
void EffectEntryReleaseNode_2da6c0(s32, Obj *, int, int);
}

extern "C" void EffectNodeStepScript_2dad50(s32 arg0, Obj *o)
{
    s32 id;
    u8 *p;

    EffectSetCurrentNode_2d9530(o);
    id = o->v44();
    if (o->v2C() == 0) {
        return;
    }
    p = o->v1C();
    if (p == NULL) {
        return;
    }
    if (id != -1) {
        if (ScriptVmHasLabel_1768f0(p, id) != 0) {
            ScriptVmRunEntry_176940(p, id);
            o->v38(id);
            o->v3C(-1);
        }
    } else {
        ScriptVmResume_176ab0(p);
        if (*(s32 *)(p + 0x3C) != 0) {
            o->v3C(200);
            if (o->v40() == 200) {
                EffectEntryReleaseNode_2da6c0(arg0, o, 0, 0);
            }
        }
    }
}
