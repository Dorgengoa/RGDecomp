#include "types.h"
extern "C" {

class A {
public:
    u8 pad0[0x18];
    s16 unk18;
    s16 unk1A;
    s32 unk1C;
    VC_VPTR_MEMBER; void f() { VCM0(void, 0x8); }
};
class B {
public:
    u8 pad0[0x68];
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    void g() { VCM0(void, 0x84); }
};

extern void MemStackRefCountDec_14d7c0(s32 arg0);
extern void MemStackReset_14d830(s32 arg0);
extern void NameTableFreeGroup_158ac0(s32 arg0, s32 arg1);
extern void DrawCtxVif1HandlerStop_15dc40(void);
extern s32 GetDrawCtxNameTable_15de40(void);
extern A *ObjRecTableGet_1c3fa0(void *arg0, s32 arg1);
extern B *ObjRecGetLiveObject_1c5250(void *arg0, s32 arg1);

s32 ObjRecRelease_1ce9c0(void *arg0, s32 arg1, s32 arg2)
{
    s32 ctx;
    A *a;
    B *b;
    A *c;
    s32 n;
    s32 base;
    s32 i;
    s32 h;
    s32 j;

    ctx = GetDrawCtxNameTable_15de40();
    a = ObjRecTableGet_1c3fa0(arg0, arg1);
    if (a == NULL) {
        return 0;
    }
    b = ObjRecGetLiveObject_1c5250(arg0, arg1);
    if (b == NULL) {
        return 0;
    }
    DrawCtxVif1HandlerStop_15dc40();
    h = a->unk1C;
    if (h != 0) {
        MemStackRefCountDec_14d7c0(h);
        a->unk1C = 0;
    }
    if (h != 0) {
        MemStackReset_14d830(h);
    }
    n = a->unk1A;
    base = a->unk18;
    if (base >= 0 && n > 0) {
        for (i = 0; i < n; i++) {
            NameTableFreeGroup_158ac0(ctx, base + i);
        }
    }
    a->f();
    b->g();
    if (arg2 == 0) {
        return 1;
    }
    if (h != 0) {
        for (j = 0; j < *(s32 *)((u8 *)arg0 + 0x3C58); j++) {
            c = ObjRecTableGet_1c3fa0(arg0, j);
            if (c != NULL && c->unk1C == h) {
                ObjRecRelease_1ce9c0(arg0, j, 0);
            }
        }
    }
    return 1;
}

}
