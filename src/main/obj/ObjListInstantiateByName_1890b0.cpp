#include "types.h"

class VC {
public:
    u8 pad[0x68];
    virtual void v08();
    virtual void v0c();
    virtual void v10();
    virtual void v14();
    virtual void v18();
    virtual void v1c();
    virtual void v20();
    virtual void v24();
    virtual void v28();
    virtual void v2c();
    virtual void v30();
    virtual void v34();
    virtual void v38();
    virtual void v3c(void *, s32);
};

struct Ent {
    u8 pad0[0xC];
    s32 unkC;
    VC *unk10;
};

struct Slot {
    u8 pad0[0x10];
    void *unk10;
};

struct OV { u8 pad[0x68]; void *vp; };

extern "C" {
extern void *MemStackNew_14e230(s32, s32);
extern void NodeSetScale_1865b0(void *, s32);
extern void NodeSetRotation_186620(void *, s32);
extern void NodeSetTranslation_1866b0(void *, s32);
extern Ent *ObjListFindByName_189500(s32, s32, s32 *);
extern Slot *ObjInstListAppendNew_18e1e0(s32, s32, s32);
extern void FuncDataTableCtor_18fbf0(void *);
extern void NodeObjCreateFuncAnimes_193900(void *, s32);
extern void NodeObjInit_1951b0(void *);
extern u8 D_00470410[];
extern u8 D_004705D0[];
}

class Th {
public:
    u8 pad0[0x68];
    void *vp;
    u8 pad6c[0x114 - 0x6C];
    u8 m114[0x148 - 0x114];
    s32 m148;
    s32 m14C;
    Th() {
        vp = D_00470410;
        vp = D_004705D0;
        FuncDataTableCtor_18fbf0(m114);
        m148 = 0;
        NodeObjInit_1951b0(this);
    }
    void *operator new(u32 sz, s32 a) { return MemStackNew_14e230(sz, a); }
};

extern "C" void *ObjListInstantiateByName_1890b0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5)
{
    s32 id;
    Th *p;
    Slot *s;
    VC *v;
    Ent *e;

    e = ObjListFindByName_189500(arg0, arg1, &id);
    if (e == 0) {
        return 0;
    }
    v = e->unk10;
    if (v == 0) {
        return 0;
    }
    s = ObjInstListAppendNew_18e1e0(arg0, id, arg5);
    if (s == 0) {
        return 0;
    }
    if (e->unkC == 0) {
        p = new (arg5) Th;
        if (p == 0) {
            return 0;
        }
        v->v3c(p, 0);
        NodeObjCreateFuncAnimes_193900(p, arg5);
        e->unkC = 1;
    } else {
        p = new (arg5) Th;
        if (p == 0) {
            return 0;
        }
        v->v3c(p, arg5);
    }
    s->unk10 = p;
    NodeSetTranslation_1866b0(p, arg2);
    NodeSetRotation_186620(p, arg3);
    NodeSetScale_1865b0(p, arg4);
    return p;
}
