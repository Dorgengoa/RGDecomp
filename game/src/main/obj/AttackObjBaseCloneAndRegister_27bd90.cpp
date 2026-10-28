#include "types.h"

struct F4 { f32 a; f32 b; f32 c; f32 d; };
struct S27 { u8 pad0[0x180]; F4 v; f32 unk190; };
struct W4 { f32 w[4]; };

struct Obj27;

class VE27 {
public:
    u8 pad000[0xB0];
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    void v25(s32 a0) { VCM(void, (void *, s32), 0x6C, a0); }
};

struct Obj27 { VE27 *unk0; s32 unk4; };
union HPun27 { Obj27 **p; s32 i; };

extern "C" void JudgeObjectAssign_219710(void *, void *);
extern "C" void HandleHeapPoolAlloc_312880(Obj27 **, s32, s32);
extern "C" s32 GetObjRefTable_313de0(void);
extern "C" s32 GetJudgeObjectHeap_313df0(void);
extern "C" s32 HandleRegistryRegister_3147e0(s32, Obj27 **);
extern "C" void *AttackObjBaseCopyCtor_3181f0(void *);

extern "C" s32 AttackObjBaseCloneAndRegister_27bd90(S27 *arg0) {
    Obj27 *volatile sp3C;
    Obj27 *volatile sp38;
    Obj27 *sp34;
    S27 *dst;
    Obj27 *temp_2;
    void *var_4;
    s32 temp_16;
    s32 rc;
    VE27 *q;
    Obj27 *p;
    Obj27 *p2;

    HandleHeapPoolAlloc_312880(&sp34, GetJudgeObjectHeap_313df0(), 0x1A0);
    { HPun27 hu; hu.i = (s32)&sp34; temp_2 = *hu.p; }
    sp3C = temp_2;
    if (temp_2 != NULL) {
        var_4 = (void *)temp_2->unk0;
    } else {
        var_4 = NULL;
    }
    if (var_4 != NULL) {
        var_4 = AttackObjBaseCopyCtor_3181f0(var_4);
    }
    if (var_4 == NULL) {
        return 0;
    }
    JudgeObjectAssign_219710(var_4, arg0);
    dst = (S27 *)var_4;
    *(W4 *)&dst->v = *(W4 *)&arg0->v;
    dst->unk190 = arg0->unk190;
    sp38 = sp3C;
    temp_16 = HandleRegistryRegister_3147e0(GetObjRefTable_313de0(), (Obj27 **)&sp38);
    p = sp38;
    if (((p != NULL) ^ 1) != 0) {
        goto done;
    }
    if (p != NULL) {
        p->unk4 = p->unk4 - 1;
    }
    p2 = sp38;
    rc = (p2 != NULL) ? p2->unk4 : 0;
    if ((rc == 0) && (p2 != NULL)) {
        q = p2->unk0;
        if (q != NULL) {
            q->v25(-1);
        }
        sp38->unk4 = 0;
        sp38 = (Obj27 *)NULL;
    }
    sp38 = (Obj27 *)NULL;
done:
    return temp_16;
}
