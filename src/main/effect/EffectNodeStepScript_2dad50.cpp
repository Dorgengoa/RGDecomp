#include "types.h"

class Obj {
    u8 pad[0x190];
public:
    virtual void v08();
    virtual void v0C();
    virtual void v10();
    virtual void v14();
    virtual void v18();
    virtual u8 *v1C();
    virtual void v20();
    virtual void v24();
    virtual void v28();
    virtual s32 v2C();
    virtual void v30();
    virtual void v34();
    virtual void v38(s16);
    virtual void v3C(s32);
    virtual s16 v40();
    virtual s16 v44();
};

extern "C" {
s32 ScriptVmHasLabel_1768f0(u8 *, s32);
void ScriptVmRunEntry_176940(u8 *, s32);
void ScriptVmResume_176ab0(u8 *);
void EffectSetCurrentNode_2d9530(Obj *);
void EffectEntryReleaseNode_2da6c0(s32, Obj *);
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
                EffectEntryReleaseNode_2da6c0(arg0, o);
            }
        }
    }
}
